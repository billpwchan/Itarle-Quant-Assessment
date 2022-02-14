#include <iostream>
#include <vector>
#include <numeric>
#include <execution>
#include <tuple>
#include <map>
#include "trade.h"
//#include "include/csv.hpp"


float average(std::vector<float> const &v) {
    if (v.empty()) {
        return 0;
    }
    auto const count = static_cast<float>(v.size());
    return std::reduce(v.begin(), v.end()) / count;
}

float median(std::vector<float> &v) {
    size_t n = v.size() / 2;
    nth_element(v.begin(), v.begin() + n, v.end());
    return v[n];
}

int main() {
    csv::CSVReader reader("../data/scandi.csv");
    std::vector<trade> tradeList;
    std::vector<trade> tickList;
    std::map<std::string, std::vector<int>> timeList;
    std::vector<int> tradeTimeList;
    std::vector<int> tickTimeList;
    std::vector<float> bidAskSpreadList;
    for (csv::CSVRow &row: reader) {
        // Only include XT / Empty Condition Code
        if (row[14].get<>() == "XT" or row[14].get<>().empty()) {
            auto *tempTrade = new trade(row);
            if (tempTrade->getUpdateType() == trade::updateTypeEnum::TRADE) {
                tradeList.push_back(*tempTrade);
                tradeTimeList.push_back(tempTrade->getTimePastMidnight());
                bidAskSpreadList.push_back(tempTrade->getAskPrice() - tempTrade->getBidPrice());
            } else if (tempTrade->getUpdateType() == trade::updateTypeEnum::CHANGEBID or
                       tempTrade->getUpdateType() == trade::updateTypeEnum::CHANGEASK) {
                tickList.push_back(*tempTrade);
                tickTimeList.push_back(tempTrade->getTimePastMidnight());
            }
            timeList[tempTrade->getDate()].push_back(tempTrade->getTimePastMidnight());
//            timeList.emplace_back(tempTrade->getUpdateType(), tempTrade->getTimePastMidnight());
        }
    }
    std::cout << "Trade. size: " << tradeList.size() << '\n';
    std::cout << "Tick. size: " << tickList.size() << '\n';

    for (auto const &element: timeList) {
        std::cout << "Key: " << element.first << '\n';
        std::cout << "Value: " << element.second.size() << '\n';
    }

    std::adjacent_difference(tradeTimeList.begin(), tradeTimeList.end(), tradeTimeList.begin());
    tradeTimeList.erase(tradeTimeList.begin());
    std::cout << "Trade Time List. size: " << tradeTimeList.size() << '\n';


    sort(bidAskSpreadList.begin(), bidAskSpreadList.end());
    std::cout << "Average bid-ask spread: " << average(bidAskSpreadList) << '\n';
    std::cout << "Median bid-ask spread: " << median(bidAskSpreadList) << '\n';

//    for (auto &trade: tradeList) {
//        std::vector<int>::iterator it;
//        it = std::unique(myvector.begin(), myvector.end());
//        myvector.resize(std::distance(myvector.begin(), it));
//    }
}