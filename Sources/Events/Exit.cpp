#include "Exit.h"
#include <iostream>

Exit::Exit(Session *m_Owner)
: Event(m_Owner) {
}

void Exit::operator()(std::stringstream &stream) {
    m_Owner->SetOpened(false);
}
