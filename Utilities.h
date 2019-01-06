// Name: Junya Sewai
// Seneca Student ID: 013019153
// Seneca email:jsewai@myseneca.ca
// Date of completion: 2018/12/02
//
// I confirm that I am the only author of this file
// and the content was created entirely by me.

#ifndef UTILITIES_H
#define UTILITIES_H

#include <iostream>
#include <string>
#include <fstream>

class Utilities {
	unsigned int m_widthField = 1;
	static char m_delimiter; 

public:
	Utilities() : m_widthField(1) {};
	void setFieldWidth(size_t); // sets the field width of the current object to the value of the parameter
	size_t getFieldWidth() const; //returns the field width of the current object
	const std::string extractToken(const std::string& str, size_t& next_pos, bool& more); // extracts tokens from the first parameter
	static void setDelimiter(const char); //sets the delimiter for this class to the character received
	const char getDelimiter() const; // returns the delimiter character of the current object.
};


#endif