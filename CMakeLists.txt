cmake_minimum_required(VERSION 3.5)

project(klient LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_MODULE_PATH "${CMAKE_MODULE_PATH};${CMAKE_CURRENT_SOURCE_DIR}/cmake")

set(FFMPEG_BREW_VERSION "4.3.2")

find_package(Qt5 COMPONENTS Widgets LinguistTools REQUIRED)

set(TS_FILES
  translations/en.ts
  translations/sr.ts
)

set(UI_FILES
  ui/mainwindow.ui
)

if(WIN32)
add_executable(${PROJECT_NAME}
  WIN32
  src/main.cpp
  src/mainwindow.cpp
  src/mainwindow.h
  src/stream.cpp
  src/stream.h

  ${UI_FILES}
  ${TS_FILES}
)
elseif(APPLE)
add_executable(${PROJECT_NAME}
  MACOSX_BUNDLE
  src/main.cpp
  src/mainwindow.cpp
  src/mainwindow.h
  src/stream.cpp
  src/stream.h

  ${UI_FILES}
  ${TS_FILES}
)
else()
add_executable(${PROJECT_NAME}
  src/main.cpp
  src/mainwindow.cpp
  src/mainwindow.h
  src/stream.cpp
  src/stream.h

  ${UI_FILES}
  ${TS_FILES}
)
endif()


if(WIN32)
  find_library(
    LIBAVCODEC_LIBRARY avcodec.lib
    HINTS "C:\\Program Files\\FFmpeg\\lib"
    REQUIRED
  )
  find_library(
    LIBAVFORMAT_LIBRARY avformat.lib
    HINTS "C:\\Program Files\\FFmpeg\\lib"
    REQUIRED
  )
  find_library(
    LIBAVUTIL_LIBRARY avutil.lib
    HINTS "C:\\Program Files\\FFmpeg\\lib"
    REQUIRED
  )

  if(EXISTS "C:\\Program Files\\FFmpeg")
    include_directories("C:\\Program Files\\FFmpeg\\include")
  endif()
else()
  find_library(LIBAVCODEC_LIBRARY avcodec HINTS "/usr/local/Cellar/ffmpeg/${FFMPEG_BREW_VERSION}/lib/" REQUIRED)
  find_library(LIBAVFORMAT_LIBRARY avformat HINTS "/usr/local/Cellar/ffmpeg/${FFMPEG_BREW_VERSION}/lib" REQUIRED)
  find_library(LIBAVUTIL_LIBRARY avutil HINTS "/usr/local/Cellar/ffmpeg/${FFMPEG_BREW_VERSION}/lib" REQUIRED)

  message("-- ${LIBAVUTIL_LIBRARY}")
endif()

if(APPLE)
  include_directories("/usr/local/Cellar/ffmpeg/${FFMPEG_BREW_VERSION}/include")
endif()

target_link_libraries(${PROJECT_NAME} PRIVATE ${LIBAVCODEC_LIBRARY} ${LIBAVFORMAT_LIBRARY} ${LIBAVUTIL_LIBRARY} Qt5::Widgets)

qt5_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})



if(WIN32)
  set(CPACK_GENERATOR NSIS)

  message("-- Use windeployqt to pack all the dependencie")

  install(TARGETS ${PROJECT_NAME} RUNTIME DESTINATION .)

  find_program(TOOL_WINDEPLOYQT NAMES windeployqt PATHS "${CMAKE_PREFIX_PATH}/tools/qt5")
  find_program(TOOL_WINDEPLOYQT_DEBUG NAMES windeployqt PATHS "${CMAKE_PREFIX_PATH}/debug/tools/qt5")

  install(CODE "
      if(CMAKE_BUILD_TYPE EQUAL \"DEBUG\")
      execute_process(
              COMMAND ${TOOL_WINDEPLOYQT_DEBUG} \"\${CMAKE_INSTALL_PREFIX}/${PROJECT_NAME}.exe\" -verbose=2
              WORKING_DIRECTORY ${CMAKE_PREFIX_PATH}/tools/qt5
      )
      else()
              execute_process(
                      COMMAND ${TOOL_WINDEPLOYQT} \"\${CMAKE_INSTALL_PREFIX}/${PROJECT_NAME}.exe\" -verbose=2
                      WORKING_DIRECTORY ${CMAKE_PREFIX_PATH}/debug/tools/qt5
              )
      endif()
  ")

  if(NOT TOOL_WINDEPLOYQT AND NOT TOOL_WINDEPLOYQT_DEBUG)
    message(FATAL_ERROR "Could not find windeployqt")
  endif()

  # Find better way to do this
  install(FILES "C:/Program Files/FFmpeg/bin/avcodec-58.dll" DESTINATION .)
  install(FILES "C:/Program Files/FFmpeg/bin/avutil-56.dll" DESTINATION .)
  install(FILES "C:/Program Files/FFmpeg/bin/avformat-58.dll" DESTINATION .)
  install(FILES "C:/Program Files/FFmpeg/bin/swresample-3.dll" DESTINATION .)
elseif(APPLE)
<<<<<<< HEAD
  set(CPACK_GENERATOR DragNDrop)

  install(TARGETS ${PROJECT_NAME} BUNDLE DESTINATION .)

  install(CODE 
    "execute_process(COMMAND \"macdeployqt\" -verbose=2)"
  )

  install(FILES "/usr/local/Cellar/ffmpeg/${FFMPEG_BREW_VERSION}/lib/libavutil.so" DESTINATION "./${PROJECT_NAME}.app/Contents/Resources")
  install(FILES "/usr/local/Cellar/ffmpeg/${FFMPEG_BREW_VERSION}/lib/libavformat.so" DESTINATION "./${PROJECT_NAME}.app/Contents/Resources")
  install(FILES "/usr/local/Cellar/ffmpeg/${FFMPEG_BREW_VERSION}/lib/libavcodec.so" DESTINATION "./${PROJECT_NAME}.app/Contents/Resources")
  install(FILES "/usr/local/Cellar/ffmpeg/${FFMPEG_BREW_VERSION}/lib/libswresample.so" DESTINATION "./${PROJECT_NAME}.app/Contents/Resources")
=======
  set(CPACK_GENERATOR Bundle)
>>>>>>> master
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
set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_SOURCE_DIR}/LICENSE")
set(CPACK_RESOURCE_FILE_README "${CMAKE_SOURCE_DIR}/README.md")
set(CPACK_STRIP_FILES TRUE)

# Debian specific
set(CPACK_DEBIAN_PACKAGE_DEPENDS "qt5-default libavcodec-dev libavdevice-dev libavformat-dev")

include(CPack)
