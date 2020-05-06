#include "Session.h"
#include "Events.h"
#include <iostream>

Session::Session()
: m_Opened(true), m_Connection(false), m_UserName(20, '\0'), m_Handler() {
    // TODO open connection
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
    while (m_Opened) {
        std::getline(std::cin, command);
        m_Handler.RunCommand(command, ss);
    }
}

Session::~Session() {
    // TODO close connection
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

bool Session::IsOpen() const {
    return m_Opened;
}

void Session::SetOpened(bool mOpened) {
    m_Opened = mOpened;
}
