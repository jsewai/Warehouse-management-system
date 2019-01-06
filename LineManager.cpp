// Name: Junya Sewai
// Seneca Student ID: 013019153
// Seneca email:jsewai@myseneca.ca
// Date of completion: 2018/12/02
//
// I confirm that I am the only author of this file
// and the content was created entirely by me.

#include <string>
#include <fstream>
#include "LineManager.h"

using namespace std;

LineManager::LineManager(const string& fileName, vector<Task*>& a_task, vector<CustomerOrder>& c_order) {
	ifstream file(fileName);

	if (!file)
		throw std::string("Cannot open the file");

	Utilities util;
	size_t pos;
	bool more;
	size_t index;

	AssemblyLine.resize(a_task.size());

	bool firstTask = true;

	while (!file.eof()) {
		pos = 0;
		more = true;

		string record;
		string first;
		string next;

		getline(file, record);
		first = util.extractToken(record, pos, more);

		if (more) {
			next = util.extractToken(record, pos, more);
		}	

		for (size_t i = 0; i < a_task.size(); i++) {
			if (a_task[i]->getName() == first) {
				if (firstTask) {
					m_firstTask = i;
					firstTask = false;
				}
				index = i;
			}
		}

		if (!next.empty()) {

			for (size_t i = 0; i < a_task.size(); i++) {
				if (a_task[i]->getName() == next) {
					a_task[index]->setNextTask(*a_task[i]);
				}
			}
		}
		else {
			m_lastTask = index;
			a_task[index]->setNextTask(*AssemblyLine[index]);
		}

		AssemblyLine.erase(AssemblyLine.begin() + index);
		AssemblyLine.insert(AssemblyLine.begin() + index, a_task[index]);
	}


	for (size_t i = 0; i < c_order.size(); i++) {
		ToBeFilled.push_back(std::move(c_order[i]));
	}

	
}


bool LineManager::run(ostream& os) {
	bool state = true;

	if (!ToBeFilled.empty()) {
		*AssemblyLine[m_firstTask] += move(ToBeFilled.front());
		ToBeFilled.pop_front();
	}

	for (size_t i = 0; i < AssemblyLine.size(); ++i) {
		AssemblyLine[i]->runProcess(os);	
	}

	CustomerOrder c_order; 
	if (AssemblyLine[m_lastTask]->getCompleted(c_order))
		Completed.push_back(move(c_order));

	for (size_t i = 0; i < AssemblyLine.size(); ++i) {
		if (AssemblyLine[i]->moveTask()) {
			state = false;
		}
	}

	return state;
}
void LineManager::displayCompleted(ostream& os) const {
	if (!Completed.empty())
		for (size_t i = 0; i < Completed.size(); ++i)
			Completed[i].display(os);
}
void LineManager::validateTasks() const {
	if (!AssemblyLine.empty()) {		
		for (size_t i = 0; i < AssemblyLine.size(); ++i) {
			AssemblyLine[i]->validate(std::cout);			
		}
	}
}