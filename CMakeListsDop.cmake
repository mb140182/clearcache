# CMakeListsDop.cmake
# svalka barahla
# 2023.12.11/01:47:16

#if(NOT IS_SUBPROJECT)
    #add_subdirectory(online)
#endif()

#list compile options in build_dir/compile_commands.json
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

#из-за сложностей с путями и переменными по виндовс+++
set(cm_HOME $ENV{HOME})
if ( WIN32 )# win32/64
  if(NOT DEFINED ENV{HOME})#если нет переменной HOME, то с борка происходит не под msys
    #set(cm_HOME "C:/msys64/home/mb14")#XXX FIXME 
    set(cm_HOME "C:/Users/mb14")#XXX FIXME 
  else()
#если сборка происходит под win то приводим строку то меняем виндовские слеш на понятные смаке юниксовские

#string(REPLACE "\\" "/" cm_HOME "${cm_HOME}")
  file(TO_CMAKE_PATH "$ENV{HOME}" cm_HOME)
#file(TO_NATIVE_PATH ${cm_HOME} cm_HOME)
#message(WARNING "cm_HOME: ${cm_HOME}")

#если сборка происходит под win то приводим строку то меняем виндовские слеш на понятные смаке юниксовские
  endif()
endif()
#из-за сложностей с путями и переменными по виндовс+++

#function(foo)
    #set(MY_VAR "hello")
    #set(MY_VAR ${MY_VAR} PARENT_SCOPE)
    #message("${MY_VAR}") # prints: hello
#endfunction()


function(PrintVariables target)

  message(----------------------PrintVariables----------------------)

  message("++ TARGET=${target}")
  message("++ HOME=$ENV{HOME}")
  message("++ cm_HOME=${cm_HOME}")
  message("++ PROJECT_SOURCE_DIR=${PROJECT_SOURCE_DIR}")
  message("++ EXECUTABLE_OUTPUT_PATH=${EXECUTABLE_OUTPUT_PATH}")
  message("++ PROJECT_NAME=${PROJECT_NAME}")
  message("++ CMAKE_CURRENT_SOURCE_DIR=${CMAKE_CURRENT_SOURCE_DIR}")

  message("++ IS_SUBPROJECT=${IS_SUBPROJECT}")
  #message("++ ---PARENT_DIRECTORY=${PARENT_DIRECTORY}")

  #get_target_property(INCLUDE_DIRECTORIES ${PROJECT_NAME} INCLUDE_DIRECTORIES)
  get_target_property(INCLUDE_DIRECTORIES ${target} INCLUDE_DIRECTORIES)
  message("++ INCLUDE_DIRECTORIES=${INCLUDE_DIRECTORIES}")

  get_target_property(LINK_DIRECTORIES ${target} LINK_DIRECTORIES)
  message("++ LINK_DIRECTORIES=${LINK_DIRECTORIES}")

  get_target_property(LINK_LIBRARIES ${target} LINK_LIBRARIES)
  message("++ LINK_LIBRARIES=${LINK_LIBRARIES}")

  get_target_property(CXX_STANDARD_REQUIRED ${target} CXX_STANDARD_REQUIRED)
  message("++ CXX_STANDARD_REQUIRED=${CXX_STANDARD_REQUIRED}")

  get_target_property(CXX_STANDARD ${target} CXX_STANDARD)
  message("++ CXX_STANDARD=${CXX_STANDARD}")

  get_target_property(COMPILE_OPTIONS ${target} COMPILE_OPTIONS)
  message("++ COMPILE_OPTIONS=${COMPILE_OPTIONS}")


  message(----------------------PrintVariables----------------------)

endfunction()

# ---SVALKA---

#option_compile+++
#set(CMAKE_CXX_STANDARD 17)
#set(CMAKE_CXX_STANDARD_REQUIRED on)
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -O3")
#add_compile_options(-O3 -Werror )
#option_compile---

#target_link_libraries(${PROJECT_NAME} ${PTHREAD_LIBRARY} ${cm_HOME}/Documents/.service/lib/libmb14static.a)
#add_executable(${PROJECT_NAME} ${src_dirs})

#cmake CMakeLists.txt -B debug  -DCMAKE_BUILD_TYPE=Debug
#cmake --build debug
#cmake CMakeLists.txt -B release  -DCMAKE_BUILD_TYPE=Release
#cmake --build release
#cmake CMakeLists.txt -B build
#cmake --build build

#set (LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)
#set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${PROJECT_SOURCE_DIR}/bin/)
#set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${PROJECT_SOURCE_DIR}/bin/)

#add_compile_options(
    ##-Werror

    #-Wall
    #-Wextra
    #-Wpedantic

    #-Wcast-align
    #-Wcast-qual
    #-Wconversion
    #-Wctor-dtor-privacy
    #-Wenum-compare
    #-Wfloat-equal
    #-Wnon-virtual-dtor
    #-Wold-style-cast
    #-Woverloaded-virtual
    #-Wredundant-decls
    #-Wsign-conversion
    #-Wsign-promo
#)

#include_directories($ENV{HOME}/Documents/.service/include . ./src ./include local_lib/include)

#aux_source_directory(./ SOURCES1)
#message(SOURCES1=${SOURCES1})

#cmake_policy(SET CMP0011 NEW)
#cmake_policy(SET CMP0003 OLD)

#OPTION(WITH_DEBUG_MODE "Build with debug mode" ON)

#if ( NOT UNIX )
    #message (FATAL_ERROR "Not Unix!")
#endif ()

#CMake можно указать конкретный тип Makefile’ов, которые вы хотите получить на выходе:
#cmake -G "Unix Makefiles" ..
#cmake -G "MinGW Makefiles" ..
# для просмотра списка всех доступных генераторов:
#cmake -G


