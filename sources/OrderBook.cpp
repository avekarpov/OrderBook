#include "OrderBook.hpp"

#include <iostream>
#include <iomanip>

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>

#include <fstream>

OrderBook::Order::Order(bool type, double price, unsigned int amount)  : type(type), price(price), amount(amount) {}

OrderBook::OrderBook() = default;

void OrderBook::update(bool type, double price, unsigned int amount)
{
    if(amount == 0)
    {
        if(type)
        {
            for(auto it = _asks.begin(); it != _asks.end(); ++it)
            {
                if(it->price == price)
                {
                    _asks.erase(it);
                    
                    return;
                }
            }
        }
        else
        {
            for(auto it = _bids.begin(); it != _bids.end(); ++it)
            {
                if(it->price == price)
                {
                    _bids.erase(it);
            
                    return;
                }
            }
        }
        
        return;
    }
    
    if(type)
    {
        if(_asks.empty() || _asks.back().price < price)
        {
            _asks.emplace_back(type, price, amount);
        }
        else
        {
            for(auto it = _asks.begin(); it != _asks.end(); ++it)
            {
                if(it->price > price)
                {
                    _asks.insert(it, {type, price, amount});
                }
            }
        }
    }
    else
    {
        if(_bids.empty() || _bids.back().price > price)
        {
            _bids.emplace_back(type, price, amount);
        }
        else
        {
            for(auto it = _bids.begin(); it != _bids.end(); ++it)
            {
                if(it->price < price)
                {
                    _bids.insert(it, {type, price, amount});
                }
            }
        }
    }
}

void OrderBook::update(const std::string &snapshotJson)
{
    std::fstream snapshotFile(snapshotJson);
    
    if(!snapshotFile.is_open())
    {
        throw OrderBookException("Snapshot file is not open");
    }
    
    boost::property_tree::ptree snapshot;
    boost::property_tree::read_json(snapshotFile, snapshot);
    
    _bids.clear();
    _asks.clear();
    
    for(const auto &order : snapshot.get_child("orders"))
    {
        update(order.second.get<bool>("type"), order.second.get<double>("price"), order.second.get<unsigned >("amount"));
    }
}

std::ostream &operator<<(std::ostream &os, const OrderBook &orderBook)
{
    os << "Price     |Amount    " << std::endl;
    os << "----------|----------" << std::endl;
    for(auto it = orderBook._asks.rbegin(); it != orderBook._asks.rend(); ++it)
    {
        os << std::setw(10) << it->price << '|' << std::setw(10) << it->amount << std::endl;
    }
    os << "----------|---------- Spread" << std::endl;
    for(auto it = orderBook._bids.begin(); it != orderBook._bids.end(); ++it)
    {
        os << std::setw(10) << it->price << '|' << std::setw(10) << it->amount << std::endl;
    }
    
    return os;
}

const OrderBook::Order &OrderBook::getTopBid() const
{
    if(_bids.empty())
    {
        throw OrderBookException("List of bids is empty");
    }
    
    return _bids.front();
}

bool OrderBook::getTopBid(unsigned int amount, Order &order) const
{
    if(_bids.empty())
    {
        throw OrderBookException("List of bids is empty");
    }
    
    for(auto it = _bids.begin(); it != _bids.end(); ++it)
    {
        if(it->amount >= amount)
        {
            order = *it;
            
            return true;
        }
    }
    
    return false;
}

const OrderBook::Order &OrderBook::getTopAsk() const
{
    if(_asks.empty())
    {
        throw OrderBookException("List of asks is empty");
    }
    
    return _asks.front();
}

bool OrderBook::getTopAsk(unsigned int amount, Order &order) const
{
    if(_asks.empty())
    {
        throw OrderBookException("List of asks is empty");
    }
    
    for(auto it = _asks.begin(); it != _asks.end(); ++it)
    {
        if(it->amount >= amount)
        {
            order = *it;
            
            return true;
        }
    }
    
    return false;
}

OrderBook::OrderBookException::OrderBookException(std::string message) : _message(std::move(message))
{

}

const char *OrderBook::OrderBookException::what() const
{
    return _message.c_str();
}
