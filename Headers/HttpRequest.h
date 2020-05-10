#pragma once
#include <string>

class Session;

class HttpRequest {
private:
    std::string m_RequestType;
    std::string m_Host;
    std::string m_Headers;
    std::string m_Cookies;
    std::string m_Data;

public:
    void SetRequest(const char* type, const char* path, const char* version, const char* queryParam = "");

    void SetHost(const char* host);

    void AddHeader(const char* name, const char* header);

    void AddCookie(const char* name, const char* cookie);

    void SetData(const char* data);

    void ClearHeaders();

    void ClearCookies();

    void Send(Session& session);
};


