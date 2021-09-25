#include <iostream>
#include "OrderBook.hpp"

int main(int argc, char *argv[])
{
    OrderBook orderBook;
    
    orderBook.update(false, 4.37, 13);
    orderBook.update(true, 9.71, 42);
    orderBook.update(true, 10.24, 5);
    orderBook.update(true, 12.1, 8);
    orderBook.update(false, 4.007, 64);
    orderBook.update(false, 8.56, 9);

    std::cout << orderBook << std::endl;
    
    return 0;
    
}