// Name: Junya Sewai
// Seneca Student ID: 013019153
// Seneca email:jsewai@myseneca.ca
// Date of completion: 2018/12/02
//
// I confirm that I am the only author of this file
// and the content was created entirely by me.

#include "Utilities.h"

using namespace std;

char Utilities::m_delimiter;

void Utilities::setFieldWidth(size_t FW) { //sets the field width of the current object to the value of the parameter
	m_widthField = FW;
}

size_t Utilities::getFieldWidth() const {
	return m_widthField;
}

const string Utilities::extractToken(const string& str, size_t& next_pos, bool& more) { // extracts tokens from the first parameter
	std::string token = str.substr(next_pos);	
	size_t pos = token.find(m_delimiter); // extract the next token	
	token = (pos == std::string::npos)? token = token.substr(0, token.find('\n')) : token = token.substr(0, pos);
	next_pos += token.size() + 1;

	more = (next_pos <= str.size());
	
	if (m_widthField < token.size() && more) 
		m_widthField = token.size();
	
	if (more && str[next_pos] == m_delimiter)
		throw "*** Empty token was received ***";	

	return token;
}



void Utilities::setDelimiter(const char delimiter) {
	m_delimiter = delimiter;
}

const char Utilities::getDelimiter() const {
	return m_delimiter;
}
