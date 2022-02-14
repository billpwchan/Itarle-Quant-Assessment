#include "include/csv.hpp"
#include <string>

class trade {
public:
    trade();

    trade(float bidPrice, float askPrice, float tradePrice, long bidVolume, long askVolume, long tradeVolume,
          std::string date, int timePastMidnight, std::string conditionCode);

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

    int getTimePastMidnight() const;

    void setTimePastMidnight(int timePastMidnight);

    const std::string &getConditionCode() const;

    void setConditionCode(const std::string &conditionCode);

private:
    long askVolume;
    long tradeVolume;
    int updateType;
    std::string date;
    int timePastMidnight;
    std::string conditionCode;
};

