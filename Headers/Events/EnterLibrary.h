#pragma once
#include "Event.h"
#include "Session.h"

class EnterLibrary : public Event {
public:
    explicit EnterLibrary(Session* m_Owner);

    void operator()(std::stringstream& stream) override;
};