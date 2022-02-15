#include <iostream>
#include <vector>
#include <numeric>
#include <execution>
#include <tuple>
#include <map>
#include "trade.h"
#include "include/CppConsoleTable.hpp"

#pragma execution_character_set( "utf-8" )
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

std::multimap<int, std::string, std::greater<>> invert(std::map<std::string, int> mymap) {
    std::multimap<int, std::string, std::greater<>> multiMap;

    std::map<std::string, int>::iterator it;
    for (it = mymap.begin(); it != mymap.end(); it++) {
        multiMap.insert(std::make_pair(it->second, it->first));
    }
    return multiMap;
}

int main() {
    // Setup Console Encoidng
    SetConsoleOutputCP(CP_UTF8);
    setvbuf(stdout, nullptr, _IOFBF, 1000);

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
    std::vector<std::string> tradePriceVolumeList;
    // A Vector of Bid Ask Spread
    std::vector<float> bidAskSpreadList;
    for (csv::CSVRow &row: reader) {
        // Only include XT / Empty Condition Code
        if (row[14].get<>() == "XT" or row[14].get<>().empty()) {
            auto *tempTrade = new trade(row);
            // Ensure Ask always greater or equal to Bid
            if (std::stof(tempTrade->getAskPrice()) < std::stof(tempTrade->getBidPrice())) { continue; }
            if (std::stoi(tempTrade->getUpdateType()) == trade::updateTypeEnum::TRADE) {
                tradeList.push_back(*tempTrade);
                tradeTimeMap[tempTrade->getDate()].push_back(std::stof(tempTrade->getTimePastMidnight()));
                tradePriceVolumeList.push_back(
                        tempTrade->getTradePrice().substr(tempTrade->getTradePrice().length() - 1));
                tradePriceVolumeList.push_back(
                        tempTrade->getTradeVolume().substr(tempTrade->getTradeVolume().length() - 1));
                bidAskSpreadList.push_back(
                        std::stof(tempTrade->getAskPrice()) - std::stof(tempTrade->getBidPrice()));
            } else if (std::stoi(tempTrade->getUpdateType()) == trade::updateTypeEnum::CHANGEBID or
                       std::stoi(tempTrade->getUpdateType()) == trade::updateTypeEnum::CHANGEASK) {
                tickList.push_back(*tempTrade);
                tickTimeMap[tempTrade->getDate()].push_back(std::stof(tempTrade->getTimePastMidnight()));
            }
        }
    }

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


    // General Questions
    ConsoleTable questionTable(1, 1, samilton::Alignment::left);
    questionTable.addRow(std::vector<std::string>{"Question", "Answer"});
    questionTable.addRow(
            std::vector<std::string>{"Mean time between trades", std::to_string(average(tradeAdjTimeList))});
    questionTable.addRow(
            std::vector<std::string>{"Median time between trades", std::to_string(median(tradeAdjTimeList))});
    questionTable.addRow(
            std::vector<std::string>{"Mean time between tick changes", std::to_string(average(tickAdjTimeList))});
    questionTable.addRow(
            std::vector<std::string>{"Median time between tick changes", std::to_string(median(tickAdjTimeList))});
    questionTable.addRow(std::vector<std::string>{"Longest time between trades", std::to_string(
            *max_element(std::begin(tradeAdjTimeList), std::end(tradeAdjTimeList)))});
    questionTable.addRow(std::vector<std::string>{"Longest time between tick changes", std::to_string(
            *max_element(std::begin(tickAdjTimeList), std::end(tickAdjTimeList)))});
    questionTable.addRow(std::vector<std::string>{"Mean bid-ask spread", std::to_string(average(bidAskSpreadList))});
    questionTable.addRow(std::vector<std::string>{"Median bid-ask spread", std::to_string(median(bidAskSpreadList))});
    std::cout << questionTable;

    // Round Number Effect
    std::map<std::string, int> freq;
    for (const auto &i: tradePriceVolumeList) {
        freq[i]++;
    }
    const std::size_t sumFreq = std::accumulate(std::begin(freq), std::end(freq), 0,
                                                [](const std::size_t previous, const auto &element) {
                                                    return previous + element.second;
                                                });
    auto freqDesc = invert(freq);
    ConsoleTable roundNumberTable(1, 1, samilton::Alignment::left);
    roundNumberTable.addRow(std::vector<std::string>{"Last Digit", "Percentage of Freq", "Freq"});
    for (const auto &elem: freqDesc) {
        roundNumberTable.addRow(std::vector<std::string>{elem.second,
                                                         std::to_string(100.0 * elem.first / sumFreq) + "%",
                                                         std::to_string(elem.first)});
    }
    std::cout << roundNumberTable;
}