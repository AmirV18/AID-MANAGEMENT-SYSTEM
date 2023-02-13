#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include "iProduct.h"
using namespace std;

namespace sdds {

	std::ostream& operator<<(std::ostream& ostr, const iProduct& iP) {
		iP.display(ostr);
		return ostr;
	}

	std::istream& operator>>(std::istream& istr, iProduct& iP) {
		iP.read(istr);
		return istr;
	}

}//NAMESPACE SDDS
