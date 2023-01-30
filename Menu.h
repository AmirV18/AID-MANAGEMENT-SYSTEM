/*
Name: Amir Vassell
Seneca Email: arvassell@myseneca.ca
Student ID: 154737209
Date Completed: April 10, 2021

I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments.
*/
#ifndef MENU_H_
#define MENU_H_

#include <iostream>
using namespace std;

namespace sdds {

	class Menu{
		char* m_menu_content = {}; //A dynamically allocated text that contains the list of options the user can select from
		unsigned int m_options; //holds the number of available options

	public:
		Menu(unsigned int, const char*);

		//RULE OF THREE//
		Menu(const Menu&) = delete;
		Menu& operator=(const Menu&) = delete;
		~Menu();

		unsigned int run() const;
		void clearMemory();
		void setEmpty();
	};

}//namespace sdds

#endif