#include "gmock/gmock.h"
#include "Portfolio.h"
#include <iostream>

using namespace std;
using namespace ::testing;

class APortfolio: public Test {
public:
    static const string IBM;
    static const string SAMSUNG;
    Portfolio portfolio_;
};
const string APortfolio::IBM = ("IBM");
const string APortfolio::SAMSUNG = ("SSNLF");

TEST_F(APortfolio, IsEmptyWhenCreated) {
    ASSERT_TRUE(portfolio_.IsEmpty());
}

TEST_F(APortfolio, IsNotEmptyAfterPurchase) {
    portfolio_.Purchase("IBM", 1);

    ASSERT_FALSE(portfolio_.IsEmpty());
}
TEST_F(APortfolio, AnswersZeroForShareCountOfUnpurchasedSymbol) {
    ASSERT_THAT(portfolio_.ShareCount("AAPL"), Eq(0u));
}

TEST_F(APortfolio, AnswersShareCountForPurchasedSymbol) {
    portfolio_.Purchase("IBM", 2);
    ASSERT_THAT(portfolio_.ShareCount("IBM"), Eq(2u));
}

TEST_F(APortfolio, ThrowOnPurchaseOfZerosShares) {
    ASSERT_THROW(portfolio_.Purchase(IBM, 0), InvalidPurchaseException);
}

TEST_F(APortfolio, AnswersShareCountForAppropriateSymbol) {
    portfolio_.Purchase(IBM, 5);
    portfolio_.Purchase(SAMSUNG, 10);

    ASSERT_THAT(portfolio_.ShareCount(IBM), Eq(5u));
}

TEST_F(APortfolio, SharedCountReflectsAccumulatedPurchaseOfSameSymbol) {
    portfolio_.Purchase(IBM, 5);
    portfolio_.Purchase(IBM, 10);

    ASSERT_THAT(portfolio_.ShareCount(IBM), Eq(5u + 10));
}

TEST_F(APortfolio, ReduceShareCountOfSymbolsOnSell) {
    portfolio_.Purchase(SAMSUNG, 30);
    portfolio_.Sell(SAMSUNG, 13);

    ASSERT_THAT(portfolio_.ShareCount(SAMSUNG), Eq(30U - 13));
}

TEST_F(APortfolio, ThrowsWhenSellingMoreSharesThanPurchased) {
    ASSERT_THROW(portfolio_.Sell(SAMSUNG, 1), InvalidSellException);
}