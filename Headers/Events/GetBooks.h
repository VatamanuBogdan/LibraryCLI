#pragma once
#include "Event.h"
#include "Session.h"

class GetBooks : public Event {
public:
    explicit GetBooks(Session* m_Owner);

    void operator()() override;
};