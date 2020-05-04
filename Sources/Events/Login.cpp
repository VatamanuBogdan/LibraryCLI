#include "Events/Login.h"
#include <iostream>

Login::Login(Session *m_Owner)
    : Event(m_Owner) {
}

void Login::operator()(std::stringstream &stream) {
    std::cout << "Login" << std::endl;
}
