#pragma once
#include <string>
#include "json.hpp"

using json=nlohmann::json;

class HttpReply {
public:
    static unsigned short ExtractSign(const std::string& reply) {
        size_t signStart = reply.find(' ');
        if (signStart == std::string::npos) return -1;
        size_t signEnd = reply.find(' ', signStart);
        if (signEnd == std::string::npos) return -1;
        signStart++;
        return std::stoi(reply.substr(signStart, signEnd - signStart));
    }

    static std::string ExtractCookie(const std::string& reply, const char* cookie) {
        size_t valueStart = reply.find(cookie);
        if (valueStart == std::string::npos) return "";
        valueStart = reply.find('=', valueStart) + 1;
        size_t valueEnd = reply.find_first_of(";\r", valueStart);
        if (valueEnd == std::string::npos || valueEnd <= valueStart) return "";
        return reply.substr(valueStart, valueEnd - valueStart);
    }

    static void ExtractData(const std::string& reply, json& Json) {
        size_t dataStart = reply.find("\r\n\r\n") + 4;
        Json = json::parse(reply.c_str() + dataStart);
    }
};