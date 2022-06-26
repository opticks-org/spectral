#######################################################################################
# Qt5/Qwt6 boilerplate shared between Opticks and Spectral.
#
if(NOT IS_DIRECTORY "${Qt5_DIR}")
   if(IS_DIRECTORY "/usr/lib64/cmake/Qt5")
      message(STATUS "Qt5_DIR ${Qt5_DIR} NOT FOUND, using /usr/lib64/cmake/Qt5")
      set(Qt5_DIR "/usr/lib64/cmake/Qt5")
   else()
      message(WARNING "Qt5_DIR ${Qt5_DIR} NOT FOUND, please set Qt5_DIR to the directory containing Qt5Config.cmake")
   endif()
endif()
if(IS_DIRECTORY ${Qt5_DIR})
   message(STATUS "Found Qt5_DIR: ${Qt5_DIR}")
else()
   message(WARNING  "Qt5_DIR ${Qt5_DIR} NOT FOUND")
endif()
find_package(Qt5 COMPONENTS Core Concurrent Gui Widgets OpenGL Xml Network PrintSupport REQUIRED PATHS ${Qt5_DIR})
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(Qt_VERSION_MAJOR ${Qt5_VERSION_MAJOR})
add_definitions(-DQt_VERSION_MAJOR=${Qt5_VERSION_MAJOR})

set(QT_INCLUDE_DIRS ${Qt5Concurrent_INCLUDE_DIRS};${Qt5Core_INCLUDE_DIRS};${Qt5Gui_INCLUDE_DIRS};${Qt5Widgets_INCLUDE_DIRS};${Qt5OpenGL_INCLUDE_DIRS};${Qt5Xml_INCLUDE_DIRS};${Qt5Network_INCLUDE_DIRS};${Qt5PrintSupport_INCLUDE_DIRS})

set(QT_LIBRARIES ${Qt5Concurrent_LIBRARIES} ${Qt5Core_LIBRARIES} ${Qt5Gui_LIBRARIES} ${Qt5Widgets_LIBRARIES} ${Qt5OpenGL_LIBRARIES} ${Qt5Xml_LIBRARIES} ${Qt5Network_LIBRARIES} ${Qt5PrintSupport_LIBRARIES})
# message(STATUS "QT_INCLUDE_DIRS: ${QT_INCLUDE_DIRS}")
message(STATUS "QT_LIBRARIES: ${QT_LIBRARIES}")

include_directories(${QT_INCLUDE_DIRS})
# Debug messages:
# Message(STATUS "QT_INCLUDES: ${QT_INCLUDES}")
# Message(STATUS "QT_INCLUDE_DIRS: ${QT_INCLUDE_DIRS}")
# Message(STATUS "QT_LIBRARIES: ${QT_LIBRARIES}")
#######################################################################################
find_package(Qwt6ForQt5 REQUIRED)
message(STATUS "Qwt6ForQt5_INCLUDE_DIR: ${Qwt6ForQt5_INCLUDE_DIR}")
include_directories(${Qwt6ForQt5_INCLUDE_DIR})
# It's important the user can verify which Qwt6-qt5 library she's linking,
# in case she's specified a non-system qt5 and doesn't want to pick up a
# system qwt6-qt5 by mistake:
if(Qwt6ForQt5_FOUND)
   message(STATUS "Qwt6ForQt5_LIBRARY: ${Qwt6ForQt5_LIBRARY}")
else()
   message(STATUS "${Qwt6ForQt5_LIBRARY}")
endif()
#######################################################################################
