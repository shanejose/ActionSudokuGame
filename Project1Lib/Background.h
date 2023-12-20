/**
 * @file Background.h
 * @author Harshita Rathod
 *
 * Class for the Background Image
 */

#ifndef PROJECT1_PROJECT1LIB_BACKGROUND_H
#define PROJECT1_PROJECT1LIB_BACKGROUND_H

#include "Item.h"
#include "Game.h"

/**
 * Class for the Background Image
 */
class Background : public Item
{
private:

    /// Reference to Game Object
    Game mGame;

    /// The building image file
    std::wstring mBackgroundImageFile;

    /// Background Image
    std::shared_ptr<wxImage> mBackgroundImage;

    /// Bitmap for Image
    std::shared_ptr<wxBitmap> mBackgroundBitmap;

public:
    /// Default constructor (disabled)
    Background() = delete;

    /// Copy constructor (disabled)
    Background(const Background &) = delete;


    /// Assignment operator
    void operator=(const Background &) = delete;

    /// Constructor
    Background(Game *game, const std::wstring &filename);


};

#endif //PROJECT1_PROJECT1LIB_BACKGROUND_H
