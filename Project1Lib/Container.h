/**
 * @file Container.h
 * @author Sanju Kona
 *
 * Class for Cauldron Item
 */

#ifndef PROJECT1_PROJECT1LIB_CONTAINER_H
#define PROJECT1_PROJECT1LIB_CONTAINER_H

#include "XMLItem.h"
#include "Digits.h"

/**
 * Class for Cauldron Item
 */
class Container : public XMLItem
{
private:

    /// Indicate if Front Image
    bool mIsFront = false;


protected:
    /// All of the digits to populate our container
    std::vector<std::shared_ptr<Item>> mDigits;

public:
    /// Default constructor (disabled)
    Container() = delete;

    /// Copy constructor (disabled)
    Container(const Container &) = delete;


    /// Assignment operator
    void operator=(const Container &) = delete;

    /// Constructor
    Container(Game *game, const std::wstring &filename, wxXmlNode *node);

    virtual void Add(std::shared_ptr<Item> item);

    /**
     * Accept a visitor
     * @param visitor The visitor we accept
     */
    void Accept (ItemVisitor* visitor) override
    {
        visitor->VisitContainer(this);
    }

    /**
     * Return Flag indicating if Front Image
     * @return Flag indicating if image is front
     */
    bool GetFrontIndicatorFlag () { return mIsFront; }


    void RandomizeDigitLocations(std::vector<std::shared_ptr<Item>> &items);

    void Clear();
    void Delete(std::shared_ptr<Item> item);
};

#endif //PROJECT1_PROJECT1LIB_CONTAINER_H
