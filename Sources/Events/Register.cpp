#include "Register.h"
#include <iostream>

Register::Register(Session *m_Owner)
    : Event(m_Owner) {
}

void Register::operator()(std::stringstream &stream) {
    std::cout << "Register" << std::endl;
}
