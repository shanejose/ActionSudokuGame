/**
 * @file Game.h
 * @author Shane Jose
 *
 * class GameView that will be responsible for drawing itself
 */

#ifndef PROJECT1_PROJECT1LIB_GAME_H
#define PROJECT1_PROJECT1LIB_GAME_H

#include <vector>
#include <wx/string.h>
#include<memory>
#include "Item.h"
#include "Level.h"
#include "Sparty.h"
#include "ErrorMessage.h"
#include "XRay.h"
#include <random>

class Level;
class Sparty;
class ItemVisitor;

/**
 * class Game that will be responsible for drawing itself
 *
 */
class Game
{
private:

    /// Random number generator
    std::mt19937 mRandom;

    /// Pointer to Level Object
    std::shared_ptr<Level> mLevel;

    /// The item bitmap
    wxGraphicsBitmap mBackgroundBitmap; ///< Background image to use

    /// The underlying background image
    std::shared_ptr<wxImage> mBackgroundImage;

    /// Head of the sparty object
    std::shared_ptr<Sparty> mSpartyHead;

    /// mouth of the sparty object
    std::shared_ptr<Sparty> mSpartyMouth;

    /// Head of the xray object
    std::shared_ptr<XRay> mXray;

    ///board row
    int mRow;
    ///board col
    int mCol;

    ///duration of dialogue box
    double mDialogueDuration = 3.0;

    /// All of the items to populate our game
    std::vector<std::shared_ptr<Item>> mItems;

    /// store the current time of the game
    double mStoreTime = 0;

    /// Level Width
    int mLevelWidth;

    /// Level Height
    int mLevelHeight;

    /// Tile Width
    int mTileWidth;

    /// Tile Height
    int mTileHeight;

    /// scale the background
    double mScale;

    /// x offset for the screen
    double mXOffset;

    /// y offset for the screen
    double mYOffset;

    /// sets true if dialogue is visible
    bool mDialogueVisible = true;

    /// sets true if level complete dialogue is visible
    bool mCompleteDialogueVisible = false;

    /// sets true if level incorrect dialogue is visible
    bool mIncorrectDialogueVisible = false;

    /// current level of the game
    int mCurrentLevel = 1;

    /// level dialogues of the game
    std::vector<std::wstring> mLevelDialogues;

    /// checks when to play the music
    bool mPlaySound = false;

    ///vector of messages
    std::vector<std::string> mMessages;


    /// vector of Error Messages
    std::vector<std::shared_ptr<ErrorMessage>> mErrorList;




public:
    Game();




    void OnDraw(std::shared_ptr<wxGraphicsContext> graphics, int width, int height);

    void Update(double elapsed);

    /**
     * Sets the new location for Sparty
     * @param spartyHead sets the location of the head of the sparty
     */
    void SetSpartyHead(std::shared_ptr<Sparty> spartyHead) { mSpartyHead = spartyHead; };

    /**
     * Sets the new location for Sparty
     *
     * @param spartyMouth sets the location of the mouth of the sparty
     */
    void SetSpartyMouth(std::shared_ptr<Sparty> spartyMouth) { mSpartyMouth = spartyMouth; };

    /**
     * Sets XRay
     *
     * @param xray
     */
    void SetXRay(std::shared_ptr<XRay> xray) { mXray = xray; };

    void Clear();
    void Load(const wxString &filename);
    void Add(std::shared_ptr<Item> item);


    /**
     * Sets visibility of the incorrect message
     * @param check boolean value
     */
    void SetIncorrectDialogue(bool check){mIncorrectDialogueVisible = check;}

    /**
     * Sets visibility of the correct message
     * @param check boolean value
     */
    void SetCompleteDialogue(bool check){mCompleteDialogueVisible = check;}
    void SetLevelParameters(int levelHeight, int levelWidth, int tileHeight, int tileWidth);
    /**
     * Sets the board coordinates to the specified row and column
     * @param row new row value for the board coordinates
     * @param col new column value for the board coordinates
     */
    void SetBoardCoordinates(int row, int col)
    {
        mRow = row;
        mCol = col;
    };

    void SpartyMovement(double x, double y);

    void SpartyMouthMovement(double x, double y);

    void SpartyHeadButtMovement();

    void SpartyEatingMovement();

    void Accept(ItemVisitor *visitor);

    /**
     * Get Tile Width
     * @return Tile Width
     */
    int GetTileWidth() { return mTileWidth; }

    /**
     * Get Tile Height
     * @return Tile height
     */
    int GetTileHeight() { return mTileHeight; }

    /**
     * Get Board Row
     * @return board row
     */
    int GetBoardRow() { return mRow; }

    /**
     * Get Board Row
     * @return board row
     */
    int GetBoardCol() { return mCol; }

    /**
     * Reset Scoreboard Timer
     */
    void ResetTimer();

    /**
     * Return the Size of the Array (For Testing)
     * @return
     */
    int GetItemsArrayLength() { return mItems.size(); }
    void Solve();
    void LevelDialogue(std::shared_ptr<wxGraphicsContext> graphics, std::wstring message);

    bool SpartyRegurgitate(int key);

    bool Eat();

    /**
     * Set Current Level of Game
     * @param x Level Value
     */
    void SetLevel(int x) { mCurrentLevel = x; }

    /**
     * Go to Next Level
     */
    void NextLevel();
    //virtual void Add(std::shared_ptr<Digits> digit);

    void Headbutt();

    /**
     * Get the random number generator
     * @return Pointer to the random number generator
     */
    std::mt19937 &GetRandom() { return mRandom; }

    std::shared_ptr<Item> DigitHitTest(int x, int y);

    /**
     * Sets the visibility of the dialogue box
     * @param visible boolean value
     */
    void SetDialogueVisible(bool visible) { mDialogueVisible = visible; }

    /**
     * Sets the duration for displaying the dialogue box
     * @param duration duration (in seconds) for displaying the dialogue box
     */
    void SetDialogueDuration(double duration) { mDialogueDuration = duration; }

    /**
     * Sets the condition true to play music for level 3
     * @param check
     */
    void TurnOnSound(bool check) { mPlaySound = check; }

    void CheckSol();
    void DisplayErrorMessage(std::shared_ptr<wxGraphicsContext> graphics, int positionY);
    void DisplayComplete(std::shared_ptr<wxGraphicsContext> graphics);
    void DisplayIncorrect(std::shared_ptr<wxGraphicsContext> graphics);

    void RemoveAndInsertSparty();


    /**
     * Adds a message to the game's message list for displaying
     * @param errorMsge error message object to be added to the list.
     *
     */
    void AddErrorMsg(std::shared_ptr<ErrorMessage> errorMsge) {mErrorList.push_back(errorMsge);}


    void LoadNewLevel();
};

#endif //PROJECT1_PROJECT1LIB_GAME_H
