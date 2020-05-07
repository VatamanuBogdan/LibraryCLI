#include "Register.h"
#include "json.hpp"
#include <string>
#include <iostream>
#include "HttpReply.hpp"
#include "Connection.hpp"

using json=nlohmann::json;

Register::Register(Session *m_Owner)
    : Event(m_Owner) {
}

void Register::operator()(std::stringstream &stream) {
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
    m_Request.SetRequest("POST", "/api/v1/tema/auth/register", "HTTP/1.1");
    m_Request.SetHost("ec2-3-8-116-10.eu-west-2.compute.amazonaws.com:8080");
    m_Request.ClearHeaders();
    m_Request.AddHeader("Content-Type", "application/json");
    m_Request.AddHeader("Content-Length", to_string(data.length()).c_str());
    m_Request.AddHeader("Connection", "keep-alive");
    m_Request.ClearCookies();
    m_Request.SetData(data.c_str());
    m_Request.Send(m_Owner->GetSockfd());
    std::string reply = Connection::ReceiveHttps(m_Owner->GetSockfd());
    unsigned short sign = HttpReply::ExtractSign(reply);
    if (sign == 201) {
        cout << "Account was created" << std::endl;
    }
    else {
        cout << "Register failed " << "error " << sign << std::endl;
    }
}
