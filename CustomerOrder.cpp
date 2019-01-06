// Name: Junya Sewai
// Seneca Student ID: 013019153
// Seneca email:jsewai@myseneca.ca
// Date of completion: 2018/11/25
//
// I confirm that I am the only author of this file
// and the content was created entirely by me.

#include <iostream>
#include <string>
#include <iomanip>
#include <vector>
#include "CustomerOrder.h"


using namespace std;
size_t CustomerOrder::m_widthField = 0;

CustomerOrder::CustomerOrder(const string& str) {
	vector<string> token;
	Utilities util;
	bool more = true;
	size_t next_pos = 0;


	m_name = util.extractToken(str, next_pos, more);
	if (more) 
		m_product = util.extractToken(str, next_pos, more);
	
	while (more) {		// count the Item to dynamic allocation
		token.push_back(util.extractToken(str, next_pos, more));
	}
	m_cntItem = token.size();
	m_listItem = new ItemInfo*[m_cntItem];	// allocate a space to store values
	
	more = true; 
	
	for (size_t i = 0; i < m_cntItem; i++) {
		m_listItem[i] = new ItemInfo(token[i]);
	}

	if (util.getFieldWidth() > m_widthField)
		m_widthField = util.getFieldWidth();

}

CustomerOrder::CustomerOrder(const CustomerOrder& c_order) {	// throw exception if copy constructor is called
	throw "Cannot copy. A copy constructor is called\n";
}

CustomerOrder::CustomerOrder(CustomerOrder&& src) noexcept {// move constructor
	m_listItem = nullptr;
	*this = move(src);
}

CustomerOrder& CustomerOrder::operator=(CustomerOrder&& src) {// move assignment operator

	if (&src != this) {
		this->m_name = src.m_name;
		this->m_product = src.m_product;

	if (m_listItem) // deallocate the pointer if array has
		for (unsigned int i = 0; i < m_cntItem; i++)
			delete this->m_listItem[i];
	delete[] this->m_listItem;

	this->m_cntItem = src.m_cntItem;
	this->m_listItem = src.m_listItem;

	src.m_listItem = nullptr;
	}

	return *this;
}

CustomerOrder::~CustomerOrder() {
	if (m_listItem) {
		for (unsigned int i = 0; i < m_cntItem; i++)
			delete m_listItem[i];
	}
	delete[] m_listItem;
}

bool CustomerOrder::getItemFillState(string str) const {
	for (unsigned int i = 0; i < m_cntItem; i++) {
		if (m_listItem[i]->m_itemName == str)
			return m_listItem[i]->m_fillState;
	}

	return true;
}

bool CustomerOrder::getOrderFillState() const {
	for (unsigned int i = 0; i < m_cntItem; i++) {
		if (!m_listItem[i]->m_fillState)
			return false;
	}

	return true;
}

void CustomerOrder::fillItem(Item& item, ostream& os) {
	for (unsigned int i = 0; i < m_cntItem; i++) {
		if (m_listItem[i]->m_itemName == item.getName()) {
			m_listItem[i]->m_serialNumber = item.getSerialNumber();
			m_listItem[i]->m_fillState = true;			

			item.updateQuantity();
			if (item.getQuantity() == 0) {
				os << "Unable to fill " << m_name << ", " << m_product << "[" << m_listItem[i]->m_itemName << "]";
			}
			else {
				os << "Filled " << m_name << ", " << m_product << "[" << m_listItem[i]->m_itemName << "]";
			}
			os << endl;
		}
	}
}

void CustomerOrder::display(ostream& os) const {

	os << m_name << " - " << m_product << endl;
	for (unsigned int i = 0; i < m_cntItem; i++) {
		os << "[" << setw(6) << right << setfill('0') << m_listItem[i]->m_serialNumber << setfill(' ') << "] "
			<< setw(m_widthField) << left << m_listItem[i]->m_itemName
			<< " - ";
		if (m_listItem[i]->m_fillState){
			os << "FILLED" << endl;
		}
		else { 
			os << "MISSING" << endl; 
		}
	}
}

