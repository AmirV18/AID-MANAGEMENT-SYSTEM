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
#include <string>
#include <fstream>
#include <iomanip>
#include "Status.h"
#include "Utils.h"
#include "Date.h"
#include "Menu.h"
#include "AidMan.h"
#include "Perishable.h"

using namespace std;

namespace sdds {

	unsigned int AidMan::menu() const{
		//int year, month, day;
		//ut.getSystemDate(&year, &month, &day);

		cout << "Aid Management System\n";
		cout << "Date: " << Date() << endl;
		cout << "Data file: ";
		if (m_filename != nullptr) {
			cout << m_filename << endl;
		}
		else {
			cout << "No file\n";
		}

		cout << "---------------------------------\n";

		unsigned int chosen = main_menu.run();
		return chosen;
	}

	AidMan::~AidMan() {
		main_menu.clearMemory();
		//delete[] m_filename;
		
		deallocate();
		//delete[] m_iProdArray; /////here
		
	}

	void AidMan::save() {
		if (m_filename != nullptr) {
			ofstream ofstr(m_filename, ios::out);

			for (int i = 0; i < m_num_of_iprod_items; i++)
			{
				m_iProdArray[i]->save(ofstr);
				//with a \n at the end
				ofstr << '\n';
			}
			//CONTINUE HERE

			ofstr.close();
		}
		else {}
	}

	void AidMan::deallocate() {
		for (int i = 0; i < m_num_of_iprod_items; i++)
		{
			delete m_iProdArray[i];
		}
			delete[] m_filename;
			m_filename = nullptr;
			m_num_of_iprod_items = 0;
	}

	bool AidMan::load() {
		
			save(); //saves all the existing iProducts
			deallocate(); //deallocates all the resources of the aidman class
			cout << "Enter file name: ";
			string tempFileName;
			cin >> tempFileName;
			ut.alocpy(m_filename, tempFileName.c_str());
			bool isLoaded = false;
			ifstream ifstr(m_filename, ios::in); //opens a file for reading
			if (!ifstr.is_open()) {
				ifstr.close(); //close dont need anymore
				cout << "Failed to open " << m_filename << " for reading!\n";
				cout << "Would you like to create a new data file?\n";
				cout << "1- Yes!\n";
				cout << "0- Exit\n";
				cout << "> ";
				int option = 0;
				option = ut.getint(0, 1);
				cout << endl;

				if (option == 1) {
					ofstream fout(m_filename);
					fout.close();
				}
				else {
					deallocate();
				}
			}//checks if the file wasnt opened correctly
			else {//the file is opened successfully here
		
				while(!ifstr.eof())
				{//FOR LOOP FOR IF FILE IS OPEN
					

					char key_ch = ifstr.peek();
					if (key_ch == '\n') {
						ut.extractChar(ifstr, '\n');
						key_ch = ifstr.peek();
					}
					if (key_ch == '\t') {
						ut.extractChar(ifstr, '\t');
						key_ch = ifstr.peek();
					}
					
					
					if (key_ch == '1' || key_ch == '2' || key_ch == '3') {
						//deallocate();
						m_iProdArray[m_num_of_iprod_items] = new Perishable;
						m_iProdArray[m_num_of_iprod_items]->load(ifstr);
						
						if (m_iProdArray[m_num_of_iprod_items]) {
							
							m_num_of_iprod_items += 1;
							isLoaded = true;

						}
						else {
							delete m_iProdArray[m_num_of_iprod_items];
						}
						
					}
					else if (key_ch == '4' || key_ch == '5' || key_ch == '6' || key_ch == '7' || key_ch == '8' || key_ch == '9') {
						
						m_iProdArray[m_num_of_iprod_items] = new Item;
						m_iProdArray[m_num_of_iprod_items]->load(ifstr);
						if (m_iProdArray[m_num_of_iprod_items]) {
							//m_iProdArray[m_num_of_iprod_items]->load(ifstr);
							m_num_of_iprod_items += 1;
							isLoaded = true;
						}
						else {
							delete m_iProdArray[m_num_of_iprod_items];
						}
						
					}
					else {
						ifstr.setstate(ios::failbit);
					}

				}
				cout << m_num_of_iprod_items << " records loaded!\n\n";
			}//ELSE FOR WHEN THE FILE IS OPENED SUCCESSFULLY
			
			ifstr.close();
			
			return isLoaded;
	}//load function

	int AidMan::list(const char* sub_desc) {
		int numOfItemsPrinted = 0;
		if (m_num_of_iprod_items > 0) {//FIX HERE
			cout << " ROW |  SKU  |";
			cout << left << setw(36) << setfill(' ') << " Description" << " | ";
			cout << "Have";
			cout << " | ";
			cout << "Need";
			cout << " | ";
			cout << " Price ";
			cout << " | ";
			cout.setf(ios::left);
			cout << "Expiry\n";
			cout.unsetf(ios::left);
			cout << "-----+-------+-------------------------------------+------+------+---------+-----------\n";

			int row = 0;
			for (int i = 0; i < m_num_of_iprod_items; i++)
			{
				row = i + 1;
				if (sub_desc == nullptr) {
					cout << setw(4)<< setfill(' ') << row << " | ";
					m_iProdArray[i]->linear(true);
					cout << *m_iProdArray[i];
					cout << endl;
					row += 1;
					numOfItemsPrinted++;
				}
				else {
					if (m_iProdArray[i]->operator==(sub_desc)) {
						m_iProdArray[i]->linear(true);
						cout << setw(4)<< setfill(' ') << row << " | ";
						cout << *m_iProdArray[i];
						cout << endl;
						row += 1;
						numOfItemsPrinted++;
					}
				}
			}

			cout << "-----+-------+-------------------------------------+------+------+---------+-----------\n";
			
			
		}
		else {
			cout << "The list is empty!\n\n";
		}


		return numOfItemsPrinted;
	}

	int AidMan::search(int sku) const {
		int foundIndex = -1;
		for (int i = 0; i < m_num_of_iprod_items; i++)
		{
			if (m_iProdArray[i]->operator==(sku)) {
				foundIndex = i;
			}
			
		}

		return foundIndex;
	}

	void AidMan::remove(int index) {
		delete m_iProdArray[index];
		//m_iProdArray[index] = nullptr;
		//HOW TO SHIFT THEM OVER
		iProduct* temp;
		for (int i = index; i < m_num_of_iprod_items; i++)
		{
			temp = m_iProdArray[i + 1];
			m_iProdArray[i] = temp;
			temp = nullptr;
		}
		/////////////////////////

		m_num_of_iprod_items -= 1;
		
		

	}

	void AidMan::update() {
		/////////////
		
		char* description = nullptr;
		//delete[] description;
		string descriptionToLookFor;
		int numFound;
		int qty;
		cout << "Item description: ";
		cin.ignore();
		getline(cin, descriptionToLookFor);
		if (descriptionToLookFor.length() > 0) {
			ut.alocpy(description, descriptionToLookFor.c_str());
		}
		else {
			delete[] description;
			description = nullptr;
		}

		numFound = list(description);
		if (numFound > 0) {
			cout << "Enter SKU: ";
			int sku = ut.getint(10000, 99999);
			int index = search(sku);
			if (index > -1) {
				cout << "1- Add\n";
				cout << "2- Reduce\n";
				cout << "0- Exit\n> ";
				int option = 0;
				option = ut.getint(0, 2);
				if (option == 0) {
					cout << "Aborted!\n\n";
				}
				else if (option == 1) {
					//ADD//
					if (m_iProdArray[index]->qty() == m_iProdArray[index]->qtyNeeded()) {
						cout << "Quantity Needed already fulfilled!\n\n";
					}
					else {
						cout << "Quantity to add: ";
						qty = ut.getint(1, (m_iProdArray[index]->qtyNeeded() - m_iProdArray[index]->qty()));
						m_iProdArray[index]->operator+=(qty);
						cout << qty << " item(s) added!\n\n";
					}
				}
				else if (option == 2) {
					if (m_iProdArray[index]->qty() == 0) {
						cout << "Quantity on hand is zero!\n\n";
					}
					else {
						cout << "Quantity to reduce: ";
						qty = ut.getint(1, m_iProdArray[index]->qty());
						m_iProdArray[index]->operator-=(qty);
						cout << qty << " item(s) removed!\n\n";
					}
				}
			}
			else {
				cout << "Item with SKU number " << sku << " not found.\n\n";
			}
		}
		else {
			cout << "No matches found\n\n";
		}
		delete[] description;
	}

	void AidMan::sort() {
		for (int i = 0; i < m_num_of_iprod_items; i++)
		{
			for (int j = 0; j < (m_num_of_iprod_items - 1); j++) {
				if ((m_iProdArray[j]->qtyNeeded() - m_iProdArray[j]->qty()) < (m_iProdArray[j + 1]->qtyNeeded() - m_iProdArray[j + 1]->qty())) 
				{
					iProduct* temp = m_iProdArray[j];
					m_iProdArray[j] = m_iProdArray[j+1];
					m_iProdArray[j+1] = temp;
				}
			}
		}

		cout << "Sort completed!\n\n";
	}

	void AidMan::ship() {
		int productsShipped = 0;
		ofstream ofstr("shippingOrder.txt", ios::out);
		ofstr << "Shipping Order, Date: " << Date() << endl;
		ofstr << " ROW |  SKU  |";
		ofstr << left << setw(36) << setfill(' ') << " Description" << " | ";
		ofstr << "Have";
		ofstr << " | ";
		ofstr << "Need";
		ofstr << " | ";
		ofstr << " Price ";
		ofstr << " | ";
		ofstr.setf(ios::left);
		ofstr << "Expiry\n";
		ofstr.unsetf(ios::left);
		ofstr << "-----+-------+-------------------------------------+------+------+---------+-----------\n";
		int row = 1;
		for (int i = 0; i < m_num_of_iprod_items; i++)
		{
			if (m_iProdArray[i]->qty() == m_iProdArray[i]->qtyNeeded()) {
				m_iProdArray[i]->linear(true);
				ofstr << setw(4) << setfill(' ') << row << " | ";
				ofstr << *m_iProdArray[i] << endl;;
				remove(i);
				productsShipped++;
				row++;
			}
		}
		ofstr << "-----+-------+-------------------------------------+------+------+---------+-----------\n";

		cout << "Shipping Order for " << productsShipped << " times saved!\n\n";
	}

	void AidMan::run() {
		int flag = 0;
		bool isLoaded = false;
		int numOfItemsPrinted = 0;
		int numFound = 0;
		int index1;
		int sku;
		string descriptionToLookFor;
		char* description{};
		while (flag == 0) {
			
			int numberOfChosen = menu();
			if (numberOfChosen != 0 && m_filename == nullptr && numberOfChosen != 7) {
				numberOfChosen = 7;
			}

			if (numberOfChosen == 0) {
				flag = 1;
				cout << "Exiting Program!\n";
				delete[] description;
				save(); //supposed to go here
				//deallocate();
			}
			else {
				switch (numberOfChosen) {
				case 1:
					cout << "\n****List Items****\n";
					numOfItemsPrinted = list();
					if (numOfItemsPrinted > 0) {
						cin.ignore();
						cout << "Enter row number to display details or <ENTER> to continue:\n> ";
						if (cin.peek() != '\n') {
							int rowNum = 0;
							rowNum = ut.getint(1, numOfItemsPrinted);
							m_iProdArray[rowNum - 1]->linear(false);
							cout << *m_iProdArray[rowNum - 1];
							cout << "\n\n";
						}
						else {
							cout << endl;
						}
					}
					break;
				case 2:
					cout << "\n****Add Item****\n";
					if (m_num_of_iprod_items >= sdds_max_num_items) {
						cout << "Database full!";
					}
					else {
						cout << "1- Perishable\n";
						cout << "2- Non-Perishable\n";
						cout << "-----------------\n";
						cout << "0- Exit\n> ";
						int option;
						option = ut.getint(0, 2);
						if (option == 0) {
							cout << "Aborted\n";
						}
						else {
							//cout << "SKU: ";
							int skuRead;
							int index;
							if (option == 1) {
								m_iProdArray[m_num_of_iprod_items] = new Perishable;
								 skuRead = m_iProdArray[m_num_of_iprod_items]->readSku(cin);
								 index = search(skuRead);//code the search
								if (index == -1) {//meaning it is not found
									m_iProdArray[m_num_of_iprod_items]->read(cin);
									cout << endl;
									if (m_iProdArray[m_num_of_iprod_items]) {
										m_num_of_iprod_items++;
									}
								}
								else {//meaning it is found
									cout << "Sku: " << skuRead << " is already in the system, try updating quantity instead.\n\n";
									delete m_iProdArray[m_num_of_iprod_items];
								}
							}
							else if (option == 2) {
								m_iProdArray[m_num_of_iprod_items] = new Item;
								 skuRead = m_iProdArray[m_num_of_iprod_items]->readSku(cin);
								 index = search(skuRead);//code the search
								if (index == -1) {//meaning it is not found
									m_iProdArray[m_num_of_iprod_items]->read(cin);
									cout << endl;
									if (m_iProdArray[m_num_of_iprod_items]) {
										m_num_of_iprod_items++;
									}
								}
								else {//meaning it is found
									cout << "Sku: " << skuRead << " is already in the system, try updating quantity instead.\n\n";
									delete m_iProdArray[m_num_of_iprod_items];
								}
							}
						}

					}
					break;
				case 3:
					cout << "\n****Remove Item****\n";
					cout << "Item description: ";
						cin.ignore();
						getline(cin, descriptionToLookFor);
						if (descriptionToLookFor.length() > 0) {
							ut.alocpy(description, descriptionToLookFor.c_str());
						}
						else {
							delete[] description;
							description = nullptr;
						}

						numFound = list(description);
						if (numFound > 0) {
							cout << "Enter SKU: ";
							sku = ut.getint(10000, 99999);
							index1 = search(sku);
							if (index1 == -1) {
								cout << "SKU not found";
							}
							else if (index1 > -1) {
								cout << "Following item will be removed: \n";
								m_iProdArray[index1]->linear(false);
								m_iProdArray[index1]->display(cout);
								cout << "\nAre you sure?\n";
								cout << "1- Yes!\n";
								cout << "0- Exit\n> ";
								int option;
								cin >> option;
								if (option == 1) {
									remove(index1);
									cout << "Item removed!\n\n";
								}
								else {
									cout << "Aborted!\n\n";
								}
							}
						}
						else {
							cout << "Item with " << description << " not found!\n\n";
						}
					
					break;
				case 4:
					cout << "\n****Update Quantity****\n";
					update();
					break;
				case 5:
					cout << "\n****Sort****\n";
					sort();
					break;
				case 6:
					cout << "\n****Ship Items****\n";
					ship();
					break;
				case 7:
					cout << "\n****New/Open Aid Database****\n";
					isLoaded = load();
					break;
				}//case block
			}//if-else block
		}//while block
	}//function block

}//namespace sdds
