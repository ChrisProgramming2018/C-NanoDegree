cmake_minimum_required(VERSION 3.14 FATAL_ERROR)

project(PredictWord)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)




list(APPEND CMAKE_PREFIX_PATH "${CMAKE_CURRENT_LIST_DIR}/third/libtorch")
find_package(Torch REQUIRED)
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${TORCH_CXX_FLAGS}")



find_package(Qt5 COMPONENTS Widgets REQUIRED)
#find_package(Qt5 COMPONENTS Concurrent REQUIRED)
set(EXECUTABLE_NAME gui-app)

add_executable(${EXECUTABLE_NAME})
target_sources(${EXECUTABLE_NAME} PRIVATE  
  src/Main.cpp
  src/LSTModel.cpp
  src/Corpus.cpp
  src/Dictionary.cpp
  src/RNNLm.cpp
  src/Gui.cpp
  include/LSTModel.h
  include/Corpus.h
  include/Dictionary.h
  include/RNNLm.h
  include/Gui.h
)

find_package(Qt5 COMPONENTS Core REQUIRED)
target_include_directories(${EXECUTABLE_NAME} PRIVATE include)
target_link_libraries(${EXECUTABLE_NAME} ${TORCH_LIBRARIES})

set(CMAKE_CXX_FLAGS_COVERAGE "${CMAKE_CXX_FLAGS_RELEASE} -fprofile-arcs -ftest-coverage")
target_link_libraries(${EXECUTABLE_NAME} "${TORCH_LIBRARIES}")
set_property(TARGET ${EXECUTABLE_NAME} PROPERTY CXX_STANDARD 17)


# set up a mapping so that the Release configuration for the Qt imported target is
# used in the COVERAGE CMake configuration.
set_target_properties(Qt5::Core PROPERTIES MAP_IMPORTED_CONFIG_COVERAGE "RELEASE")

target_link_libraries(gui-app  Qt5::Widgets)
