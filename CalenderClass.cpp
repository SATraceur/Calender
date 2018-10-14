#include <iostream>
#include <iomanip> 

using namespace std;


int month_lengths_common[] = {// months start from 1
    0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31
    //0 is not used
};
int month_lengths_leap[] = {// months start from 1
    0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31
};



class Date
{
public:
  Date(){}
  Date(int day, int month, int year)
  {
    this->day = day; this->month = month; this->year = year; 
    //sets the instance variables to the parameters of the function.
    //Could also use date.day = day; If you were a scrub. Or you wanted more control. Should be using date.day_ = day; anyway.
  }
  
  int getDay() const { return day; }
  int getMonth() const { return month; }
  int getYear() const { return year; }
  
  void next(){
    bool isleap = year % 4 == 0;
    int days_in_month = isleap ? month_lengths_leap[month] :  month_lengths_common[month];

    day += 1;
    if (day > days_in_month) { // end of month
      day = 1;
      month += 1;
    }
    if (month > 12) { // end of year
      month = 1;
      year += 1;
    }
  }
  bool precedes(const Date& other) const {
    return year < other.year || (year == other.year && month < other.month)
      || (year == other.year && month == other.month && day < other.day);
  }
  
private:
  //int day = 0, month = 0, year = 0; Don't do this. //Why not? It only works in c++11, much better to initialise variables in the constructor. fairo
  int day;
  int month;
  int year;
};

void next(int& year, int& month, int& day) {
    bool isleap = year % 4 == 0;//wrong y?
    int days_in_month = isleap ? month_lengths_leap[month] : month_lengths_common[month];

    day += 1;
    if (day > days_in_month) { // end of month
        day = 1;
        month += 1;
    }
    if (month > 12) { // end of year
        month = 1;
        year += 1;
    }
}

void write_calendar_grid(int month, int year) {
    // start at the Sunday before 1 January 1901 ...
    Date d = Date(30, 12, 1900); // ... which is 30 December 1900
    
    int weekday = 0;

    Date start;
  
    while (d.precedes(Date(1, month, year))) {
        d.next();
        weekday = (weekday + 1) % 7; // weekdays are 0 .. 6
        if (weekday == 0) {
            start = d;
        }
   }
    d = start;
    weekday = 0;

    while (d.precedes(Date(1, month+1, year))) {
        if (d.getMonth() == month) {
            cout << setw(2) << d.getDay();
        } else {
            cout << "--";
        }
        cout << " ";
        d.next();
        weekday = (weekday + 1) % 7;
        if (weekday == 0) cout << endl; // Sunday starts new row
  }
    cout << endl;
}

int main(int argc, char** argv) {
    //should change the year to 2999 y?
    int month = 3, year = 2016;
    //while (cin >> month >> year)
    {
        cout << month << " " << year << endl;
        cout << "Su Mo Tu We Th Fr Sa" << endl;
        write_calendar_grid(month, year);
    }
}