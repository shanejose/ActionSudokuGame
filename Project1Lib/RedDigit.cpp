/**
 * @file RedDigit.cpp
 * @author Harshita Rathod
 */

#include "pch.h"
#include "RedDigit.h"

/**
 * Constructor for RedDigit Object
 * @param game Game Pointer
 * @param filename Name of the File
 * @param node XMl Node
 */
RedDigit::RedDigit(Game *game, const std::wstring &filename, wxXmlNode *node) : Digits(game, filename, node)
{

}