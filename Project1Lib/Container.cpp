/**
 * @file Container.cpp
 * @author Sanju Kona
 */

#include "pch.h"
#include "Container.h"
#include "Game.h"
#include <random>

/**
 * Constructor for Container Object
 * @param game Game Pointer to Game object
 * @param filename Filename for Object
 * @param node XMl Node
 */
Container::Container(Game *game, const std::wstring &filename, wxXmlNode *node) : XMLItem(game, filename, node)
{
    if (filename == L"resources/images/cauldron-2.png" || filename == L"resources/images/pumpkin-front.png")
    {
        mIsFront = true;
    }
}

/**
 * Add an item to container
 * @param item Item to add to container
 */
void Container::Add(std::shared_ptr<Item> item)
{
    mDigits.push_back(item);
}


/**
 * Delete an item in container
 * @param item
 */
void Container::Delete(std::shared_ptr<Item> item)
{
    auto endIterator = end(mDigits);
    auto loc = find(begin(mDigits), endIterator, item);
    if(loc != endIterator){
        mDigits.erase(loc);
    }
}


/**
 * Randomize Location of Digits when Popped out of Container
 * @param items Vector of Items
 */
void Container::RandomizeDigitLocations(std::vector<std::shared_ptr<Item>> &items)
{
    for (auto digit : mDigits)
    {
        std::uniform_real_distribution<> yDistribution(2, 6);
        std::uniform_real_distribution<> xDistribution(0, 4);
        double newX = xDistribution(mGame->GetRandom());
        double newY = yDistribution(mGame->GetRandom());
        digit->SetLocation(GetX() + newX, GetY() - newY);
        digit->SetContained(false);
        items.push_back(digit);
    }
    Clear();
}

/**
 * Clear the Container
 */
void Container::Clear()
{
    mDigits.clear();
}