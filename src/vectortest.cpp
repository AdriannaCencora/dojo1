#include <gtest/gtest.h>
#include "vector.hpp"
#include <vector>
#include <exception>

class vectortest: public testing::Test
{
public:
    vectortest()
    {
        EXPECT_EQ(4, uut.get_capacity());
        EXPECT_EQ(0, uut.get_size());
    }

    void assertStateEq(int _size, int _capacity)
    {
        ASSERT_EQ(_size, uut.get_size());
        ASSERT_EQ(_capacity, uut.get_capacity());
    }

    void assertValuesEq(std::vector<int> givenValues) {
        ASSERT_EQ(givenValues.size(), uut.get_size());
        for(unsigned int i = 0; i< uut.get_size(); i++)
            ASSERT_EQ(givenValues[i], uut[i]);
    }

public:
    vector uut;
};


TEST_F(vectortest, IfPush2TimesExpctSize2) {
    uut.push_back(1);
    assertStateEq(1, 4);
    assertValuesEq({1});

    uut.push_back(2);
    assertStateEq(2, 4);
    assertValuesEq({1, 2});

    uut.push_back(3);
    assertStateEq(3, 4);
    assertValuesEq({1, 2, 3});

    uut.push_back(5);
    assertStateEq(4, 4);
    assertValuesEq({1, 2, 3, 5});

    uut.push_back(6);
    assertStateEq(5, 8);
    assertValuesEq({1, 2, 3, 5, 6});
}

TEST_F(vectortest, IfPushBack16TimesExpctResizeTwice){
    for(size_t i = 0 ; i<17 ; ++i)
    {
    uut.push_back(i);
    }
    assertStateEq(17, 32);
}

TEST_F(vectortest, IfAtOnEmptyVectorExpctThrow){
    EXPECT_THROW(uut.at(0), std::bad_alloc);
}

TEST_F(vectortest, IfAtOnElementofVectorExpctReturn1){
    uut.push_back(1);
    EXPECT_EQ(1, uut.at(0));
}

TEST_F(vectortest, IfPopBackOnEmptyThrowException) {
    EXPECT_THROW(uut.pop_back(), std::bad_alloc);
}

TEST_F(vectortest, IfPopBackOnNonEmptyDeleteLastElement) {
    uut.push_back(1);
    assertStateEq(1, 4);
    assertValuesEq({1});

    uut.pop_back();
    assertStateEq(0, 4);
    assertValuesEq({});
}

TEST_F(vectortest, IfPopBackMoreThan2ThenCapacityTheSame)
{
    uut.push_back(1);
    uut.push_back(2);
    uut.push_back(3);
    uut.push_back(4);
    uut.push_back(5);

    assertStateEq(5, 8);
    assertValuesEq({1, 2, 3, 4, 5});

    uut.pop_back();
    uut.pop_back();

    assertStateEq(3, 8);
    assertValuesEq({1, 2, 3});

    uut.push_back(11);
    uut.push_back(21);
    uut.push_back(31);
    uut.push_back(41);
    uut.push_back(51);

    assertStateEq(8, 8);
    assertValuesEq({1, 2, 3, 11, 21, 31, 41, 51});
}


TEST_F(vectortest, IfInsertIndexMoreThanSizeCapicityIncrease){
    uut.push_back(1);
    uut.push_back(2);
    uut.push_back(3);
    uut.push_back(4);

    assertStateEq(4, 4);
    assertValuesEq({1, 2, 3, 4});

    uut.insert(1,5);

    assertStateEq(5, 8);
    assertValuesEq({1, 5, 2, 3, 4});
}

TEST_F(vectortest, IfInsertIndexOutOfSizeThrowExcption){
    EXPECT_THROW(uut.insert(5,5), std::bad_alloc);
}

TEST_F(vectortest, IfShrinkToFitOnEmptyExpectCapacity0){
    uut.shrinkToFit();
    assertStateEq(0,0);
    assertValuesEq({});
}

TEST_F(vectortest, IfShrinkToFitOnOneElementVectorExpectCapacity1) {
    uut.push_back(1);
    assertStateEq(1,4);
    assertValuesEq({1});
    uut.shrinkToFit();
    assertStateEq(1,1);
    assertValuesEq({1});
}

TEST_F(vectortest, IfDeleteEmptyIndexReturnThrow) {
    EXPECT_THROW(uut.pop(1), std::bad_alloc);
}

TEST_F(vectortest, IfDeleteNonEmptyIndexDeleteElement) {
    uut.push_back(1);
    assertStateEq(1,4);
    assertValuesEq({1});
    uut.pop(0);
    assertStateEq(0,4);
    assertValuesEq({});
}

TEST_F(vectortest, IfDeleteNonEmptyIndexDeleteElement2) {
    uut.push_back(1);
    uut.push_back(1);
    uut.push_back(2);
    uut.push_back(3);
    uut.push_back(4);
    assertStateEq(5,8);
    assertValuesEq({1,1,2,3,4});
    uut.pop(2);
    assertStateEq(4,8);
    assertValuesEq({1,1,3,4});
}