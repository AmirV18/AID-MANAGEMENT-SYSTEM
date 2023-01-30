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
#include "Date.h"

using namespace std;
namespace sdds {
	bool Date::allValid() {
		ut.getSystemDate(&Year);
		int cYear = this->Year;
		return Year >= cYear && Year <= MAXYEARVALUE && Month >= 1 && Month <= 12 && Day >= 1 && Day <= ut.daysOfMon(Month, Year);
	}

	bool Date::validate() {
		bool rValue = true;

		int cyear;
		int cmonth;

		ut.getSystemDate(&cyear, &cmonth);

		//if (allValid() == false) {
			if (this->Year < cyear || this->Year > MAXYEARVALUE) {//invalid
				State = "Invalid year in date";
				State = 1;
				return false;
			}else {
				if (this->Month < 1 || this->Month > 12) {
					State = "Invalid month in date";
					State = 2;
					return false;
				}
				else {

					if (this->Day < 1 || this->Day > ut.daysOfMon(cmonth - 1, cyear)) {
						State = "Invalid day in date";
						State = 3;
						return false;
					}
					else {//ERASE THIS ELSE IF PROBLEM ARISE
						State.clear(); //could be here
					}
					
					

				}
			}
	//REVERT TO THIS IF PROBLEM		State.clear(); //could be here
		/*}
		else {
			State.clear();
		}*/

		return rValue;
	}

	int Date::uniqueDateValue() {
		return Year * 372 + Month * 31 + Day;
	}

	Date::Date() {
		ut.getSystemDate(&Year, &Month, &Day);
		Formatted = true;
	}

	Date::Date(const int year, const int month, const int day ) {
		//if (allValid()) {

			Year = year;
			Month = month;
			Day = day;
			Formatted = true;
			validate();
		//}
	}

	bool Date::operator== (Date& d) {
		return uniqueDateValue() == d.uniqueDateValue();
	}

	bool Date::operator!= (Date& d) {
		return uniqueDateValue() != d.uniqueDateValue();
	}

	bool Date::operator< (Date& d) {
		return uniqueDateValue() < d.uniqueDateValue();
	}

	bool Date::operator> (Date& d) {
		return uniqueDateValue() > d.uniqueDateValue();
	}

	bool Date::operator<= (Date& d) {
		return uniqueDateValue() <= d.uniqueDateValue();
	}

	bool Date::operator>= (Date& d) {
		return uniqueDateValue() >= d.uniqueDateValue();
	}

	const Status& Date::state(){
		return State;
	}

	Date& Date::formatted(bool flag) {
		Formatted = flag;
		return *this;
	}

	Date::operator bool() const {
		return int(State) == 0;
	}

	std::ostream& Date::write(std::ostream& ostr) const {
		if (Date::Formatted == true) {
			ostr << Year << "/";
			ostr.fill('0');
			ostr.width(2);
			ostr << Month << "/";
			ostr.width(2);
			ostr << Day;
		}
		else {
			if (Date::Formatted == false) {
				int uYear = Date::Year % 100;
				ostr << uYear;
				ostr.fill('0');
				ostr.width(2);
				ostr << Month;
				ostr.width(2);
				ostr << Day;
			}
		}

		return ostr;
	}

	std::istream& Date::read(std::istream& istr) {
		int date;
		istr >> date;
		if (istr.good()) {

			if (date < 99999)
			{
				Day = date % 100;
				date /= 100;
				Month = date;
				int currentYear = {};
				ut.getSystemDate(&currentYear);
				Year = currentYear;
				Formatted = true;
			}
			else if (date > 99999)
			{
				Day = date % 100;
				date /= 100;
				Month = date % 100;
				date /= 100;
				Year = 2000 + date;
				Formatted = true;
			}

		

			if (validate() == false) {
				istr.setstate(ios::failbit);
			}
		}
		else {
			Date::State = "Invalid date value";
		}
		
		return istr;

	}
	
	std::ostream& operator<<(std::ostream& ostr, const Date& d) {
		d.write(ostr);
		return ostr;
	}

	std::istream& operator>>(std::istream& istr, Date& d) {
		d.read(istr);
		return istr;
	}

	







}//namespace sdds