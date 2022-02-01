/*
** EPITECH PROJECT, 2022
** B-PDG-300-STG-3-1-PDGRUSH3-elliot.waldvogel
** File description:
** get_file
*/

#include "get_file.hpp"

Get_file::Get_file()
{
    char hostname[HOST_NAME_MAX];
    char username[LOGIN_NAME_MAX];
    time_t now = time(0);
    char *dt = ctime(&now);

    gethostname(hostname, HOST_NAME_MAX);
    getlogin_r(username, LOGIN_NAME_MAX);

    _hostname = hostname;
    _username = username;
    _time = dt;
    _time.pop_back();
    _sysname = getOsName();
    _ram = getRamInfo();
}

Get_file::~Get_file()
{
}

void Get_file::updateTime()
{
    time_t now = time(0);
    char *dt = ctime(&now);

    _time = dt;
}

std::string Get_file::getHostname() {
    return _hostname;
}

std::vector<size_t> get_cpu_times() {
    std::ifstream proc_stat("/proc/stat");
    proc_stat.ignore(5, ' ');
    std::vector<size_t> times;
    for (size_t time; proc_stat >> time; times.push_back(time));
    return times;
}

bool get_cpu_times(size_t &idle_time, size_t &total_time) {
    const std::vector<size_t> cpu_times = get_cpu_times();
    if (cpu_times.size() < 4)
        return false;
    idle_time = cpu_times[3];
    total_time = std::accumulate(cpu_times.begin(), cpu_times.end(), 0);
    return true;
}

std::string Get_file::getActivity()
{
    static size_t previous_idle_time=0, previous_total_time=0;
    size_t idle_time, total_time;
    get_cpu_times(idle_time, total_time);
    const float idle_time_delta = idle_time - previous_idle_time;
    const float total_time_delta = total_time - previous_total_time;
    const float utilization = 100.0 * (1.0 - idle_time_delta / total_time_delta);
    previous_idle_time = idle_time;
    previous_total_time = total_time;

    return std::to_string(utilization);
}

std::string Get_file::get_file_content(const std::string &filename)
{
    std::ifstream file(filename, std::ios::in);
    std::string err = "";

    if (!file) {//cannot open file
        return err;
    }
    std::string str((std::istreambuf_iterator<char>(file)),(std::istreambuf_iterator<char>()));
    file.close();
    return str;
}

std::string Get_file::get_file_line(const char *find, std::string content, const char *delim)
{
    char *str = strdup(content.c_str());
    std::string ptr = strtok(str, delim);
    std::string err = "";
    int i = 0;

    while (ptr[i] != '\0') {
        if (strncmp(find, str, strlen(find)) == 0) {
            return ptr;
        }
        i++;
    }
    return (err);
}

std::string Get_file::eraseSubStr(std::string mainStr, const std::string &toErase)
{
    size_t pos = std::string::npos;
    std::string err = "";
    if (mainStr.compare(err))
        return (err);
    while ((pos = mainStr.find(toErase))!= std::string::npos)
    {
        mainStr.erase(pos, toErase.length());
    }
    return (mainStr);
}

std::string Get_file::getOsName()
{
    std::string os_name = get_file_content("/etc/os-release");
    char *str = strdup(os_name.c_str());
    char *ptr = strtok(str, "\n");
    int i = 0;
    std::string tmp;

    while (ptr != NULL) {
        if (strncmp("NAME=", ptr, 5) == 0) {
            tmp = strdup(ptr);
            break;
        }
        for (; ptr[i] != '\n'; i++);
        ptr = strtok(NULL, "\n");
    }
    tmp.erase(0, 6);
    tmp.pop_back();
    return tmp;
}

std::string Get_file::getRamInfo()
{
    std::string err = "";
    return (err);
}

std::string Get_file::getUsername()
{
    return _username;
}

std::string Get_file::getTime()
{
    return _time;
}

std::string Get_file::getCores()
{
    std::string _coresNb = get_file_content("/proc/cpuinfo");
    char *str = strdup(_coresNb.c_str());
    char *ptr = strtok(str, "\n");
    int i = 0;
    std::string tmp;

    while (ptr != NULL) {
        if (strncmp("cpu cores", ptr, 9) == 0) {
            tmp = strdup(ptr);
            break;
        }
        for (; ptr[i] != '\n'; i++);
        ptr = strtok(NULL, "\n");
    }
    tmp = tmp.erase(0, 12);
    return tmp;
}

std::string Get_file::getModel()
{
    std::string model_name = get_file_content("/proc/cpuinfo");
    char *str = strdup(model_name.c_str());
    char *ptr = strtok(str, "\n");
    int i = 0;
    std::string tmp;

    while (ptr != NULL) {
        if (strncmp("model name", ptr, 8) == 0) {
            tmp = strdup(ptr);
            break;
        }
        for (; ptr[i] != '\n'; i++);
        ptr = strtok(NULL, "\n");
    }
    tmp = tmp.erase(0, 12);
    return tmp;
}

std::string Get_file::getFrequency()
{
    std::string cpuInfo = get_file_content("/proc/cpuinfo");
    return (eraseSubStr(get_file_line("cpu MHz		: ", cpuInfo, "\n"), "cpu MHz		: "));
}

// std::string *Get_file::getActivity()
// {
//     std::string *tab = NULL;
//     const char *cores = this->getCores().c_str();
//     int n = std::stoi(cores);
//     tab = new std::string[n];
//     std::string cpuInfo = get_file_content("/proc/stat");
//     std::string temp;
//     std::string dest;
//     char ascii = 48;
//     char space = ' ';
//     char *cpu = "";

//     for (int i = -1; i <= n; i++) {
//         if (i < 0)
//             tab[i] = (eraseSubStr(get_file_line("cpu  ", cpuInfo, "\n"), "cpu  "));
//         if (i >= 0)
//             dest = "cpu";
//             dest.push_back(ascii);
//             dest.push_back(space);
//             tab[i] = (eraseSubStr(get_file_line(dest.c_str() , cpuInfo, "\n"), dest));
//             ascii ++;
//     }
//     return (tab);
// }

// std::string Get_file::get_file_line(const char *find, std::string content, const char *delim)
// {
//     char *str = strdup(content.c_str());
//     char *ptr = strtok(str, delim);
//     int i = 0;

//     while (ptr[i] != '\0') {
//         if (strncmp(find, str, strlen(find)) == 0) {
//             return ptr;
//         }
//         i++;
//     }
//     return ("\0");
// }

// std::string Get_file::eraseSubStr(std::string mainStr, const std::string &toErase)
// {
//     size_t pos = std::string::npos;
//     if (mainStr.compare("\0"))
//         return ("\0");
//     while ((pos = mainStr.find(toErase))!= std::string::npos)
//     {
//         mainStr.erase(pos, toErase.length());
//     }
//     return (mainStr);
// }

// std::string Get_file::getOsName()
// {
//     char *ptr, *ptr2;
//     std::string final, os;
//     std::string version = get_file_content("/proc/version");
//     std::string os_name = get_file_content("/etc/os-release");
//     //std::string str = get_file_line("NAME=", os_name, "\n")_str();
//     //char *str = strdup(version.c_str());
//     //char *str2 = strdup(os_name.c_str());
//     return (eraseSubStr(get_file_line("NAME=", os_name, "\n"), "NAME="));
//     //return get_file_line("version", version, " ");

//     /*ptr = strtok(str, " ");
//     os = ptr;
//     while (ptr != NULL)
//     {
//         if (strncmp("version", ptr, 5) == 0)
//             break;
//         ptr = strtok (NULL, " ");
//         i++;
//     }
//     ptr2 = strtok(str2, "\n");
//     if (strncmp("NAME=", ptr2, 4) == 0) {
//             ptr2 = strtok(NULL, "\n");
//             os = ptr2;
//             return os;
//         }
//     while (ptr2 != NULL) {
//         if (strncmp("NAME=", ptr2, 4) == 0) {
//             ptr2 = strtok(NULL, "\"");
//             break;
//         }

//     }

//     final = ptr;
//     os = ptr2;*/
//     //return os;
// }
