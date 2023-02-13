#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include <string.h>
#include "Item.h"

using namespace std;
namespace sdds {

	bool Item::linear() const{
		return m_linear_flag;
	}

	Item::Item() {
		setEmpty();
	}

	///////////////////////////////////////////////////////////////////
						//RULE OF THREE//
	Item::Item(const Item& i) {
		setEmpty();
		*this = i;
	}

	Item& Item::operator=(const Item& i) {
		if (this != &i) {
			if (i.m_item_description != nullptr) {
				ut.alocpy(m_item_description, i.m_item_description);
			}

			m_price = i.m_price;
			m_quantity_on_hand = i.m_quantity_on_hand;
			m_quantity_needed = i.m_quantity_needed;
			m_linear_flag = i.m_linear_flag;
			m_sku = i.m_sku;
		}

		return *this;
	}

	Item::~Item() {
		clearMemory();
	}
	///////////////////////////////////////////////////////////////////

	int Item::qtyNeeded() const {
		return m_quantity_needed;
	}

	int Item::qty() const {
		return m_quantity_on_hand;
	}

	Item::operator double() const {
		return m_price;
	}

	Item::operator bool() const {
		if (m_item_description != nullptr) {
			return true;
		}
		else {
			return false;
		}
	}

	int Item::operator-=(int qty) {
		return (m_quantity_on_hand -= qty);
	}

	int Item::operator+=(int qty) {
		return (m_quantity_on_hand += qty);
	}

	void Item::linear(bool isLinear) {
		m_linear_flag = isLinear;
	}

	void Item::clear() {
		state_of_item.clear();
	}

	bool Item::operator==(int sku) const {
		return m_sku == sku;
	}

	bool Item::operator==(const char* description) const {
		bool isFound = false;
		
		if (description != nullptr || m_item_description != nullptr) {
			if (strstr(m_item_description, description) != nullptr) {
				isFound = true;
			}
		}

		return isFound;
	}

	std::ofstream& Item::save(std::ofstream& ofstr) const {
		if (state_of_item.operator bool()) {
			ofstr << m_sku << "\t" << m_item_description << "\t" << m_quantity_on_hand << "\t" << m_quantity_needed << "\t";
			ofstr << fixed << setprecision(2) << m_price;
		}

		return ofstr;
	}

	std::ifstream& Item::load(std::ifstream& ifstr) {
		if (m_item_description != nullptr) {
			delete[] m_item_description;
			m_item_description = nullptr;
		} 

		string itemDescription;
		ifstr >> m_sku;
		ut.extractChar(ifstr, '\t');
		getline(ifstr, itemDescription, '\t');
		m_item_description = new char[itemDescription.length() + 1];
		strcpy(m_item_description, itemDescription.c_str());
		ifstr >> m_quantity_on_hand;
		ifstr >> m_quantity_needed;
		ifstr >> m_price;
		
		return ifstr;
	}

	std::ostream& Item::display(std::ostream& ostr)const {
		if (state_of_item) {
				if (m_linear_flag == true) {

					ostr << m_sku << " | ";
					int i = 0;
					int len = strlen(m_item_description);
					if (len > 35) {
						for (i = 0; i < 35; i++) {
							ostr << m_item_description[i];
						}
					}
					else {
						ostr.width(35);
						ostr.fill(' ');
						ostr.setf(ios::left);
						ostr << m_item_description;
					}
					ostr.unsetf(ios::left);
					ostr << " | ";
					ostr.width(4);
					ostr.fill(' ');
					ostr << m_quantity_on_hand;
					ostr << " | ";
					ostr.width(4);
					ostr << m_quantity_needed;
					ostr << " | ";
					ostr.width(7);
					ostr << m_price;
					ostr << " |";

				}//if (m_linear_flag == true)
				else {
						ostr << "AMA Item:\n";
						ostr << m_sku << ": " << m_item_description << "\n";
						ostr << "Quantity Needed: " << m_quantity_needed << "\n";
						ostr << "Quantity Available: " << m_quantity_on_hand << "\n";
						ostr << "Unit Price: $";
						ostr << m_price << "\n";
						
						double needed_purchase_fund = m_price * (m_quantity_needed - m_quantity_on_hand);
						ostr.fill(0);
						ostr << "Needed Purchase Fund: $" << fixed << setprecision(2) << needed_purchase_fund << endl;
				}
		}//if (state_of_item.operator bool())
		else {
			ostr << int(this->state_of_item) << ": " << (const char*)(this->state_of_item);
		}
		return ostr;
	}

	int Item::readSku(std::istream& istr) {
		cout << "SKU: ";
		m_sku = ut.getint(40000, 99999);
		return m_sku;
	}

	std::istream& Item::read(std::istream& istr) {
		
		if (m_item_description != nullptr) {
			delete[] m_item_description;
			m_item_description = nullptr;
		}
		clear();

		cout << "AMA Item:"<< endl << "SKU: " << m_sku << endl;
		cout << "Description: ";
		istr.ignore();
	
		string getDescription;
		getline(istr, getDescription, '\n');
		m_item_description = new char[getDescription.length() + 1];
		strcpy(m_item_description, getDescription.c_str());

		//reading quantity needed
		cout << "Quantity Needed: ";
		m_quantity_needed = ut.getint(1, 9999);

		//reading quantity on hand
		cout << "Quantity On Hand: ";
		m_quantity_on_hand = ut.getint(0, m_quantity_needed);

		cout << "Unit Price: $";
		double price;
		istr >> price;
		while (istr.fail()) {
			cout << "Invalid number, retry: ";
			istr.clear();
			istr.ignore(256, '\n');
			istr >> price;
		}

		while (price < 0.0 || price > 9999.00) {
			cout << "Value out of range [0.00<=val<=9999.00]: ";
			istr >> price;
			while (istr.fail()) {
				cout << "Invalid number, retry: ";
				istr.clear();
				istr.ignore(256, '\n');
				istr >> price;
			}
		}
		
		m_price = price; //sets m_price to validated price value

		if (istr.fail()) {
			state_of_item = "\nConsole entry failed!\n";
		}
		return istr;
	}
}//NAMESPACE SDDS