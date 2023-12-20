/**
 * @file ItemVisitor.h
 * @author Sanju Kona
 *
 * Base Visitor Class
 */

#ifndef PROJECT1_PROJECT1LIB_ITEMVISITOR_H
#define PROJECT1_PROJECT1LIB_ITEMVISITOR_H
// Forward references to item types
class Pumpkin;
class Cauldron;
class Digits;
class Sparty;
class XRay;
class RedDigit;
class XMLItem;
class Container;

/**
 * Base Visitor Class
 */
class ItemVisitor
{
private:
protected:
    /**
     * Constructor
     * Ensures this is an abstract class
     */
    ItemVisitor() {}

public:
    virtual ~ItemVisitor() {}


    /**
     * Visit a Sparty Object
     * @param sparty Sparty that we are visiting
     */
    virtual void VisitSparty(Sparty* sparty) {}


    /**
     * Visit an XRay Object
     * @param xray Xray we are visiting
     */
    virtual void VisitXray(XRay* xray) {}

    /**
     * Visit the Red Digits
     * @param red Red Digit we Are Visiting
     */
    virtual void VisitRedDigit(RedDigit* red) {}

    /**
     * Visit a Container Item
     * @param container Container Object
     */
    virtual void VisitContainer(Container* container) {}

};

#endif //PROJECT1_PROJECT1LIB_ITEMVISITOR_H
