#include "AddBook.h"
#include <iostream>

AddBook::AddBook(Session *m_Owner)
: Event(m_Owner) {
}

void AddBook::operator()(std::stringstream &stream) {
    std::cout << "Add books" << std::endl;
}
