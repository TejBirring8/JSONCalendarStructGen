#ifndef NUMBEROFDAYSINMONTH_ERRORHANDLING_H
#define NUMBEROFDAYSINMONTH_ERRORHANDLING_H

#include <string>
#include <iostream>
#include <type_traits>
#include <exception>

/*
 * functions return an object which encapsulates the legitimate result (if present), otherwise
 * holds the error message, an indicator of how the error will be handled, and the handler itself.
 */
enum class ErrorHandlingOpt { TERMINATE, WRITE_TO_CERR, IGNORE };


template <typename THowToHandle>
struct Error {
    const std::string Message;
    explicit Error(const std::string&& errorMsg) : Message(errorMsg) {
        if (std::is_same<THowToHandle, std::integral_constant<ErrorHandlingOpt, ErrorHandlingOpt::IGNORE> >::value) {}

        if (std::is_same<THowToHandle, std::integral_constant<ErrorHandlingOpt, ErrorHandlingOpt::WRITE_TO_CERR> >::value) {
            std::cerr << "Error: " << Message << std::endl;
        }

        if (std::is_same<THowToHandle, std::integral_constant<ErrorHandlingOpt, ErrorHandlingOpt::TERMINATE> >::value) {
            std::cerr << "Fatal Error: " << Message << std::endl;
            std::terminate();
        }
    }
};


typedef Error<std::integral_constant<ErrorHandlingOpt, ErrorHandlingOpt::IGNORE> > IgnoredError;
typedef Error<std::integral_constant<ErrorHandlingOpt, ErrorHandlingOpt::WRITE_TO_CERR> > VerboseError;
typedef Error<std::integral_constant<ErrorHandlingOpt, ErrorHandlingOpt::TERMINATE> > FatalError;






#endif //NUMBEROFDAYSINMONTH_ERRORHANDLING_H
