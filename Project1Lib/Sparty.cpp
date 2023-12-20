/**
 * @file Sparty.cpp
 * @author Shane Jose
 */

#include "pch.h"
#include "Game.h"
#include "Sparty.h"

using namespace std;



/**
 * Constructor For Sparty Class
 * @param game Pointer to Game Object
 * @param filename file name of the image
 * @param node node of the item
 */
Sparty::Sparty(Game *game, const std::wstring &filename, wxXmlNode* node):Item(game,filename)
{
    node->GetAttribute(L"target-x", L"0").ToDouble(&mTargetX);
    node->GetAttribute(L"target-y", L"0").ToDouble(&mTargetY);
    node->GetAttribute(L"head-pivot-x", L"0").ToDouble(&mHeadPivotX);
    node->GetAttribute(L"head-pivot-y", L"0").ToDouble(&mHeadPivotY);
    node->GetAttribute(L"head-pivot-angle", L"0").ToDouble(&mHeadPivotAngle);

    node->GetAttribute(L"mouth-pivot-x", L"0").ToDouble(&mMouthPivotX);
    node->GetAttribute(L"mouth-pivot-y", L"0").ToDouble(&mMouthPivotY);
    node->GetAttribute(L"mouth-pivot-angle", L"0").ToDouble(&mMouthPivotAngle);


    mSpartyImage = make_unique<wxImage>(filename, wxBITMAP_TYPE_ANY);

}

/**
 * Set the move location of the sparty where the user clicked
 * @param x x location where sparty has to move
 * @param y y location where sparty has to move
 */
void Sparty::SetMovetoLocation(double x, double y)
{
    mMoveToX = x -  (mTargetX/mGame->GetTileWidth());
    mMoveToY = y - (mTargetY /mGame->GetTileHeight());
}


/**
 * Updates the movement of Sparty
 * @param elapsed
 */
void Sparty::Update(double elapsed)
{
    if(mStop){


        if (mMovement)
        {
            auto targetX = mMoveToX - GetX();
            auto targetY = mMoveToY - GetY();
            auto distance = sqrt((targetX*targetX) + (targetY*targetY));

            targetX /= distance;
            targetY /= distance;

            targetX *= MaxSpeed;
            targetY *= MaxSpeed;


            targetX /= mGame->GetTileWidth();
            targetY /= mGame->GetTileHeight();


            if(sqrt((targetX*targetX) + (targetY*targetY)) * elapsed < distance)
            {
                SetLocation(GetX() + (targetX*elapsed) , GetY()+ (targetY*elapsed));
            }
            else{
                SetLocation(mMoveToX , mMoveToY);
                mMovement = false;
            }

        }

        if(mHeadButtCurrent > 0)
        {
            auto newTime = mHeadButtCurrent - elapsed;

            if(newTime < 0)
            {
                mHeadButtCurrent = 0;
                mCheckHeadbutt = false;
            }
            else
            {
                mHeadButtCurrent = newTime;
            }

        }

        if(mEatingCurrent > 0)
        {
            auto newEatTime = mEatingCurrent - elapsed;
            mEatingCurrent = newEatTime;
            if(mEatingCurrent <= 0)
            {
                mEatingCurrent = 0;
                mCheckEating = false;
            }
        }
    }

}

/**
 * Draws the sparty movements
 * @param graphics
 *
 */
void Sparty::Draw(std::shared_ptr<wxGraphicsContext> graphics)
{

    if(mCheckHeadbutt)
    {

        double headAngle = 0;

        if(mHeadButtCurrent > 0)
        {
            if(mHeadButtCurrent < HeadbuttTime/2)
            {
                headAngle = mHeadButtCurrent/(HeadbuttTime/2) * mHeadPivotAngle;
            }
            else
            {
                headAngle = (HeadbuttTime-mHeadButtCurrent)/(HeadbuttTime/2) * mHeadPivotAngle;
            }
        }

        int x = int(GetX() * mGame->GetTileWidth());

        int y = int((GetY() + 1) * mGame->GetTileHeight() - GetHeight());

        graphics->PushState();

        graphics->Translate(x , y);
        graphics->Translate(mHeadPivotX, mHeadPivotY);
        graphics->Rotate(headAngle);
        graphics->Translate(-mHeadPivotX, -mHeadPivotY);



        if (mSpartyBitmap.IsNull())
        {
            mSpartyBitmap = graphics->CreateBitmapFromImage(*mSpartyImage);
        }
        graphics->DrawBitmap(mSpartyBitmap,
                             0,
                             0, GetWidth(), GetHeight());

        graphics->PopState();

    }


    else if(mCheckEating)
    {

        double mouthAngle = 0;

        if(mEatingCurrent > 0)
        {
            if(mEatingCurrent < EatingTime/2)
            {
                mouthAngle = mEatingCurrent/(EatingTime/2) * mMouthPivotAngle;
            }
            else
            {
                mouthAngle = (EatingTime-mEatingCurrent)/(EatingTime/2) * mMouthPivotAngle;
            }
        }


        int x = int(GetX() * mGame->GetTileWidth());
        int y = int((GetY() + 1) * mGame->GetTileHeight() - GetHeight());

        graphics->PushState();

        graphics->Translate(x , y);
        graphics->Translate(mMouthPivotX, mMouthPivotY);
        graphics->Rotate(mouthAngle);
        graphics->Translate(-mMouthPivotX, -mMouthPivotY);



        if (mSpartyBitmap.IsNull())
        {
            mSpartyBitmap = graphics->CreateBitmapFromImage(*mSpartyImage);
        }

        graphics->DrawBitmap(mSpartyBitmap,
                             0,
                             0, GetWidth(), GetHeight());


        graphics->PopState();
    }
    else
    {
        Item::Draw(graphics);
    }

}



/**
 * Updates the current eating time
 *
 */
void Sparty::Eat()
{
    mEatingCurrent = EatingTime;
}

/**
 * Start the Headbutt Timer
 */
void Sparty::SetHeadButtTime()
{
    mHeadButtCurrent = HeadbuttTime;
}




