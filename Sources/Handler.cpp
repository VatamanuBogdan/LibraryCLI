#include "Handler.h"
#include <memory>

void Handler::AddCommand(const std::string &command, Event* event) {
    m_Commands.insert({command, std::unique_ptr<Event>(event)});
}

bool Handler::RunCommand(const std::string &command) {
    auto handlerIter = m_Commands.find(command);
    if (handlerIter != m_Commands.end()) {
        (*handlerIter->second)();
        return true;
    }
    return false;
}

bool Handler::RemoveCommand(const std::string &command) {
    auto handlerIter = m_Commands.find(command);
    if (handlerIter != m_Commands.end()) {
        m_Commands.erase(handlerIter);
        return true;
    }
    return false;
}

void Handler::Clear() {
    m_Commands.clear();
}
