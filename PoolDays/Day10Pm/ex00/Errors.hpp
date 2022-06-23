
#pragma once

#include <string>
#include <exception>

class NasaError : public std::exception
{
    public:
        NasaError(std::string const &message, std::string const &component = "Unknown");
        std::string const &getComponent() const;
        virtual const char* what() const noexcept;

    protected:
        std::string _message;
        std::string _component;

};

class MissionCriticalError : public NasaError
{
    public:
        MissionCriticalError(std::string const &message, std::string const &component = "Unknown");
};

class LifeCriticalError : public NasaError
{
    public:
        LifeCriticalError(std::string const &message, std::string const &component = "Unknown");
};

class UserError : public NasaError
{
    public:
        UserError(std::string const &message, std::string const &component = "Unknown");
};

class CommunicationError : public NasaError
{int main(void)
{
    int i = 0;
    return (i);
}
    public:
        CommunicationError(std::string const &message);
};
