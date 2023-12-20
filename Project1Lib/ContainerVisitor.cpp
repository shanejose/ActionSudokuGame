/**
 * @file ContainerVisitor.cpp
 * @author Areeb Islam
 */

#include "pch.h"
#include "ContainerVisitor.h"
#include "Sparty.h"
#include "Container.h"

using namespace std;


/**
 * Assign Sparty Pointer to Member Variable
 * @param sparty
 */
void ContainerVisitor::VisitSparty(Sparty *sparty)
{
    mSparty = sparty;
    mXLocation = mSparty->GetX() + (mSparty->GetXOffset() / mTileHeight);
    mYLocation = mSparty->GetY() + (mSparty->GetYOffset() / mTileHeight);
}


/**
 * Visitor to Determine if the Object is a Container
 *
 * @param container
 */
void ContainerVisitor::VisitContainer(Container *container)
{
    if (mSparty != nullptr)
    {
        if (abs(mXLocation - container->GetX()) < 2.0 && abs(mYLocation - container->GetY()) < 2.0)
        {
            mInRange = true;

            if(mFront == nullptr && container->GetFrontIndicatorFlag())
            {
                mFront = container;
            }
            if(mContainer == nullptr && !container->GetFrontIndicatorFlag())
            {
                mContainer = container;
            }
        }
    }
}