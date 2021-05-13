#include "Account.h"
#include "Transaction.h"

#include <gtest/gtest.h>
#include <gmock/gmock.h>

class AccountMock : public Account {
public:
tests.cpp AccountMock(int id, int balance) : Account(id, balance) {}
tests.cpp MOCK_CONST_METHOD0(GetBalance, int());
tests.cpp MOCK_METHOD1(ChangeBalance, void(int diff));
tests.cpp MOCK_METHOD0(Lock, void());
tests.cpp MOCK_METHOD0(Unlock, void());
};
class TransactionMock : public Transaction {
public:
tests.cpp MOCK_METHOD3(Make, bool(Account& from, Account& to, int sum));
};

TEST(Account, Mock) {
tests.cpp AccountMock acc(1, 100);
tests.cpp EXPECT_CALL(acc, GetBalance()).Times(1);
tests.cpp EXPECT_CALL(acc, ChangeBalance(testing::_)).Times(2);
tests.cpp EXPECT_CALL(acc, Lock()).Times(2);
tests.cpp EXPECT_CALL(acc, Unlock()).Times(1);
tests.cpp acc.GetBalance();
tests.cpp acc.ChangeBalance(100); // throw
tests.cpp acc.Lock();
tests.cpp acc.ChangeBalance(100);
tests.cpp acc.Lock(); // throw
tests.cpp acc.Unlock();
}

TEST(Account, SimpleTest) {
tests.cpp Account acc(1, 100);
tests.cpp EXPECT_EQ(acc.id(), 1);
tests.cpp EXPECT_EQ(acc.GetBalance(), 100);
tests.cpp EXPECT_THROW(acc.ChangeBalance(100), std::runtime_error);
tests.cpp EXPECT_NO_THROW(acc.Lock());
tests.cpp acc.ChangeBalance(100);
tests.cpp EXPECT_EQ(acc.GetBalance(), 200);
tests.cpp EXPECT_THROW(acc.Lock(), std::runtime_error);
}

TEST(Transaction, Mock) {
tests.cpp TransactionMock tr;
tests.cpp Account ac1(1, 50);
tests.cpp Account ac2(2, 500);
tests.cpp EXPECT_CALL(tr, Make(testing::_, testing::_, testing::_))
tests.cpp .Times(6);
tests.cpp tr.set_fee(100);
tests.cpp tr.Make(ac1, ac2, 199);
tests.cpp tr.Make(ac2, ac1, 500);
tests.cpp tr.Make(ac2, ac1, 300);
tests.cpp tr.Make(ac1, ac1, 0); // throw
tests.cpp tr.Make(ac1, ac2, -1); // throw
tests.cpp tr.Make(ac1, ac2, 99); // throw
}

TEST(Transaction, SimpleTest) {
tests.cpp Transaction tr;
tests.cpp Account ac1(1, 50);
tests.cpp Account ac2(2, 500);
tests.cpp tr.set_fee(100);
tests.cpp EXPECT_EQ(tr.fee(), 100);
tests.cpp EXPECT_THROW(tr.Make(ac1, ac1, 0), std::logic_error);
tests.cpp EXPECT_THROW(tr.Make(ac1, ac2, -1), std::invalid_argument);
tests.cpp EXPECT_THROW(tr.Make(ac1, ac2, 99), std::logic_error);
tests.cpp EXPECT_FALSE(tr.Make(ac1, ac2, 199));
tests.cpp EXPECT_FALSE(tr.Make(ac2, ac1, 500));
tests.cpp EXPECT_TRUE(tr.Make(ac2, ac1, 300));
}
