/*
Name: Amir Vassell
Seneca Email: arvassell@myseneca.ca
Student ID: 154737209
Date Completed: April 10, 2021

I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments.
*/

#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <string.h>
#include "Status.h"
#include "Utils.h"

using namespace std;

namespace sdds {

	Status::Status(const char* description, int statusCode) {
		if (description != nullptr) {
			ut.alocpy(m_description, description);
			m_statusCode = statusCode;
		}
		else {
			m_description = nullptr;
			m_statusCode = 0;
		}
	}

	Status::Status(int statusCode) {
		m_description = nullptr;
		m_statusCode = statusCode;
	}

	Status::Status(const Status& status) {
		this->m_description = nullptr;
		*this = status;
	}

	Status& Status::operator=(const Status& status) {
		if (this != &status) {
			if (status.m_description != nullptr) {
				ut.alocpy(m_description, status.m_description);
			}
			m_statusCode = status.m_statusCode;
		}

		return *this;
	}

	Status::~Status() {
		delete[] m_description;
		m_description = nullptr;
	}

	Status& Status::operator=(int code) {
		this->m_statusCode = code;
		return *this;
	}

	Status& Status::operator=(const char* description) {
		if (description != nullptr) {
			ut.alocpy(this->m_description, description);
		}

		return *this;
	}

	//type conversion overloads
	Status::operator int() const{
		return m_statusCode;
	}

	Status::operator const char* () const{
		return m_description;
	}

	Status::operator bool() const{
		return m_description == nullptr;
	}

	Status& Status::clear() {
		if (m_description != nullptr) {
			delete[] m_description;
			m_description = nullptr;
			m_statusCode = 0;
		}

		return *this;
	}

	std::ostream& operator<<(std::ostream& ostr, const Status& status) {
		if (status.operator bool() == false) {
			if (status.operator int() != 0) {
				ostr << "ERR#" << /*status.operator int() */(int)status<< ": " << status.operator const char* ();
			}
			else {
				ostr << status.operator const char* ();
			}
		}

		return ostr;
	}





}//namespace sdds