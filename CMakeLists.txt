#Cmake template 0.5 b 20231213221105
cmake_minimum_required(VERSION 3.18)
project(Test_cmake
        VERSION 1.0.0
        DESCRIPTION "Test_cmake Template for C++ library built with CMake"
        LANGUAGES CXX)

include(CMakeListsDop.cmake)

get_directory_property(IS_SUBPROJECT PARENT_DIRECTORY)

#option(STATIC_BUILD "Enable static build" ON)

#find_library+++
find_library(PTHREAD_LIBRARY pthread)
#find_library(PCRE_LIBRARY pcre)
#find_library(CURL_LIBRARY curl)
#find_library(ZIP_LIBRARY zip)
#find_library(FLTK_LIB fltk)
#find_library(CURSES_LIB curses)
#find_library(NCURSES_LIB ncurses)

#find_library---

#find_package(OpenGL REQUIRED)
#find_package(Curses REQUIRED)

file(GLOB src_dirs ./*.cpp ./src/*.cpp ./aliaswindows2/*.cpp)
message("++ CPP_src_dirs=${src_dirs}")

# mode compilation debug|release|default
if(CMAKE_BUILD_TYPE AND (CMAKE_BUILD_TYPE STREQUAL "Debug"))
    set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG}" -O0 -DDEBUG_LEVEL=1)
    add_executable(${PROJECT_NAME} ${src_dirs})
    set (EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/debug)
    message(STATUS "Debug mode:${CMAKE_C_FLAGS_DEBUG}")
elseif(CMAKE_BUILD_TYPE AND (CMAKE_BUILD_TYPE STREQUAL "Release"))
    set(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE}" -O3)
    add_executable(${PROJECT_NAME} ${src_dirs})
    set (EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/release)
    message(STATUS "Release mode:${CMAKE_C_FLAGS_RELEASE}")
else()
    set(CMAKE_C_FLAGS_DEFAULT_ "${CMAKE_C_FLAGS_DEFAULT_}" -O0 -DDEBUG_LEVEL=1 -g)
    add_executable(${PROJECT_NAME} ${src_dirs})
    set (EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/debug)
    message(STATUS "Default mode:${CMAKE_C_FLAGS_DEFAULT_}")
endif()
# mode compilation debug|release|default

set_target_properties(${PROJECT_NAME} PROPERTIES 
    CXX_STANDARD_REQUIRED ON
    CXX_STANDARD 20
    CXX_EXTENSIONS NO
    )

target_compile_options(${PROJECT_NAME} PUBLIC
  ${CMAKE_C_FLAGS_RELEASE} ${CMAKE_C_FLAGS_DEBUG} ${CMAKE_C_FLAGS_DEFAULT_}
  #-O3
  #-g 
  #-DDEBUG_LEVEL=1
  -Wall
  -Wextra -Wpedantic
  #-Wcast-align -Wcast-qual -Wconversion -Wctor-dtor-privacy -Wenum-compare -Wfloat-equal -Wnon-virtual-dtor -Wold-style-cast -Woverloaded-virtual -Wredundant-decls -Wsign-conversion -Wsign-promo
  #-Werror
)

target_include_directories(${PROJECT_NAME} PUBLIC . ./src ./include)
target_include_directories(${PROJECT_NAME} PUBLIC ${cm_HOME}/Documents/.service/include)
#target_include_directories(${PROJECT_NAME} PUBLIC local_lib/include C:/msys64/ucrt64/include/ncursesw)

#add_subdirectory(local_lib)

target_link_directories(${PROJECT_NAME} PUBLIC ${cm_HOME}/Documents/.service/lib)
target_link_libraries(${PROJECT_NAME} ${PTHREAD_LIBRARY})
target_link_libraries(${PROJECT_NAME} -lmb14static)
target_link_libraries(${PROJECT_NAME} minizip zip)
target_link_libraries(${PROJECT_NAME} curl pcre)
#target_link_libraries(${PROJECT_NAME} SDL2 SDL2_image SDL2_ttf SDL2_mixer GLU glut GL)
if ( WIN32 )# win32/64
#target_link_libraries(${PROJECT_NAME} mingw32)
    target_link_libraries(${PROJECT_NAME} ws2_32)
endif()

install(DIRECTORY ./include 
        DESTINATION ${cm_HOME}/Documents/src/cmake_test5/i
        FILES_MATCHING PATTERN "*.h")#необязательная опция

if(NOT IS_SUBPROJECT)
    PrintVariables(${PROJECT_NAME})
else()
  message(STATUS "PrintVariables не запускается в режиме подмодуля")
endif()

