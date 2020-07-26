cmake_minimum_required(VERSION 3.1.0)

project(helloworld)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)




list(APPEND CMAKE_PREFIX_PATH "/home/architect/pytorch")
find_package(Torch REQUIRED)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${TORCH_CXX_FLAGS}")


if(CMAKE_VERSION VERSION_LESS "3.7.0")
    set(CMAKE_INCLUDE_CURRENT_DIR ON)
endif()

find_package(Qt5 COMPONENTS Widgets REQUIRED)
set(EXECUTABLE_NAME gui-app)
add_executable(${EXECUTABLE_NAME} 
  main.cpp
  helper.cpp
  corpus.cpp
  dictionary.cpp
  rnn_lm.cpp
  MyDlg.cpp
)
find_package(Qt5 COMPONENTS Core REQUIRED)
target_include_directories(${EXECUTABLE_NAME} PRIVATE include)
target_link_libraries(${EXECUTABLE_NAME} ${TORCH_LIBRARIES})

set(CMAKE_CXX_FLAGS_COVERAGE "${CMAKE_CXX_FLAGS_RELEASE} -fprofile-arcs -ftest-coverage")
target_link_libraries(${EXECUTABLE_NAME} "${TORCH_LIBRARIES}")
set_property(TARGET ${EXECUTABLE_NAME} PROPERTY CXX_STANDARD 17)

SET(GCC_COVERAGE_COMPILE_FLAGS "-lstdc++fs")

# set up a mapping so that the Release configuration for the Qt imported target is
# used in the COVERAGE CMake configuration.
set_target_properties(Qt5::Core PROPERTIES MAP_IMPORTED_CONFIG_COVERAGE "RELEASE")

target_link_libraries(gui-app  Qt5::Widgets)
#target_link_libraries(window  Qt5::Widgets)
#target_link_libraries(window Qt5::Core)
