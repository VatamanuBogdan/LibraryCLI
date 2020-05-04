#pragma once
#include "Event.h"
#include "Session.h"

class Login : public Event {
public:
    explicit Login(Session* m_Owner);

    void operator()(std::stringstream& stream) override;
};


