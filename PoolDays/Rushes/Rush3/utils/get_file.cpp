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

std::string Get_file::getRamInfo()
{
    std::string ram_info = get_file_content("/proc/meminfo");
    char *str = strdup(ram_info.c_str());
    char *ptr = strtok(str, "\n");
    char *str2 = strdup(ram_info.c_str());
    char *ptr2 = strtok(str2, "\n");
    int i = 0;
    std::string tmp;
    std::string tmp2;
    std::string tmp3;
    int total;

    while (ptr != NULL) {
        if (strncmp("MemTotal:", ptr, 9) == 0) {
            tmp = strdup(ptr);
            break;
        }
        for (; ptr[i] != '\n'; i++);
        ptr = strtok(NULL, "\n");
    }
    while (ptr2 != NULL) {
        if (strncmp("MemAvailable:", ptr2, 13) == 0) {
            tmp2 = strdup(ptr2);
            break;
        }
        for (; ptr2[i] != '\n'; i++);
        ptr2 = strtok(NULL, "\n");
    }
    tmp.erase(0, 17);
    tmp.pop_back();
    tmp.pop_back();
    tmp2.erase(0, 17);
    tmp2.pop_back();
    tmp2.pop_back();
    total = (atoi(tmp.c_str()) - atoi(tmp2.c_str()));
    tmp3 = std::to_string(total);
    return tmp3;
}

std::string Get_file::getFrequency()
{
    std::string cpuInfo = get_file_content("/proc/cpuinfo");
    return (eraseSubStr(get_file_line("cpu MHz		: ", cpuInfo, "\n"), "cpu MHz		: "));
}
