 /**
 * @file Pumpkin.h
 * @author Rida Mahmood
 *
 *
 */

#ifndef PROJECT1_PROJECT1LIB_PUMPKIN_H
#define PROJECT1_PROJECT1LIB_PUMPKIN_H

#include "Container.h"
#include "Digits.h"

/**
 * Class for Pumpkin Item
 */

class Pumpkin : public Container
{
private:
    /// All of the digits to populate our container
    std::vector<std::shared_ptr<Digits>> mDigits;

public:
    /// Default constructor (disabled)
    Pumpkin() = delete;

    /// Copy constructor (disabled)
    Pumpkin(const Pumpkin &) = delete;


    /// Assignment operator
    void operator=(const Pumpkin &) = delete;

    /// Constructor
    Pumpkin(Game *game, const std::wstring &filename, wxXmlNode *node);
};

#endif //PROJECT1_PROJECT1LIB_PUMPKIN_H
