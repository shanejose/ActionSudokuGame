/**
 * @file DigitVisitor.h
 * @author Areeb Islam
 *
 * Visit Digit Items for Eating
 */

#ifndef PROJECT1_PROJECT1LIB_DIGITVISITOR_H
#define PROJECT1_PROJECT1LIB_DIGITVISITOR_H

#include "ItemVisitor.h"
#include <cfloat>

/**
 * Visit Digit Items for Eating
 */
class DigitVisitor : public ItemVisitor
{
private:
    /// Pointer to XRay object
    XRay* mXray = nullptr;

    /// Pointer to Sparty Object
    std::shared_ptr<Sparty> mSparty = nullptr;

    /// Flag in Range of Digit
    RedDigit* mDigit = nullptr;

    /// Current Lowest Distance
    double mDistance = DBL_MAX;

    /// Tile Width
    double mTileWidth;
    /// Tile Height
    double mTileHeight;


public:

    void VisitXray(XRay* xray) override;

    void VisitRedDigit(RedDigit* digit) override;

    /**
     * Setter for Sparty Object
     * @param sparty Pointer to Sparty Object
     */
    void SetSparty (std::shared_ptr<Sparty> sparty) { mSparty = sparty; }

    /**
     * Get the Digit We Visited
     * @return Digit Pointer
     */
    RedDigit* GetRedDigit () const { return mDigit; }

    /**
     * Get the XRay Item in mItems
     * @return XRay Pointer
     */
    XRay* GetXRay () const { return mXray; }

    /**
     * Set tile width and height
     * @param width Tile Width
     * @param height Tile Height
     */
    void SetTileWidthHeight (double width, double height) { mTileHeight = height; mTileWidth = width; }

};

#endif //PROJECT1_PROJECT1LIB_DIGITVISITOR_H
