#pragma once
#include "Event.h"
#include "Session.h"

class Exit : public Event {
public:
    explicit Exit(Session* m_Owner);

    void operator()(std::stringstream& stream) override;
};