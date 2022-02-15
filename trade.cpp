#include "trade.h"

trade::trade() {}

trade::trade(csv::CSVRow &row) {
    this->identifier = row[0].get<>();
    this->bidPrice = row[2].get<>();
    this->askPrice = row[3].get<>();
    this->tradePrice = row[4].get<>();
    this->bidVolume = row[5].get<>();
    this->askVolume = row[6].get<>();
    this->tradeVolume = row[7].get<>();
    this->updateType = row[8].get<>();
    this->date = row[10].get<>();
    this->timePastMidnight = row[11].get<>();
    this->conditionCode = row[14].get<>();
}

const std::string &trade::getIdentifier() const {
    return identifier;
}

void trade::setIdentifier(const std::string &identifier) {
    trade::identifier = identifier;
}

const std::string &trade::getBidPrice() const {
    return bidPrice;
}

void trade::setBidPrice(const std::string &bidPrice) {
    trade::bidPrice = bidPrice;
}

const std::string &trade::getAskPrice() const {
    return askPrice;
}

void trade::setAskPrice(const std::string &askPrice) {
    trade::askPrice = askPrice;
}

const std::string &trade::getTradePrice() const {
    return tradePrice;
}

void trade::setTradePrice(const std::string &tradePrice) {
    trade::tradePrice = tradePrice;
}

const std::string &trade::getBidVolume() const {
    return bidVolume;
}

void trade::setBidVolume(const std::string &bidVolume) {
    trade::bidVolume = bidVolume;
}

const std::string &trade::getAskVolume() const {
    return askVolume;
}

void trade::setAskVolume(const std::string &askVolume) {
    trade::askVolume = askVolume;
}

const std::string &trade::getTradeVolume() const {
    return tradeVolume;
}

void trade::setTradeVolume(const std::string &tradeVolume) {
    trade::tradeVolume = tradeVolume;
}

const std::string &trade::getUpdateType() const {
    return updateType;
}

void trade::setUpdateType(const std::string &updateType) {
    trade::updateType = updateType;
}

const std::string &trade::getDate() const {
    return date;
}

void trade::setDate(const std::string &date) {
    trade::date = date;
}

const std::string &trade::getTimePastMidnight() const {
    return timePastMidnight;
}

void trade::setTimePastMidnight(const std::string &timePastMidnight) {
    trade::timePastMidnight = timePastMidnight;
}

const std::string &trade::getConditionCode() const {
    return conditionCode;
}

void trade::setConditionCode(const std::string &conditionCode) {
    trade::conditionCode = conditionCode;
}