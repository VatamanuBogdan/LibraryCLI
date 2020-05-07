#include "Session.h"
#include "Events.h"
#include "Connection.hpp"
#include <iostream>

Session::Session()
: m_Opened(true), m_Connection(false), m_Sockfd(-1), m_UserName(""), m_ConnectSid(""), m_Token("") , m_Handler() {
    m_Handler.AddCommand("login",(Event*) new Login(this));
    m_Handler.AddCommand("register",(Event*) new Register(this));
    m_Handler.AddCommand("logout",(Event*) new Logout(this));
    m_Handler.AddCommand("enter_library",(Event*) new EnterLibrary(this));
    m_Handler.AddCommand("get_book",(Event*) new GetBook(this));
    m_Handler.AddCommand("get_books",(Event*) new GetBooks(this));
    m_Handler.AddCommand("add_book",(Event*) new AddBook(this));
    m_Handler.AddCommand("delete_book",(Event*) new DeleteBook(this));
    m_Handler.AddCommand("exit",(Event*) new Exit(this));
}

void Session::MainPoint() {
    std::string command(20, '\0');
    std::stringstream ss;
    while (IsOpened()) {
        m_Sockfd = Connection::OpenConnection("3.8.116.10", 8080, AF_INET);
        std::getline(std::cin, command);
        if(!m_Handler.RunCommand(command, ss)) {
            std::cout << "Command: " << command << " doesn't exists" << std::endl;
        }
        Connection::CloseConnection(m_Sockfd);
    }
}

Session::~Session() {
    Connection::CloseConnection(m_Sockfd);
}

bool Session::IsConnected() const {
    return m_Connection;
}

void Session::SetConnection(bool mConnection) {
    m_Connection = mConnection;
}

const std::string &Session::GetUserName() const {
    return m_UserName;
}

void Session::SetUserName(const std::string &mUserName) {
    m_UserName = mUserName;
}

bool Session::IsOpened() const {
    return m_Opened;
}

void Session::SetOpened(bool mOpened) {
    m_Opened = mOpened;
}

int Session::GetSockfd() const {
    return m_Sockfd;
}

const std::string &Session::GetConnectSid() const {
    return m_ConnectSid;
}

void Session::SetConnectSid(const std::string &mConnectSid) {
    m_ConnectSid = mConnectSid;
}

const std::string &Session::GetToken() const {
    return m_Token;
}

void Session::SetToken(const std::string &mToken) {
    m_Token = mToken;
}
