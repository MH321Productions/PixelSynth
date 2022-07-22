cmake_minimum_required(VERSION 3.16)

project(project-name LANGUAGES CXX)

include_directories(src)
include_directories(lib)
include_directories(include)
include_directories(res)

#Subdirectories
add_subdirectory(lib/SDL)
include_directories(lib/SDL/include)
include_directories(lib/stb)
add_subdirectory(lib/libremidi)
include_directories(lib/libremidi/include)

if(WIN32)
else()
set(HAVE_DLOPEN 1) #Enable dlopen for unix bc cmake check fails
endif()

set(wxBUILD_SHARED OFF)
add_subdirectory(lib/wxWidgets)
include_directories(lib/wxWidgets/include)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_COMPILER g++)

#Wenn Der Build im Debug-Modus ist
if(CMAKE_BUILD_TYPE MATCHES RelWithDebInfo)
endif()

#libraries
add_library(Hardware src/Hardware/Device.cpp src/Hardware/HardwareHandler.cpp)
target_link_libraries(Hardware PRIVATE SDL2-static)
add_library(Synth src/Synth/Synth.cpp)
add_library(Mixer src/Mixer/Mixer.cpp src/Mixer/SimpleMixer.cpp)
#add_library(UIutil src/UI/ImageHandler/ImageHandler.cpp)

list(APPEND SynthLibs
    Hardware Synth Mixer
)

list(APPEND wxLibs
    wx::core wx::base
)

#Externe Libraries
if (WIN32)
    set(CMAKE_BUILD_TYPE Release)
	#set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded")
else()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -no-pie")
endif()

#Hauptprogramm
add_executable(SimpleSynth src/UI/SimpleSynth/SSynth.cpp src/UI/SimpleSynth/SSynthImpl.cpp src/UI/ImageHandler/ImageHandler.cpp)
set_target_properties(SimpleSynth PROPERTIES OUTPUT_NAME "SimpleSynth" WIN32_EXECUTABLE TRUE)
target_compile_definitions(SimpleSynth PRIVATE IH_USE_WX)

if (WIN32)
    target_link_libraries(SimpleSynth PRIVATE "${SynthLibs}" "${wxLibs}")
	
	#set_target_properties(${SynthLibs} SDL2-static PROPERTIES MSVC_RUNTIME_LIBRARY "MultiThreaded")
    #set_target_properties(${BUILDSYSTEM_TARGETS} PROPERTIES MSVC_RUNTIME_LIBRARY "MultiThreaded")
    #set_target_properties(${wxLibs} PROPERTIES MSVC_RUNTIME_LIBRARY "MultiThreaded")
else()
    target_link_libraries(SimpleSynth PRIVATE "${SynthLibs}" "${wxLibs}")
endif()

#Tests
enable_testing()

add_executable(SineTest src/Test/SineTest.cpp)
target_link_libraries(SineTest SDL2-static)
add_test(NAME SineTest COMMAND SineTest)

add_executable(SurroundTest src/Test/SurroundTest.cpp src/UI/ImageHandler/ImageHandler.cpp)
set_target_properties(SurroundTest PROPERTIES WIN32_EXECUTABLE TRUE)
target_link_libraries(SurroundTest SDL2-static SDL2main)
target_compile_definitions(SurroundTest PRIVATE IH_USE_SDL)
add_test(NAME SurroundTest COMMAND SurroundTest)