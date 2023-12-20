/**
 * @file Level.cpp
 * @author Areeb Islam
 */

#include "pch.h"
#include "Level.h"
#include "Digits.h"
#include "XRay.h"
#include "Background.h"
#include "Pumpkin.h"
#include "Cauldron.h"
#include "RedDigit.h"



using namespace std;

/// Image directory to access all the images
const wstring imageDir= L"resources/images/";

///number of columns/rows in a sudoku board
const int boardLen = 9;

/**
 * Constructor
 * @param game game the user is playing
 */
Level::Level(Game *game)
{
    mGame = game;

}

/**
 * Load the data from a XML file.
 *
 * Opens the XML file and reads the nodes, creating items as appropriate.
 *
 * @param filename The filename of the file to load the game from.
 */
void Level::Load(const wxString &filename)
{
    wxXmlDocument xmlDoc;
    if(!xmlDoc.Load(filename))
    {
        wxMessageBox(L"Unable to load the Level File");
        return;
    }

    // Clear the Game Array
    mGame->Clear();

    auto root = xmlDoc.GetRoot();
    double tileWidth;
    double tileHeight;
    double levelWidth;
    double levelHeight;
    root->GetAttribute(L"width", L"0").ToDouble(&levelWidth);
    root->GetAttribute(L"height", L"0").ToDouble(&levelHeight);
    root->GetAttribute(L"tilewidth", L"0").ToDouble(&tileWidth);
    root->GetAttribute(L"tileheight", L"0").ToDouble(&tileHeight);

    mGame->SetLevelParameters(levelHeight, levelWidth, tileHeight, tileWidth);

    // Traverse the children of the root

    auto child = root->GetChildren();
    for(; child; child = child->GetNext())
    {
        auto name = child->GetName();
        if (name == L"declarations")
        {
            ProcessDeclarations(child);
        }

        if (name == L"game")
        {
            ProcessGameSolution(child);
        }

        if (name == L"items")
        {
            ProcessItems(child);
        }
    }

}

/**
 * Process all declarations
 * @param node all declaration nodes of XML Node
 */
void Level::ProcessDeclarations(wxXmlNode* node)
{
    auto child = node->GetChildren();

    for (; child; child = child->GetNext())
    {
        auto name = child->GetName();
        auto imgID = child->GetAttribute(L"id");
        mItemMap[imgID] = child;
    }
}

/**
 * Process the Solution to the Game
 * @param node all Game Nodes for Solution
 */
void Level::ProcessGameSolution(wxXmlNode* node)
{
    node->GetAttribute(L"col", L"0").ToInt(&mCol);
    node->GetAttribute(L"row", L"0").ToInt(&mRow);

    mGame->SetBoardCoordinates(mRow, mCol);
    std::wstring content(node->GetNodeContent().ToStdWstring());
    mDigitsArray = wxSplit(content, ' ');
}

/**
 * Define the actual items appearing in the level
 * Set the locations of the items
 * @param node XML Node for items
 */
void Level::ProcessItems(wxXmlNode* node)
{
    auto child = node->GetChildren();

    for (; child; child = child->GetNext())
    {
        auto name = child->GetName();
        auto imgID = child->GetAttribute(L"id");
        double x; double y;

        child->GetAttribute(L"col", L"0").ToDouble(&x);
        child->GetAttribute(L"row", L"0").ToDouble(&y);

        auto declarationNode = mItemMap[imgID];

        auto imgFileName = declarationNode->GetAttribute(L"image");
        auto image = imageDir + imgFileName.ToStdWstring();

        if (mItemMap.find(imgID) != mItemMap.end())
        {
            if(name == L"xray")
            {
                int capacity;
                declarationNode->GetAttribute(L"capacity", L"0").ToInt(&capacity);
                auto xray = make_shared<XRay>(mGame, image, capacity, node);
                xray->SetLocation(x, y);
                Add(xray);
                mGame->SetXRay(xray);
            }

            if(name == L"given")
            {
                auto digit = make_shared<Digits>(mGame, image, node);
                digit->SetLocation(x, y);
                Add(digit);
            }

            if (name == L"digit")
            {
                auto red = make_shared<RedDigit>(mGame, image, node);
                red->SetLocation(x, y);
                Add(red);
            }

            if(name == L"background")
            {
                auto background = make_shared<Background>(mGame, image);
                background->SetLocation(x, y);
                Add(background);
            }

            if(name == L"sparty")
            {
                auto headFileName = declarationNode->GetAttribute(L"image1");
                auto head = imageDir + headFileName.ToStdWstring();
                auto spartyHead = make_shared<Sparty>(mGame, head, declarationNode);
                spartyHead->SetLocation(x, y);
                Add(spartyHead);
                mGame->SetSpartyHead(spartyHead);

                auto mouthFileName = declarationNode->GetAttribute(L"image2");
                auto mouth = imageDir + mouthFileName.ToStdWstring();
                auto spartyMouth = make_shared<Sparty>(mGame,mouth, declarationNode);
                spartyMouth->SetLocation(x,y);
                Add(spartyMouth);
                mGame->SetSpartyMouth(spartyMouth);
            }

            if(name == L"container")
            {
                auto frontFileName = declarationNode->GetAttribute(L"front");
                auto front = imageDir + frontFileName.ToStdWstring();

                if (imgFileName == "pumpkin.png")
                {
                    auto pumpkin = make_shared<Pumpkin>(mGame, image, child);
                    pumpkin->SetLocation(x, y);
                    Add(pumpkin);
                    ProcessContainerDigits(child, pumpkin);

                    auto pumpkinFront = make_shared<Pumpkin>(mGame, front, child);
                    pumpkinFront->SetLocation(x, y);
                    Add(pumpkinFront);
                }
                if (imgFileName == "cauldron.png")
                {
                    auto cauldron = make_shared<Cauldron>(mGame, image, child);
                    cauldron->SetLocation(x , y);
                    Add(cauldron);
                    ProcessContainerDigits(child, cauldron);

                    auto cauldronFront = make_shared<Cauldron>(mGame, front, child);
                    cauldronFront->SetLocation(x, y);
                    Add(cauldronFront);
                }
            }

        }
    }
}

/**
 * Add an Item to List of Items in Game
 * @param item  New item to add
 */
void Level::Add(std::shared_ptr<Item> item)
{
    mGame->Add(item);
}
/**
 * Processes the digits that is in the container
 * @param node
 * @param container
 */
void Level::ProcessContainerDigits(wxXmlNode* node, std::shared_ptr<Container> container)
{
    auto child = node->GetChildren();

    for (; child; child = child->GetNext())
    {
        auto name = child->GetName();
        auto imgID = child->GetAttribute(L"id");
        double x; double y;

        child->GetAttribute(L"col", L"0").ToDouble(&x);
        child->GetAttribute(L"row", L"0").ToDouble(&y);

        auto containerNode = mItemMap[imgID];

        if(name == L"digit")
        {
            auto imgFileName = containerNode->GetAttribute(L"image");
            auto image = imageDir + imgFileName.ToStdWstring();
            auto digit = make_shared<RedDigit>(mGame, image, node);
            digit->SetLocation(x, y);
            Add(digit);
            container->Add(digit);
            digit->SetContained(true);
        }

    }
}

/**
 * Solves the Sudoku board
 * @param items
 */
void Level::Solve(std::vector<std::shared_ptr<Item>> items)
{
    int col = mCol;
    int row = mRow;

    double startCol = col;
    for(auto digitStr: mDigitsArray){

        std::wstring expectedRedFilename = imageDir + digitStr.ToStdWstring() + L"r.png";
        std::wstring expectedBlackFilename = imageDir + digitStr.ToStdWstring() + L"b.png";

        for(auto item : items )
        {
            if (item->GetX() == col and item->GetY() == row){
                if(item->GetFilename() != expectedRedFilename && item->GetFilename() != expectedBlackFilename){
                    item->SetLocation(0,0);
                    item->SetPositioned(false);
                }
            }

        }

        for(auto item : items )
        {
            if(item->IsContained()){
                continue;
            }
            if ((item->GetFilename() == expectedBlackFilename || item->GetFilename() == expectedRedFilename) && item->GetX() == col && item->GetY() == row)
            {
                break;
            }
            if(item->GetFilename() == expectedRedFilename && !item->IsPositioned())
            {
                item->SetLocation(col, row);
                item->SetPositioned(true);
                break;
            }

        }

        col++;
        if(col >= (startCol + boardLen))
        {
            col = startCol;
            row++;
        }

    }
    mGame->CheckSol();
}
/**
 * Creates and plays Level Three background sound
 * @param filename filename of the sound to be played
 */
void Level::LevelThreeSoundPlay(const wxString &filename)
{
    mLevelThreeSound.Create(filename);

    if(mLevelThreeSound.IsOk())
    {
        mLevelThreeSound.Play(wxSOUND_ASYNC | wxSOUND_LOOP);
    }



}

/**
 * Checks the solution of the sudoku board
 * @param items
 * @return bool, true if solution is true otherwise false
 */
bool Level::CheckSolution(std::vector<std::shared_ptr<Item>> items){
    int col = mCol;
    int row = mRow;

    for(auto digitStr: mDigitsArray){
        std::wstring expectedRedFilename = imageDir + digitStr.ToStdWstring() + L"r.png";
        std::wstring expectedBlackFilename = imageDir + digitStr.ToStdWstring() + L"b.png";

        bool found = false;
        for(auto item : items ){
            if((item->GetFilename() == expectedRedFilename || item->GetFilename() == expectedBlackFilename) && (item->GetX() == col && item->GetY() == row) )
            {
                found = true;
                break;
            }
        }

        if(!found){
            return false;
        }

        col++;
        if(col >= (mCol + boardLen)){
            col = mCol;
            row++;
        }

    }
    return true;
}

/**
 * Checks if the board is full
 * @param items
 * @return bool true if board is full otherwise false
 */
bool Level::IsBoardFull(std::vector<std::shared_ptr<Item>> items){
    int startCol = mCol;
    int startRow = mRow;

    for(int row=0; row < boardLen; ++row){
        for(int col =0; col < boardLen; ++col)
        {
            bool found = false;
            for(auto item : items ){
                if(item->GetX() == (startCol + col) && item->GetY() == (startRow + row))
                {
                    found = true;
                    break;
                }
            }

            if(!found){
                return false;
            }
        }

    }
    return true;
}