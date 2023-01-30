/*
Name: Amir Vassell
Seneca Email: arvassell@myseneca.ca
Student ID: 154737209
Date Completed: April 10, 2021

I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments.
*/

#ifndef PERISHABLE_H_
#define PERISHABLE_H_
#include "Date.h"
#include "Item.h"

namespace sdds {

	class Perishable : public Item {

	private:
		Date m_expiry_date; //The Perishable class adds an expiry date to the Item.
		char* m_handling_instructions;//Dynamically holds a text for the instructions with which the perishable item should be handled.


	public:
//A Perishable object is created using the default constructor that creates an empty perishable item.
		Perishable(); 
		
		//RULE OF THREE//
		Perishable(const Perishable&);
		Perishable& operator=(const Perishable&);
		~Perishable();
		/////////////////

//constant query called expiry that returns a constant reference of the expiry date.
		const Date& expiry() const;

		//Override readSKU function to only receive SKU 
		//numbers between 10000 and 39999 (only SKUs starting with digits 1 to 3)
		int readSku(std::istream& istr);


		std::ofstream& save(std::ofstream& ofstr) const; //overrides
		std::ifstream& load(std::ifstream& ifstr); //overrides
		std::ostream& display(std::ostream& ostr)const; //overrides
		std::istream& read(std::istream& istr);
	};//Class Perishables

}//NAMESPACE SDDS

#endif