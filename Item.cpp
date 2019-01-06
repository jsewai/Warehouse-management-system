// Name: Junya Sewai
// Seneca Student ID: 013019153
// Seneca email:jsewai@myseneca.ca
// Date of completion: 2018/12/02
//
// I confirm that I am the only author of this file
// and the content was created entirely by me.
#include "Item.h"

using namespace std;

unsigned int Item::m_widthField;

Item::Item(const string& singleRecord){ // singleRecords contains one line 
	bool more = true;
	size_t next_pos = 0;
	Utilities utilities;
	
	m_name = utilities.extractToken(singleRecord, next_pos, more);					// store name token from singleRecord
	m_widthField = (m_widthField < m_name.length()) ? m_name.length() : m_widthField;
	
	if (more) 
		m_serialNumber = stoi(utilities.extractToken(singleRecord, next_pos, more)); // cast token to integer type and store it in serialNumber 
	if (more)
		m_quantity = stoi(utilities.extractToken(singleRecord, next_pos, more));
	if (more)
		m_description = utilities.extractToken(singleRecord, next_pos, more);
	
}

const std::string& Item::getName() const {					// returns the name of the current Item object
	return m_name;
}

const unsigned int Item::getSerialNumber() {				// returns the next serial number to be used on the assembly line and increments m_serialNumber
	int number = m_serialNumber;
	m_serialNumber++; 
	return number;
}

const unsigned int Item::getQuantity() {					// returns the remaining quantity of the current Item object
	return m_quantity;
}

void Item::updateQuantity() {								// substracts 1 from the available quantity; should not go below 0.
	if (m_quantity > 0) {
		m_quantity--;
	}
	else {
		m_quantity = 0;
	}
		
}

void Item::display(ostream& os, bool full) const {			// inserts the content of the current object into first parameter.
	
	if (full) {
		os << left << setfill(' ') << setw(m_widthField) << m_name ;
		os << " [" << right << setfill('0') << setw(6)  << m_serialNumber << "]";
		os << " Quantity: " << left << setw(m_widthField) << setfill(' ') << m_quantity;
		os << " Description: " << m_description << endl;
	}
	else {
		os << left << setfill(' ') << setw(m_widthField) << m_name;
		os << " [" << right << setfill('0') << setw(6) << m_serialNumber << "]" << endl;
	}
}