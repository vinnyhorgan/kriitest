#include "Logger.h"

#include <chrono>
#include <iostream>
#include <raylib.h>

std::vector<LogMessage> Logger::messages;

std::string CurrentDateTimeToString()
{
    std::time_t now = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
    std::string output(30, '\0');
    std::strftime(&output[0], output.size(), "%d-%b-%Y %H:%M:%S", std::localtime(&now));
    return output;
}

void Logger::Log(const std::string& message)
{
    LogMessage logMessage;
    logMessage.type = LogType::Info;
    logMessage.message = CurrentDateTimeToString() + " [INFO] " + message;
    messages.push_back(logMessage);

    std::cout << "\033[1;32m" << logMessage.message << "\033[0m" << std::endl;
}

void Logger::Warn(const std::string& message)
{
    LogMessage logMessage;
    logMessage.type = LogType::Warning;
    logMessage.message = CurrentDateTimeToString() + " [WARN] " + message;
    messages.push_back(logMessage);

    std::cout << "\033[1;33m" << logMessage.message << "\033[0m" << std::endl;
}

void Logger::Err(const std::string& message)
{
    LogMessage logMessage;
    logMessage.type = LogType::Error;
    logMessage.message = CurrentDateTimeToString() + " [ERROR] " + message;
    messages.push_back(logMessage);

    std::cout << "\033[1;31m" << logMessage.message << "\033[0m" << std::endl;
}

void Logger::RaylibCallback(int logType, const char* text, va_list args)
{
    int messageSize = std::vsnprintf(nullptr, 0, text, args) + 1;
    std::string message(messageSize, '\0');
    std::vsnprintf(&message[0], message.size(), text, args);

    switch (logType)
    {
        case LOG_INFO:
            Log(message);
            break;
        case LOG_WARNING:
            Warn(message);
            break;
        case LOG_ERROR:
            Err(message);
            break;
        default:
            break;
    }
}