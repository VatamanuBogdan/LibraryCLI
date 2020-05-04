#pragma once
#include "Handler.h"

class Session {
private:
    bool m_Opened;
    bool m_Connection;
    std::string m_UserName;
    Handler m_Handler;
public:
    bool IsConnected() const;

    void SetConnection(bool mConnection);

    bool IsOpen() const;

    void SetOpened(bool mOpened);

    const std::string& GetUserName() const;

    void SetUserName(const std::string &mUserName);

public:
    Session();

    ~Session();

    void MainPoint();
};


