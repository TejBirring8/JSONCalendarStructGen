#include "UI.hpp"
#include "ErrorHandling.h"
#include <sys/ioctl.h>
#include <sys/ttycom.h>
#include <cstdlib>
#include <unistd.h>
#include <functional>
#include <cctype>
bool UserInterface::termAvailable = false;
int UserInterface::nRows = 0;
int UserInterface::nCharsPerRow = 0;

template <>
int UserInterface::parseUserInput<int>(const std::string& str) {
    return stoi(str);
}

template <>
std::string UserInterface::parseUserInput<std::string>(const std::string& str) {
    return str;
}

void UserInterface::initialize() {
    const char* term = getenv("TERM");
    termAvailable = term != nullptr;

    // get terminal attributes
    static struct winsize ws;
    if (ioctl(STDIN_FILENO, TIOCGWINSZ, &ws) == -1)
        VerboseError("Failed to get terminal attributes.");

    // print terminal info, (some terminal emulators do not report info, in that case: ignore)
    if (termAvailable) {
        nRows = ws.ws_row;
        nCharsPerRow = ws.ws_col;

        system("clear");

        {
            using namespace std;
            cout << "####~terminal info~####" << endl
                      << term << endl
                      << ws.ws_row << " rows  X  " << ws.ws_col << " chars" << endl
                      << "#######################" << endl << endl;
        }
    } // if (termAvailable)
}



void UserInterface::clear() {
    system("clear");
}



void serveSpecialKey(const std::string& userInput, char specialKey, const std::function<void()>& callback) {
    // dismiss if > 1 char entered
    if (userInput.size() != 1) return;
    // look for LOWER CASE of specialKey char
    size_t pos = userInput.find(specialKey,0);
    if (pos == 0) callback();
    // look for UPPER CASE of specialKey char
    pos = userInput.find(toupper(specialKey),0);
    if (pos == 0) callback();
}