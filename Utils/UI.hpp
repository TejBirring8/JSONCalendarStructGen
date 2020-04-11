#ifndef NUMBEROFDAYSINMONTH_UI_HPP
#define NUMBEROFDAYSINMONTH_UI_HPP
#include <string>
#include <iostream>

void serveSpecialKey(const std::string& userInput, char specialKey, const std::function<void()>& callback);

namespace UserInterface {
    extern bool termAvailable;
    extern int nRows;
    extern int nCharsPerRow;
    void initialize();
    void clear();


    template <typename T> T parseUserInput(const std::string& str);

    template <>
    int parseUserInput<int>(const std::string& str);

    template <>
    std::string parseUserInput<std::string>(const std::string& str);


    template <typename T>
    T getUserInput(const std::string&& prompt) {
        using namespace std;
        BEGIN:
        // show prompt
        cout << prompt << " ['x' to exit] " << endl;
        // get user input into buff
        char userInput[256];
        cin.getline(userInput, 256);
        // to string obj
        string userInputStr(userInput);
        // act on special keys
        serveSpecialKey(userInput, 'x',
            []{
                cout << "exiting..." << endl;
                exit(EXIT_SUCCESS);
            });
        // parse to specified T
            T t;
            try {
                t = parseUserInput<T>(userInputStr);
            }
            catch(exception& e) { goto BEGIN; }; // if here: try again!
        // return parsed type
        return t;
    }
};



#endif //NUMBEROFDAYSINMONTH_UI_HPP
