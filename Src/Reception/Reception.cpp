/*
** EPITECH PROJECT, 2022
** plazza
** File description:
** Reception
*/

#include "Reception.hpp"
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

    for (int i = 0; i < 7; i++) {
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

bool operator==(Order value, const Order o)
{
    return (value.getOrderId() == o.getOrderId());
}

void Reception::createKitchen()
{
    CFork cfork;
    std::string str;

    cfork.CMakeFifo();
    if (cfork.getPid() == 0) {
        cfork.COpenFifoWrite();
        cfork.CWriteFifo("Lol");
        //we are in child -> kitchen must be created here
        //child read ?
        //to read : get _message
    } else {
        cfork.COpenFifoRead();
        str = cfork.CReadFifo();
        cfork.CKillPid();
        //we are in parent -> shm
        //parent write ?
        //to write : (printf ?) or use of gets/getline
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

void Reception::loop()
{
    std::string buff = "";
    uint32_t orderId = 0;

    while (1) {
        std::cout << "Waiter : What would you like to order ?" << std::endl;
        std::cin >> buff;
        createKitchen();
        if (!buff.compare("No"))
            break;
        createOrder(orderId);
        dropPizzaId(0);
        dropOrder();
        orderId++;
    }
}

Reception::~Reception()
{
}
