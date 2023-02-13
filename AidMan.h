#ifndef AIDMAN_H_
#define AIDMAN_H_

#include <iostream>
#include "Menu.h"
#include "iProduct.h"
using namespace std;

namespace sdds {
	const int sdds_max_num_items = 100;

	/*
	Class called AidMan that offers a Menu with the list 
	of tasks needed to be done to manage the preparation of 
	products to be shipped to places in need.
	*/
	class AidMan {

		iProduct* m_iProdArray[sdds_max_num_items];

		//n integer to keep track of the number 
		//of iProduct Items pointed by the iProduct pointers.
		//Obviously this number can not grow more than 100.
		int m_num_of_iprod_items;

		char* m_filename{};
		Menu main_menu;

		unsigned int menu() const;

		void save(); //a method for saving data records in file
		void deallocate(); //a method to dallocate all the memory allocated by the class
		bool load(); //a method to load all the records from the data file into the class
		int list(const char* sub_desc = nullptr);
		int search(int sku) const;
		void remove(int index); //menu item 3
		void update(); //menu item 4
		void sort(); //menu item 5
		void ship(); //menu item 6

	public:
		AidMan() : main_menu(7, "1- List Items\n2- Add Item\n3- Remove Item\n4- Update Quantity\n5- Sort\n6- Ship Items\n7- New/Open Aid Database\n---------------------------------\n") {
			m_filename = nullptr;
			m_num_of_iprod_items = 0;
		}

		//RULE OF THREE//
		AidMan(const AidMan&) = delete;
		AidMan& operator=(const AidMan&) = delete;
		~AidMan();

		void run(); //runs the whole application
	};

}//namespace sdds

#endif

