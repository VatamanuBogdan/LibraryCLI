#include "AddBook.h"
#include "HttpReply.hpp"
#include "Connection.hpp"
#include "json.hpp"
#include <iostream>
#include <exception>

AddBook::AddBook(Session *m_Owner)
: Event(m_Owner) {
}

void AddBook::operator()() {
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
    string title, author, genre, publisher, s_pageCount;
    cout << "title="    ,   getline(cin, title);
    cout << "author="   ,   getline(cin, author);
    cout << "genre="    ,   getline(cin, genre);
    cout << "publisher="    ,   getline(cin, publisher);
    cout << "page_count="    ,   getline(cin, s_pageCount);
    unsigned int pageCount;
    size_t charNum;
    if (s_pageCount[0] == '-' || s_pageCount.size() > 6) {
        cout << "Page count value is invalid" << endl;
        return;
    }
    try {
        pageCount = stoi(s_pageCount, &charNum);
    }
    catch (exception& e) {
        std::cout << "Page count value is invalid"  << std::endl;
        return;
    }
    json dataContent;
    dataContent["title"] = title    ,   dataContent["author"] = author;
    dataContent["genre"] = genre    ,   dataContent["publisher"] = publisher;
    dataContent["page_count"] = pageCount;
    string data = dataContent.dump();
    cout << endl;
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
    m_Owner->OpenConnection();
    m_Request.Send(*m_Owner);
    std::string reply = Connection::ReceiveHttps(*m_Owner);
    m_Owner->CloseConnection();
    unsigned short sign = HttpReply::ExtractSign(reply);
    if (sign == 200) {
        cout << "Add book succeed" << endl;
    }
    else {
        cout << "Add book failed " << "error " << sign << std::endl;
    }
}
