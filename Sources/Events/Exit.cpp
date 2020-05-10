#include "Exit.h"

Exit::Exit(Session *m_Owner)
: Event(m_Owner) {
}

void Exit::operator()() {
    m_Owner->SetOpened(false);
}
