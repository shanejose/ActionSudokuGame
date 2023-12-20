/**
 * @file ItemTest.cpp
 * @author Shane Jose
 *
 * class that performs unit test for Item class
 */


#include <pch.h>
#include "gtest/gtest.h"
#include <Item.h>
#include <Game.h>

const std::wstring &filename = L"resources/images/sparty-1.png";

/** Mock class for testing the class Item */
class ItemMock : public Item {
public:
    ItemMock(Game *game) : Item(game, filename) {}

};

/**
 * Test function that creates an object
 */
TEST(ItemTest, Construct)
{
    Game game;
    ItemMock item(&game);
}

/**
 * Test function that tests getters and setters in Item class
 *
 */
TEST(ItemTest, SettersGetters)
{
    Game game;
    ItemMock item(&game);

    // Test SetLocation, GetX, and GetY
    item.SetLocation(10, 17);
    ASSERT_NEAR(10, item.GetX(), 0.0001);
    ASSERT_NEAR(17, item.GetY(), 0.0001);

    // Test a second with with different values
    item.SetLocation(45, 32);
    ASSERT_NEAR(45, item.GetX(), 0.0001);
    ASSERT_NEAR(32, item.GetY(), 0.0001);
}

