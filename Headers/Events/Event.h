#pragma once
#include "HttpRequest.h"

class Session;

class Event {
protected:
    Session *m_Owner;
    HttpRequest m_Request;
public:
    explicit Event(Session* owner)
    : m_Owner(owner){
    }

    virtual void operator()() = 0;
};


