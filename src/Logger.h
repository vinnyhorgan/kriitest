#pragma once

#include <string>
#include <vector>

enum LogType
{
    Info,
    Warning,
    Error
};

struct LogMessage
{
    LogType type;
    std::string message;
};

class Logger
{
public:
    static std::vector<LogMessage> messages;
    static void Log(const std::string& message);
    static void Warn(const std::string& message);
    static void Err(const std::string& message);
    static void RaylibCallback(int logType, const char* text, va_list args);
};
