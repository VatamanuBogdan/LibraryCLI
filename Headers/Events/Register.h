#pragma once
#include "Event.h"
#include "Session.h"

class Register : public Event {
public:
    explicit Register(Session* m_Owner);

    void operator()(std::stringstream& stream) override;
};