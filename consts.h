#ifndef NUMBEROFDAYSINMONTH_CONSTS_H
#define NUMBEROFDAYSINMONTH_CONSTS_H
#include <array>

const int nOfDaysInMonth[2][12] = {
        //  common year = [0]
        {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
        //  leap year = [1]
        {31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
};

const std::array<int, 11> idxFirstDayOfMonth[2] = { // accumulative
        //  common year = [0]
        {/*0,*/ 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334},
        //  leap year = [1]
        {/*0,*/ 31, 60, 91, 121, 152, 182, 213, 244, 274, 305, 335}
};

const int nOfDaysInYear[2] = {
        365,    // common year = [0]
        366     // leap year = [1]
};












#endif //NUMBEROFDAYSINMONTH_CONSTS_H
