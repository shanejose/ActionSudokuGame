/**
 * @file XRay.h
 * @author Sanju Kona
 *
 * class that describes xray in the game
 */

#ifndef PROJECT1_PROJECT1LIB_XRAY_H
#define PROJECT1_PROJECT1LIB_XRAY_H
#include "Container.h"

/**
 * Describes Xray in the Game
 */
class XRay: public Container
{
private:

    /// Capacity of XRay
    int mCapacity;
public:
    /// Default constructor (disabled)
    XRay() = delete;

    /// Copy constructor (disabled)
    XRay(const XRay &) = delete;


    /// Assignment operator
    void operator=(const XRay &) = delete;

    /// Constructor
    XRay(Game *game, const std::wstring &filename, int capacity,  wxXmlNode *node);



    void Add(std::shared_ptr<Item> item) override;

    /**
     * Accept a visitor
     * @param visitor The visitor we accept
     */
    void Accept (ItemVisitor* visitor) override
    {
        visitor->VisitXray(this);
    }

    /**
     * Indicate if XRay is Full
     * @return
     */
    bool GetIsFullFlag () const {
        return mDigits.size() == mCapacity;
    }

    void Draw(std::shared_ptr<wxGraphicsContext> graphics) override;
    void SpitDigit(int key, double x , double y);
};

#endif //PROJECT1_PROJECT1LIB_XRAY_H
