// Name: Junya Sewai
// Seneca Student ID: 013019153
// Seneca email:jsewai@myseneca.ca
// Date of completion: 2018/12/02
//
// I confirm that I am the only author of this file
// and the content was created entirely by me.


#ifndef TASK_H
#define TASK_H

#include <iostream>
#include <deque>
#include <string>

#include "CustomerOrder.h"
#include "Item.h"

class Task : public Item {
	std::deque<CustomerOrder> m_orders;
	Task* m_pNextTask;

public:

	Task() : m_pNextTask(nullptr) {};
	Task(const std::string& singleRec) : Item(singleRec), m_pNextTask(nullptr) {};
	// delete a capability of copy and move for Task object
	Task(Task&) = delete;
	Task(Task&&) = delete;
	Task& operator=(Task&) = delete;
	Task& operator=(Task&&) = delete;

	void runProcess(std::ostream&);
	bool moveTask();
	void setNextTask(Task&);
	bool getCompleted(CustomerOrder&);
	void validate(std::ostream&);
	Task& operator+=(CustomerOrder&&);
};

#endif 