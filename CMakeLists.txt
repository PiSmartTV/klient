cmake_minimum_required(VERSION 3.5)

project(klient LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set (CMAKE_MODULE_PATH "${CMAKE_MODULE_PATH};${CMAKE_CURRENT_SOURCE_DIR}/cmake")

find_package(Qt5 COMPONENTS Widgets LinguistTools REQUIRED)
find_package(LibAV REQUIRED)

set(TS_FILES
  translations/en.ts
  translations/sr.ts
)

add_executable(klient
  src/main.cpp
  src/mainwindow.cpp
  src/mainwindow.h
  ui/mainwindow.ui
  ${TS_FILES}
)

target_link_libraries(klient PRIVATE Qt5::Widgets)

qt5_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
