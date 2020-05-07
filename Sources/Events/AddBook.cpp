#include "AddBook.h"
#include "HttpReply.hpp"
#include "Connection.hpp"
#include "json.hpp"
#include <iostream>

AddBook::AddBook(Session *m_Owner)
: Event(m_Owner) {
}

void AddBook::operator()(std::stringstream &stream) {
    using namespace std;
    if (!m_Owner->IsConnected() && !m_Owner->GetToken().empty()) {
        cout << "You are not connected" << endl;
        cout << "Please login to proceed this command" << endl;
        return;
    }
    string title, author, genre, publisher;
    int page_count;
    cout << "title="    ,   getline(cin, title);
    cout << "author="   ,   getline(cin, author);
    cout << "genre="    ,   getline(cin, genre);
    cout << "publisher="    ,   getline(cin, publisher);
    cout << "page_count="    ,   cin >> page_count;
    if (page_count <= 0) {
        cout << "page_count invalid value" << endl;
        return;
    }
    json dataContent;
    dataContent["title"] = title    ,   dataContent["author"] = author;
    dataContent["genre"] = genre    ,   dataContent["publisher"] = publisher;
    dataContent["page_count"] = page_count;
    string data = dataContent.dump();

    m_Request.SetRequest("POST", "/api/v1/tema/library/books", "HTTP/1.1");
    m_Request.SetHost("ec2-3-8-116-10.eu-west-2.compute.amazonaws.com:8080");
    m_Request.ClearHeaders();
    m_Request.AddHeader("Content-Type", "application/json");
    m_Request.AddHeader("Content-Length", to_string(data.length()).c_str());
    m_Request.AddHeader("Connection", "keep-alive");
    m_Request.AddHeader("Authorization", ("Bearer " + m_Owner->GetToken()).c_str());
    m_Request.ClearCookies();
    m_Request.AddCookie("connect.sid", m_Owner->GetConnectSid().c_str());
    m_Request.SetData(data.c_str());
    m_Request.Send(m_Owner->GetSockfd());
    std::string reply = Connection::ReceiveHttps(m_Owner->GetSockfd());
    unsigned short sign = HttpReply::ExtractSign(reply);
    std::cout << reply << std::endl;
    if (sign == 200) {
        cout << "Add book succeed" << endl;
    }
    else {
        cout << "Add book failed " << "error " << sign << std::endl;
    }
}
