set(Spectral_VERSION "1.9.0.0") #  1.9.0rc1Unofficial, but project(Spectral VERSION) below only takes dotted-decimal Version strings
cmake_minimum_required (VERSION 2.8.3)

# Order is important on this. It MUST be before project()
if(DEFINED CMAKE_BUILD_TYPE)
   set(CMAKE_BUILD_TYPE ${CMAKE_BUILD_TYPE} CACHE STRING "Choose the type of build. options are: None, Debug, Release, RelWithDebInfo, MinSizeRel")
else()
   set(CMAKE_BUILD_TYPE Debug CACHE STRING "Choose the type of build. options are: None, Debug, Release, RelWithDebInfo, MinSizeRel")
endif()
if(CMAKE_INSTALL_PREFIX)
   set(CMAKE_INSTALL_PREFIX ${CMAKE_INSTALL_PREFIX} CACHE PATH "Location to install Spectral" FORCE)
else()
   set(CMAKE_INSTALL_PREFIX ${CMAKE_BINARY_DIR}/../install CACHE PATH "Location to install Spectral" FORCE)
endif()

# Prevent in-source builds, build directory must be external to the source tree
set(CMAKE_DISABLE_IN_SOURCE_BUILD ON)

if(CMAKE_MAJOR_VERSION GREATER 2)
  cmake_policy(SET CMP0043 NEW)
  cmake_policy(SET CMP0048 NEW)
endif()

project (Spectral VERSION ${Spectral_VERSION} DESCRIPTION "Spectral PlugIn for Opticks GIS")

############################################################
# From https://gitlab.kitware.com/cmake/community/-/wikis/doc/cmake/RPATH-handling
#
# use, i.e. don't skip the full RPATH for the build tree
set(CMAKE_SKIP_BUILD_RPATH FALSE)

# when building, don't use the install RPATH already
# (but later on when installing)
set(CMAKE_BUILD_WITH_INSTALL_RPATH FALSE)

set(CMAKE_INSTALL_RPATH "${CMAKE_INSTALL_PREFIX}/lib")

# add the automatically determined parts of the RPATH
# which point to directories outside the build tree to the install RPATH
set(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)

# the RPATH to be used when installing, but only if it's not a system directory
list(FIND CMAKE_PLATFORM_IMPLICIT_LINK_DIRECTORIES "${CMAKE_INSTALL_PREFIX}/lib" isSystemDir)
if("${isSystemDir}" STREQUAL "-1")
    set(CMAKE_INSTALL_RPATH "${CMAKE_INSTALL_PREFIX}/lib")
endif("${isSystemDir}" STREQUAL "-1")
###########################################################################################################
# Opticks source and build paths:
if($ENV{OPTICKS_CODE_DIR})
   set(OPTICKS_DEFAULT_CODEDIR $ENV{OPTICKS_CODE_DIR})
else()
   set(OPTICKS_DEFAULT_CODEDIR "${CMAKE_SOURCE_DIR}/../../opticks/Code")
endif()
set(Opticks_CODEDIR ${OPTICKS_DEFAULT_CODEDIR} CACHE PATH "Path to the opticks/Code directory for which this Spectral plugin is to be built.")

if(EXISTS ${Opticks_CODEDIR})
   message("Found Opticks Code directory ${Opticks_CODEDIR}")
else()
   message(SEND_ERROR " Opticks_CODEDIR ${Opticks_CODEDIR} not found!")
endif()

if($ENV{OPTICKS_BUILD_DIR})
   set(OPTICKS_DEFAULT_BUILDDIR $ENV{OPTICKS_BUILD_DIR})
else()
   set(OPTICKS_DEFAULT_BUILDDIR ${Opticks_CODEDIR}/Build)
endif()
set(Opticks_BUILDDIR ${OPTICKS_DEFAULT_BUILDDIR} CACHE PATH "Path to opticks CMake Build directory for which this Spectral plugin is to be built.")

if(EXISTS ${Opticks_BUILDDIR})
   message("Found Opticks_BUILDDIR directory ${Opticks_BUILDDIR}")
   set(Opticks_LIBDIR ${Opticks_BUILDDIR}/lib)
   if(EXISTS ${Opticks_LIBDIR})
      set(Opticks_LIBRARIES
#         ${Opticks_LIBDIR}/libopticks-hdfpluginlib.a
#         ${Opticks_LIBDIR}/libopticks-nitfpluginlib.a
         ${Opticks_LIBDIR}/libopticks-pluginutilities.a
         ${Opticks_LIBDIR}/libopticks-pluginlib.a
         )
      message("Opticks_LIBRARIES: ${Opticks_LIBRARIES}") # TODO make VERBOSE
   else()
      message(SEND_ERROR " Opticks_LIBDIR ${Opticks_LIBDIR} not found!")
   endif()
else()
   message(SEND_ERROR " Opticks_BUILDDIR ${Opticks_BUILDDIR} not found!")
endif()

##################################################################################################################
# Spectral source and build paths:
if($ENV{SPECTRAL_CODE_DIR})
   set(Spectral_CODEDIR $ENV{SPECTRAL_CODE_DIR} CACHE PATH "Path to the spectral/Code directory which will build this Spectral plugin" FORCE)
else()
   set(Spectral_CODEDIR "${CMAKE_SOURCE_DIR}" CACHE PATH "Path to the spectral/Code directory which will build this Spectral plugin" FORCE)
endif()

if($ENV{SPECTRAL_BUILD_DIR})
   set(Spectral_BUILDDIR $ENV{SPECTRAL_BUILD_DIR} CACHE PATH "Path to where you want this Spectral plugin to be built." FORCE)
else() # TODO use cmake's OS-agnostic path join facility
   set(Spectral_BUILDDIR ${Spectral_CODEDIR}/../Build CACHE PATH "Path to where you want this Spectral plugin to be built." FORCE)
endif()

# Location of the Dependencies directory. On some platforms and configurations, it may not be necessary, but it's still searched.
if(NOT Spectral_DEPENDENCIES)
   if($ENV{SPECTRALDEPENDENCIES})
      set(Spectral_DEPENDENCIES $ENV{SPECTRALDEPENDENCIES} CACHE PATH "Location of Spectral pre-built dependencies" FORCE)
   else()
      set(Spectral_DEPENDENCIES "${Spectral_CODEDIR}/../Dependencies" CACHE PATH "Location of Spectral pre-built dependencies" FORCE)
   endif()
endif()

if(NOT Spectral_DEPENDENCIES)
   get_filename_component(Spectral_DEFAULT_DEPENDENCIES "${Spectral_CODEDIR}/../Dependencies" ABSOLUTE)
   set(Spectral_DEPENDENCIES ${Spectral_DEFAULT_DEPENDENCIES} CACHE PATH "Location of Spectral pre-built dependencies" FORCE)
endif()
Message(STATUS "Setting Spectral_DEPENDENCIES to ${Spectral_DEPENDENCIES}")
if(NOT (EXISTS "${Spectral_DEPENDENCIES}" AND IS_DIRECTORY "${Spectral_DEPENDENCIES}"))
    message(STATUS "Spectral_DEPENDENCIES was not provided or does not exist, so required 3rd-party libraries will only be searched for on the system. "
        "Spectral_DEPENDENCIES can be retrieved by running the retrieve-dependencies script from the Dependencies directory.")
    set(Spectral_DEPENDENCIES "" CACHE PATH "Location of Spectral pre-built dependencies" FORCE)
endif()
# 64-bit or 32-bit dependencies?
if(CMAKE_CXX_SIZEOF_DATA_PTR EQUAL 4)
   set(BITS "32")
elseif(CMAKE_CXX_SIZEOF_DATA_PTR EQUAL 8)
   set(BITS "64")
endif()
set(SPECTRAL_DEP_PATH ${Spectral_DEPENDENCIES}/${BITS})
set(CMAKE_PREFIX_PATH "${CMAKE_PREFIX_PATH}" ${SPECTRAL_DEP_PATH})
set(CMAKE_MODULE_PATH "${CMAKE_MODULE_PATH}" "${CMAKE_SOURCE_DIR}/cmake/Modules/")
message(VERBOSE "CMAKE_PREFIX_PATH: ${CMAKE_PREFIX_PATH}")

set_property(DIRECTORY APPEND PROPERTY COMPILE_DEFINITIONS_DEBUG DEBUG) #-DDEBUG only for debug configurations
if(MSVC)
    add_definitions(-DNOMINMAX)
endif()
if(NOT Spectral_FLAGS_SET)
    set(Spectral_FLAGS_SET 1 CACHE INTERNAL "Compiler specific flags for Spectral")
    if(MSVC)
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /fp:except- /wd4996 /wd4267 /wd4250" CACHE STRING "Compiler flags" FORCE)
        set(Spectral_LINK_FLAGS /LARGEADDRESSAWARE)
        if(CMAKE_CXX_SIZEOF_DATA_PTR EQUAL 4)
            set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /arch:SSE" CACHE STRING "Compiler flags" FORCE)
            set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /ZI" CACHE STRING "Compiler flags" FORCE)
        elseif(CMAKE_CXX_SIZEOF_DATA_PTR EQUAL 8)
            set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /Zi" CACHE STRING "Compiler flags" FORCE)
        endif()
        set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /Gm /RTC1 /Gy" CACHE STRING "Compiler flags" FORCE)
        set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /MP /Zi /Oi /Ot /Oy /GF /GS-" CACHE STRING "Compiler flags" FORCE)

        set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /LARGEADDRESSAWARE" CACHE STRING "Linker flags" FORCE)
        set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} /LARGEADDRESSAWARE" CACHE STRING "Linker flags" FORCE)
        
        set(CMAKE_EXE_LINKER_FLAGS_RELEASE "${CMAKE_EXE_LINKER_FLAGS_RELEASE} /debug /OPT:NOREF /OPT:NOICF" CACHE STRING "Linker flags" FORCE)
        set(CMAKE_SHARED_LINKER_FLAGS_RELEASE "${CMAKE_SHARED_LINKER_FLAGS_RELEASE} /debug /OPT:NOREF /OPT:NOICF" CACHE STRING "Linker flags" FORCE)

        set(CMAKE_EXE_LINKER_FLAGS_DEBUG "${CMAKE_EXE_LINKER_FLAGS_DEBUG} /NODEFAULTLIB:msvcrt.lib" CACHE STRING "Flags used by the linker during debug builds." FORCE)
        set(CMAKE_MODULE_LINKER_FLAGS_DEBUG "${CMAKE_MODULE_LINKER_FLAGS_DEBUG} /NODEFAULTLIB:msvcrt.lib" CACHE STRING "Flags used by the linker during debug builds." FORCE)
        set(CMAKE_SHARED_LINKER_FLAGS_DEBUG "${CMAKE_SHARED_LINKER_FLAGS_DEBUG} /NODEFAULTLIB:msvcrt.lib" CACHE STRING "Flags used by the linker during debug builds." FORCE)
    endif()
    if(CMAKE_COMPILER_IS_GNUCC)
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fpic" CACHE STRING "Compiler flags" FORCE)
    endif()
endif()

if(WIN32)
    set(ONE_SPECTRAL_LIB FALSE)
else()
    set(ONE_SPECTRAL_LIB TRUE)
endif()

set(Spectral_INCLUDE_DIRS
   "${Spectral_SOURCE_DIR}/Include"
   "${Spectral_SOURCE_DIR}/SpectralUtilities"
)

# Get the working copy revision
set(Spectral_Build_Revision "Unknown")
unset(SpectralGit)
find_package(Git)
if(GIT_FOUND)
    execute_process(COMMAND ${GIT_EXECUTABLE} log -n1 COMMAND /usr/bin/grep commit OUTPUT_VARIABLE SpectralGit OUTPUT_STRIP_TRAILING_WHITESPACE)
    string(SUBSTRING ${SpectralGit} 7 40 SpectralGit)
    if(SpectralGit)
        set(Spectral_Build_Revision "${SpectralGit}")
    endif()
endif()
if(NOT SpectralGit)
    find_package(Subversion)
    if(Subversion_FOUND)
      Subversion_WC_INFO(${Spectral_SOURCE_DIR} SpectralSvn)
      set(Spectral_Build_Revision "${SpectralSvn_WC_LAST_CHANGED_REV}")
    endif()
endif()
Message(STATUS "Setting Build Revision To ${Spectral_Build_Revision}")
configure_file(cmake/Templates/BuildRevision.h "${Spectral_SOURCE_DIR}/SpectralUtilities")

# runtime configurations
file(MAKE_DIRECTORY "${CMAKE_BINARY_DIR}/bin")
if(WIN32)
    configure_file(cmake/Templates/Spectral.vcxproj.user "${CMAKE_BINARY_DIR}")
    configure_file(cmake/Templates/spectral.dep "${CMAKE_BINARY_DIR}/bin")
    configure_file(cmake/Templates/spectral-debug.dep "${CMAKE_BINARY_DIR}/bin")
elseif(CMAKE_BUILD_TYPE STREQUAL "Release")
    configure_file(cmake/Templates/spectral.dep "${CMAKE_BINARY_DIR}/bin")
else()
    configure_file(cmake/Templates/spectral-debug.dep "${CMAKE_BINARY_DIR}/bin/spectral.dep")
endif()
install(FILES cmake/Templates/spectral-debug-sdk.dep DESTINATION bin CONFIGURATIONS Debug)
file(MAKE_DIRECTORY "${CMAKE_BINARY_DIR}/ApplicationUserSettings")

#----- Required packages -----
#add pthreads library on all platforms and verify it works at configure time
include(CheckCXXSourceCompiles)
if(WIN32)
    find_package(pthreads REQUIRED)
    set(CMAKE_REQUIRED_INCLUDES ${pthreads_INCLUDE_DIRS})
    include_directories(${CMAKE_REQUIRED_INCLUDES})
    set(CMAKE_REQUIRED_LIBRARIES ${pthreads_LIBRARIES})
    set(PTHREADS_LIBRARY ${CMAKE_REQUIRED_LIBRARIES})
elseif(CMAKE_COMPILER_IS_GNUCXX)
    set(CMAKE_REQUIRED_DEFINITIONS -pthread)
    add_definitions(${CMAKE_REQUIRED_DEFINITIONS})
    set(CMAKE_REQUIRED_LIBRARIES -pthread)
    set(PTHREADS_LIBRARY ${CMAKE_REQUIRED_LIBRARIES})
endif()
#verify that pthreads is working
CHECK_CXX_SOURCE_COMPILES("#include \"pthread.h\"
int main(char* argc, int argv) { pthread_attr_t attr; return pthread_attr_init(&attr); }" PTHREAD_WORKS)
if(NOT PTHREAD_WORKS)
   message(FATAL_ERROR "pthreads code cannot be built on this system.")
endif()

set(OpenGL_GL_PREFERENCE GLVND)

#######################################################################################
# The subsequent find_package(Qt4...) (below) fails with Spectral' default
# Dependencies/64/bin/qmake, because that qmake incorrectly -- for this purpose --
# sets QT_BINARY_DIR=/tmp/<something>/install/bin, which does not yet exist. But
# Dependencies/64/bin/qmake is required for any build that links much from Dependencies/64/lib,
# because as our CmakeLists.txt tree is currently written, -L<Dependencies path>/64/bin/qmake
# appears first in ld's argument list, and therefore shadows /usr/lib64.
#
# For now, we just work around the Dependencies/64/bin/qmake QT_BINARY_DIR quirk by setting
# QT_BINARY_DIR explicitly to Dependencies/64/bin, then make call find_program(moc) etc. calls
# here, that /usr/share/cmake/Modules/FindQt4.cmake would otherwise call later after querying
# qmake for an invalid QT_BINARY_DIR path:
set(HAVE_QT5 0)
set(QT_BINARY_DIR ${Spectral_DEPENDENCIES}/${BITS}/bin CACHE STRING "directory containing qmake, moc, uic, rcc. default ${Spectral_DEPENDENCIES}/${BITS}/bin")
set(QT_QMAKE_EXECUTABLE ${QT_BINARY_DIR}/qmake CACHE STRING "path to qmake. default ${QT_BINARY_DIR}/qmake")
message(VERBOSE " QT_BINARY_DIR:       ${QT_BINARY_DIR}")
message(VERBOSE " QT_QMAKE_EXECUTABLE: ${QT_QMAKE_EXECUTABLE}")
if(EXISTS ${QT_QMAKE_EXECUTABLE})
   # Get Qt version from Qmake
   execute_process(COMMAND ${QT_QMAKE_EXECUTABLE} -query QT_VERSION OUTPUT_VARIABLE qt_version  OUTPUT_STRIP_TRAILING_WHITESPACE)
   execute_process(COMMAND ${QT_QMAKE_EXECUTABLE} -query QT_INSTALL_LIBS OUTPUT_VARIABLE qt_install_libs  OUTPUT_STRIP_TRAILING_WHITESPACE)
   message(" Qt version: ${qt_version}")
   if("${qt_version}" VERSION_GREATER_EQUAL "5.0.0")
      set(HAVE_QT5 1)
      set(QT_Qt5_DIR "${qt_install_libs}/cmake/Qt5" CACHE PATH "Path to directory containing Qt5Config.cmake")
      set(Qt5_DIR ${QT_Qt5_DIR})
      set(ENV{CMAKE_PREFIX_PATH} ${Qt5_DIR}) # might not be necessary
      set(CMAKE_AUTOMOC ON)
      set(CMAKE_AUTORCC ON)
      set(CMAKE_AUTOUIC ON)
   else()
      # Qt4
      if(EXISTS ${QT_BINARY_DIR})
         find_program(QT_MOC_EXECUTABLE
            NAMES moc-qt4 moc4 moc
            PATHS ${QT_BINARY_DIR}
            NO_DEFAULT_PATH NO_CMAKE_FIND_ROOT_PATH
            )
         find_program(QT_UIC_EXECUTABLE
            NAMES uic-qt4 uic4 uic
            PATHS ${QT_BINARY_DIR}
            NO_DEFAULT_PATH NO_CMAKE_FIND_ROOT_PATH
            )
         find_program(QT_RCC_EXECUTABLE
            NAMES rcc
            PATHS ${QT_BINARY_DIR}
            NO_DEFAULT_PATH NO_CMAKE_FIND_ROOT_PATH
            )
         message(VERBOSE " Moc: ${QT_MOC_EXECUTABLE}")
         message(VERBOSE " Uic: ${QT_UIC_EXECUTABLE}")
         message(VERBOSE " Rcc: ${QT_RCC_EXECUTABLE}")
      else()
         message(WARNING " QT_BINARY_DIR ${QT_BINARY_DIR} does not exists")
      endif()
   endif()
else()
   message(WARNING " QT_QMAKE_EXECUTABLE ${QT_QMAKE_EXECUTABLE} does not exist")
endif()
add_definitions(-DHAVE_QT5=${HAVE_QT5})

if(HAVE_QT5)
   # We include(${QT_USE_FILE}) throughout for Qt4. Qt5 doesn't use it. Check if
   # QT_USE_FILE is empty, and set it to a dummy file if it is.
   set(QT_USE_FILE QtDummy)

   # Redefine some qt4 macros for qt5:
   macro(qt4_wrap_cpp)
      qt5_wrap_cpp(${ARGV})
   endmacro()
   macro(qt4_wrap_ui)
      qt5_wrap_ui(${ARGV})
   endmacro()
   macro(qt4_add_resources)
      qt5_add_resources(${ARGV})
   endmacro()
   find_package(Qt5 COMPONENTS Core Gui Widgets OpenGL Xml Network PrintSupport REQUIRED)
   set(Qt_VERSION_MAJOR ${Qt5_VERSION_MAJOR})
   add_definitions(-DQt_VERSION_MAJOR=${Qt5_VERSION_MAJOR})
   set(QT_INCLUDE_DIRS ${Qt5Core_INCLUDE_DIRS};${Qt5Gui_INCLUDE_DIRS};${Qt5Widgets_INCLUDE_DIRS};${Qt5OpenGL_INCLUDE_DIRS};${Qt5Xml_INCLUDE_DIRS};${Qt5Network_INCLUDE_DIRS};${Qt5PrintSupport_INCLUDE_DIRS})
   set(QT_LIBRARIES ${Qt5Core_LIBRARIES} ${Qt5Gui_LIBRARIES} ${Qt5Widgets_LIBRARIES} ${Qt5OpenGL_LIBRARIES} ${Qt5Xml_LIBRARIES} ${Qt5Network_LIBRARIES} ${Qt5PrintSupport_LIBRARIES})
else()
   find_package(Qt4 COMPONENTS QtCore QtGui QtOpenGL QtXml QtNetwork REQUIRED)
   set(Qt_VERSION_MAJOR 4)
   add_definitions(-DQt_VERSION_MAJOR=${Qt_VERSION_MAJOR})
endif(HAVE_QT5)
include_directories(${QT_INCLUDE_DIRS})
Message(STATUS "QT_INCLUDE_DIRS: ${QT_INCLUDE_DIRS}")
Message(STATUS "QT_LIBRARIES: ${QT_LIBRARIES}")
#######################################################################################

find_package(Boost 1.45.0 REQUIRED)
find_package(Xerces REQUIRED)

if(HAVE_QT5)
   set(Qwt5ForQt5_INCLUDE_DIR "/usr/include/qt5/qwt5-qt5" CACHE PATH "Directory containing Qwt5ForQt5 headers")
   find_package(Qwt5ForQt5 REQUIRED)
   include_directories(${Qwt5ForQt5_INCLUDE_DIR})
   message(STATUS "Qwt5ForQt5_INCLUDE_DIR: ${Qwt5ForQt5_INCLUDE_DIR}")
else()
   set(Qwt5ForQt4_INCLUDE_DIR "/usr/include/qwt5-qt4" CACHE PATH "Directory containing Qwt5ForQt4 headers")
   find_package(Qwt5ForQt4 REQUIRED)
endif()
find_package(ZLIB REQUIRED)
find_package(OpenGL REQUIRED)
find_package(Glew REQUIRED)
#find_package(Hdf4 COMPONENTS SD REQUIRED)
#find_package(Hdf5 REQUIRED)
#find_package(shapelib REQUIRED)
find_package(tiff REQUIRED)
find_package(geotiff REQUIRED)
find_package(proj REQUIRED)

set(XERCES_NAMESPACE_VERSION "${Xerces_VERSION_MAJOR}_${Xerces_VERSION_MINOR}")
configure_file(cmake/Templates/XercesIncludes.h "${Spectral_SOURCE_DIR}/Include/")

#----- Optional packages -----
# Need components for Ace, Tad, Rx, and WangBovik. TODO check component requirements
find_package(OpenCv COMPONENTS ImgProc Flann)
if(OpenCv_FOUND)
   add_definitions(-DOpenCv_VERSION_MAJOR=${OpenCv_MAJOR_VERSION})
endif()

set(OLD_CMAKE_PREFIX_PATH "${CMAKE_PREFIX_PATH}")
set(CMAKE_PREFIX_PATH "${CMAKE_PREFIX_PATH}" "${SPECTRAL_DEP_PATH}/tools/graphviz")
find_package(Doxygen)
set(CMAKE_PREFIX_PATH "${OLD_CMAKE_PREFIX_PATH}")
find_package(MsHelpCompiler)

configure_file(cmake/Templates/DependencyConfigs.h .)

#----- Adding public libraries -----
# we may want to change these to ${Opticks_BUILDDIR}, or leave as ${CMAKE_BINARY_DIR} and let the control script copy them 
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/PlugIns") 
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_DEBUG "${CMAKE_BINARY_DIR}/PlugIns/debug")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_RELEASE "${CMAKE_BINARY_DIR}/PlugIns")
set(CMAKE_DEBUG_POSTFIX "d")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_DEBUG "${CMAKE_BINARY_DIR}/lib")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_RELEASE "${CMAKE_BINARY_DIR}/lib")

#----- Done adding public libraries -----
#----- Adding plug-ins -----
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/LibPrivate")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_DEBUG "${CMAKE_BINARY_DIR}/LibPrivate")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_RELEASE "${CMAKE_BINARY_DIR}/LibPrivate")

#for windows, .dll go into "PlugIns" and .lib go into "LibPrivate"
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/PlugIns")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG "${CMAKE_BINARY_DIR}/PlugIns/debug")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE "${CMAKE_BINARY_DIR}/PlugIns")

#----- Done adding plug-ins -----
#----- Adding private libraries and Spectral executables -----
# can likely get rid of these, Spectral is a plugin library, not and executable
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG "${CMAKE_BINARY_DIR}/bin")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE "${CMAKE_BINARY_DIR}/bin")

include_directories(${Spectral_INCLUDE_DIRS})
include_directories(${Spectral_BINARY_DIR}) # Is this needed? There are no header files here
#############################################################
# Ideally, we would like options to set Opticks libraries and includes from Opticks' install directory, or it's build directory
# we're already using it's Build directory, and will put Spectral there when done. We should be able to do the same with
# install directory, so user needn't have an Opticks_BUILDDIR, only an install. The install directory created by Opticks' CMake
# has the needed libs and headers, although the default installed in /opt/Opticks by opticks-4.12.0-3.x86_64.rpm does not.
# 
set(Opticks_COREDIR ${Opticks_CODEDIR}/application)
if(NOT EXISTS ${Opticks_COREDIR})
   message(SEND_ERROR "Opticks Code/application directory ${Opticks_COREDIR} not found")
endif()
if(NOT EXISTS ${Opticks_COREDIR}/Interfaces)
   message(SEND_ERROR " Opticks interface include directory ${Opticks_COREDIR}/Interfaces not found")
endif()
if(NOT EXISTS ${Opticks_COREDIR}/PlugInLib)
   message(SEND_ERROR " Opticks interface include directory ${Opticks_COREDIR}/PlugInLib not found")
endif()
if(NOT EXISTS ${Opticks_COREDIR}/PlugInUtilities)
   message(SEND_ERROR " Opticks interface include directory ${Opticks_COREDIR}/PlugInUtilities not found")
endif()
if(NOT EXISTS ${Opticks_COREDIR}/PlugInUtilities/Interfaces)
   message(SEND_ERROR " Opticks interface include directory ${Opticks_COREDIR}/PlugInUtilities/Interfaces not found")
endif()
if(NOT EXISTS ${Opticks_COREDIR}/PlugInUtilities/pthreads-wrapper)
   message(SEND_ERROR " Opticks interface include directory ${Opticks_COREDIR}/PlugInUtilities/pthreads-wrapper not found")
endif()
set(Opticks_INCLUDE_DIRS
   "${Opticks_COREDIR}/Interfaces"
   "${Opticks_COREDIR}/PlugInLib"
   "${Opticks_COREDIR}/PlugInUtilities/Interfaces"
   "${Opticks_COREDIR}/PlugInUtilities/pthreads-wrapper"
   )
include_directories(${Opticks_INCLUDE_DIRS})
#############################################################


include(${QT_USE_FILE})
include_directories(${Boost_INCLUDE_DIRS})
include_directories(${Xerces_INCLUDE_DIRS})
#include_directories(${XQilla_INCLUDE_DIRS})
if(HAVE_QT5)
   include_directories(${Qwt5ForQt5_INCLUDE_DIR})
else()
   # TODO Careful -- for DEFAULT builds this finds /usr/include/qwt5-qt4 when it should have Dependencies64/include/qwt-qt4
   # the files are the same -- use diff -w -- but Dependencies Version is 5.2.1, while system is Version 5.2.2
   # Should still be fixed
   include_directories(${Qwt5ForQt4_INCLUDE_DIRS}) 
endif()
include_directories(${ZLIB_INCLUDE_DIRS})
include_directories(${OPENGL_INCLUDE_DIRS})
include_directories(${Glew_INCLUDE_DIRS})
include_directories(${tiff_INCLUDE_DIRS})
include_directories(${geotiff_INCLUDE_DIRS})

if(CMAKE_SYSTEM_NAME STREQUAL "Linux")
    include_directories(${EXPAT_INCLUDE_DIRS}) # is this needed for Qt5?
endif()



add_definitions(-DAPPLICATION_XERCES)

add_subdirectory(SpectralUtilities)

set(OLD_SHARED_LIBRARY_PREFIX "${CMAKE_SHARED_LIBRARY_PREFIX}")
set(CMAKE_SHARED_LIBRARY_PREFIX "")
set(SPECTRAL_PLUGINS # all subfolders that contain a ModuleManager.cpp or modulemanager.cpp
    Aster
    Cem
    DgFormats
    Elm
    Iarr
    KMeans
    Landsat
    Mnf
    Ndvi
    Plotting
    RangeProfile
    Resampler
    Sam
    Signature
    SpectralLibrary
    SpectralLibraryMatch
    )
  if(OpenCv_FOUND)
     list(APPEND SPECTRAL_PLUGINS
        Ace
        Rx
        Tad
        WangBovik
        )
  endif()
foreach(LIB_NAME IN LISTS SPECTRAL_PLUGINS)
   add_subdirectory(${LIB_NAME})
endforeach()
set(CMAKE_SHARED_LIBRARY_PREFIX "${OLD_SHARED_LIBRARY_PREFIX}")

set(ONE_SPECTRAL_LIB OFF) # We'll never want one spectral lib, it has many separate plugins
if(ONE_SPECTRAL_LIB)
   # eventually eliminate this
   foreach(LIB_NAME IN LISTS SPECTRAL_PLUGINS)
      get_directory_property(LIB_SOURCES DIRECTORY ${LIB_NAME} ALL_SOURCES)
      foreach(SOURCE IN LISTS LIB_SOURCES)
         list(APPEND SPECTRAL_LIB_SOURCES "${LIB_NAME}/${SOURCE}")
      endforeach()
      get_directory_property(LIB_MOC_HEADERS DIRECTORY ${LIB_NAME} MOC_HEADERS)
      set(LIB_CONV_MOC_HEADERS "")
      foreach(SOURCE IN LISTS LIB_MOC_HEADERS)
         list(APPEND LIB_CONV_MOC_HEADERS "${LIB_NAME}/${SOURCE}")
      endforeach()
      qt4_wrap_cpp(LIB_MOC_OUTFILES ${LIB_CONV_MOC_HEADERS})
      list(APPEND SPECTRAL_LIB_SOURCES ${LIB_MOC_OUTFILES} ${LIB_CONV_MOC_HEADERS})
      get_directory_property(LIB_QRC_FILES DIRECTORY ${LIB_NAME} QRC_FILES)
      set(LIB_CONV_QRC_FILES "")
      foreach(SOURCE IN LISTS LIB_QRC_FILES)
         list(APPEND LIB_CONV_QRC_FILES "${LIB_NAME}/${SOURCE}")
      endforeach()
      qt4_add_resources(LIB_RCC_OUTFILES ${LIB_CONV_QRC_FILES})
      list(APPEND SPECTRAL_LIB_SOURCES ${LIB_RCC_OUTFILES} ${LIB_CONV_QRC_FILES})
   endforeach()
   # we only need one ModuleManager.cpp -- if that
   list(REMOVE_DUPLICATES SPECTRAL_LIB_SOURCES)
#   add_library(SpectralLib          STATIC ${SPECTRAL_LIB_SOURCES})
   list(FILTER SPECTRAL_LIB_SOURCES EXCLUDE REGEX ^.*/ModuleManager.cpp)
   list(APPEND SPECTRAL_LIB_SOURCES Ace/ModuleManager.cpp)
   add_library(SpectralLib STATIC ${SPECTRAL_LIB_SOURCES})
   #   add_library(Spectral    SHARED ${SPECTRAL_LIB_SOURCES})
   add_library(Spectral    MODULE ${SPECTRAL_LIB_SOURCES})
   set_target_properties(Spectral PROPERTIES PREFIX "")
   target_link_libraries(Spectral
      ${Opticks_LIBRARIES}
      )
   set(Spectral_LIBRARIES SpectralLib)
else() # Multiple plugins, as Opticks' interface intends for Spectral
   message("CMAKE_BUILD_TYPE: ${CMAKE_BUILD_TYPE}")
      if( (CMAKE_BUILD_TYPE STREQUAL "Release") OR (CMAKE_BUILD_TYPE STREQUAL "RelWithDebInfo") )
         set(Spectral_LIBRARIES ${CMAKE_BINARY_DIR}/LibPrivate/libSpectralUtilities.a)
      else()
         set(Spectral_LIBRARIES ${CMAKE_BINARY_DIR}/LibPrivate/libSpectralUtilitiesd.a)
      endif()
   message("OpenCv_LIBRARIES: ${OpenCv_LIBRARIES}")
   foreach(LIB_NAME IN LISTS SPECTRAL_PLUGINS) # disable for tests
      set(PLUGIN_LIB_SOURCES "")
      set(PLUGIN_MOC_HEADERS "")
      set(PLUGIN_QRC_FILES "")
      set(PLUGIN_MOC_OUTFILES "")
      set(PLUGIN_QRC_OUTFILES "")
      
      set(LIB_SOURCES "")
      set(LIB_HEADERS "")
      set(LIB_MOC_HEADERS "")
      set(LIB_QRC_FILES "")
      
      get_directory_property(LIB_SOURCES DIRECTORY ${LIB_NAME} DEFINITION SOURCE_FILES)
      foreach(SOURCE IN LISTS LIB_SOURCES)
         list(APPEND PLUGIN_LIB_SOURCES "${LIB_NAME}/${SOURCE}")
      endforeach()

#      Shouldn't need headers...      
#      get_directory_property(LIB_HEADERS DIRECTORY ${LIB_NAME} DEFINITION HEADER_FILES)
#      foreach(SOURCE IN LISTS LIB_HEADERS)
#         list(APPEND PLUGIN_LIB_SOURCES "${LIB_NAME}/${SOURCE}")
#      endforeach()

      get_directory_property(LIB_MOC_HEADERS DIRECTORY ${LIB_NAME} DEFINITION MOC_HEADERS)
      foreach(SOURCE IN LISTS LIB_MOC_HEADERS)
         list(APPEND PLUGIN_MOC_HEADERS "${LIB_NAME}/${SOURCE}")
      endforeach()
      qt4_wrap_cpp(PLUGIN_MOC_OUTFILES ${PLUGIN_MOC_HEADERS})
      list(APPEND PLUGIN_LIB_SOURCES ${PLUGIN_MOC_OUTFILES} ${PLUGIN_MOC_HEADERS})
      
      get_directory_property(LIB_QRC_FILES DIRECTORY ${LIB_NAME} DEFINITION QRC_FILES)
      foreach(SOURCE IN LISTS LIB_QRC_FILES)
         list(APPEND PLUGIN_QRC_FILES "${LIB_NAME}/${SOURCE}")
      endforeach()
      qt4_add_resources(PLUGIN_QRC_OUTFILES ${PLUGIN_QRC_FILES})
      list(APPEND PLUGIN_LIB_SOURCES ${PLUGIN_QRC_OUTFILES} ${PLUGIN_QRC_FILES})

      add_library(${LIB_NAME} SHARED ${PLUGIN_LIB_SOURCES} )
      set_target_properties(${LIB_NAME} PROPERTIES PREFIX "")
      target_link_libraries(${LIB_NAME}
         ${Opticks_LIBRARIES}
         ${Spectral_LIBRARIES}
         ${QT_LIBRARIES}
         ${tiff_LIBRARIES}
         ${geotiff_LIBRARIES}
         ${ossim_LIBRARIES}
         ${Xerces_LIBRARIES}
         ${OpenCv_LIBRARIES}
         ${pthreads_LIBRARIES}
         )
      #      message("${LIB_NAME}: ${PLUGIN_LIB_SOURCES} \n")  # Devel test
   endforeach()
   if(WIN32)
      install(TARGETS ${SPECTRAL_PLUGINS} RUNTIME DESTINATION "${CMAKE_BINARY_DIR}/PlugIns" CONFIGURATIONS Release;RelWithDebInfo;MinSizeRel)
      install(TARGETS ${SPECTRAL_PLUGINS} RUNTIME DESTINATION "${CMAKE_BINARY_DIR}/PlugIns/debug" CONFIGURATIONS Debug)
   else()
      install(TARGETS ${SPECTRAL_PLUGINS} LIBRARY DESTINATION "${CMAKE_BINARY_DIR}/PlugIns" CONFIGURATIONS Release;RelWithDebInfo;MinSizeRel)
      install(TARGETS ${SPECTRAL_PLUGINS} LIBRARY DESTINATION "${CMAKE_BINARY_DIR}/PlugIns/debug" CONFIGURATIONS Debug)
   endif()
endif()




# add_executable(Spectral WIN32 ${SOURCE_FILES} ${INTERFACE_HEADER_FILES}) # Spectral is a plugin, not an executable...
source_group(Interfaces FILES ${INTERFACE_HEADER_FILES})

if(0)
target_link_libraries(Spectral
    ${Spectral_LIBRARIES}
    ${QT_LIBRARIES}
    ${OPENGL_LIBRARIES}
    ${OpenCv_LIBRARIES}
    ${ZLIB_LIBRARIES}    
    ${Xerces_LIBRARIES}
#    ${XQilla_LIBRARIES}
#    ${Raptor_LIBRARIES}
    ${Glew_LIBRARIES}
    ${PTHREADS_LIBRARY}
    )
 if(HAVE_QT5)
    target_link_libraries(Spectral  ${Qwt5ForQt5_LIBRARY})
 else()
    target_link_libraries(Spectral  ${Qwt5ForQt4_LIBRARY})
 endif()
endif()
# set_target_properties(Spectral PROPERTIES DEBUG_POSTFIX "d")
# if(CMAKE_SYSTEM_NAME STREQUAL "Linux")
#     set_target_properties(Spectral PROPERTIES OUTPUT_NAME "linuxSpectral")
#     target_link_libraries(Spectral
#         ${EXPAT_LIBRARIES} -ldl
#    )
# endif()
#if(WIN32)
#    target_link_libraries(Spectral
#        ${QT_QTMAIN_LIBRARY}
#    )
#endif()

if (EXISTS "CppTests" AND IS_DIRECTORY "CppTests")
   add_subdirectory(CppTests)
endif()
include(FeatureSummary)
feature_summary(WHAT ALL)



if(ONE_SPECTRAL_LIB)
   # TODO not needed, remove later
   install(TARGETS SpectralLib Spectral LIBRARY DESTINATION "${CMAKE_BINARY_DIR}/PlugIns") # TODO bin -> lib or PlugInLib or something, see install(stuff) below
endif()

#mark variables as advanced that the finders should have marked
mark_as_advanced(FORCE QT_QMAKE_EXECUTABLE)
mark_as_advanced(FORCE Boost_LIB_DIAGNOSTIC_DEFINITIONS)

#----- Done adding private libraries and Spectral executables -----
#----- Adding install targets for other items -----
#
# TODO: Opticks stuff, update for Spectral
# Need: (going by Code/SConstruct
# 1. OPTICKSDEPENDENCIES (command line or environment, handled above, including BITS extension
#    a. OPTICKSDEPENDENCIESINCLUDE=${OPTICKSDEPENDENCIES}/${BITS}/include
#    b. OPTICKSDEPENDENCIESBIN=${OPTICKSDEPENDENCIES}/${BITS}/bin
# DOES Spectral actually USE OPTICKSDEPENDENCIES? It does need ${OPTICKS_CODE_DIR} for some headers
# 
# 2. SPECTRALDEPENDENCIES
# 3. BUILDDIR (from command line or environment, where Spectral is built) -> SPECTRALBUILDDIR
#    a. OPTICKSLIBDIR ${OPTICKSBUILDDIR}/lib   (Where Opticks' CMake build put it's libopticks-hdfpluginlibd.a
#                                              libopticks-nitfpluginlibd.a  libopticks-pluginlibd.a  libopticks-pluginutilitiesd.a,
#                                              which isn't where SCons would put them but oh well.)
#    b. OPTICKSPLUGINDIR ${OPTICKSBUILDDIR}/PlugIns (Where we will install our Spectral.so etc. results)
# 4. OPTICKSBUILDDIR ${Opticks_CODE_DIR}/Build (default). CL or Env, but allow arbitrary out-of-source Opticks and Spectral build folders
# 5. SDKMODE Opticks  build mode debug,release (CL, Env) or deduce from OPTICKSBUILDDIR if it has only one build mode, or default to MODE)
# 6. MODE    Spectral build mode debug,release (CL, Env)
if(0) # additional install stuff not needed for a PlugIn?
install(DIRECTORY ${Spectral_SOURCE_DIR}/../Release/DefaultSettings
   ${Spectral_SOURCE_DIR}/../Release/Extensions
   ${Spectral_SOURCE_DIR}/../Release/SupportFiles
   ${Spectral_SOURCE_DIR}/../Release/Templates  DESTINATION . FILES_MATCHING
   PATTERN "*" PATTERN ".svn" EXCLUDE PATTERN "_svn" EXCLUDE)
install(DIRECTORY ${Spectral_SOURCE_DIR}/Interfaces
   ${Spectral_SOURCE_DIR}/PlugInLib
   ${Spectral_SOURCE_DIR}/HdfPlugInLib ${Spectral_SOURCE_DIR}/NitfPlugInLib
   ${Spectral_SOURCE_DIR}/SimpleApiLib DESTINATION include FILES_MATCHING
   PATTERN "*.h" PATTERN ".svn" EXCLUDE PATTERN "_svn" EXCLUDE)
install(DIRECTORY ${Spectral_SOURCE_DIR}/PlugInUtilities/Interfaces
   ${Spectral_SOURCE_DIR}/PlugInUtilities/pthreads-wrapper DESTINATION
   include/PlugInUtilities FILES_MATCHING PATTERN "*.h" PATTERN ".svn" EXCLUDE
   PATTERN "_svn" EXCLUDE)
install(DIRECTORY ${Spectral_SOURCE_DIR}/PlugIns/src/Aspam
   ${Spectral_SOURCE_DIR}/PlugIns/src/PlugInSampler
   ${Spectral_SOURCE_DIR}/PlugIns/src/PlugInSamplerHdf
   ${Spectral_SOURCE_DIR}/PlugIns/src/PlugInSamplerQt
   ${Spectral_SOURCE_DIR}/PlugIns/src/Tutorial DESTINATION examples/PlugIns/src
   FILES_MATCHING PATTERN "*" PATTERN ".svn" EXCLUDE PATTERN "_svn" EXCLUDE)
install(DIRECTORY ${Spectral_SOURCE_DIR}/cmake/Modules DESTINATION cmake FILES_MATCHING
   PATTERN "*" PATTERN ".svn" EXCLUDE PATTERN "_svn" EXCLUDE)
endif(0)
