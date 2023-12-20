/**
 * @file RedDigit.h
 * @author Harshita Rathod
 *
 * Class for Red Digits
 */

#ifndef PROJECT1_PROJECT1LIB_REDDIGIT_H
#define PROJECT1_PROJECT1LIB_REDDIGIT_H

#include "Digits.h"

/**
 * Class for Red Digits
 */
class RedDigit : public Digits
{
private:

public:
    /// Default constructor (disabled)
    RedDigit() = delete;

    /// Copy constructor (disabled)
    RedDigit(const RedDigit &) = delete;

    /// Assignment operator
    void operator=(const RedDigit &) = delete;

    RedDigit(Game* game, const std::wstring &filename,  wxXmlNode *node);

    /**
     * Accept a visitor
     * @param visitor The visitor we accept
     */
    void Accept (ItemVisitor* visitor) override
    {
        visitor->VisitRedDigit(this);
    }
};

#endif //PROJECT1_PROJECT1LIB_REDDIGIT_H
