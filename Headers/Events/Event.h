#pragma once
#include <sstream>

class Session;

class Event {
protected:
    Session *m_Owner;
public:
    explicit Event(Session* owner)
    : m_Owner(owner){
    }

    virtual void operator()(std::stringstream& stream) = 0;
};

