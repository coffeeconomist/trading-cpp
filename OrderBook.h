#pragma once
#include "OrderBookEntry.h"
#include "CSVReader.h"
#include <string>
#include <vector>

class OrderBook
{
  public:
  /** construct, reading a csv data file  */
    OrderBook(std::string filename);
  /** return vector of al know products in the dataset */
    std::vector<std::string> getKnownProducts();
  /** return vector of Orders acording to ther sent filters */
    std::vector<OrderBookEntry> getOrders(OrderBookType type,
                                          std::string product,
                                          std::string timestamp);
    /* returns the earliest time in the order book */
    std::string getEarliestTime();
    /* returns the next time after the 
      sent time in the orderbook
      If there is no next timestamp, wraps around to the start */
    std::string getNextTime(std::string timestamp);

    void insertOrder(OrderBookEntry& order);

    std::vector<OrderBookEntry> matchAsksToBids(std::string product, std::string timestamp);


    static double getHighPrice(std::vector<OrderBookEntry>& orders);
    static double getLowPrice(std::vector<OrderBookEntry>& orders);
  // returns the mid price of a product
    static double getMidPrice(std::vector<OrderBookEntry>& bidOrders,
                            	std::vector<OrderBookEntry>& askOrders );
  // returns the spread between the ask price and the best bid
    static double getBidAskSpread(std::vector<OrderBookEntry>& bidOrders,
                                  std::vector<OrderBookEntry>& askOrders );
    



  private:
    std::vector<OrderBookEntry> orders;
};