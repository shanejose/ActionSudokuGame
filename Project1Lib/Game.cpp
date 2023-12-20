/**
 * @file Game.cpp
 * @author Shane Jose
 *
 */

#include "pch.h"
#include "Game.h"
#include "Level.h"
#include "Sparty.h"
#include "ContainerVisitor.h"
#include "DigitVisitor.h"
#include "RedDigit.h"
#include "ErrorMessage.h"
#include <iomanip>
#include <sstream>
#include <string>



/// Size of the scoreboard text in virtual pixels
const int ScoreboardTextSize = 64;

using namespace std;

/**
 * location of the scoreboard
 * @return x and y location of scoreboard
 *
 */
const wxPoint ScoreboardTopLeft(10, 10);

/// file name for music
const wstring musicFileName = L"resources/sounds/Band.wav";



/**
 * Game Constructor
 *
 */
Game::Game()
{

    // Seed the random number generator
    std::random_device rd;
    mRandom.seed(rd());
}

/**
 * Draw the Game
 * @param graphics displays the background
 * @param width width of the background
 * @param height height of the background
 *
 */
void Game::OnDraw(std::shared_ptr<wxGraphicsContext> graphics, int width, int height)
{

    int pixelWidth = mLevelWidth * mTileWidth;
    int pixelHeight = mLevelHeight * mTileHeight;

    //
    // Automatic Scaling
    //
    auto scaleX = double(width) / double(pixelWidth);
    auto scaleY = double(height) / double(pixelHeight);
    mScale = std::min(scaleX, scaleY);

    mXOffset = (width - pixelWidth * mScale) / 2.0;
    mYOffset = 0;
    if (height > pixelHeight * mScale)
    {
        mYOffset = (double)((height - pixelHeight * mScale) / 2.0);
    }

    graphics->PushState();

    graphics->Translate(mXOffset, mYOffset);
    graphics->Scale(mScale, mScale);

    for(auto item: mItems){
        item->Draw(graphics);
    }



    if (mDialogueVisible) {
        // Draw the white rectangle.
        wxBrush brush(*wxWHITE);
        graphics->SetBrush(brush);
        graphics->DrawRectangle(80,200,700,350);
        if(mCurrentLevel==1){
            LevelDialogue(graphics, L"Level 1 Begin!");
        } else if(mCurrentLevel==2){
            LevelDialogue(graphics, L"Level 2 Begin!");
        } else if(mCurrentLevel==3){
            LevelDialogue(graphics, L"Level 3 Begin!");
        }
    } else {
        // Only draw the timer when the dialogue is not visible
        int minutes = (int)mStoreTime / 60; // Calculate minutes
        int seconds = (int)mStoreTime % 60;

        auto fontStyle = graphics->CreateFont(ScoreboardTextSize, "Arial", wxFONTFLAG_BOLD,*wxWHITE);

        graphics->SetFont(fontStyle);
        wstringstream time;
        time << setw(2) << setfill(L' ')<< minutes << L":" << setw(2) << setfill(L'0') << seconds << ends;
        graphics->DrawText(time.str(), ScoreboardTopLeft.x, ScoreboardTopLeft.y);
    }
    if(mCompleteDialogueVisible){
        DisplayComplete(graphics);
    }
    if(mIncorrectDialogueVisible){
        DisplayIncorrect(graphics);
    }

    for(auto errorMsge: mErrorList)
    {
        errorMsge->Draw(graphics);
    }


    graphics->PopState();
}

/**
 * Handle updates for animation
 * @param elapsed The time since the last update
 */
void Game::Update(double elapsed)
{

    if (mDialogueVisible) {
        // If the dialogue is visible, decrease the dialogue duration
        mDialogueDuration -= elapsed;

        if (mDialogueDuration <= 0.0) {
            // If the dialogue duration has elapsed, hide the dialogue, reset the timer, and allow Sparty to move
            mDialogueVisible = false;
            mStoreTime = 0.0;  // Reset the timer
            // Allow Sparty to move
            mSpartyHead->StopSpartyMovement(true);
            mSpartyMouth->StopSpartyMovement(true);
        }
    } else {
        // If the dialogue is not visible, continue updating the timer
        mStoreTime += elapsed;
    }

    if(mCompleteDialogueVisible)
    {
        mDialogueDuration -= elapsed;
        if(mDialogueDuration <= 0.0)
        {
            mCompleteDialogueVisible = false;
            LoadNewLevel();
        }
    }

    if(mIncorrectDialogueVisible)
    {
        mDialogueDuration -= elapsed;
        if(mDialogueDuration <= 0.0)
        {
            mIncorrectDialogueVisible = false;
            LoadNewLevel();
        }
    }

    for (auto Item : mItems)
    {
            Item->Update(elapsed);
    }

    for(auto errorMsg: mErrorList)
    {
        errorMsg->Update(elapsed);
    }
}

/**
 * Loads the level from XML file
 *
 * Open the XML file and reads the nodes, creating items as appropriate
 * @param filename  The filename of the file being loaded.
 */
void Game::Load(const wxString &filename)
{
    mLevel = std::make_shared<Level>(this);

    if(mPlaySound)
    {
        mLevel->LevelThreeSoundPlay(musicFileName);
        TurnOnSound(false);
    }
    mLevel->Load(filename);
}

/**
 * Add an Item to List of Items in Game
 * @param item  New item to add
 */
void Game::Add(std::shared_ptr<Item> item)
{
    mItems.push_back(item);
}

/**
 * Set the Level Parameters
 * @param levelHeight Height Attribute of Level
 * @param levelWidth  Width Attribute of Level
 * @param tileHeight Tile Height of Level
 * @param tileWidth Tile Width of Level
 */
void Game::SetLevelParameters(int levelHeight, int levelWidth, int tileHeight, int tileWidth)
{
    mLevelHeight = levelHeight;
    mLevelWidth = levelWidth;
    mTileWidth = tileWidth;
    mTileHeight = tileHeight;
}

/**
 * Clear the game data.
 *
 * Deletes all known items in Game Object
 */
void Game::Clear()
{
    mItems.clear();
}

/**
 * Reset the timer when playing new game
 *
 */
void Game::ResetTimer()
{
    mStoreTime = 0;
}


/**
 * Moves the head of the sparty to where the user clicked
 * @param x x location of where sparty moves to
 * @param y y location of where sparty moves to
 */
void Game::SpartyMovement(double x, double y)
{

    double pixelX = (x - mXOffset) / mScale;
    double pixelY = (y - mYOffset) / mScale;

    int pixelWidth = mLevelWidth * mTileWidth;
    int pixelHeight = mLevelHeight * mTileHeight;

    if((pixelX > 0 && pixelX < pixelWidth) && (pixelY > 0 && pixelY < pixelHeight))
    {

        if(pixelX < mSpartyHead->GetWidth())
        {
            pixelX += mSpartyHead->GetXOffset();
        }

        if(pixelY > pixelHeight - mSpartyHead->GetYOffset())
        {
            pixelY = pixelHeight - mSpartyHead->GetYOffset();
        }

        if(pixelY < mSpartyHead->GetYOffset())
        {
            pixelY += mSpartyHead->GetYOffset();
        }

        mSpartyHead->SetMovetoLocation(pixelX/mTileWidth, pixelY/mTileHeight);
        mSpartyHead->SetSpartyMovement(true);
    }


}


/**
 * Moves the mouth of the sparty to where the user clicked
 * @param x x location of where sparty moves to
 * @param y y location of where sparty moves to
 */
void Game::SpartyMouthMovement(double x, double y)
{
    double pixelX = (x - mXOffset) / mScale;
    double pixelY = (y - mYOffset) / mScale;

    int pixelWidth = mLevelWidth * mTileWidth;
    int pixelHeight = mLevelHeight * mTileHeight;

    if((pixelX > 0 && pixelX < pixelWidth) && (pixelY > 0 && pixelY < pixelHeight))
    {
        if(pixelX < mSpartyMouth->GetWidth())
        {
            pixelX += mSpartyMouth->GetXOffset();
        }

        if(pixelY > pixelHeight - mSpartyMouth->GetYOffset())
        {
            pixelY = pixelHeight - mSpartyMouth->GetYOffset();
        }

        if(pixelY < mSpartyMouth->GetYOffset())
        {
            pixelY += mSpartyMouth->GetYOffset();
        }

        mSpartyMouth->SetMovetoLocation(pixelX/mTileWidth, pixelY/mTileHeight);
        mSpartyMouth->SetSpartyMovement(true);
    }

}


/**
 * Solves the sudoku board
 *
 */
void Game::Solve()
{
    mLevel->Solve(mItems);
}

/**
 * Check solution of the game
 *
 */
void Game::CheckSol()
{
    if(mLevel->IsBoardFull(mItems)){
        if(mLevel->CheckSolution(mItems)){
            NextLevel();
        }else{
            SetIncorrectDialogue(true);
            mSpartyHead->StopSpartyMovement(false);
            mSpartyMouth->StopSpartyMovement(false);
            mDialogueDuration = 2;
        }
    }

}

/**
 * Display Level Intro messages
 * @param graphics displays the messages
 * @param message intro messages for levels
 */
void Game::LevelDialogue(std::shared_ptr<wxGraphicsContext> graphics, std::wstring message)
{
    graphics->PushState();

    // Set font and color for the text
    wxFont font(wxSize(0, 80),
                wxFONTFAMILY_SWISS,
                wxFONTSTYLE_NORMAL,
                wxFONTWEIGHT_BOLD);
    wxColour color(65, 172, 10);
    graphics->SetFont(font, color);
    graphics->DrawText(message, 200, 210);



    // Set font and color for the additional instructions (smaller font size).
    wxFont font2(wxSize(0, 50),
                 wxFONTFAMILY_SWISS,
                 wxFONTSTYLE_NORMAL,
                 wxFONTWEIGHT_BOLD);
    wxColour color2(0, 0, 0);
    graphics->SetFont(font2, color2);
    graphics->DrawText(L"space: Eat", 280, 320);
    graphics->DrawText(L"0-8: Regurgitate", 250, 380);
    graphics->DrawText(L"B: Headbutt", 280, 440);

    graphics->PopState();
}

/**
 * Sets the Headbutt time and Sets flag for sparty to headbutt
 *
 */
void Game::SpartyHeadButtMovement()
{
    mSpartyHead->SetHeadButtTime();
    mSpartyHead->CheckSpartyHeadbutt(true);
    mSpartyMouth->SetHeadButtTime();
    mSpartyMouth->CheckSpartyHeadbutt(true);
    Headbutt();
}

/**
 * Handle Visitor for Headbutt
 */
void Game::Headbutt()
{
    ContainerVisitor visitor;
    visitor.SetTileWidthHeight(mTileWidth, mTileHeight);
    this->Accept(&visitor);
    bool hit = visitor.GetRangeFlag();
    if (hit)
    {
        // Remove all the items from Cauldron or Pumpkin containers
        auto container = visitor.GetMainContainer();
        container->RandomizeDigitLocations(mItems);
    }
}

/**
 * Sets the eating time and Sets flag for sparty to eat
 *
 */
void Game::SpartyEatingMovement()
{
    mSpartyMouth->Eat();
    mSpartyMouth->CheckSpartyEating(true);
}

/**
 * Eat a Red Digit Object and Store in XRay
 * @return bool
 */
bool Game::Eat()
{
    DigitVisitor visitor;
    visitor.SetTileWidthHeight(mTileWidth, mTileHeight);
    visitor.SetSparty(mSpartyMouth);
    // First Pass to Get the XRay Pointer
    Accept(&visitor);

    auto digit = visitor.GetRedDigit();
    if (digit != nullptr && !digit->IsContained())
    {
        auto xray = visitor.GetXRay();
        for (auto item: mItems)
        {
            if (item.get() == digit)
            {
                if (!xray->GetIsFullFlag())
                {
                    auto newItem = item;
                    xray->Add(newItem);
                    auto loc = find(begin(mItems), end(mItems), newItem);
                    if(loc != end(mItems))
                    {
                        mItems.erase(loc);
                        break;
                    }

                }
                else {
                    return true;

                }
            }
        }

    }
    return false;
}

/**
 * Test an x,y click location to see if it clicked
 * on some item in the game.
 * @param x X location in pixels
 * @param y Y location in pixels
 * @returns Pointer to item we clicked on or nullptr if none.
*/
std::shared_ptr<Item> Game::DigitHitTest(int x, int y)
{

    for(auto item : mItems)
    {
        if(item->GetX() == x && item->GetY() == y && item != mSpartyMouth && item !=mSpartyHead){;
            return item;
        }
    }
    return nullptr;
}



/**
 * We are passed a pointer to a sparty that regurgitates. We check to see
 * if there are any digits it is currently over. If not, regurgitate
 *
 * @param key The item that is doing the regurgitating
 * @return true if a item is regurgitated
 */
bool Game::SpartyRegurgitate(int key)
{

    mSpartyMouth->CheckSpartyEating(false);

    double x = (mSpartyMouth->GetX() + 1);
    double y = (mSpartyMouth->GetY());
    double xFrac, yFrac, xInt, yInt;

    xFrac = modf(x, &xInt);
    yFrac = modf(y, &yInt);

    if(xFrac < 0.5){
        x = floor(x);
    }

    if(xFrac > 0.5){
        x = ceil(x);
    }

    if(yFrac < 0.5){
        y = floor(y);
    }

    if(yFrac > 0.5){
        y = ceil(y);
    }

    std::shared_ptr<Item> itemAtMouth = DigitHitTest(x,y);

    if(!itemAtMouth){
        mSpartyMouth->CheckSpartyEating(true);
        mXray->SpitDigit(key, x, y);
    }
    else
    {
        return true;

    }

    return false;
}


/**
 * Accepts the visitor to the game
 * @param visitor Item Visitor
 */
void Game::Accept(ItemVisitor* visitor)
{
    for (auto i = mItems.rbegin(); i != mItems.rend(); i++)
    {
        (*i)->Accept(visitor);
    }


}


void Game::NextLevel() {
    SetCompleteDialogue(true);
    mSpartyHead->StopSpartyMovement(false);
    mSpartyMouth->StopSpartyMovement(false);
    mDialogueDuration = 2;
    mCurrentLevel = (mCurrentLevel + 1) % 4;
}






/**
 * Display "Level Complete!" message
 * @param graphics displays text
 */
void Game::DisplayComplete(std::shared_ptr<wxGraphicsContext> graphics){
    graphics->PushState();

    // Set font and color for the text
    wxFont font(wxSize(100, 100),
                wxFONTFAMILY_SWISS,
                wxFONTSTYLE_NORMAL,
                wxFONTWEIGHT_BOLD);
    wxColour color(65, 172, 10);
    graphics->SetFont(font, color);
    graphics->DrawText(L"Level Complete!", 100, 300);

    graphics->PopState();

}

/**
 * Display "Incorrect!" message
 * @param graphics displays text
 */
void Game::DisplayIncorrect(std::shared_ptr<wxGraphicsContext> graphics){
    graphics->PushState();

    // Set font and color for the text
    wxFont font(wxSize(60, 70),
                wxFONTFAMILY_SWISS,
                wxFONTSTYLE_NORMAL,
                wxFONTWEIGHT_BOLD);
    wxColour color(65, 172, 10);
    graphics->SetFont(font, color);
    graphics->DrawText(L"Incorrect!", 280, 320);

    graphics->PopState();

}



/**
 * Remove and Insert Sparty at End of mItems Vector
 */
void Game::RemoveAndInsertSparty()
{
    // Readjust Head
    auto headLoc = find(begin(mItems), end(mItems), mSpartyHead);
    if (headLoc != end(mItems))
    {
        auto itemToRemove = *headLoc;
        mItems.erase(headLoc);
        mItems.push_back(itemToRemove);
    }

    // Readjust Mouth
    auto mouthLoc = find(begin(mItems), end(mItems), mSpartyMouth);
    if (mouthLoc != end(mItems))
    {
        auto itemToRemove = *mouthLoc;
        mItems.erase(mouthLoc);
        mItems.push_back(itemToRemove);
    }
}

/**
 * Load a new level
 */
void Game::LoadNewLevel()
{
    if (mCurrentLevel == 0)
    {
        const wstring level0FileName = L"resources/levels/level0.xml";
        ResetTimer();
        Load(level0FileName);
        SetDialogueVisible(true);
        mDialogueDuration = 3;
    }
    if (mCurrentLevel == 1)
    {
        const wstring level1FileName = L"resources/levels/level1.xml";
        ResetTimer();
        Load(level1FileName);
        SetDialogueVisible(true);
        mDialogueDuration = 3;
    }
    if (mCurrentLevel == 2)
    {
        const wstring level2FileName = L"resources/levels/level2.xml";
        ResetTimer();
        Load(level2FileName);
        SetDialogueVisible(true);
        mDialogueDuration = 3;
    }
    if (mCurrentLevel == 3)
    {
        const wstring level3FileName = L"resources/levels/level3.xml";
        ResetTimer();
        TurnOnSound(true);
        Load(level3FileName);
        SetDialogueVisible(true);
        mDialogueDuration = 3;
    }
}


