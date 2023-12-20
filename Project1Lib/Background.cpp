/**
 * @file Background.cpp
 * @author Harshita Rathod
 */

#include "pch.h"
#include "Background.h"

/**
 * Constructor for Background Object
 * @param game Pointer to Game object
 * @param filename String for Filename
 */
Background::Background(Game *game, const std::wstring &filename) : Item(game, filename)
{
}
