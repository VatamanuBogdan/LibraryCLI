#include "DeleteBook.h"
#include <iostream>

DeleteBook::DeleteBook(Session *m_Owner)
: Event(m_Owner) {
}

void DeleteBook::operator()(std::stringstream &stream) {
    std::cout << "Delete book" << std::endl;
}
