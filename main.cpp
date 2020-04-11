//struct tm {
//    int tm_sec;         /* seconds,  range 0 to 59          */
//    int tm_min;         /* minutes, range 0 to 59           */
//    int tm_hour;        /* hours, range 0 to 23             */
//    int tm_mday;        /* day of the month, range 1 to 31  */
//    int tm_mon;         /* month, range 0 to 11             */
//    int tm_year;        /* The number of years since 1900   */
//    int tm_wday;        /* day of the week, range 0 to 6    */
//    int tm_yday;        /* day in the year, range 0 to 365  */
//    int tm_isdst;       /* daylight saving time             */
//};
#include "consts.h"
#include <iostream>
#include "Utils/UI.hpp"
#include "Utils/ErrorHandling.h"
#include <fstream>
#include <ctime>
#include <algorithm>
#include <unordered_map>
#include "Day.h"




std::unordered_map<std::string, bool> options;
Day days[366];




int getDayOfWeekOfFirstDayOfYear(int year) {
    // get current time as ref
    time_t rawTime;
    struct tm *timeInfo;
    time(&rawTime);
    timeInfo = localtime(&rawTime);
    // modify timeInfo
    timeInfo->tm_year = year - 1900; // Specified year
    timeInfo->tm_mon = 0; // Jan
    timeInfo->tm_mday = 1; // 1st day of Month
    // mktime to re-compute timeInfo
    mktime(timeInfo);
    // get day of week (starting Sunday)
    int day = timeInfo->tm_wday;
    // return day of week (starting Monday)
    return (day == 0) ? 6 : day - 1;
}




void captureArgs(int nArgs, char* argsVector[], char* envVector[]) try {
    using namespace std;

    for (int i = 0; i < nArgs; i++) {
        // arg as string
        string arg = string(argsVector[i]);
        // arg to lowercase
        transform(arg.begin(), arg.end(), arg.begin(),
                      [](unsigned char c){ return tolower(c); });
        // capture arg in map
        if (arg == "debug")
            options["debug"] = true;
    }
} catch (...) {
    VerboseError("Failed to parse args.");
}




int main(int nArgs, char* argsVector[], char* envVector[]) try {
    captureArgs(nArgs, argsVector, envVector);
    UserInterface::initialize();


    auto outputPath = UserInterface::getUserInput<std::string>("Enter output filename:");
    auto outputFile = std::ofstream(outputPath, std::ios::out);


    auto year = UserInterface::getUserInput<int>("Enter year:");
    int _dayOfWeekOfFirstDayOfYear = getDayOfWeekOfFirstDayOfYear(year);
    bool isLeapYear = (year % 4 == 0);
    int _isLeapYearIdx = isLeapYear ? 1 : 0;
    int nDaysInYear = nOfDaysInYear[_isLeapYearIdx];


    // idxDoY - index Day of Year
    outputFile << "{" << std::endl;
    for (int countIdxDayOfYear = 0; countIdxDayOfYear < nDaysInYear; countIdxDayOfYear++) {
        using namespace std;

        /////
        static int countIdxMonthOfYear = 0;
        static int countIdxWeekOfYear = 0;
        static int countIdxDayOfMonth = 0;
        static int countIdxWeekOfMonth = 0;
        static int countIdxDayOfWeek = _dayOfWeekOfFirstDayOfYear;
        /////

        /* if: first day of month */
        if (std::any_of(idxFirstDayOfMonth[_isLeapYearIdx].cbegin(), idxFirstDayOfMonth[_isLeapYearIdx].cend(), [&](int i) {
            return (i == countIdxDayOfYear);
        })) {
            countIdxDayOfMonth = 0;
            countIdxWeekOfMonth = 0;
            countIdxMonthOfYear++;
        };

        // select *this* day
        Day &day = days[countIdxDayOfYear];
        // assign year info
        day.year = year;
        day.isLeapYear = isLeapYear;
        // assign week of year
        day.weekOfYear = countIdxWeekOfYear;
        // assign day of year
        day.dayOfYear = countIdxDayOfYear;
        // assign day of week
        day.dayOfWeek = countIdxDayOfWeek;
        countIdxDayOfWeek = (countIdxDayOfWeek+1) % 7;
        // assign month of year
        day.monthOfYear = countIdxMonthOfYear;
        // assign day of month
        day.dayOfMonth = countIdxDayOfMonth;
        countIdxDayOfMonth++;
        // assign week of month
        day.weekOfMonth = countIdxWeekOfMonth;

        /* if: first day of week */
        if (countIdxDayOfWeek == 0) {
            countIdxWeekOfMonth++;
            countIdxWeekOfYear++;
        }

        if (options["debug"])
            cout << "dayOfWeek: " << day.dayOfWeek <<
            ", dayOfYear: " << day.dayOfYear <<
            ", dayOfMonth: " << day.dayOfMonth <<
            ", monthOfYear: " << day.monthOfYear <<
            ", weekOfMonth: " << day.weekOfMonth <<
            ", weekOfYear: " << day.weekOfYear
            << endl;

        outputFile << " {" << endl;
        outputFile << "     year: " << day.year << ", " << endl;
        outputFile << "     isLeapYear: " << (day.isLeapYear ? "true" : "false") << ", " << endl;
        outputFile << "     dayOfYear: " << day.dayOfYear << ", " << endl;
        outputFile << "     weekOfYear: " << day.weekOfYear << ", " << endl;
        outputFile << "     monthOfYear: " << day.monthOfYear << ", " << endl;
        outputFile << "     weekOfMonth: " << day.weekOfMonth << ", " << endl;
        outputFile << "     dayOfMonth: " << day.dayOfMonth << ", " << endl;
        outputFile << "     dayOfWeek: " << day.dayOfWeek << ", " << endl;
        outputFile << " }," << endl;
    }



    outputFile << "}" << std::endl;
    outputFile.close();
    return 0;
} catch(...) {
    FatalError("Unknown error occurred.");
}