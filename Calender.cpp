#include <iostream>
#include <iomanip>

using namespace std;

int month_lengths_common[] = {// months start from 1
    0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31
};
int month_lengths_leap[] = {// months start from 1
    0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31
};

void next(int& year, int& month, int& day) {
    bool isleap = year % 4 == 0;
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
    int y = 1900, m = 12, d = 30; // ... which is 30 December 1900
    int weekday = 0;

    int start_y, start_m, start_d;
    while (y < year || (y == year && m < month)) {
        next(y, m, d);
        weekday = (weekday + 1) % 7; // weekdays are 0 .. 6
        if (weekday == 0) {
            start_y = y;
            start_m = m;
            start_d = d;
        }
   }
    y = start_y;
    m = start_m;
    d = start_d;
    weekday = 0;

    while (m == start_m || m == month) {
        if (m == month) {
            cout << setw(2) << d;
        } else {
            cout << "  ";
        }
        cout << " ";
        next(y, m, d);
        weekday = (weekday + 1) % 7;
        if (weekday == 0) cout << endl; // Sunday starts new row
  }
    cout << endl;
}

int main(int argc, char** argv) {
    int month, year;
    while (cin >> month >> year) {
        cout << month << " " << year << endl;
        cout << "Su Mo Tu We Th Fr Sa" << endl;
        write_calendar_grid(month, year);
    }
}