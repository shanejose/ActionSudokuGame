/**
 * @file Digits.cpp
 * @author Harshita Rathod
 */

#include "pch.h"
#include "Digits.h"
#include "XMLItem.h"


/**
 * Constructor for digits
 * @param game game we are playing
 * @param filename file of the image
 * @param node node of the item
 *
 */
Digits::Digits(Game* game, const std::wstring &filename, wxXmlNode *node) : XMLItem(game, filename, node){


}