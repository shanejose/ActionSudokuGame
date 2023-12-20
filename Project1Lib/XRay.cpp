/**
 * @file XRay.cpp
 * @author Sanju Kona
 */

#include "pch.h"
#include "XRay.h"
#include "Game.h"
#include <string>

using namespace std;

/// Base Directory for Images
const wstring imageDir= L"resources/images/";

/// Min X For Random Generator
double minXRange = 0;

/// Min Y For Random Generator
double minYRange = 0;

/// Max Y For Random Generator
double maxYRange = 1.75;

/// Max X For Random Generator
double maxXRange = 2;

///number of columns/rows in a sudoku board
const int boardLen = 9;


/**
 * Constructor for XRay
 * @param game game Game this XRay is a member of
 * @param filename filename of XRay
 * @param capacity capacity of XRay
 * @param node xml node to get xray attributes
 */
XRay::XRay(Game *game, const std::wstring &filename, int capacity, wxXmlNode *node):Container(game, filename, node)
{
    mCapacity = capacity;
}

/**
 * Adds XRay to container
 * @param item
 */
void XRay::Add(std::shared_ptr<Item> item)
{
    std::uniform_real_distribution<> yDistribution(minYRange, maxYRange);
    std::uniform_real_distribution<> xDistribution(minXRange, maxXRange);
    double newX = xDistribution(mGame->GetRandom());
    double newY = yDistribution(mGame->GetRandom());
    item->SetLocation(GetX() + newX, GetY() - newY);
    item->SetXRayFlag();
    Container::Add(item);
}

/**
 * Spits the digit from Xray to Sudoku board
 * @param key digit
 * @param x x location
 * @param y y location
 */
void XRay::SpitDigit(int key, double x , double y){
    wstring keyStr = to_wstring(key);
    wstring expectedFilename = imageDir + keyStr + L"r.png";

    for(auto digit : mDigits){
        if(digit->GetFilename() == expectedFilename){
            digit->SetXRayFlag();
            digit->SetLocation(x,y);
            if(x >= mGame->GetBoardCol() && x <= mGame->GetBoardCol() + boardLen && y >= mGame->GetBoardRow() && y <= mGame->GetBoardRow() + boardLen){
                digit->SetPositioned(true);
            }
            mGame->Add(digit);
            Delete(digit);
            mGame->RemoveAndInsertSparty();
            break;
        }
    }
}

/**
 * Draws the digits on the Xray
 * @param graphics
 */
void XRay::Draw(std::shared_ptr<wxGraphicsContext> graphics)
{
    Item::Draw(graphics);
    for (auto digit : mDigits)
    {
        digit->Draw(graphics);
    }
}



