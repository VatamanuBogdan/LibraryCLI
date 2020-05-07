#include "Events/Logout.h"
#include "HttpReply.hpp"
#include "Connection.hpp"
#include <iostream>

Logout::Logout(Session *m_Owner)
: Event(m_Owner) {
}

void Logout::operator()(std::stringstream &stream) {
    using namespace std;
    if (!m_Owner->IsConnected()) {
        cout << "You are not connected" << endl;
        cout << "Please login to proceed this command" << endl;
        return;
    }
    m_Request.SetRequest("GET", "/api/v1/tema/auth/logout", "HTTP/1.1");
    m_Request.SetHost("ec2-3-8-116-10.eu-west-2.compute.amazonaws.com:8080");
    m_Request.ClearHeaders();
    m_Request.AddHeader("Connection", "keep-alive");
    m_Request.ClearCookies();
    m_Request.AddCookie("connect.sid", m_Owner->GetConnectSid().c_str());
    m_Request.SetData("");
    m_Request.Send(m_Owner->GetSockfd());
    std::string reply = Connection::ReceiveHttps(m_Owner->GetSockfd());
    unsigned short sign = HttpReply::ExtractSign(reply);
    if (sign == 200) {
        cout << "Logout successfully" << std::endl;
        m_Owner->SetConnectSid("");
        m_Owner->SetUserName("");
        m_Owner->SetConnection(false);
        m_Owner->SetToken("");
    }
    else {
        cout << "Logout failed " << "error " << sign << std::endl;
    }
}
