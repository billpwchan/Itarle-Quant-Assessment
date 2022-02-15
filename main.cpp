#include <iostream>
#include <vector>
#include <numeric>
#include <execution>
#include <tuple>
#include <map>
#include "trade.h"
#include "include/CppConsoleTable.hpp"

using ConsoleTable = samilton::ConsoleTable;

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
            if (std::stoi(tempTrade->getUpdateType()) == trade::updateTypeEnum::TRADE) {
                tradeList.push_back(*tempTrade);
                tradeTimeMap[tempTrade->getDate()].push_back(std::stof(tempTrade->getTimePastMidnight()));
                tradePriceVolumeList.push_back(tempTrade->getTradePrice().back());
                tradePriceVolumeList.push_back(tempTrade->getTradeVolume().back());
                bidAskSpreadList.push_back(
                        abs(std::stof(tempTrade->getAskPrice()) - std::stof(tempTrade->getBidPrice())));
            } else if (std::stoi(tempTrade->getUpdateType()) == trade::updateTypeEnum::CHANGEBID or
                       std::stoi(tempTrade->getUpdateType()) == trade::updateTypeEnum::CHANGEASK) {
                tickList.push_back(*tempTrade);
                tickTimeMap[tempTrade->getDate()].push_back(std::stof(tempTrade->getTimePastMidnight()));
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

    std::cout << "Longest time between trades: "
              << *max_element(std::begin(tradeAdjTimeList), std::end(tradeAdjTimeList))
              << '\n';
    std::cout << "Longest time between tick changes: "
              << *max_element(std::begin(tickAdjTimeList), std::end(tickAdjTimeList))
              << '\n';

    std::cout << "Mean bid-ask spread: " << average(bidAskSpreadList) << '\n';
    std::cout << "Median bid-ask spread: " << median(bidAskSpreadList) << '\n';

    std::unordered_map<char, int> freq;
    for (auto &i: tradePriceVolumeList) {
        freq[i]++;
    }
    for (const auto &elem: freq) {
        std::cout << elem.first << " " << elem.second << "\n";
    }

    ConsoleTable table(1, 1, samilton::Alignment::centre);
    table.addColumn({"Question", "Answer"});
    table.addRow(std::vector<std::string>{"Mean time between trades", std::to_string(average(tradeAdjTimeList))});
    table.addRow(std::vector<std::string>{"Median time between trades", std::to_string(median(tradeAdjTimeList))});
    table.addRow(std::vector<std::string>{"Mean time between tick changes", std::to_string(average(tickAdjTimeList))});
    table.addRow(std::vector<std::string>{"Median time between tick changes", std::to_string(median(tickAdjTimeList))});
    table.addRow(std::vector<std::string>{"Longest time between trades", std::to_string(
            *max_element(std::begin(tradeAdjTimeList), std::end(tradeAdjTimeList)))});
    table.addRow(std::vector<std::string>{"Longest time between tick changes", std::to_string(
            *max_element(std::begin(tickAdjTimeList), std::end(tickAdjTimeList)))});
    table.addRow(std::vector<std::string>{"Mean bid-ask spread", std::to_string(average(bidAskSpreadList))});
    table.addRow(std::vector<std::string>{"Median bid-ask spread", std::to_string(median(bidAskSpreadList))});

    std::cout << table;

//    table.addRow({"Mean time between tick changes", std::to_string(average(tickAdjTimeList))});

}