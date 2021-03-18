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



if(WIN32)
  set(CPACK_GENERATOR NSIS)

  message(INFO "-- Use windeployqt to pack all the dependencie")

  install(TARGETS ${PROJECT_NAME} RUNTIME DESTINATION .)

  include(Windeployqt)
  windeployqt(${PROJECT_NAME} .)


  # Find better way to do this
  install(FILES "C:\\Program Files\\FFmpeg\\bin\\avcodec-58.dll" DESTINATION .)
  install(FILES "C:\\Program Files\\FFmpeg\\bin\\avutil-56.dll" DESTINATION .)
  install(FILES "C:\\Program Files\\FFmpeg\\bin\\avformat-58.dll" DESTINATION .)
elseif(APPLE)
  # MacOS is not currently supported
  set(CPACK_GENERATOR DragNDrop)
elseif(UNIX)
  set(CPACK_GENERATOR DEB)
endif()

# All
set(CPACK_PACKAGE_NAME ${PROJECT_NAME})
set(CPACK_PACKAGE_CONTACT "Aleksa Ognjanovic")
set(CPACK_PACKAGE_VENDOR "github.com/PiSmartTV")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "${PROJECT_NAME} - desktop streaming client for PiTV")
set(CPACK_PACKAGE_VERSION "1.0.0")
set(CPACK_PACKAGE_VERSION_MAJOR "1")
set(CPACK_PACKAGE_VERSION_MINOR "0")
set(CPACK_PACKAGE_VERSION_PATCH "0")
set(CPACK_PACKAGE_INSTALL_DIRECTORY ${PROJECT_NAME})

# Debian specific
set(CPACK_DEBIAN_PACKAGE_DEPENDS "qt5-default libavcodec-dev libavdevice-dev libavformat-dev")

include(CPack)