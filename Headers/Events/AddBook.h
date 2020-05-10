#pragma once
#include "Event.h"
#include "Session.h"

class AddBook : public Event {
public:
    explicit AddBook(Session* m_Owner);

    void operator()() override;
};