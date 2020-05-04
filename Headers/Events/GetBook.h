#pragma once
#include "Event.h"
#include "Session.h"

class GetBook : public Event {
public:
    explicit GetBook(Session* m_Owner);

    void operator()(std::stringstream& stream) override;
};