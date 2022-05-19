/*
** EPITECH PROJECT, 2022
** plazza
** File description:
** Reception
*/

#include <cmath>

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

void Reception::createKitchen(uint32_t kitchenId)
{
    CFifo cfifo(kitchenId);
    std::cout << "create child" << std::endl;
    cfork.CCreateChild();
    cfifo.CMakeFifo();

    if (cfork.getPid() == 0) {
        cfifo.COpenFifoRead();
        std::cout << "Child recieved: " << cfifo.CReadFifo() << std::endl;
        cfifo.CCloseIn();
        cfifo.COpenFifoWrite();
        cfifo.CWriteFifo("Child sent this\n");
        cfifo.CCloseOut();
    } else {
        cfifo.COpenFifoWrite();
        cfifo.CWriteFifo("Parent sent this\n");
        cfifo.CCloseOut();
        cfifo.COpenFifoRead();
        std::cout << "Parent recieved this: "<< cfifo.CReadFifo() << std::endl;
        cfifo.CCloseIn();
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

void Reception::loop()
{
    std::string buff = "";
    uint32_t orderId = 0;

    while (1) {
        std::cout << "Waiter : What would you like to order ?" << std::endl;
        std::cin >> buff;
        if (!buff.compare("No"))
            break;
        createOrder(orderId);
        dropOrder();
        if (1) {
            sendOrder();
            orderId++;
        }
    }
}

Reception::~Reception()
{
}
