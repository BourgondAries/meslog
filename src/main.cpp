#include <ctime>
#include <fstream>
#include <iostream>
#include <string>


std::string padZero(std::string string, int zeros)
{
    if (string.size() < zeros)
        string.insert(0, zeros - string.size(), '0');
    return string;
}


std::string getCurrentUTCTime()
{
    std::time_t simple_time;
    std::time(&simple_time);
    std::tm *structured_time = std::gmtime(&simple_time);
    return
        padZero(std::to_string(structured_time->tm_year + 1900), 4)
        + "-"
        + padZero(std::to_string(structured_time->tm_mon + 1), 2)
        + "-"
        + padZero(std::to_string(structured_time->tm_mday), 2)
        + "."
        + padZero(std::to_string(structured_time->tm_hour), 2)
        + ":"
        + padZero(std::to_string(structured_time->tm_min), 2)
        + ":"
        + padZero(std::to_string(structured_time->tm_sec), 2);
}


int main(int argc, char *argv[])
{
    std::string output = "log.txt";
    if (argc == 2)
    {
        output = std::string(argv[1]);
    }
    else if (argc > 2)
    {
        std::cout << "Program does not handle more than 1 parameter.";
        return 1;
    }

    std::cout << "meslog v 1.0.1. Output to " << output << std::endl;

    std::fstream file(output, std::ios::app | std::ios::out);

    std::string begin_time = getCurrentUTCTime();

    std::string text;
    std::getline(std::cin, text);
    file
        << "=== BEGIN OF MESSAGE ===\nMessage time from "
        << begin_time
        << " to "
        << getCurrentUTCTime()
        << "\n";
    file << text;
    file << "\n=== END OF MESSAGE ===\n\n";
}
