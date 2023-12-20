/**
 * @file ContainerVisitor.h
 * @author Areeb Islam
 *
 * Visitor for Container Object
 */

#ifndef PROJECT1_PROJECT1LIB_CONTAINERVISITOR_H
#define PROJECT1_PROJECT1LIB_CONTAINERVISITOR_H

#include "ItemVisitor.h"

/**
 * Visitor for Container Object
 */
class ContainerVisitor : public ItemVisitor
{
private:
    /// Pointer to Sparty Object
    Sparty* mSparty = nullptr;

    /// X Location of Sparty
    double mXLocation;

    /// Y Location of Sparty
    double mYLocation;

    /// Flag to determine if Sparty in Range
    bool mInRange = false;

    /// Pointer to Container Front
    Container* mFront = nullptr;

    /// Pointer to Container
    Container* mContainer = nullptr;

    /// Tile Width
    double mTileWidth;

    /// Tile Height
    double mTileHeight;


public:

    void VisitSparty(Sparty* sparty) override;

    void VisitContainer(Container* container) override;

    /**
     * Getter for In Range Flag
     * @return Flag indicating sparty in range
     */
    bool GetRangeFlag() const {return mInRange;}


    /**
     * Retrieves a pointer to the front container of the game.
     * @return pointer to the front container
     */
    Container* GetFrontContainer () const { return mFront; }


    /**
     * Retrieves a pointer to the main container of the game.
     * @return A pointer to the main container.
     */
    Container* GetMainContainer () const { return mContainer; }

    /**
     * Set tile width and height
     * @param width Tile Width
     * @param height Tile Height
     */
    void SetTileWidthHeight (double width, double height) { mTileHeight = height; mTileWidth = width; }

};


#endif //PROJECT1_PROJECT1LIB_CONTAINERVISITOR_H
