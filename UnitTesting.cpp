// Uncomment the next line to use precompiled headers
#include "pch.h"
// uncomment the next line if you do not use precompiled headers
//#include "gtest/gtest.h"
//
// the global test environment setup and tear down
// you should not need to change anything here
class Environment : public ::testing::Environment
{
public:
    ~Environment() override {}

    // Override this to define how to set up the environment.
    void SetUp() override
    {
        //  initialize random seed
        srand(time(nullptr));
    }

    // Override this to define how to tear down the environment.
    void TearDown() override {}
};

// create our test class to house shared data between tests
// you should not need to change anything here
class CollectionTest : public ::testing::Test
{
protected:
    // create a smart point to hold our collection
    std::unique_ptr<std::vector<int>> collection;

    void SetUp() override
    { // create a new collection to be used in the test
        collection.reset(new std::vector<int>);
    }

    void TearDown() override
    { //  erase all elements in the collection, if any remain
        collection->clear();
        // free the pointer
        collection.reset(nullptr);
    }

    // helper function to add random values from 0 to 99 count times to the collection
    void add_entries(int count)
    {
        assert(count > 0);
        for (auto i = 0; i < count; ++i)
            collection->push_back(rand() % 100);
    }
};

// When should you use the EXPECT_xxx or ASSERT_xxx macros?
// Use ASSERT when failure should terminate processing, such as the reason for the test case.
// Use EXPECT when failure should notify, but processing should continue

// Test that a collection is empty when created.
// Prior to calling this (and all other TEST_F defined methods),
//  CollectionTest::StartUp is called.
// Following this method (and all other TEST_F defined methods),
//  CollectionTest::TearDown is called
TEST_F(CollectionTest, CollectionSmartPointerIsNotNull)
{
    // is the collection created
    ASSERT_TRUE(collection);

    // if empty, the size must be 0
    ASSERT_NE(collection.get(), nullptr);
}

// Test that a collection is empty when created.
TEST_F(CollectionTest, IsEmptyOnCreate)
{
    // is the collection empty?
    ASSERT_TRUE(collection->empty());

    // if empty, the size must be 0
    ASSERT_EQ(collection->size(), 0);
}

/* Comment this test out to prevent the test from running
 * Uncomment this test to see a failure in the test explorer */
/*TEST_F(CollectionTest, AlwaysFail)
{
    FAIL();
}*/

// TODO: Create a test to verify adding a single value to an empty collection
TEST_F(CollectionTest, CanAddToEmptyVector)
{
    // is the collection empty?
    // if empty, the size must be 0
   ASSERT_EQ(collection->size(), 0) << "Collection is empty";

    add_entries(1);

    // is the collection still empty?
    // if not empty, what must the size be?
    ASSERT_EQ(collection->size(), 1) << "Collection has 1 entry";
}

// TODO: Create a test to verify adding five values to collection
TEST_F(CollectionTest, CanAddFiveValuesToVector)
{
    // verify collection empty
    ASSERT_EQ(collection->size(), 0) << "Collection is empty";
    // add 5 entries
    add_entries(5);
    // verify collection has 5 entries
    ASSERT_EQ(collection->size(), 5) << "Collection has 5 entries";
    
}

// TODO: Create a test to verify that max size is greater than or equal to size for 0, 1, 5, 10 entries
TEST_F(CollectionTest, MaxsizeShouldBeGreaterOfEqualToSizeOfCollection) 
{
    // check empty collection (0); test for 0
    ASSERT_EQ(collection->size(), 0) << "Collection has 0 entries";
    ASSERT_TRUE(collection->max_size() >= collection->size());

    // add one entry and verify; test for 1
    add_entries(1);
    ASSERT_EQ(collection->size(), 1) << "Collection has 1 entries";
    ASSERT_TRUE(collection->max_size() >= collection->size());

    // add 4 to make it 5 entries and verify; test for 5
    add_entries(4);
    ASSERT_EQ(collection->size(), 5) << "Collection has 5 entries";
    ASSERT_TRUE(collection->max_size() >= collection->size());

    // add 5 mroe to make it 10 entries and verify; test for 10
    add_entries(5);
    ASSERT_EQ(collection->size(), 10) << "Collection has 10 entries";
    ASSERT_TRUE(collection->max_size() >= collection->size());

}

// TODO: Create a test to verify that capacity is greater than or equal to size for 0, 1, 5, 10 entries
TEST_F(CollectionTest, CapacityShouldBeGreaterOfEqualToSizeOfCollection)
{
    // check empty collection (0); test for 0
    ASSERT_EQ(collection->size(), 0) << "Collection has 0 entries";
    ASSERT_TRUE(collection->capacity() >= collection->size());

    // add one entry and verify; test for 1
    add_entries(1);
    ASSERT_EQ(collection->size(), 1) << "Collection has 1 entries";
    ASSERT_TRUE(collection->capacity() >= collection->size());

    // add 4 to make it 5 entries and verify; test for 5
    add_entries(4);
    ASSERT_EQ(collection->size(), 5) << "Collection has 5 entries";
    ASSERT_TRUE(collection->capacity() >= collection->size());

    // add 5 mroe to make it 10 entries and verify; test for 10
    add_entries(5);
    ASSERT_EQ(collection->size(), 10) << "Collection has 10 entries";
    ASSERT_TRUE(collection->capacity() >= collection->size());

}

// TODO: Create a test to verify resizing increases the collection
TEST_F(CollectionTest, ResizingShouldIncreaseWhenSizeIsIncreased)
{
    // add 2 entries
    add_entries(2);

    // store size of collection as int
    int initialSize = collection->size();

    // increase to three with resize()
    collection->resize(3);

    // verify size decreased
    ASSERT_TRUE(collection->size() > initialSize);
}

// TODO: Create a test to verify resizing decreases the collection
TEST_F(CollectionTest, ResizingShouldDecreaseWhenSizeIsDecreased)
{
    // add 2 entries
    add_entries(2);

    // store size of collection as int
    int initialSize = collection->size();

    // decrease to one with resize()
    collection->resize(1);

    // verify size decreased
    ASSERT_TRUE(collection->size() < initialSize);
}

// TODO: Create a test to verify resizing decreases the collection to zero
TEST_F(CollectionTest, ResizingShouldDecreaseSizeToZero)
{
    // add 2 entries
    add_entries(2);

    // store size of collection as int
    int initialSize = collection->size();

    // decrease to one with resize()
    collection->resize(0);

    // verify size of collection is 0
    ASSERT_EQ(collection->size(), 0);
}

// TODO: Create a test to verify clear erases the collection
TEST_F(CollectionTest, ClearShouldEraseTheEntriesInTheCollection)
{
    // add 2 entries
    add_entries(2);

    // call to clear
    collection->clear();

    // verify entries are cleared
    ASSERT_EQ(collection->size(), 0);
}

// TODO: Create a test to verify erase(begin,end) erases the collection
TEST_F(CollectionTest, CallToErase_Begin_End_SchouldEraseAllEntries)
{
    // add 10 entries
    add_entries(10);

    // call erase(begin/end)
    collection->erase(collection->begin(), collection->end());

    // verify size is 0
    ASSERT_EQ(collection->size(), 0);
}

// TODO: Create a test to verify reserve increases the capacity but not the size of the collection
TEST_F(CollectionTest, ReserveShouldIncreaseCapacityAndNotSize)
{
    // add 7 entries
    add_entries(7);
    
    // store size and capacity of collection as int values respectively
    int collectionSize = collection->size();
    int collectionCapacity = collection->capacity();

    // call to reserve
    collection->reserve(10);

    // verify results
    ASSERT_EQ(collection->size(), collectionSize);
    ASSERT_TRUE(collection->capacity() > collectionCapacity);
    
}

// TODO: Create a test to verify the std::out_of_range exception is thrown when calling at() with an index out of bounds
// NOTE: This is a negative test
TEST_F(CollectionTest, ShouldThrowOutOfRangeWhenOutOfBoundsIndexAccessed)
{
    // add 5 entries
    std::vector<int> entries(5);

    // attempt to acces index 6
    EXPECT_THROW(entries.at(6), std::out_of_range);
}

// TODO: Create 2 unit tests of your own to test something on the collection - do 1 positive & 1 negative
// poitive test
TEST_F(CollectionTest, PopBackShouldRomoveLastEntry)
{
    // add 2 entries
    add_entries(2);

    // store entries as variables
    int entry1 = collection->at(0);
    int entry2 = collection->at(1);

    // call to pop_back
    collection->pop_back();

    // verify removal
    ASSERT_EQ(collection->size(), 1);

    // verify remaining entry is the same
    ASSERT_EQ(collection->at(0), entry1);
}

// nagative test
TEST_F(CollectionTest, PushBackShouldOnlyAddOneEntry)
{
    // add 2 entries
    add_entries(2);

    // call to push_back
    collection->push_back(rand() % 100);

    // verify only one entry was added
    EXPECT_THROW(collection->at(4), std::out_of_range);
}
