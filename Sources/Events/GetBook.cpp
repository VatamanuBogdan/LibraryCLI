#include "GetBook.h"
#include "HttpReply.hpp"
#include "Connection.hpp"
#include "json.hpp"
#include <iostream>

GetBook::GetBook(Session *m_Owner)
: Event(m_Owner) {
}

void GetBook::operator()() {
    using namespace std;
    if (!m_Owner->IsConnected()) {
        cout << "You are not connected" << endl;
        cout << "Please login to proceed this command" << endl;
        return;
    }
    else if (m_Owner->GetToken().empty()) {
        cout << "To proceed this command you need library access" << endl;
        return;
    }
    string id;
    cout << "Id:"   ,   getline(cin, id);
    m_Request.SetRequest("GET", ("/api/v1/tema/library/books/" + id).c_str(), "HTTP/1.1");
    m_Request.SetHost("ec2-3-8-116-10.eu-west-2.compute.amazonaws.com:8080");
    m_Request.ClearHeaders();
    m_Request.AddHeader("Connection", "keep-alive");
    m_Request.AddHeader("Authorization", ("Bearer " + m_Owner->GetToken()).c_str());
    m_Request.ClearCookies();
    m_Request.AddCookie("connect.sid", m_Owner->GetConnectSid().c_str());
    m_Request.SetData("");
    m_Owner->OpenConnection();
    m_Request.Send(*m_Owner);
    std::string reply = Connection::ReceiveHttps(*m_Owner);
    m_Owner->CloseConnection();
    unsigned short sign = HttpReply::ExtractSign(reply);
    if (sign == 200) {
        json Json;
        HttpReply::ExtractData(reply, Json);
        auto& book = *Json.begin();
        cout << "Title: " << book["title"] << endl;
        cout << "Author: " << book["author"] << endl;
        cout << "Genre: " << book["genre"] << endl;
        cout << "Publisher: " << book["publisher"] << endl;
        cout << "Page count: " << book["page_count"] << endl;
    }
    else {
        cout << "Get book failed " << "error " << sign << std::endl;
    }
}
