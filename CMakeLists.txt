cmake_minimum_required(VERSION 3.0)

set(CMAKE_CXX_STANDARD 14)

project(pc_tema3)

include_directories(./Headers)

include_directories(./Headers/Events)

add_executable(main ./Sources/main.cpp Sources/Handler.cpp Headers/Handler.h Headers/Events/Event.h Sources/Events/Login.cpp Headers/Events/Login.h Sources/Session.cpp Headers/Session.h Sources/Events/Register.cpp Headers/Events/Register.h Sources/Events/Logout.cpp Headers/Events/Logout.h Sources/Events/Exit.cpp Headers/Events/Exit.h Headers/Events/Events.h Sources/Events/EnterLibrary.cpp Headers/Events/EnterLibrary.h Sources/Events/GetBook.cpp Headers/Events/GetBook.h Sources/Events/GetBooks.cpp Headers/Events/GetBooks.h)