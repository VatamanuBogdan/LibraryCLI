#pragma once
#include "Handler.h"

class Session {
private:
    bool m_Opened;
    bool m_Connection;
    int m_Sockfd;
public:
    int GetSockfd() const;

    void OpenConnection();

    void CloseConnection();

private:
    std::string m_UserName;
    std::string m_ConnectSid;
    std::string m_Token;
public:
    const std::string &GetToken() const;

    void SetToken(const std::string &mToken);

private:
    Handler m_Handler;
public:
    bool IsConnected() const;

    void SetConnection(bool mConnection);

    const std::string &GetConnectSid() const;

    void SetConnectSid(const std::string &mConnectSid);

    bool IsOpened() const;

    void SetOpened(bool mOpened);

    const std::string& GetUserName() const;

    void SetUserName(const std::string &mUserName);

public:
    Session();

    ~Session();

    void MainPoint();
};


