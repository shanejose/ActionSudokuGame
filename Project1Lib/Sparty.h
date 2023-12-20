/**
 * @file Sparty.h
 * @author Shane Jose
 *
 * Base class that describes sparty attributes in the game
 */

#ifndef PROJECT1_PROJECT1LIB_SPARTY_H
#define PROJECT1_PROJECT1LIB_SPARTY_H

#include "Item.h"



/**
 * Base class that describes sparty attributes in the game
 *
 */
class Sparty : public Item
{
private:


    /// The time for a headbutt cycle in seconds
    const double HeadbuttTime = 0.5;

    /// The time for an eating cycles in seconds
    const double EatingTime = 0.5;

    /// Current Headbutt time
    double mHeadButtCurrent = 0;

    /// Current Eating time
    double mEatingCurrent = 0;

    /// Character maximum speed in pixels per second
    const double MaxSpeed = 400.00;

    /// x location that sparty has to move to
    double mMoveToX;

    /// y location that sparty has to move to
    double mMoveToY;

    /// X offset
    double mTargetX;

    /// Y Offset
    double mTargetY;

    /// Head Pivot Angle
    double mHeadPivotAngle;

    /// Head Pivot X
    double mHeadPivotX;

    /// Head Pivot Y
    double mHeadPivotY;

    /// checks if sparty has to move
    bool mMovement = false;

    /// checks if sparty has to headbutt
    bool mCheckHeadbutt = false;

    /// checks if sparty has to eat
    bool mCheckEating = false;

    /// The underlying sparty image
    std::unique_ptr<wxImage> mSpartyImage;

    /// The bitmap we can display this item
    wxGraphicsBitmap mSpartyBitmap;

    /// Mouth Pivot Angle
    double mMouthPivotAngle;

    /// Mouth Pivot X
    double mMouthPivotX;

    /// Mouth Pivot Y
    double mMouthPivotY;

    /// Stops sparty movement for first 3 seconds of the game
    bool mStop= false;


public:
    /// Default constructor (disabled)
    Sparty() = delete;

    /// Copy constructor (disabled)
    Sparty(const Sparty &) = delete;

    /// Assignment operator
    void operator=(const Sparty &) = delete;


    Sparty(Game *game, const std::wstring &filename, wxXmlNode* node);


    void SetMovetoLocation(double x, double y);

    /**
     * Check if sparty has to headbutt
     * @param check true if sparty wants to headbutt otherwise false
     *
     */
    void CheckSpartyHeadbutt(bool check) {mCheckHeadbutt = check;}

    /**
     * Check if sparty has to eat
     * @param check true if sparty wants to eat otherwise false
     *
     */
    void CheckSpartyEating(bool check) {mCheckEating = check;}


    /**
     * Get the X Offset for Sparty
     * @return Value of the X Offset
     */
    double GetXOffset () const { return mTargetX; }

    /**
     * Get the Y Offset for Sparty
     * @return Value for the Y Offset
     */
    double GetYOffset () const { return mTargetY; }

    /**
     * Checks if sparty has to move
     * @param check
     */
    void SetSpartyMovement(bool check) {mMovement = check;}


    void Update(double elapsed) override;

    /**
     * Headbutting for Sparty
     */
    void HeadButt();


    void Draw(std::shared_ptr<wxGraphicsContext> graphics) override;

    void SetHeadButtTime ();

   /**
    * Accept a visitor
    * @param visitor The visitor we accept
    */
   void Accept(ItemVisitor* visitor) override
   {
       visitor->VisitSparty(this);
   }

   void Eat();

   /**
    * Sets Sparty's movement stat
    * @param check boolean flag to control Sparty's movement
    */
   void StopSpartyMovement(bool check){mStop= check;};

};

#endif //PROJECT1_PROJECT1LIB_SPARTY_H
