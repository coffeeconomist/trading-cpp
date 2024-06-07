#pragma once

#include <vector>
#include "OrderBookEntry.h"
#include "OrderBook.h"
#include "Wallet.h"

class MerkelMain{
    public:
        MerkelMain();
        void init();
    private:
        void printMenu();
        int getUserOption();
        void processUserOption(int);
        void printHelp();
        void printMarketStats();
        void enterAsk();
        void enterBid();
        void printWallet();
        void gotoNextTimeFrame();
        void printPriceStats();

        std::string currentTime;

        OrderBook orderBook{"test.csv"};

        Wallet wallet;
};



