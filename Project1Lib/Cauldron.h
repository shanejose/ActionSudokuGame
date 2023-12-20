/**
 * @file Cauldron.h
 * @author Areeb Islam
 *
 * Class for Cauldron Item
 */

#ifndef PROJECT1_PROJECT1LIB_CAULDRON_H
#define PROJECT1_PROJECT1LIB_CAULDRON_H

#include "Container.h"
#include "Digits.h"

/**
 * Class for Cauldron Item
 */
class Cauldron : public Container
{
private:
public:
    /// Default constructor (disabled)
    Cauldron() = delete;

    /// Copy constructor (disabled)
    Cauldron(const Cauldron &) = delete;


    /// Assignment operator
    void operator=(const Cauldron &) = delete;

    /// Constructor
    Cauldron(Game *game, const std::wstring &filename, wxXmlNode *node);
};

#endif //PROJECT1_PROJECT1LIB_CAULDRON_H
