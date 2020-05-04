#include "Events/GetBooks.h"
#include <iostream>

GetBooks::GetBooks(Session *m_Owner)
: Event(m_Owner) {
}

void GetBooks::operator()(std::stringstream &stream) {
    std::cout << "Get Books" << std::endl;
}
