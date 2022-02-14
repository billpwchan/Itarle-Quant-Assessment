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
    float bidPrice;
    float askPrice;
    float tradePrice;
    long bidVolume;
    long askVolume;
    long tradeVolume;
    int updateType;
    std::string date;
    float timePastMidnight;
    std::string conditionCode;
public:
    const std::string &getIdentifier() const;

    void setIdentifier(const std::string &identifier);

    float getBidPrice() const;

    void setBidPrice(float bidPrice);

    float getAskPrice() const;

    void setAskPrice(float askPrice);

    float getTradePrice() const;

    void setTradePrice(float tradePrice);

    long getBidVolume() const;

    void setBidVolume(long bidVolume);

    long getAskVolume() const;

    void setAskVolume(long askVolume);

    long getTradeVolume() const;

    void setTradeVolume(long tradeVolume);

    int getUpdateType() const;

    void setUpdateType(int updateType);

    const std::string &getDate() const;

    void setDate(const std::string &date);

    float getTimePastMidnight() const;

    void setTimePastMidnight(float timePastMidnight);

    const std::string &getConditionCode() const;

    void setConditionCode(const std::string &conditionCode);
};

