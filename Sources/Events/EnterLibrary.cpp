#include "EnterLibrary.h"
#include <iostream>

EnterLibrary::EnterLibrary(Session *m_Owner)
: Event(m_Owner) {
}

void EnterLibrary::operator()(std::stringstream &stream) {
    std::cout << "Enter library" << std::endl;
}
