/**
 * @file XMLItem.h
 * @author Harshita Rathod
 *
 * Parent Class for Item that are Special
 */

#ifndef PROJECT1_PROJECT1LIB_XMLITEM_H
#define PROJECT1_PROJECT1LIB_XMLITEM_H

#include "Item.h"
class Game;

/**
 * Parent Class for Items that are Special
 */
class XMLItem: public Item
{
private:

protected:
    XMLItem(Game *game, const std::wstring &filename, wxXmlNode *node);

public:

};

#endif //PROJECT1_PROJECT1LIB_XMLITEM_H
