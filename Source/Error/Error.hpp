/*
** EPITECH PROJECT, 2022
** B-OOP-400-STG-4-1-arcade-alexandre.frantz
** File description:
** Error
*/

#ifndef ERROR_HPP_
#define ERROR_HPP_

#include <iostream>

class Error {
    public:
        Error();
        ~Error();

        // Checking
        void checkArgs(int ac, char **av);

        // Setter
        void setReason(const std::string reason);
        void setReturnValue(int returnValue);

        // Guetter
        std::string getReason() const;
        int getReturnValue() const;

        // Display
        void displayReason() const;

        // Exit
        void exitProgram() const;

    protected:
        std::string _reason;
        int _returnValue;
};

#endif /* !ERROR_HPP_ */
