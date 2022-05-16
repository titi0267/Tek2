cmake_minimum_required (VERSION 3.17)

project(arcade CXX)

set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_SHARED_LIBRARY_PREFIX "")
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake" ${CMAKE_MODULE_PATH})

set(
SRCS
Src/main.cpp
Src/Encapsulations/Mutex/CMutex.cpp
Src/Encapsulations/Fork/CFork.cpp
Src/Encapsulations/Threads/CThreads.cpp
Src/Encapsulations/ConditionnalVar/ConditionnalVar.cpp
Src/Reception/Reception.cpp
Src/Reception/Order.cpp
Src/Pizza/Margarita.cpp
Src/Error/Error.cpp
Src/Utils/Utils.cpp
Src/Kitchen/Stock.cpp
Src/Kitchen/Kitchen.cpp
)

add_executable(plazza ${SRCS} ${HEADERS})

target_link_libraries(plazza pthread)
set_target_properties(plazza PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/")