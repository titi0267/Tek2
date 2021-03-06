/*
** EPITECH PROJECT, 2022
** plazza
** File description:
** Reception
*/

#include <cmath>
#include <regex>

#include "Reception.hpp"
#include "../Kitchen/Kitchen.hpp"
#include "../Error/Error.hpp"

Reception::Reception(int ac, char **av)
{
    if (ac != 4)
        throw (Error("Not Enough Arguments"));
    for (int i = 1; av[i]; i++) {
        if (!_tools.is_number(av[i]))
            throw (Error("Argument is not a number"));
    }
    _cookingTime = std::atoi(av[1]);
    _cooksPerKitchen = std::atoi(av[2]);
    _timeToReplace = std::atoi(av[3]);
    for (int i = 0; i <= 1; i++)
        _recptionThread.push_back(CThreads());
}

void Reception::createOrder(uint32_t orderId)
{
    static u_int32_t id = 0;
    Order order(orderId);

    for (int i = 0; i < 12; i++) {
        _pizzaQueue.push_back(std::make_unique<Margarita>(id, IPizza::PizzaSize::L));
        order.pushPizza(id);
        id++;
    }
    _orderList.push_back(order);
}

void Reception::dropPizzaId(uint32_t pizzaId)
{
    auto itr = _orderList.begin();

    if (pizzaId == -1)
        return;
    for (; itr != _orderList.end(); itr++) {
        _pizzasId = itr->getId();
        _pizzasId.remove(pizzaId);
        itr->setId(_pizzasId);
    }
    std::cout << "Finished pizza " << pizzaId << std::endl;
}

void Reception::setOrderId(uint32_t orderId)
{
    _orderId = orderId;
}

void Reception::createKitchen()
{
    static int kitchenId = 0;
    SendPizza_t pizzaInfo;
    int totalKitchen = 0;

    for (int i = 0;  i <= ceil(_pizzaQueue.size() / (_cooksPerKitchen * 2)); i++)
        _forkList.push_back(std::make_unique<CFork>(_forkList.size() + 1, _cooksPerKitchen, _cookingTime));
    for (int i = 0; i < _forkList.size(); i++) {
        for (int d = _pizzaQueue.size(); totalKitchen < (_cooksPerKitchen * 2) && d != 0; d--) {
            pizzaInfo = {_pizzaQueue[0]->getPizzaId(), (uint32_t)_pizzaQueue[0]->getPizzaSize(), _pizzaQueue[0]->getIngredients()[0], _pizzaQueue[0]->getIngredients()[1], _pizzaQueue[0]->getIngredients()[2], _pizzaQueue[0]->getIngredients()[3],_pizzaQueue[0]->getIngredients()[4], _pizzaQueue[0]->getIngredients()[5], _pizzaQueue[0]->getIngredients()[6], _pizzaQueue[0]->getIngredients()[7], _pizzaQueue[0]->getIngredients()[8], 0};
            _forkList[i]->parentWrite.CWriteFifo(&pizzaInfo);
            _pizzaQueue.pop_front();
            totalKitchen++;
        }
        totalKitchen = 0;
    }
}

void Reception::dropOrder()
{
    auto itr = _orderList.begin();
    int IdToRemove = -1;

    for (; itr != _orderList.end(); itr++) {
        _pizzasId = itr->getId();
        if (_pizzasId.size() == 0) {
            _orderList.remove(*itr);
            std::cout << "Waiter : Order " << itr->getOrderId() << " is ready !" << std::endl;
            break;
        }
    }
}

void Reception::createPizza(std::string pizza, std::string size, std::string number, Order &order)
{
    static u_int32_t id = 1;
    IPizza::PizzaSize pizzaSize = _tools.getSizeFromStr(size);
    IPizza::PizzaType type = _tools.getTypeFromStr(pizza);
    int nbr = std::atoi(number.c_str());

    switch (type) {
        case IPizza::PizzaType::Margarita :
            for (int i = 0; i < nbr; i++, id++) {
                _pizzaQueue.push_back(std::make_unique<Margarita>(id, pizzaSize));
                order.pushPizza(id);
            }
            break;
        case IPizza::PizzaType::Regina :
            for (int i = 0; i < nbr; i++, id++) {
                _pizzaQueue.push_back(std::make_unique<Regina>(id, pizzaSize));
                order.pushPizza(id);
            }
            break;
        case IPizza::PizzaType::Fantasia :
            for (int i = 0; i < nbr; i++, id++) {
                _pizzaQueue.push_back(std::make_unique<Fantasia>(id, pizzaSize));
                order.pushPizza(id);
            }
            break;
        default:
            for (int i = 0; i < nbr; i++, id++) {
                _pizzaQueue.push_back(std::make_unique<Americana>(id, pizzaSize));
                order.pushPizza(id);
            }
            break;
    }
}

bool Reception::checkOrder(std::string buff, uint32_t orderId)
{
    std::regex all_regex("((margarita|regina|americana|fantasia) (S|M|L|XL|XXL) x([1-9][0-9]*))(; (margarita|regina|americana|fantasia) (S|M|L|XL|XXL) x([1-9][0-9]*))*");
    std::regex my_regex("((margarita|regina|americana|fantasia) (S|M|L|XL|XXL) x([1-9][0-9]*))");
    std::sregex_iterator end;
    std::sregex_iterator iter(buff.begin(), buff.end(), my_regex);

    if (!std::regex_match(buff, all_regex)) {
        std::cout << "ERROR, order syntaxe isn't correct!" << std::endl;
        return (false);
    }
    Order order(orderId);
    while (iter != end) {
        createPizza((*iter)[2], (*iter)[3], (*iter)[4], order);
        ++iter;
    }
    _orderList.push_back(order);
    return (true);
}

void *InputThread(void *ptr)
{
    std::string buff = "";
    bool checkOrderRet;
    uint32_t orderId = 0;
    SendPizza_t pizzaInfo;

    Reception *reception = (Reception *)ptr;
    while (1) {
        std::cout << "Waiter : What would you like to order ?" << std::endl;
        if (!std::getline(std::cin, buff))
            break;
        if (buff.compare("status") == 0) {
            for (int i = 0; i < reception->getForkList().size(); i++) {
                pizzaInfo = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1};
                reception->getForkList()[i]->parentWrite.CWriteFifo(&pizzaInfo);
            }
            continue;
        }
        checkOrderRet = reception->checkOrder(buff, orderId);
        if (checkOrderRet) {
            orderId++;
            reception->createKitchen();
        }
    }
    return (NULL);
}

std::deque<std::unique_ptr<CFork>> &Reception::getForkList()
{
    return (_forkList);
}

void *CommThread(void *ptr)
{
    Reception *reception = (Reception *)ptr;
    uint32_t pizzaId = 0;

    while (1) {
        for (int i = 0; i < reception->getForkList().size(); i++) {
            if (reception->getForkList().size() > 0 && reception->getForkList()[i]->childWrite.test_poll()) {
            pizzaId = reception->getForkList()[i]->childWrite.CReadFifo();
            if (pizzaId != 0) {
                    reception->dropPizzaId(pizzaId);
                }
            }
            reception->dropOrder();
        }
    }
    return (NULL);
}

void Reception::loop()
{
    _recptionThread[0].createThread(InputThread, (void *)this);
    _recptionThread[1].createThread(CommThread, (void *)this);
    _recptionThread[0].joinThreads();
    _recptionThread[1].joinThreads();
}

Reception::~Reception()
{
}
