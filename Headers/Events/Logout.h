#pragma once
#include "Event.h"
#include "Session.h"

class Logout : public Event {
public:
    explicit Logout(Session* m_Owner);

    void operator()(std::stringstream& stream) override;
};