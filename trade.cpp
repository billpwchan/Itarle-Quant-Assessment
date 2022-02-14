#include "trade.h"

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

const std::string &trade::getIdentifier() const {
    return identifier;
}

void trade::setIdentifier(const std::string &identifier) {
    trade::identifier = identifier;
}

float trade::getBidPrice() const {
    return bidPrice;
}

void trade::setBidPrice(float bidPrice) {
    trade::bidPrice = bidPrice;
}

float trade::getAskPrice() const {
    return askPrice;
}

void trade::setAskPrice(float askPrice) {
    trade::askPrice = askPrice;
}

float trade::getTradePrice() const {
    return tradePrice;
}

void trade::setTradePrice(float tradePrice) {
    trade::tradePrice = tradePrice;
}

long trade::getBidVolume() const {
    return bidVolume;
}

void trade::setBidVolume(long bidVolume) {
    trade::bidVolume = bidVolume;
}

long trade::getAskVolume() const {
    return askVolume;
}

void trade::setAskVolume(long askVolume) {
    trade::askVolume = askVolume;
}

long trade::getTradeVolume() const {
    return tradeVolume;
}

void trade::setTradeVolume(long tradeVolume) {
    trade::tradeVolume = tradeVolume;
}

int trade::getUpdateType() const {
    return updateType;
}

void trade::setUpdateType(int updateType) {
    trade::updateType = updateType;
}

const std::string &trade::getDate() const {
    return date;
}

void trade::setDate(const std::string &date) {
    trade::date = date;
}

int trade::getTimePastMidnight() const {
    return timePastMidnight;
}

void trade::setTimePastMidnight(int timePastMidnight) {
    trade::timePastMidnight = timePastMidnight;
}

const std::string &trade::getConditionCode() const {
    return conditionCode;
}

void trade::setConditionCode(const std::string &conditionCode) {
    trade::conditionCode = conditionCode;
}