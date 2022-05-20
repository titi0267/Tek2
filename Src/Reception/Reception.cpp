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

void Reception::dropPizzaId(uint32_t orderId)
{
    auto itr = _orderList.begin();

    for (; itr != _orderList.end(); itr++) {
        _pizzasId = itr->getId();
        _pizzasId.remove(orderId);
        itr->setId(_pizzasId);
    }
}

void Reception::setOrderId(uint32_t orderId)
{
    _orderId = orderId;
}

void Reception::createKitchen(uint32_t kitchenId)
{
    //_fifoList.push_back(CFifo(kitchenId));
    cfork.CCreateChild();
    _fifoList[kitchenId].CMakeFifo();

    if (cfork.getPid() == 0) {
        _runningKitchens.push_back(std::make_unique<Kitchen>(kitchenId, _cooksPerKitchen, _cookingTime));
        _runningKitchens[kitchenId]->loop();
        // enleve de la list
        // enleve le fifo de la list;
        exit(0);
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

void Reception::sendOrder()
{
    for (int i = 0; i < ceil(_pizzaQueue.size() / _cooksPerKitchen); i++)
        createKitchen(i);
}

void Reception::createPizza(std::string pizza, std::string size, std::string number, Order &order)
{
    static u_int32_t id = 0;
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

int Reception::checkOrder(std::string buff, uint32_t orderId)
{
    std::regex checkRgx("((Margarita|Regina|Americana|Fantasia) (S|M|L|XL|XXL) x([1-9][0-9]*))(; (Margarita|Regina|Americana|Fantasia) (S|M|L|XL|XXL) x([1-9][0-9]*))*");
    std::regex rgx("((Margarita|Regina|Americana|Fantasia) (S|M|L|XL|XXL) x([1-9][0-9]*))");
    std::sregex_iterator end;
    std::sregex_iterator iter(buff.begin(), buff.end(), rgx);

    if (!std::regex_match(buff, checkRgx)) {
        std::cerr << "Invalid Pizza" << std::endl;
        return (-1);
    }
    Order order(orderId);
    while (iter != end) {
        createPizza((*iter)[2], (*iter)[3], (*iter)[4], order);
        ++iter;
    }
    _orderList.push_back(order);
    return (0);
}

void Reception::loop()
{
    std::string buff = "";
    uint32_t orderId = 0;
    int checkOrderRet;

    while (1) {
        std::cout << "Waiter : What would you like to order ?" << std::endl;
        if (!std::getline(std::cin, buff))
            break;
        checkOrderRet = checkOrder(buff, orderId);
        // createOrder(orderId);
        // dropOrder();
        // if (1) {
        //     sendOrder();
        //     orderId++;
        // }
    }
}

Reception::~Reception()
{
}
