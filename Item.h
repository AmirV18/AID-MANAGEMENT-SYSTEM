#ifndef	ITEM_H_
#define ITEM_H_
#include "iProduct.h"
#include "Status.h"
#include "Utils.h"
namespace sdds {

	class Item : public iProduct { //inheriting funcitons from iProduct
	private:
		double m_price; //a double for price
		int m_quantity_on_hand; //an integer for quantity on hand
		int m_quantity_needed; //an integer for needed quantity. This integer is the target amount for the item to be acquired.
		char* m_item_description; //dynamic cstring foritem description
		bool m_linear_flag; //a boolean flag to dictate to the display function if the next output is going to be linear to descriptive.

	protected:
		Status state_of_item; // Status object to hold the state of the Item object
		int m_sku; //an integer value to hold the Stock - Keeping Unit number.
		bool linear() const; //query called linear that returns the linear flag of the Item

	public:
		Item(); //default constructor sets all attributes to 0, nullptr and false
		
		//RULE OF THREE//
		Item(const Item&);
		Item& operator=(const Item&);
		~Item();
		/////////////////

		//virtual public query iProduct overrides
		int qtyNeeded() const; //returns the needed-quantity attribute
		int qty() const; //returns the on - hand quantity attribute
		operator double() const; //overload returns the price
		operator bool() const; //overload returns the state of the object being good

		//virtual public modifier iProduct overrides
		int operator-=(int qty); //reduces the on-hand quantity by the received value
		int operator+=(int qty); // increases the on-hand quantity by the received value
		void linear(bool isLinear); //sets the linear flag attribute to true or false

		/*
		modifier called clear that does not accept any argument and sets 
		the state of the Item object back to good, by resetting the state attribute.
		*/
		void clear();

		bool operator==(int sku)const;
		bool operator==(const char* description)const;

		std::ofstream& save(std::ofstream& ofstr) const;
		std::ifstream& load(std::ifstream& ifstr);
		std::ostream& display(std::ostream& ostr)const;
		int readSku(std::istream& istr);
		std::istream& read(std::istream& istr);

		void setEmpty() {
			m_price = 0.0; //a double for price
			m_quantity_on_hand = 0; //an integer for quantity on hand
			m_quantity_needed = 0; //an integer for needed quantity. This integer is the target amount for the item to be acquired.
			m_item_description = nullptr; //dynamic cstring foritem description
			m_linear_flag = false; //a boolean flag to dictate to the display function if the next output is going to be linear to descriptive.
			//Status state_of_item; // Status object to hold the state of the Item object
			m_sku = 0; //an integer value to hold the Stock - Keeping Unit number.
		}

		void clearMemory() {
			delete[] m_item_description;

			m_price = 0.0; //a double for price
			m_quantity_on_hand = 0; //an integer for quantity on hand
			m_quantity_needed = 0; //an integer for needed quantity. This integer is the target amount for the item to be acquired.
			m_item_description = nullptr; //dynamic cstring foritem description
			m_linear_flag = false; //a boolean flag to dictate to the display function if the next output is going to be linear to descriptive.
			//Status state_of_item; // Status object to hold the state of the Item object
			m_sku = 0; //an integer value to hold the Stock - Keeping Unit number.
		}

	};//CLASS ITEM
}//NAMESPACE SDDS
#endif