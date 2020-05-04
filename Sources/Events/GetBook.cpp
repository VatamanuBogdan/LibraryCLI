#include "GetBook.h"
#include <iostream>

GetBook::GetBook(Session *m_Owner)
: Event(m_Owner) {
}

void GetBook::operator()(std::stringstream &stream) {
    std::cout << "Get Book" << std::endl;
}
