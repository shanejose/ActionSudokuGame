/**
 * @file GameTest.cpp
 * @author Shane Jose
 */

#include <pch.h>
#include "gtest/gtest.h"
#include <Game.h>
#include <regex>
#include <string>
#include <fstream>
#include <streambuf>
#include <wx/filename.h>

using namespace std;


class GameTest : public ::testing::Test {
protected:

    /**
     * Create a path to place temporary files
     */
    wxString TempPath()
    {
        // Create a temporary filename we can use
        auto path = wxFileName::GetTempDir() + L"/game";
        if(!wxFileName::DirExists(path))
        {
            wxFileName::Mkdir(path);
        }

        return path;

    }

    /**
    * Read a file into a wstring and return it.
    * @param filename Name of the file to read
    * @return File contents
    */
    wstring ReadFile(const wxString &filename)
    {
        ifstream t(filename.ToStdString());
        wstring str((istreambuf_iterator<char>(t)),
                    istreambuf_iterator<char>());
        return str;
    }

    /**
     * Test to ensure an xml file is empty
     */
    void TestRoot(wxString filename)
    {
        cout << "Temp file: " << filename << endl;

        auto xml = ReadFile(filename);
        cout << xml << endl;

        ASSERT_TRUE(regex_search(xml, wregex(L"<\\?xml.*\\?>")));
        ASSERT_TRUE(regex_search(xml, wregex(L"<level.* width=\"20\" height=\"15*\"")));
        ASSERT_TRUE(regex_search(xml, wregex(L"<level.* tilewidth=\"48\" tileheight=\"48*\"")));

    }

    wxXmlNode* CreateRoot (const wxString &filename)
    {
        auto root = new wxXmlNode(wxXML_ELEMENT_NODE, L"level");
        root->AddAttribute(L"width", wxString::FromDouble(20.0));
        root->AddAttribute(L"height", wxString::FromDouble(15.0));
        root->AddAttribute(L"tilewidth", wxString::FromDouble(48.0));
        root->AddAttribute(L"tileheight", wxString::FromDouble(48.0));
        return root;
    }

    /**
     * Test Save Function to Test Loading
     * @param filename Save the XML File
     */
    void TempSave(const wxString &filename)
    {
        wxXmlDocument xmlDoc;
        auto root = CreateRoot(filename);
        xmlDoc.SetRoot(root);

        if(!xmlDoc.Save(filename, wxXML_NO_INDENTATION))
        {
            wxMessageBox(L"Write to XML failed");
            return;
        }
    }

    /**
     * Create some temporary Declaration Items
     * @param filename XML Filename
     * @return A wxXmlDocument that will be passed to another function
     */
    void SaveDeclarationItems(const wxString &filename)
    {
        wxXmlDocument xmlDoc;
        auto root = CreateRoot(filename);
        xmlDoc.SetRoot(root);
        auto declarations = new wxXmlNode(wxXML_ELEMENT_NODE, L"declarations");
        AddChildren(declarations, false);
        root->AddChild(declarations);

        if(!xmlDoc.Save(filename, wxXML_NO_INDENTATION))
        {
            wxMessageBox(L"Write to XML failed");
            return;
        }

    }

    /**
     * Helper function to add children
     * @param node Root wxXML Node for these children
     */
    void AddChildren(wxXmlNode *node, bool items)
    {
        //Create some dummy children
        auto child1 = new wxXmlNode(wxXML_ELEMENT_NODE, L"given");
        auto child2 = new wxXmlNode(wxXML_ELEMENT_NODE, L"background");
        auto child3 = new wxXmlNode(wxXML_ELEMENT_NODE, L"sparty");

        if (!items)
        {
            child1->AddAttribute(L"id", L"i579");
            child1->AddAttribute(L"image", L"0b.png");

            child2->AddAttribute(L"id", L"i600");
            child2->AddAttribute(L"image", L"background.png");

            child3->AddAttribute(L"id", L"i599");
            child3->AddAttribute(L"image1", L"sparty-1.png");
        }

        if (items)
        {
            child1->AddAttribute(L"id", L"i579");
            child1->AddAttribute(L"col", L"10");
            child1->AddAttribute(L"row", L"7");

            child2->AddAttribute(L"id", L"i600");
            child2->AddAttribute(L"col", L"0.0");
            child2->AddAttribute(L"row", L"14.0");

            child3->AddAttribute(L"id", L"i599");
            child3->AddAttribute(L"col", L"1.4");
            child3->AddAttribute(L"row", L"10.0");
        }

        node->AddChild(child1);
        node->AddChild(child2);
        node->AddChild(child3);

    }

    /**
     * Create some temporary Declarations and Items
     * @param filename XML Filename
     * @return A wxXmlDocument that will be passed to another function
     */
    void SaveDeclarationsAndItems(const wxString &filename)
    {
        wxXmlDocument xmlDoc;
        auto root = CreateRoot(filename);
        xmlDoc.SetRoot(root);
        auto declarations = new wxXmlNode(wxXML_ELEMENT_NODE, L"declarations");
        AddChildren(declarations, false);

        auto items = new wxXmlNode(wxXML_ELEMENT_NODE, L"items");
        AddChildren(items, true);
        root->AddChild(declarations);
        root->AddChild(items);

        if(!xmlDoc.Save(filename, wxXML_NO_INDENTATION))
        {
            wxMessageBox(L"Write to XML failed");
            return;
        }

    }

};

/**
 * Test constructing a Game object
 */
TEST_F(GameTest, Construct){
    Game game;
}

TEST_F(GameTest, Load){

    auto path = TempPath();

    Game game;

    auto file1 = path + L"/test1.xml";

    TempSave(file1);

    // Test the Root is Correct
    TestRoot(file1);

    // Test tile Sizes are Loaded Correctly
    game.Load(file1);
    ASSERT_TRUE(game.GetTileWidth() == 48);
    ASSERT_TRUE(game.GetTileHeight() == 48);

    // Test the Size of the Array
    ASSERT_FALSE(game.GetItemsArrayLength() > 0);

    Game game2;
    // Now load some dummy variables to the Game
    auto file2 = path + L"/test2.xml";

    SaveDeclarationItems(file2);

    game2.Load(file2);
    // Loading Declarations should Not Create the Items in Items Array
    // Items should only be created once!
    ASSERT_FALSE(game2.GetItemsArrayLength() > 0);

    SaveDeclarationsAndItems(file2);
    game2.Load(file2);
    ASSERT_TRUE(game2.GetItemsArrayLength() > 0);


}