#ifndef STATUS_H_
#define STATUS_H_

#include <iostream>
using namespace std;

namespace sdds {
	class Status {
		char* m_description = {}; //A dynamic CString for the description of the status of an object.
		int m_statusCode; //An integer for an optional status Code.

	public:
		//Status();
		Status(const char*, int = 0);
		Status(int = 0);

		//rule of three
		Status(const Status&);
		Status& operator=(const Status&);
		~Status();

		//Assignment operator overloads
		Status& operator=(int);
		Status& operator=(const char*);

		//Type conversion overloads
		operator int() const;
		operator const char* () const;
		operator bool() const;

		Status& clear();
	};

	std::ostream& operator<<(std::ostream&, const Status&);
}//namespace sdds
#endif