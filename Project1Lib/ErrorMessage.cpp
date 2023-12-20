/**
 * @file ErrorMessage.cpp
 * @author Shane Jose
 */

#include "pch.h"
#include "ErrorMessage.h"

/**
 * Constructor for Error Message
 *
 */
ErrorMessage::ErrorMessage()
{

}


/**
 * Updates the error message box
 * @param elapsed
 */
void ErrorMessage::Update(double elapsed)
{
    mLocation -= 10;

}

/**
 * Draw the error message
 * @param graphics
 */
void ErrorMessage::Draw(std::shared_ptr<wxGraphicsContext> graphics)
{
    wxBrush whiteBrush(*wxWHITE);
    wxPen blackPen(*wxBLACK, 4);
    graphics->SetBrush(whiteBrush);
    graphics->SetPen(blackPen);
    if (mCheckFont){
        graphics->DrawRectangle(400,mLocation,200,45);
    }
    else{
        graphics->DrawRectangle(300,mLocation,400,45);
    }

    // Set font and color for the text
    wxFont font(wxSize(20, 25),
                wxFONTFAMILY_SWISS,
                wxFONTSTYLE_NORMAL,
                wxFONTWEIGHT_BOLD);
    wxColour color(250, 0, 0);
    graphics->SetFont(font, color);
    if (mCheckFont){
        graphics->DrawText(mMessage, 450, mLocation+10);
    }
    else {
        graphics->DrawText(mMessage, 340, mLocation+10);
    }

}
