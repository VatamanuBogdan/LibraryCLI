#include "Login.h"
#include "HttpReply.hpp"
#include "Connection.hpp"
#include "json.hpp"
#include <iostream>

using json=nlohmann::json;

Login::Login(Session *m_Owner)
    : Event(m_Owner) {
}

void Login::operator()() {
    using namespace std;
    if (m_Owner->IsConnected()) {
        cout << "You are already connected as " << m_Owner->GetUserName() << endl;
        cout << "Please logout to proceed this command" << endl;
        return;
    }
    static string username(20, '\0'), password(20, '\0');
    cout << "username: "    ,   getline(cin, username);
    cout << "password: "    ,   getline(cin, password);
    json dataContent;
    dataContent["username"] = username;
    dataContent["password"] = password;
    string data = dataContent.dump();
    m_Request.SetRequest("POST", "/api/v1/tema/auth/login", "HTTP/1.1");
    m_Request.SetHost("ec2-3-8-116-10.eu-west-2.compute.amazonaws.com:8080");
    m_Request.ClearHeaders();
    m_Request.AddHeader("Content-Type", "application/json");
    m_Request.AddHeader("Content-Length", to_string(data.length()).c_str());
    m_Request.AddHeader("Connection", "keep-alive");
    m_Request.ClearCookies();
    m_Request.SetData(data.c_str());
    m_Owner->OpenConnection();
    m_Request.Send(*m_Owner);
    std::string reply = Connection::ReceiveHttps(*m_Owner);
    m_Owner->CloseConnection();
    unsigned short sign = HttpReply::ExtractSign(reply);
    if (sign == 200) {
        cout << "Login successfully" << std::endl;
        m_Owner->SetConnectSid(HttpReply::ExtractCookie(reply, "connect.sid"));
        m_Owner->SetUserName(username);
        m_Owner->SetConnection(true);
    }
    else {
        cout << "Login failed " << "error " << sign << std::endl;
    }
}
