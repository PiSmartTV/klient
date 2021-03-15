cmake_minimum_required(VERSION 3.5)

project(klient LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_MODULE_PATH "${CMAKE_MODULE_PATH};${CMAKE_CURRENT_SOURCE_DIR}/cmake")

find_package(Qt5 COMPONENTS Widgets LinguistTools REQUIRED)

set(TS_FILES
  translations/en.ts
  translations/sr.ts
)

set(UI_FILES
  ui/mainwindow.ui
)

add_executable(${PROJECT_NAME}
  src/main.cpp
  src/mainwindow.cpp
  src/mainwindow.h
  src/stream.cpp
  src/stream.h

  ${UI_FILES}
  ${TS_FILES}
)



if(WIN32)
  find_library(
    LIBAVCODEC_LIBRARY avcodec.lib
    HINTS "C:\\Program Files\\FFmpeg\\lib"
  )
  find_library(
    LIBAVFORMAT_LIBRARY avformat.lib
    HINTS "C:\\Program Files\\FFmpeg\\lib"
  )
  find_library(
    LIBAVUTIL_LIBRARY avutil.lib
    HINTS "C:\\Program Files\\FFmpeg\\lib"
  )

  if(EXISTS "C:\\Program Files\\FFmpeg")
    include_directories("C:\\Program Files\\FFmpeg\\include")
  endif()
else()
  find_library(LIBAVCODEC_LIBRARY avcodec)
  find_library(LIBAVFORMAT_LIBRARY avformat)
  find_library(LIBAVUTIL_LIBRARY avutil)
endif()

target_link_libraries(${PROJECT_NAME} PRIVATE ${LIBAVCODEC_LIBRARY} ${LIBAVFORMAT_LIBRARY} ${LIBAVUTIL_LIBRARY} Qt5::Widgets)

qt5_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
