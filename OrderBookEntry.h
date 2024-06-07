#pragma once

#include <string>

enum class OrderBookType{bid, ask, unknown, asksale, bidsale};

class OrderBookEntry{
    public:
        OrderBookEntry( double _price,
                        double _amount,
                        std::string _timestamp,
                        std::string _product,
                        OrderBookType _orderType,
                        std::string username = "dataset");

        static OrderBookType stringToOderBookType(std::string s);

        static bool comparebyTimestamp(const OrderBookEntry& e1,const OrderBookEntry& e2)
        {
            return e1.timestamp < e2.timestamp;
        }
        static bool comparebyPriceAsc(const OrderBookEntry& e1,const OrderBookEntry& e2)
        {
            return e1.price < e2.price;
        }
        static bool comparebyPriceDesc(const OrderBookEntry& e1,const OrderBookEntry& e2)
        {
            return e1.price > e2.price;
        }

        double price;
        double amount;
        std::string timestamp;
        std::string product;
        OrderBookType orderType;
        std::string username;
};