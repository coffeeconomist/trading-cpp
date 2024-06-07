#include <iostream>
#include <string>
#include <vector>
#include "MerkelMain.h"
#include "OrderBookEntry.h"
#include "CSVReader.h"
#include "Wallet.h"


int main() {

/*     MerkelMain app{};
    app.init(); */


    Wallet wallet;
    wallet.insertCurrency("BTC", 10);
    wallet.insertCurrency("USDT", 10000);
    std::cout << wallet.toString() << std::endl;
    wallet.removeCurrency("USDT", 1000);
    std::cout << wallet.toString() << std::endl;

    wallet.removeCurrency("ETH", 1000);
    std::cout << wallet.toString() << std::endl;
    
    wallet.insertCurrency("ETH", 500);
    std::cout << wallet.toString() << std::endl;

    wallet.removeCurrency("ETH", 1000);
    std::cout << wallet.toString() << std::endl;

    wallet.removeCurrency("ETH", 500);
    std::cout << wallet.toString() << std::endl;
    
}

