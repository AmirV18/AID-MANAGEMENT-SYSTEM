#ifndef DATE_H_
#define DATE_H_

#include "Status.h"

namespace sdds {

	const int MAXYEARVALUE = 2030;

	class Date{
		int Year; //an integer between the current year the maximum year value.
		int Month; //an integer between 1 and 12
		int Day; //an integer between 1 and the number of days in the month based on the year.
		sdds::Status State; //a Status object that holds the validity status of date.
		bool Formatted; //a boolean value that is set to true to print the date as YYYY/MM/DD or false to print it as YYMMDD.

	private:
		bool allValid();
		bool validate(); //validates the year, month and day, kept in the object in the following order (and validation stops if an invalid value is found):
		int uniqueDateValue();

	public:
		Date();
		Date(const int, const int, const int);
		
		//OPERATOR OVERLOADS FOR COMPARISON		
		bool operator== (Date&);
		bool operator!= (Date&);
		bool operator< (Date&);
		bool operator> (Date&);
		bool operator<= (Date&);
		bool operator>= (Date&);
	
		const Status& state(); //accessor method returns a constant reference to the State of the Date.
		

		/*set the Formatted flag(attribute) of the Date.
		This method should return the reference of the current object.*/
		Date& formatted(bool = true); 
	
		operator bool() const; //If the Date object is casted to a boolean, the state of the date object is returned.

		std::ostream& write(std::ostream&) const;
		std::istream& read(std::istream&);

	};//class Date

	std::ostream& operator<<(std::ostream&, const Date&);
	std::istream& operator>>(std::istream&, Date&);
}//namespace sdds

#endif