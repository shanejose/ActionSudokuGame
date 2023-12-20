/**
 * @file Item.h
 * @author Harshita Rathod
 *
 * Base class for items in the game
 */

#ifndef PROJECT1_PROJECT1LIB_ITEM_H
#define PROJECT1_PROJECT1LIB_ITEM_H

#include "ItemVisitor.h"

class Game;

/**
 * Base class for items in the game
 *
 */
class Item
{
private:

    /// The underlying item image
    std::unique_ptr<wxImage> mItemImage;

    /// The bitmap we can display this item
    wxGraphicsBitmap mItemBitmap;

    // Item location in the game
    double  mX;     ///< X location for the center of the item
    double  mY;     ///< Y location for the center of the item

    ///Holds filename of item
    std::wstring mFilename;

    /// Flag to check if item is already in game solution
    bool mPositioned = false;

    /// Flag to check if item is contained
    bool mContained = false;

    /// Flag to Check if Item in XRay
    bool mInXray = false;

    /// Image DownScale
    double ImageDownscale = 1.5;

protected:
    Item(Game *game, const std::wstring &filename);

    /// The game this item is contained in
    Game   *mGame;

public:
    /**
     * The X location of the item
     * @return X location in pixels
     */
    double GetX() const { return mX; }

    /**
    * The Y location of the item
    * @return Y location in pixels
    */
    double GetY() const { return mY; }

    /**
     * Set the item location
     * @param x X location in pixels
     * @param y Y location in pixels
     */
    virtual void SetLocation(double x, double y) { mX = x; mY = y; }

    /**
    * Get the filename of the item
    * @return Item filename
    */
    const std::wstring GetFilename() const {return mFilename;}

    /**
    * Get the width of the item
    * @return Item width in pixels
    */
    int GetWidth() const { return mItemImage->GetWidth(); }

    /**
     * Get the height of the item
     * @return Item height in pixels
     */
    int GetHeight() const { return mItemImage->GetHeight(); }

    virtual void Draw(std::shared_ptr<wxGraphicsContext> graphics);

    /**
    * Handle updates for animation
    * @param elapsed The time since the last update
    */
    virtual void Update(double elapsed) {}

    /**
     * Accept a visitor
     * @param visitor The Visitor we accept
     */
    virtual void Accept(ItemVisitor* visitor) {};

    /**
     * Set the Positioned Flag for Item
     * @param positioned Flag Indicating if Item is Positioned
     */
    void SetPositioned(bool positioned) {mPositioned = positioned;}

    /**
     * Set the Container Flag for Item
     * @param contained Flag indicating if Item is Container in Container
     */
    void SetContained(bool contained) {mContained = contained;}

    /**
     * Getter for is Positioned Flag
     * @return Flag indicating if Item is positioned
     */
    bool IsPositioned() const {return mPositioned;}

    /**
     * Getter for is Contained Flag
     * @return Flag indicating if Item is contained
     */
    bool IsContained() const {return mContained;}

    /**
     * Set the Flag to Indicate item in XRay
     */
    void SetXRayFlag () { mInXray = !mInXray; }
};

#endif //PROJECT1_PROJECT1LIB_ITEM_H
