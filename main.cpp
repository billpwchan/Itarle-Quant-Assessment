#include <iostream>
#include <vector>
#include <numeric>
#include <execution>
#include <tuple>
#include <map>
#include "trade.h"

template<typename T>
double average(std::vector<T> const &v) {
    if (v.empty()) {
        return 0;
    }

    return std::reduce(v.begin(), v.end(), 0.0) / v.size();
}

template<typename T>
float median(std::vector<T> &v) {
    sort(v.begin(), v.end());
    size_t n = v.size() / 2;
    nth_element(v.begin(), v.begin() + n, v.end());
    return v[n];
}

int main() {
    csv::CSVReader reader("../data/scandi.csv");
    // A vector of Trade Objections that can be used for other applications.
    // Due to time complexity, we directly use the following map and vectors instead of iterating the
    // vector of trade objects again.
    std::vector<trade> tradeList;
    std::vector<trade> tickList;
    // A map with date as key and a vector of trade time as value
    std::map<std::string, std::vector<float>> tradeTimeMap;
    std::map<std::string, std::vector<float>> tickTimeMap;
    // For Round Number Effects. A Vector of Trade Prices & Volumes in Strings
    std::vector<char> tradePriceVolumeList;
    // A Vector of Bid Ask Spread
    std::vector<float> bidAskSpreadList;
    for (csv::CSVRow &row: reader) {
        // Only include XT / Empty Condition Code
        if (row[14].get<>() == "XT" or row[14].get<>().empty()) {
            auto *tempTrade = new trade(row);
            if (tempTrade->getUpdateType() == trade::updateTypeEnum::TRADE) {
                tradeList.push_back(*tempTrade);
                tradeTimeMap[tempTrade->getDate()].push_back(tempTrade->getTimePastMidnight());
                tradePriceVolumeList.push_back(std::to_string(tempTrade->getTradePrice()).back());
                tradePriceVolumeList.push_back(std::to_string(tempTrade->getTradeVolume()).back());
                bidAskSpreadList.push_back(tempTrade->getAskPrice() - tempTrade->getBidPrice());
            } else if (tempTrade->getUpdateType() == trade::updateTypeEnum::CHANGEBID or
                       tempTrade->getUpdateType() == trade::updateTypeEnum::CHANGEASK) {
                tickList.push_back(*tempTrade);
                tickTimeMap[tempTrade->getDate()].push_back(tempTrade->getTimePastMidnight());
            }
        }
    }
    std::cout << "Trade. size: " << tradeList.size() << '\n';
    std::cout << "Tick. size: " << tickList.size() << '\n';

    std::vector<float> tradeAdjTimeList;
    std::vector<float> tickAdjTimeList;

    for (auto const &element: tradeTimeMap) {
        auto timeVec = element.second;
        std::adjacent_difference(timeVec.begin(), timeVec.end(), timeVec.begin());
        timeVec.erase(timeVec.begin());
        tradeAdjTimeList.insert(tradeAdjTimeList.end(), timeVec.begin(), timeVec.end());
    }

    for (auto const &element: tickTimeMap) {
        auto timeVec = element.second;
        std::adjacent_difference(timeVec.begin(), timeVec.end(), timeVec.begin());
        timeVec.erase(timeVec.begin());
        tickAdjTimeList.insert(tickAdjTimeList.end(), timeVec.begin(), timeVec.end());
    }

    std::cout << "Trade. avg. adj. time: " << average(tradeAdjTimeList) << '\n';
    std::cout << "Tick. avg. adj. time: " << average(tickAdjTimeList) << '\n';

    std::cout << "Trade. median. adj. time: " << median(tradeAdjTimeList) << '\n';
    std::cout << "Tick. median. adj. time: " << median(tickAdjTimeList) << '\n';

    std::cout << "Trade. Longest. adj. time: " << *max_element(std::begin(tradeAdjTimeList), std::end(tradeAdjTimeList))
              << '\n';
    std::cout << "Tick. Longest. adj. time: " << *max_element(std::begin(tickAdjTimeList), std::end(tickAdjTimeList))
              << '\n';

    std::cout << "Average bid-ask spread: " << average(bidAskSpreadList) << '\n';
    std::cout << "Median bid-ask spread: " << median(bidAskSpreadList) << '\n';

    std::unordered_map<int, int> freq;
    for (auto &i: tradePriceVolumeList) {
        freq[i]++;
    }
    for (const auto &elem: freq) {
        std::cout << elem.first << " " << elem.second << "\n";
    }
}