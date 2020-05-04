#include "Events/Logout.h"
#include <iostream>

Logout::Logout(Session *m_Owner)
: Event(m_Owner) {
}

void Logout::operator()(std::stringstream &stream) {
    std::cout << "Logout" << std::endl;
}
