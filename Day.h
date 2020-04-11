#ifndef NUMBEROFDAYSINMONTH_DAY_H
#define NUMBEROFDAYSINMONTH_DAY_H
#include <string>
#include <array>
#include "DayOfWeek.h"

struct Day {
    // year
    int year;
    bool isLeapYear;

    // month
    int monthOfYear;

    // week of year
    int weekOfYear;
    // week of month
    int weekOfMonth;

    // day of year
    int dayOfYear;
    // day of month
    int dayOfMonth;
    // day of week
    int dayOfWeek;
};

#endif //NUMBEROFDAYSINMONTH_DAY_H
