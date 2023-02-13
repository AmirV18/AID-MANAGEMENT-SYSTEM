#ifndef SDDS_UTILS_H
#define SDDS_UTILS_H
namespace sdds {
   const int sdds_testYear = 2023; //change the date here
   const int sdds_testMon = 03;
   const int sdds_testDay = 31;
   class Utils {
      bool m_testMode = false;
   public:

      // this function will be used to get the current system date or the test date if m_testMode is true
      void getSystemDate(int* year = nullptr, int* mon = nullptr, int* day = nullptr);
      // this function will return the number of days in a month based on the year
      // 1<=mon<=12  year: four digit number (example: 2021)
      int daysOfMon(int mon, int year)const;
      // Puts the system date in test mode, where getSystemDate() function will return 2022, 03, 31
      // or whatever the three constant test dates are set to
      void testMode(bool testmode = false);

      //=====================================
      /*Safely allocates memory in destination and copies the source into it.
        deletes the destination dynamic array and sets it to null
        if the source is not null
        Allocates memory in the destination to the size of the source and copies the source into it.*/
      void alocpy(char*& destination, const char* source);

      //===============================================
      /*If the prompt is not null, it will display it. Then it 
      performs a foolproof entry of an integer. If the user enters 
      an invalid integer it will display "Invalid Integer, retry: " 
      and will not let the user leave the function until a valid integer is entered.*/
      int getint(const char* prompt = nullptr);

      //==================================
      /*If the prompt is not null it will be displayed before getting 
      a valid integer.(reuse the previous getint())
      If the entered integer is not within the acceptable range (min and max) then 
      an error message is displayed and it will not let the user leave the function 
      until an acceptable value is entered. When printing the error message, if the 
      errMes argument is not null it will be displayed followed by ", retry: " otherwise the 
      general error message "Value out of range [min<=val<=max]: " is displayed (replacing min 
      and max with their values)*/
      int getint(int min, int max, const char* prompt = nullptr, const char* errMes = nullptr);
   
      void extractChar(std::istream&, char) const;
   };
   extern Utils ut;
}

#endif // !SDDS_UTILS_H
