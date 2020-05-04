#pragma once
#include "Events/Event.h"
#include <unordered_map>
#include <sstream>
#include <string>
#include <memory>

using EventWraper = std::unique_ptr<Event>;

class Handler {
public:
    explicit Handler() = default;

private:
    std::unordered_map<std::string, EventWraper> m_Commands;

public:
    /*
     * @event take his custody
     */
    void AddCommand(const std::string& command, Event* event);

    bool RunCommand(const std::string& command, std::stringstream& stream);

    bool RemoveCommand(const std::string& command);

    void Clear();
};


