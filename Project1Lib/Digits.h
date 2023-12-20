/**
 * @file Digits.h
 * @author Harshita Rathod
 *
 * Class for Digits Item
 */

#ifndef PROJECT1_PROJECT1LIB_DIGITS_H
#define PROJECT1_PROJECT1LIB_DIGITS_H

#include "XMLItem.h"

/**
 * Class for Digits Item
 */
class Digits : public XMLItem
{
private:


public:
    /// Default constructor (disabled)
    Digits() = delete;

    /// Copy constructor (disabled)
    Digits(const Digits &) = delete;

    /// Assignment operator
    void operator=(const Digits &) = delete;

    Digits(Game* game, const std::wstring &filename,  wxXmlNode *node);

};

#endif //PROJECT1_PROJECT1LIB_DIGITS_H
