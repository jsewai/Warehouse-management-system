// Name: Junya Sewai
// Seneca Student ID: 013019153
// Seneca email:jsewai@myseneca.ca
// Date of completion: 2018/12/02
//
// I confirm that I am the only author of this file
// and the content was created entirely by me.


#include "Task.h"

using namespace std;

void Task::runProcess(ostream& os) {
	if(!m_orders.empty()) {// if m_orders holds CustomerOrder in the queue
		if(!m_orders.front().getOrderFillState())
			while (!m_orders.front().getItemFillState(getName())) { // will verify the fill status
					m_orders.front().fillItem(*this, os);
			}
	}
}

bool Task::moveTask() {

	if (!m_orders.empty()) {
		if (m_pNextTask) {
			if (m_orders.front().getItemFillState(getName())) {
				*m_pNextTask += std::move(m_orders.front());
				m_orders.pop_front();
			}
		}
		return true;
	}
	else {
		return false;
	}
}

void Task::setNextTask(Task& nextTask) {
	m_pNextTask = &nextTask;
}

bool Task::getCompleted(CustomerOrder& c_order) {
	if (!m_orders.empty()) {
		if (m_orders.front().getOrderFillState()) {
			c_order = move(m_orders.front());
			m_orders.pop_front();
			return true;
		}
		else {
			return false;
		}
	}
	else {
		return false;
	}

}

void Task::validate(std::ostream& os) {
	os << getName() << " --> ";
	if (m_pNextTask) {
		os << m_pNextTask->getName();
	}
	else {
		os << "END OF LINE";
	}
	os << std::endl;
}


Task& Task::operator+=(CustomerOrder&& c_order) {
	m_orders.push_back(move(c_order));
	return *this;
}

