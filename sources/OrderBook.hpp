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
        bool type; //equals to 1 bid, else ask
        double price;
        unsigned amount;
    };
    
    OrderBook();
    
    void update(bool, double price, unsigned amount);
    void update(std::string snapshotJson);
    
    const Order &getTopBid() const;
    const Order &getTopBid(unsigned amount) const;
    const Order &getTopAsk() const;
    const Order &getTopAsk(unsigned amount) const;
    
    friend std::ostream &operator<<(std::ostream &os, const OrderBook &orderBook);
    
    ~OrderBook();
    
    class OrderBookException : public std::exception
    {
    public:
        OrderBookException(const std::string &message);
        
        const char * what() const override;
        
    private:
        std::string _message;
        
    };
    
private:
    std::list<Order> _orders;
    std::list<Order>::iterator _topBid;
    
};

#endif //ORDERBOOK_HPP
