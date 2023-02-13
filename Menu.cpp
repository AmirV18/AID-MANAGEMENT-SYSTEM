#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <string.h>
#include "Status.h"
#include "Utils.h"
#include "Date.h"
#include "Menu.h"

using namespace std;

namespace sdds {

	void Menu::clearMemory() {
		delete[] m_menu_content;
		m_menu_content = nullptr;
		m_options = 0;
	}

	void Menu::setEmpty() {
		m_menu_content = nullptr;
		m_options = 0;
	}

	Menu::Menu(unsigned int options, const char* menu_content) {
		const int maxOptions = 15;

		if (options <= maxOptions && menu_content != nullptr) {
			m_options = options;
			sdds::ut.alocpy(m_menu_content, menu_content);
		}
		else {
			clearMemory();
		}
	}

	Menu::~Menu() {
		clearMemory();
	}

	unsigned int Menu::run() const{
		cout << m_menu_content << "0- Exit\n" << "> ";
		unsigned int optionChosen = ut.getint(0, m_options);

		return optionChosen;
	}

}//namespace sdds
