#include "HttpRequest.h"
#include <iostream>

void HttpRequest::SetRequest(const char *type, const char *path, const char *version) {
    (m_RequestType = type).append(" ").append(path).append(" ").append(version).append("\r\n");
}

void HttpRequest::SetHost(const char *host) {
    (m_Host = "Host: ").append(host).append("\r\n");
}

void HttpRequest::AddHeader(const char *name, const char *header) {
    m_Headers.append(name).append(": ").append(header).append("\r\n");
}

void HttpRequest::AddCookie(const char *name, const char *cookie) {
    if (m_Cookies.empty()) {
        m_Cookies.append("Cookie: ").append(name).append("=").append(cookie);
    }
    else {
        m_Cookies.append("; ").append(name).append("=").append(cookie);
    }
}

void HttpRequest::SetData(const char *data) {
    if (!m_Cookies.empty()) m_Cookies.append("\r\n");
    (m_Data = "\r\n").append(data);
}

void HttpRequest::ClearCookies() {
    m_Cookies = "";
}

void HttpRequest::ClearHeaders() {
    m_Headers = "";
}

void HttpRequest::Send() {
    std::cout << m_RequestType;
    std::cout << m_Host;
    std::cout << m_Headers;
    std::cout << m_Cookies;
    std::cout << m_Data;
}
