#ifndef ORDERBOOK_HPP
#define ORDERBOOK_HPP

#include <list>
#include <string>
#include <exception>

class OrderBook
{
public:
    struct Order
    {
        Order(bool type, double price, unsigned amount);
        
        bool type; //equals to 1 bid, else ask
        double price;
        unsigned amount;
    };
    
    OrderBook();
    
    void update(bool type, double price, unsigned amount);
    void update(const std::string &snapshotJson);

    [[nodiscard]] const Order &getTopBid() const;
    [[nodiscard]] bool getTopBid(unsigned amount, Order &order) const;
    [[nodiscard]] const Order &getTopAsk() const;
    [[nodiscard]] bool getTopAsk(unsigned amount, Order &order) const;

    friend std::ostream &operator<<(std::ostream &os, const OrderBook &orderBook);
    
    class OrderBookException : public std::exception
    {
    public:
        explicit OrderBookException(std::string message);
        
        [[nodiscard]] const char * what() const override;
        
    private:
        std::string _message;
        
    };
    
private:
    std::list<Order> _bids, _asks;
    
};

#endif //ORDERBOOK_HPP
