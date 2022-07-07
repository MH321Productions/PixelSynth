cmake_minimum_required(VERSION 3.16)

project(project-name LANGUAGES CXX)

include_directories(src)
include_directories(lib)
include_directories(include)

#Subdirectories
add_subdirectory(lib/SDL)
include_directories(lib/SDL/include)

#Subdirectories Plattformabhängig
if(WIN32)
else()
endif()

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_COMPILER g++)

#Wenn Der Build im Debug-Modus ist
if(CMAKE_BUILD_TYPE MATCHES RelWithDebInfo)
endif()

#Unterlibraries

list(APPEND libs
    SDL2-static
)

#Externe Libraries
if (WIN32)
    set(CMAKE_BUILD_TYPE Release)
	set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded")
else()
    set(CMAKE_CXX_FLAGS -no-pie)
endif()

#Hauptprogramm
add_executable(Program src/Main.cpp)
set_target_properties(Program PROPERTIES OUTPUT_NAME "Voller Programmname")

if (WIN32)
    target_link_libraries(Program PRIVATE "${libs}")
	
	set_target_properties("${libs}" PROPERTIES MSVC_RUNTIME_LIBRARY "MultiThreaded")
	set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /SUBSYSTEM:WINDOWS")
else()
    target_link_libraries(Program PRIVATE "${libs}")
endif()

#Tests
add_executable(SineTest src/Test/SineTest.cpp)
target_link_libraries(SineTest SDL2-static)