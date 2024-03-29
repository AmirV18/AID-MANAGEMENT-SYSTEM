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