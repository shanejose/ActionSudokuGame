/**
 * @file XMLItem.cpp
 * @author Harshita Rathod
 */

#include "pch.h"
#include "XMLItem.h"
#include "Item.h"
#include "Game.h"

using namespace std;

/**
 * XML Item Constructor
 * @param game
 * @param filename
 * @param node
 */
XMLItem::XMLItem(Game *game, const std::wstring &filename, wxXmlNode *node) :  Item(game, filename)
{

}
