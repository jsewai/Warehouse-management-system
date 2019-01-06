// Name: Junya Sewai
// Seneca Student ID: 013019153
// Seneca email:jsewai@myseneca.ca
// Date of completion: 2018/12/02
//
// I confirm that I am the only author of this file
// and the content was created entirely by me.

#ifndef ITEM_H
#define ITEM_H

#include "Utilities.h"
#include <iostream>
#include <string>
#include <iomanip>

//All Item objects share the same m_widthField

class Item {
	std::string m_name;			// the name of the Item
	std::string m_description;	// description of the item
	unsigned int m_serialNumber;		// the next serial number to be assigned on the assembly line
	unsigned int m_quantity;			// the number of current items left in stock
	static unsigned int m_widthField;		// the maximum characters to be displayed for a field

public:

	Item() : m_name(""), m_description(""), m_serialNumber(0), m_quantity(0) {}; // kesu
	Item(const std::string& singleRecord);

	const std::string& getName() const;					// returns the name of the current Item object
	const unsigned int getSerialNumber();				// returns the next serial number to be used on the assembly line and increments m_serialNumber
	const unsigned int getQuantity();					// returns the remaining quantity of the current Item object
	void updateQuantity();								// substracts 1 from the available quantity; should not go below 0.
	void display(std::ostream& os, bool full) const;	// inserts the content of the current object into first parameter.
};

#endif