#include "include/csv.hpp"
#include <string>

class trade {
public:
    trade();

    explicit trade(csv::CSVRow &row);

    enum updateTypeEnum {
        TRADE = 1, CHANGEBID = 2, CHANGEASK = 3
    };
private:
    std::string identifier;
    std::string bidPrice;
    std::string askPrice;
    std::string tradePrice;
    std::string bidVolume;
    std::string askVolume;
    std::string tradeVolume;
    std::string updateType;
    std::string date;
    std::string timePastMidnight;
    std::string conditionCode;
public:
    const std::string &getIdentifier() const;

    void setIdentifier(const std::string &identifier);

    const std::string &getBidPrice() const;

    void setBidPrice(const std::string &bidPrice);

    const std::string &getAskPrice() const;

    void setAskPrice(const std::string &askPrice);

    const std::string &getTradePrice() const;

    void setTradePrice(const std::string &tradePrice);

    const std::string &getBidVolume() const;

    void setBidVolume(const std::string &bidVolume);

    const std::string &getAskVolume() const;

    void setAskVolume(const std::string &askVolume);

    const std::string &getTradeVolume() const;

    void setTradeVolume(const std::string &tradeVolume);

    const std::string &getUpdateType() const;

    void setUpdateType(const std::string &updateType);

    const std::string &getDate() const;

    void setDate(const std::string &date);

    const std::string & getTimePastMidnight() const;

    void setTimePastMidnight(const std::string &timePastMidnight);

    const std::string &getConditionCode() const;

    void setConditionCode(const std::string &conditionCode);

};

