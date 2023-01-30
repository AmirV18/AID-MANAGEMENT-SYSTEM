#define _CRT_SECURE_NO_WARNINGS

/*
Name: Amir Vassell
Seneca Email: arvassell@myseneca.ca
Student ID: 154737209
Date Completed: April 10, 2021

I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments.
*/

#include <iostream>
#include <ctime>
#include <string.h>
#include "Utils.h"
using namespace std;
namespace sdds {
   Utils ut;
   void Utils::testMode(bool testmode) {
      m_testMode = testmode;
   }

   void Utils::getSystemDate(int* year, int* mon, int* day) {
      if (m_testMode) {
         if(day) *day = sdds_testDay;
         if(mon) *mon = sdds_testMon;
         if(year) *year = sdds_testYear;
      }
      else {
         time_t t = std::time(NULL);
         tm lt = *localtime(&t);
         if (day) *day = lt.tm_mday;
         if (mon) *mon = lt.tm_mon + 1;
         if (year) *year = lt.tm_year + 1900;
      }
   }

   int Utils::daysOfMon(int month, int year)const {
      int days[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31, -1 };
      int mon = (month >= 1 && month <= 12 ? month : 13)-1;
      return days[mon] + int((mon == 1) * ((year % 4 == 0) && (year % 100 != 0)) || (year % 400 == 0));
   }

   void Utils::alocpy(char*& destination, const char* source) {
       delete[] destination;
       destination = nullptr;
       if (source != nullptr) {
           destination = new char[strlen(source) + 1];
           strcpy(destination, source);

           //edited here
           source = nullptr;
       }
   }

   int Utils::getint(const char* prompt) {
       int number;
       if (prompt != nullptr) {
           cout << prompt;
       }
       cin >> number;
       while (cin.fail()) {
           cout << "Invalid Integer, retry: ";
           cin.clear();
           cin.ignore(256, '\n');
           cin >> number;
       }

       return number;
   }//done

   int Utils::getint(int min, int max, const char* prompt, const char* errMes) {

       int number = getint(prompt);

       while (number < min || number > max) {
           if (errMes != nullptr) {
               cout << errMes << ", retry: ";
               number = getint(prompt);
           }
           else {
               cout << "Value out of range [" << min << "<=val<=" << max << "]: ";
               number = getint(prompt);
           }
       }

       return number;
   }

   void Utils::extractChar(istream& istr, char ch) const {
       char key_ch = istr.peek();
       if (key_ch == ch) {
           istr.ignore();
       }
       else {
           if (key_ch != ch) {
               istr.ignore(1000, ch);
               istr.setstate(ios::failbit);
           }
       }
   }
   
}//namespace sdds