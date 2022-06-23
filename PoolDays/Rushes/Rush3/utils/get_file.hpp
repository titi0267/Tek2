/*
** EPITECH PROJECT, 2022
** B-PDG-300-STG-3-1-PDGRUSH3-elliot.waldvogel
** File description:
** get_file
*/

#ifndef GET_FILE_HPP_
#define GET_FILE_HPP_

#pragma once
#include <string.h>
#include <iostream>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fstream>
#include <vector>
#include <numeric>

class Get_file {
    public:
        Get_file();
        ~Get_file();
        std::string get_file_content(const std::string &);
        std::string get_file_line(const char *find, std::string content, const char *delim);
        std::string eraseSubStr(std::string mainStr, const std::string &toErase);
        std::string getOsName();
        std::string getRamInfo();
        std::string getUsername();
        std::string getHostname();
        std::string getTime();
        std::string getModel();
        std::string getFrequency();
        std::string getCores();
        std::string getActivity();
        void updateTime();
    protected:
    private:
        std::string _hostname;
        std::string _username;
        std::string _time;
        std::string _sysname;
        std::string _cpuModel;
        std::string _cpuFrequency;
        std::string _coresNb;
        std::string _activity;
        std::string _ram;
};

#endif /* !GET_FILE_HPP_ */
