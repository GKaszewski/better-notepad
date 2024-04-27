cmake_minimum_required(VERSION 3.14 FATAL_ERROR)
project(better_notepad)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static-libgcc -static-libstdc++")

set(wxWidgets_USE_STATIC 1)
set(wxBUILD_SHARED OFF)


if (MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /O1")
else ()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Os")
endif ()


include(FetchContent)
message(STATUS "Fetching wxWidgets...")

FetchContent_Declare(
        wxWidgets
        GIT_REPOSITORY https://github.com/wxWidgets/wxWidgets.git
        GIT_TAG v3.2.4
        GIT_SHALLOW ON
)
FetchContent_MakeAvailable(wxWidgets)

file(COPY ${CMAKE_SOURCE_DIR/icon.ico} DESTINATION ${CMAKE_BINARY_DIR})
set(APP_ICON_RESOURCE_WINDOWS "${CMAKE_BINARY_DIR}/icon.ico")
set(SRCS src/main.cpp
        src/App.cpp
        src/App.hpp
        src/Frame.cpp
        src/Frame.hpp
        src/TextManager.cpp
        src/TextManager.hpp
        src/TextFileDropTarget.cpp
        src/TextFileDropTarget.hpp)
set(RESOURCES_FILES src/resource.rc)
add_executable(better_notepad WIN32 ${SRCS} ${RESOURCES_FILES})
target_link_libraries(better_notepad PRIVATE wxcore wxbase)

