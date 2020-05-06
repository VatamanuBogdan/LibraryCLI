#pragma once
#include "Event.h"
#include "Session.h"

class DeleteBook : public Event {
public:
    explicit DeleteBook(Session* m_Owner);

    void operator()(std::stringstream& stream) override;
};