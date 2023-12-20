/**
 * @file ErrorMessage.h
 * @author Shane Jose
 *
 * Class that creates Error messages
 */

#ifndef PROJECT1_PROJECT1LIB_ERRORMESSAGE_H
#define PROJECT1_PROJECT1LIB_ERRORMESSAGE_H

#include <wx/string.h>
#include<memory>

/**
 * Class that creates Error Message
 *
 */
class ErrorMessage
{
private:
    /// Location of the error message
    int mLocation = 0;

    /// Message to display
    std::string mMessage;

    /// Checks the type of error message
    bool mCheckFont = false;


public:

    ErrorMessage();

    void Draw(std::shared_ptr<wxGraphicsContext> graphics);

    void Update(double elapsed);

    /**
     * Sets the location of the error message
     * @param x
     */
    void SetErrorLocation(int x ) {mLocation = x;}

    /**
     * Sets the error message
     * @param message
     */
    void SetErrorMessage(std::string message) {mMessage = message;}

    /**
     * Sets the font for error messages
     * @param check
     */
    void SetFullFontMessage(bool check) {mCheckFont = check;}



};

#endif //PROJECT1_PROJECT1LIB_ERRORMESSAGE_H
