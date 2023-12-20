/**
 * @file DigitVisitor.cpp
 * @author Areeb Islam
 */

#include "pch.h"
#include "DigitVisitor.h"
#include "Sparty.h"
#include "XRay.h"
#include "RedDigit.h"


/**
 * Visit XRay Object
 * @param xray
 */
void DigitVisitor::VisitXray(XRay *xray)
{
    if (mXray == nullptr)
    {
        mXray = xray;
    }
}

/**
 * Visits Red digits
 * @param digit digit being visited
 */
void DigitVisitor::VisitRedDigit(RedDigit *digit)
{
    double xLocation = mSparty->GetX() + (mSparty->GetXOffset() / mTileWidth) - digit->GetX();
    double yLocation = mSparty->GetY() + (mSparty->GetYOffset() / mTileHeight) - digit->GetY();
    if (xLocation > 0)
    {
        double currDistance = sqrt((xLocation*xLocation) + (yLocation*yLocation));
        if (currDistance < mDistance && currDistance < 1.0)
        {
            mDistance = currDistance;
            mDigit = digit;
        }
    }

}