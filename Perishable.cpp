#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include <string.h>
#include "Item.h"
#include "Perishable.h"

using namespace std;
namespace sdds {

	Perishable::Perishable() {
		m_handling_instructions = nullptr;
	}

	Perishable::Perishable(const Perishable& p) {
		m_handling_instructions = nullptr;
		m_expiry_date = p.expiry();
		*this = p;
	}

	Perishable& Perishable::operator=(const Perishable& p) {
		if (this != &p) {
			(Item&)*this = p; 
			m_expiry_date = p.m_expiry_date;
			Item::operator=(p);
			ut.alocpy(m_handling_instructions, p.m_handling_instructions);
		}
		return *this;
	}

	Perishable::~Perishable() {
		delete[] m_handling_instructions;
		m_handling_instructions = nullptr;
	}

	const Date& Perishable::expiry() const {
		return m_expiry_date;
	}

	int Perishable::readSku(std::istream& istr) {
		cout << "SKU: ";
		m_sku = ut.getint(10000, 39999);
		return m_sku;
	}

	std::ofstream& Perishable::save(std::ofstream& ofstr) const{
		if (state_of_item) {
			Item::save(ofstr);
			ofstr << "\t";
			if (m_handling_instructions != nullptr) {
				ofstr << m_handling_instructions;
			}
			ofstr << "\t";
			Date temp_date = m_expiry_date;
			temp_date.formatted(false);
			temp_date.write(ofstr);
		}
		return ofstr;
	}

	std::ifstream& Perishable::load(std::ifstream& ifstr) {
		Item::load(ifstr);
		if (m_handling_instructions != nullptr) {
			delete[] m_handling_instructions;
			m_handling_instructions = nullptr;
		}

		ut.extractChar(ifstr, '\t');
		string handling_instructions;
		getline(ifstr, handling_instructions, '\t');
		if (handling_instructions.length() > 0) {
			ut.alocpy(m_handling_instructions, handling_instructions.c_str());
		}
		else {
			m_handling_instructions = nullptr;
			
		}
		
		ifstr >> m_expiry_date;
		
		ifstr.ignore();
		if (ifstr.fail()) {
			Item::state_of_item = "Input file stream read (perishable) failed!";
		}
		return ifstr;
	}

	std::ostream& Perishable::display(std::ostream& ostr)const {
		if (!state_of_item) {
			ostr << int(this->state_of_item) << ": " << (const char*)(this->state_of_item);
		}
		else {
			if (linear()) {
				Item::display(ostr);
				if (m_handling_instructions != nullptr && strlen(m_handling_instructions) > 0) {
					ostr << "*";
				}
				else {
					ostr << " ";
				}
				ostr << m_expiry_date;
			}
			else {
				ostr << "Perishable ";
				Item::display(ostr);
				ostr << "Expiry date: ";

				ostr << m_expiry_date;
				ostr << endl;
				if (m_handling_instructions != nullptr && strlen(m_handling_instructions) > 0) {
					ostr << "Handling Instructions: ";
					ostr << m_handling_instructions;
					ostr << endl;
				}
			}
		}
		return ostr;
	}

	std::istream& Perishable::read(std::istream& istr) {
		Item::read(istr);
		if (m_handling_instructions != nullptr) {
			delete[] m_handling_instructions;
			m_handling_instructions = nullptr;
		}

		cout << "Expiry date (YYMMDD): ";
		m_expiry_date.read(istr);
		ut.extractChar(istr, '\n');
		cout << "Handling Instructions, ENTER to skip: ";
		char key_ch = istr.peek();
		if (key_ch != '\n') {
			string handling_instructions;
			getline(istr, handling_instructions, '\n');
			ut.alocpy(m_handling_instructions, handling_instructions.c_str());
		}else{
			m_handling_instructions = nullptr;
		}

		if (istr.fail()) {
			this->state_of_item = "Perishable console date entry failed!";
		}
		return istr;
	}

}//NAMESPACE SDDS