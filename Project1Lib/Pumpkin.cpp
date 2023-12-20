/**
 * @file Pumpkin.cpp
 * @author Rida Mahmood
 */

#include "pch.h"
#include "Pumpkin.h"

using namespace std;



/**
 * Constructor for Pumpkin class
 * @param game game Pointer to Game Object
 * @param filename file name of pumpkin
 * @param node node attributes for pumpkin
 */
Pumpkin::Pumpkin(Game *game, const std::wstring &filename, wxXmlNode *node) : Container(game, filename, node)
{

}