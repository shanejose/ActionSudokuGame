/**
 * @file Item.cpp
 * @author Harshita Rathod
 */

#include "pch.h"
#include "Item.h"
#include "Game.h"

using namespace std;


/**
 * Constructor
 * @param game The game this item is a member of
 * @param filename file name of the image
 *
 */
Item::Item(Game *game, const std::wstring &filename) : mGame(game)
{
    mItemImage = make_unique<wxImage>(filename, wxBITMAP_TYPE_ANY);
    mFilename = filename;
}


/**
 * Draw the item
 * @param graphics graphics context to draw on
 */
void Item::Draw(std::shared_ptr<wxGraphicsContext> graphics)
{
    if (mItemBitmap.IsNull())
    {
        mItemBitmap = graphics->CreateBitmapFromImage(*mItemImage);
    }
    if (!mInXray)
    {
        graphics->DrawBitmap(mItemBitmap,
                             int(GetX() * mGame->GetTileWidth()),
                             int((GetY() + 1) * mGame->GetTileHeight() - GetHeight()), GetWidth() - 1, GetHeight());
    }
    else
    {
        graphics->DrawBitmap(mItemBitmap,
                             int(GetX() * mGame->GetTileWidth()),
                             int((GetY() + 1) * mGame->GetTileHeight() - GetHeight()), (GetWidth() - 1) / ImageDownscale, GetHeight() / ImageDownscale);
    }

}
