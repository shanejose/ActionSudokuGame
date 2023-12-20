/**
 * @file Level.h
 * @author Areeb Islam
 *
 * Class used to Draw the Levels
 */

#ifndef PROJECT1_PROJECT1LIB_LEVEL_H
#define PROJECT1_PROJECT1LIB_LEVEL_H


#include "Digits.h"
#include "Container.h"
#include<map>
#include <wx/wx.h>
#include <wx/sound.h>

class Game;
/**
 * Class for Drawing Levels
 */
class Level
{
private:
    /// The game object of this system
    Game *mGame;

    /// The map that keeps track of the IDs of items created
    ///to place it in its position
    std::map<wxString, wxXmlNode*> mItemMap;

    ///Level solution digits
    wxArrayString mDigitsArray;

    ///board row
    int mRow;
    ///board col
    int mCol;

    ///Level Three Sound Member Variable
    wxSound mLevelThreeSound;

public:

    /// Default constructor (disabled)
    Level() = delete;

    /// Copy constructor (disabled)
    Level(const Level &) = delete;

    /// Assignment operator
    void operator=(const Level &) = delete;

    Level(Game *game);
    void Load(const wxString &filename);
    void ProcessDeclarations(wxXmlNode *node);
    void ProcessGameSolution(wxXmlNode *node);
    void ProcessItems(wxXmlNode *node);
    void Add(std::shared_ptr<Item> item);
    void ProcessContainerDigits(wxXmlNode *node, std::shared_ptr<Container> container);
    void Solve(std::vector<std::shared_ptr<Item>> items);
    void LevelThreeSoundPlay(const wxString &filename);
    bool CheckSolution(std::vector<std::shared_ptr<Item>> items);
    bool IsBoardFull(std::vector<std::shared_ptr<Item>> items);
};

#endif //PROJECT1_PROJECT1LIB_LEVEL_H
