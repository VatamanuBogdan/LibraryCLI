#include "Events/GetBooks.h"
#include "HttpReply.hpp"
#include "Connection.hpp"
#include "json.hpp"
#include <iostream>

GetBooks::GetBooks(Session *m_Owner)
: Event(m_Owner) {
}

void GetBooks::operator()(std::stringstream &stream) {
    using namespace std;
    if (!m_Owner->IsConnected() && !m_Owner->GetToken().empty()) {
        cout << "You are not connected" << endl;
        cout << "Please login to proceed this command" << endl;
        return;
    }
    m_Request.SetRequest("GET", "/api/v1/tema/library/books", "HTTP/1.1");
    m_Request.SetHost("ec2-3-8-116-10.eu-west-2.compute.amazonaws.com:8080");
    m_Request.ClearHeaders();
    m_Request.AddHeader("Connection", "keep-alive");
    m_Request.AddHeader("Authorization", ("Bearer " + m_Owner->GetToken()).c_str());
    m_Request.ClearCookies();
    m_Request.AddCookie("connect.sid", m_Owner->GetConnectSid().c_str());
    m_Request.SetData("");
    m_Request.Send(m_Owner->GetSockfd());
    std::string reply = Connection::ReceiveHttps(m_Owner->GetSockfd());
    unsigned short sign = HttpReply::ExtractSign(reply);
    if (sign == 200) {
        json Json;
        // TODO print data nicer
        HttpReply::ExtractData(reply, Json);
        std::cout << Json << std::endl;
    }
    else {
        cout << "Get books failed " << "error " << sign << std::endl;
    }
}
