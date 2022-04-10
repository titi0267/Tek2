/*
** EPITECH PROJECT, 2022
** B-OOP-400-STG-4-1-arcade-alexandre.frantz
** File description:
** Error
*/

#ifndef ERROR_HPP_
#define ERROR_HPP_

#include <iostream>
#include "../define.hpp"
#include <string>

class Error {
    public:
        Error(char *error);
        ~Error();

        // Checking
        void checkArgs(int ac, char **av);

        // Setter
        void setError(const char *reason);
        void getError(const char *reason);
        void setReason(const std::string reason);
        void setReturnValue(int returnValue);

        const char *what();
        // Getter
        std::string getReason() const;
        int getReturnValue() const;

        // Display
        void displayReason() const;

        // Exit
        void exitProgram() const;
        void exitError(int retValue, const std::string reason);

    protected:
        std::string _reason;
        int _returnValue;
        std::string _error;
};

#endif /* !ERROR_HPP_ */
