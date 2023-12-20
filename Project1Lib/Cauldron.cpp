/**
 * @file Cauldron.cpp
 * @author Areeb Islam
 */
#include "pch.h"
#include "Cauldron.h"


using namespace std;


/**
 * Constructor for Cauldron Object
 * @param game Game Pointer to Game object
 * @param filename Filename for Object
 * @param node XMl Node
 */
Cauldron::Cauldron(Game *game, const std::wstring &filename, wxXmlNode *node) : Container(game, filename, node)
{

}
