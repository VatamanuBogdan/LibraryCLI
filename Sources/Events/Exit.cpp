#include "Exit.h"
#include <iostream>

Exit::Exit(Session *m_Owner)
: Event(m_Owner) {
}

void Exit::operator()(std::stringstream &stream) {
    std::cout << "exit" << std::endl;
    m_Owner->SetOpened(false);
}
