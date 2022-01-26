
#pragma once

#include <string>
#include <exception>

class NasaError : std::exception
{
    public:
        NasaError(std::string const &message, std::string const &component = "Unknown") throw();
        std::string const &getComponent() const;
        virtual const char* what() const throw();
    //virtual ~Erreur() throw();

    protected:
        std::string _message;
        std::string _component;

};

class MissionCriticalError : public NasaError
{
    public:
        MissionCriticalError(std::string const &message, std::string const &component = "Unknown") throw();
};

class LifeCriticalError : public NasaError
{
    public:
        LifeCriticalError(std::string const &message, std::string const &component = "Unknown") throw();
};

class UserError : public NasaError
{
    public:
        UserError(std::string const &message, std::string const &component = "Unknown") throw();
};

class CommunicationError : public NasaError
{
    public:
        CommunicationError(std::string const &message, std::string const &component = "CommunicationDevice") throw();
};
