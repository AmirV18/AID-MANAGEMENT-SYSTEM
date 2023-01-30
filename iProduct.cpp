/*
Name: Amir Vassell
Seneca Email: arvassell@myseneca.ca
Student ID: 154737209
Date Completed: April 10, 2021

I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments.
*/

#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include "iProduct.h"
using namespace std;

namespace sdds {

	std::ostream& operator<<(std::ostream& ostr, const iProduct& iP) {
		iP.display(ostr);
		return ostr;
	}

	std::istream& operator>>(std::istream& istr, iProduct& iP) {
		iP.read(istr);
		return istr;
	}

}//NAMESPACE SDDS
