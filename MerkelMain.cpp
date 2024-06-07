#include "MerkelMain.h"
#include <string>
#include <vector>
#include <iostream>
#include "OrderBookEntry.h"
#include "CSVReader.h"
#include "Wallet.h"


MerkelMain::MerkelMain(){

}

void MerkelMain::init(){
   // loadOrderBook();
    int input;
    currentTime = orderBook.getEarliestTime();

    wallet.insertCurrency("BTC",10);



    while(true)
    {
        printMenu();
        input = getUserOption();
        processUserOption(input);
    }
}



void MerkelMain::printMenu () {
    //1 print help
    std::cout << "1: Print Help" << std::endl;
    //2 print exchange stats
    std::cout << "2: Print Exchange Stats" << std::endl;
    //3 make an offer
    std::cout << "3: Make an Offer" << std::endl;
    //4 make a bid
    std::cout << "4: Make a Bid" << std::endl;
    //5 print wallet
    std::cout << "5: Print Wallet" << std::endl;
    //6 continue
    std::cout << "6: Continue" << std::endl;
    //7 More Statistics
    std::cout << "7: Print Price Stats" << std::endl;

    std::cout << "===============" << std::endl;
    std::cout << "Current time is : " << currentTime << std::endl;
}
void MerkelMain::printHelp(){
    std::cout << "Help - your aim is to make money. Analyse the market and make bids and offers " << std::endl;
}
void MerkelMain::printMarketStats()
{

    for (std::string const p : orderBook.getKnownProducts())
    {
        std::cout << "Products : " << p << std::endl;
        std::vector<OrderBookEntry> entries = orderBook.getOrders(OrderBookType::ask , p , currentTime);
        
        std::cout << "Asks seen: " << entries.size() << std::endl;
        std::cout << "Max ask: " << OrderBook::getHighPrice(entries) << std:: endl;
        std::cout << "Min ask: " << OrderBook::getLowPrice(entries) << std:: endl;
    }
/*     unsigned int bids = 0;
    unsigned int asks = 0;
    for (OrderBookEntry& e : orders)
    {
        if (e.orderType == OrderBookType::ask) 
        {
            asks ++;
        }
        if (e.orderType == OrderBookType::bid) 
        {
            bids ++;
        }
    
    }    
    std::cout <<std::endl << "OrderBook asks: " << asks << " OrderBook asks: "<< bids<< std::endl; */
}
void MerkelMain::enterAsk() { 
    std::cout << "Make an offer - enter an amount : product,price,amount. e.g. ETH/BTC,200,0.5 " << std::endl;
    std::string input;
    std::getline(std::cin, input);

    std::vector<std::string> tokens = CSVReader::tokenise(input, ',');
    if (tokens.size() != 3) {
        std::cout << "MerkelMain::enterAsk Bad input! " << input << std::endl;
    } else {
        try {
            OrderBookEntry obe = CSVReader::stringsToOBE(
                tokens[1],
                tokens[2],
                currentTime,
                tokens[0],
                OrderBookType::ask  
            );
            obe.username = "simuser";
            if (wallet.canFulfillOrder(obe))
            {
                std::cout << "Wallet looks good." << std::endl;
                orderBook.insertOrder(obe);
            }
            else {
                std::cout << "Wallet has insuficient funds." << std::endl;
            }
        } catch (const std::exception& e) 
        {
            std::cout << "MerkelMain::enterAsk Bad input! " << std::endl;
        }
    }

    std::cout << "You typed : " << input << std::endl;
}
void MerkelMain::enterBid() 
{

    std::cout << "Make a bid - enter an amount : product,price,amount. e.g. ETH/BTC,200,0.5 " << std::endl;
    std::string input;
    std::getline(std::cin, input);

    std::vector<std::string> tokens = CSVReader::tokenise(input, ',');
    if (tokens.size() != 3) {
        std::cout << "MerkelMain::enterBid Bad input! " << input << std::endl;
    } else {
        try {
            OrderBookEntry obe = CSVReader::stringsToOBE(
                tokens[1],
                tokens[2],
                currentTime,
                tokens[0],
                OrderBookType::bid  
            );
            obe.username = "simuser";
            if (wallet.canFulfillOrder(obe))
            {
                std::cout << "Wallet looks good." << std::endl;
                orderBook.insertOrder(obe);
            }
            else {
                std::cout << "Wallet has insuficient funds." << std::endl;
            }
        } catch (const std::exception& e) 
        {
            std::cout << "MerkelMain::enterBid Bad input! " << std::endl;
        }
    }

    std::cout << "You typed : " << input << std::endl;

    

}
void MerkelMain::printWallet() {
    std::cout <<  wallet.toString() << std::endl;
}
void MerkelMain::gotoNextTimeFrame() {
    std::cout << "Going to the next time frame " << std::endl;
    std::vector<OrderBookEntry> sales =  orderBook.matchAsksToBids("ETH/BTC", currentTime);

    std::cout << "Sales: " << sales.size() << std::endl;

    for (OrderBookEntry& sale : sales) 
    {
        std::cout << "Sale price : " << sale.price << " amount " << sale.amount << std::endl;
        if (sale.username == "simuser")
        {
            wallet.processSale(sale);
        }
    }


    currentTime = orderBook.getNextTime(currentTime);
}
int MerkelMain::getUserOption(){
    int userOption=0;
    std::string line;
    std::cout << "Type in 1-6" << std::endl;
    std::getline (std::cin, line);
    try {
        userOption = std::stoi(line);
    }catch (const std::exception& e) 
    { 
        // 
    }
    std::cout << "You Chose " << userOption << std::endl;
    return userOption;
}
void MerkelMain::processUserOption(int userOption){
    if (userOption == 0){ //bad input
        std::cout << "Invalid Choice. Choose 1-6 " << std::endl;
    } else if (userOption == 1) {
        printHelp();
    }else if (userOption == 2) {
        printMarketStats();
    }else if (userOption == 3) {
        enterAsk();
    }else if (userOption == 4) {
        void enterBid();
    }else if (userOption == 5) {
        printWallet();
    }else if (userOption == 6) {
        gotoNextTimeFrame();
    }else if (userOption == 7) {
        printPriceStats();
    } else {
        std::cout << "Invalid Choice. Choose 1-6 " << std::endl;
    }
    std::cout << std::endl << "===============" << std::endl << std::endl;
}




void MerkelMain::printPriceStats()
{

    for (std::string const p : orderBook.getKnownProducts())
    {
        std::cout << "Products : " << p << std::endl;
        std::vector<OrderBookEntry> bidEntries = orderBook.getOrders(OrderBookType::bid , p , currentTime);
        std::vector<OrderBookEntry> askEntries = orderBook.getOrders(OrderBookType::ask , p , currentTime);
        
        std::cout << "Mid Price : " << OrderBook::getMidPrice(bidEntries,askEntries) << std::endl;
        std::cout << "Bid-Ask Spread : " << OrderBook::getBidAskSpread(bidEntries,askEntries) << std::endl;


    }

}