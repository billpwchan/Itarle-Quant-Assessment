#include <iostream>
#include <utility>
#include <vector>
#include "include/rapidcsv.h"
#include "include/csv.hpp"

class trade {
public:
    trade();

    trade(float bidPrice, float askPrice, float tradePrice, long bidVolume, long askVolume, long tradeVolume,
          std::string date, int timePastMidnight, std::string conditionCode);

    trade(csv::CSVRow &row);


private:

    std::string identifier;
    float bidPrice;
    float askPrice;
    float tradePrice;
    long bidVolume;
    long askVolume;
    long tradeVolume;
    enum updateTypeEnum {
        TRADE = 1, CHANGEBID = 2, CHANGEASK = 3
    };
    int updateType;
    std::string date;
    int timePastMidnight;
    std::string conditionCode;
};


trade::trade() {}

trade::trade(float bidPrice,
             float askPrice,
             float tradePrice,
             long bidVolume,
             long askVolume,
             long tradeVolume,
             std::string date,
             int timePastMidnight,
             std::string conditionCode) : bidPrice{bidPrice}, askPrice{askPrice}, tradePrice{tradePrice},
                                          bidVolume{bidVolume}, askVolume{askVolume}, tradeVolume{tradeVolume},
                                          date{std::move(date)}, timePastMidnight{timePastMidnight},
                                          conditionCode{std::move(conditionCode)} {}

trade::trade(csv::CSVRow &row) {
    this->identifier = row[0].get<>();
    this->bidPrice = std::stof(row[2].get<>());
    this->askPrice = std::stof(row[3].get<>());
    this->tradePrice = std::stof(row[4].get<>());
    this->bidVolume = std::stol(row[5].get<>());
    this->askVolume = std::stol(row[6].get<>());
    this->tradeVolume = std::stol(row[7].get<>());
    this->updateType = std::stoi(row[8].get<>());
    this->date = row[10].get<>();
    this->timePastMidnight = std::stoi(row[11].get<>());
    this->conditionCode = row[14].get<>();
}

int main() {
    csv::CSVReader reader("../data/scandi.csv");
    std::vector<trade> tradesList;
    for (csv::CSVRow &row: reader) {
        // Only include XT / Empty Condition Code
        if (row[15].get<>() != "XT" and !row[15].get<>().empty()) { continue; }
        auto *tempTrade = new trade(row);
        tradesList.push_back(*tempTrade);
    }
    std::cout << "0. size: " << tradesList.size() << '\n';
}