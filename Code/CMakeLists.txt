set(Spectral_VERSION "1.9.0rc1Unofficial") # Change project(Spectral) call below when VERSION becomes an official dotted-decimal
cmake_minimum_required (VERSION 3.11.1)

# Order is important on this. It MUST be before project()
if(DEFINED CMAKE_BUILD_TYPE)
   set(CMAKE_BUILD_TYPE ${CMAKE_BUILD_TYPE} CACHE STRING "Choose the type of build. options are: None, Debug, Release, RelWithDebInfo, MinSizeRel")
else()
   set(CMAKE_BUILD_TYPE Debug CACHE STRING "Choose the type of build. options are: None, Debug, Release, RelWithDebInfo, MinSizeRel")
endif()
message(STATUS "CMAKE_BUILD_TYPE: ${CMAKE_BUILD_TYPE}")

if(NOT CMAKE_INSTALL_PREFIX)
   get_filename_component(CMAKE_INSTALL_PREFIX "${CMAKE_BINARY_DIR}/../install" ABSOLUTE)
endif()
set(CMAKE_INSTALL_PREFIX ${CMAKE_INSTALL_PREFIX} CACHE PATH "Location to install Spectral" FORCE)      

# Prevent in-source builds, build directory must be external to the source tree
set(CMAKE_DISABLE_IN_SOURCE_BUILD ON)

if(CMAKE_MAJOR_VERSION GREATER 2)
  cmake_policy(SET CMP0043 NEW)
  cmake_policy(SET CMP0048 NEW)
endif()

if(CMAKE_MAJOR_VERSION GREATER 2)
   #project (Spectral VERSION ${Spectral_VERSION} DESCRIPTION "Spectral PlugIn for Opticks GIS") # VERSION must be dotted-decimal
   project(Spectral DESCRIPTION "Spectral ${Spectral_VERSION} PlugIn for Opticks GIS")
else()
   project(Spectral)
endif()

############################################################
# From https://gitlab.kitware.com/cmake/community/-/wikis/doc/cmake/RPATH-handling
#
# use, i.e. don't skip the full RPATH for the build tree
set(CMAKE_SKIP_BUILD_RPATH FALSE)

# when building, don't use the install RPATH already
# (but later on when installing)
set(CMAKE_BUILD_WITH_INSTALL_RPATH FALSE)

set(CMAKE_INSTALL_RPATH "${CMAKE_INSTALL_PREFIX}/lib;${CMAKE_INSTALL_PREFIX}/PlugIns;${CMAKE_INSTALL_PREFIX}/PlugIns/debug")

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
   get_filename_component(OPTICKS_DEFAULT_CODEDIR "${CMAKE_SOURCE_DIR}/../../opticks/Code" ABSOLUTE)
endif()
set(Opticks_CODEDIR ${OPTICKS_DEFAULT_CODEDIR} CACHE PATH "Path to the opticks/Code directory for which this Spectral plugin is to be built.")

if(IS_DIRECTORY ${Opticks_CODEDIR})
   message(STATUS "Found Opticks Code directory ${Opticks_CODEDIR}")
else()
   message(SEND_ERROR " Opticks_CODEDIR ${Opticks_CODEDIR} not found!")
endif()

if($ENV{OPTICKS_BUILD_DIR})
   set(OPTICKS_DEFAULT_BUILDDIR $ENV{OPTICKS_BUILD_DIR})
else()
   set(OPTICKS_DEFAULT_BUILDDIR "${Opticks_CODEDIR}/Build")
endif()
set(Opticks_BUILDDIR "${OPTICKS_DEFAULT_BUILDDIR}" CACHE PATH "Path to opticks CMake Build directory for which this Spectral plugin is to be built.")

if(IS_DIRECTORY ${Opticks_BUILDDIR})
   message(STATUS "Found Opticks_BUILDDIR directory ${Opticks_BUILDDIR}")
   set(Opticks_LIBDIR ${Opticks_BUILDDIR}/lib)
   if(IS_DIRECTORY ${Opticks_LIBDIR})
      if(CMAKE_BUILD_TYPE STREQUAL "Debug")
         set(Opticks_LIBRARIES
            ${Opticks_LIBDIR}/libopticks-pluginutilitiesd.a
            ${Opticks_LIBDIR}/libopticks-pluginlibd.a
            )
      else()
         set(Opticks_LIBRARIES
            #         ${Opticks_LIBDIR}/libopticks-hdfpluginlib.a
            #         ${Opticks_LIBDIR}/libopticks-nitfpluginlib.a
            ${Opticks_LIBDIR}/libopticks-pluginutilities.a
            ${Opticks_LIBDIR}/libopticks-pluginlib.a
            )
      endif()
      message(STATUS "Opticks_LIBRARIES: ${Opticks_LIBRARIES}") # TODO make VERBOSE
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
else()
   set(get_filename_component(Spectral_BUILDDIR ${Spectral_CODEDIR}/../Build ABSOLUTE) CACHE PATH "Path to where you want this Spectral plugin to be built." FORCE)
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
set(CMAKE_PREFIX_PATH "${SPECTRAL_DEP_PATH}") # must be set to SPECTRAL_DEP_PATH exactly, otherwise system tbb will be found when SPECTRAL_DEP_PATH is desired
set(CMAKE_MODULE_PATH "${CMAKE_MODULE_PATH}" "${CMAKE_SOURCE_DIR}/cmake/Modules/")
if(CMAKE_MAJOR_VERSION GREATER 2)
   message(STATUS "CMAKE_PREFIX_PATH: ${CMAKE_PREFIX_PATH}")
endif()

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
    configure_file(cmake/Templates/spectral.dep          "${CMAKE_BINARY_DIR}/bin")
    configure_file(cmake/Templates/spectral-debug.dep    "${CMAKE_BINARY_DIR}/bin")
elseif(CMAKE_BUILD_TYPE STREQUAL "Release")
    configure_file(cmake/Templates/spectral-release.dep  "${CMAKE_BINARY_DIR}/bin")
else()
   configure_file(cmake/Templates/spectral-debug.dep     "${CMAKE_BINARY_DIR}/bin")
   configure_file(cmake/Templates/spectral-debug-sdk.dep "${CMAKE_BINARY_DIR}/bin")
endif()
install(FILES cmake/Templates/spectral-debug-sdk.dep DESTINATION bin CONFIGURATIONS Debug)
install(FILES cmake/Templates/spectral-debug.dep DESTINATION bin CONFIGURATIONS Debug)
install(FILES cmake/Templates/spectral-release.dep DESTINATION bin)

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
   message(SEND_ERROR "pthreads code cannot be built on this system.")
endif()

set(OpenGL_GL_PREFERENCE GLVND)

# Qt/Qwt boilerplate is in a separate file to share with Opticks
set(DEPENDENCY_PATH ${SPECTRAL_DEP_PATH})
include(ConfigureQt5Qwt6)
unset(DEPENDENCY_PATH)

find_package(Boost 1.45.0 REQUIRED)
find_package(Xerces REQUIRED)
find_package(ZLIB REQUIRED)
find_package(OpenGL REQUIRED)
find_package(Glew REQUIRED)
find_package(tiff REQUIRED)
find_package(geotiff REQUIRED)
find_package(Ossim REQUIRED) # Is ossim needed? Cem, Mnf, and Elm SConscripts mention it, but not in the code...
find_package(proj REQUIRED)
find_package(TBB REQUIRED)

set(XERCES_NAMESPACE_VERSION "${Xerces_VERSION_MAJOR}_${Xerces_VERSION_MINOR}")
configure_file(cmake/Templates/XercesIncludes.h "${Spectral_SOURCE_DIR}/Include/")

#----- Optional packages -----
# Need components for Ace, Tad, Rx, and WangBovik. TODO check component requirements
find_package(OpenCv COMPONENTS ImgProc Flann)
if(OpenCv_FOUND)
   add_definitions(-DOpenCv_VERSION_MAJOR=${OpenCv_MAJOR_VERSION})
   include_directories(${OpenCv_INCLUDE_DIRS})
   message(STATUS "OpenCv_LIBRARIES: ${OpenCv_LIBRARIES}")
endif()

set(OLD_CMAKE_PREFIX_PATH "${CMAKE_PREFIX_PATH}")
set(CMAKE_PREFIX_PATH "${CMAKE_PREFIX_PATH}" "${SPECTRAL_DEP_PATH}/tools/graphviz")
find_package(Doxygen)
set(CMAKE_PREFIX_PATH "${OLD_CMAKE_PREFIX_PATH}")
find_package(MsHelpCompiler)

configure_file(cmake/Templates/DependencyConfigs.h .)

#----- Adding public libraries -----
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/PlugIns") 
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_DEBUG "${CMAKE_BINARY_DIR}/PlugIns/debug")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_RELEASE "${CMAKE_BINARY_DIR}/PlugIns")
set(CMAKE_DEBUG_POSTFIX "d")
#----- Done adding public libraries -----

#----- Adding LibPrivate to hold libSpectralUtilities.a
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/LibPrivate")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_DEBUG "${CMAKE_BINARY_DIR}/LibPrivate")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_RELEASE "${CMAKE_BINARY_DIR}/LibPrivate")

#for windows, .dll go into "PlugIns" and .lib go into "LibPrivate"
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/PlugIns")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG "${CMAKE_BINARY_DIR}/PlugIns/debug")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE "${CMAKE_BINARY_DIR}/PlugIns")

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
include_directories(${Spectral_INCLUDE_DIRS})

#############################################################

include_directories(${Boost_INCLUDE_DIRS})
include_directories(${Xerces_INCLUDE_DIRS})
include_directories(${ZLIB_INCLUDE_DIRS})
include_directories(${OPENGL_INCLUDE_DIRS})
include_directories(${Glew_INCLUDE_DIRS})
include_directories(${tiff_INCLUDE_DIRS})
include_directories(${geotiff_INCLUDE_DIRS})
include_directories(${Ossim_INCLUDE_DIRS})
include_directories(${TBB_INCLUDE_DIRS})

if(CMAKE_SYSTEM_NAME STREQUAL "Linux")
    include_directories(${EXPAT_INCLUDE_DIRS}) # expat is an XML parser
endif()

add_definitions(-DAPPLICATION_XERCES)

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
    SignatureWindow
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

# First create libSpectralUtilities.a, needed by some of the other plugins:
add_subdirectory(SpectralUtilities)

# Then cause the leading "lib" prefix to not be prepended to our plugin LIB_NAME.so names
set(OLD_SHARED_LIBRARY_PREFIX "${CMAKE_SHARED_LIBRARY_PREFIX}")
set(CMAKE_SHARED_LIBRARY_PREFIX "")

# For now our subdir CMakeLists.txt need to have CODEDIR_PLUGIN_BUILD TRUE. Setting CODEDIR_PLUGIN_BUILD FALSE will
# result in the plugin libraries being written, but without their requisite target_link_libraries(LIB_NAME...),
# If that changes, all we'll need below (after the add_subdirectory loop) are the final install(TARGETS...) commands.
set(CODEDIR_PLUGIN_BUILD TRUE)
foreach(LIB_NAME IN LISTS SPECTRAL_PLUGINS)
   add_subdirectory(${LIB_NAME})
endforeach()

if(CODEDIR_PLUGIN_BUILD) # Create the multiple plugins here, rather than in the subdir CMakeLists.txt
   foreach(LIB_NAME IN LISTS SPECTRAL_PLUGINS)
      set(PLUGIN_LIB_SOURCES "")
      set(PLUGIN_MOC_HEADERS "")
      set(PLUGIN_QRC_FILES "")
      set(PLUGIN_MOC_OUTFILES "")
      set(PLUGIN_QRC_OUTFILES "")

      set(LIB_SOURCES "")
      set(LIB_HEADERS "")
      set(LIB_MOC_HEADERS "")
      set(LIB_QRC_FILES "")

      get_directory_property(LIB_SOURCES DIRECTORY ${LIB_NAME} DEFINITION ALL_SOURCES)

      foreach(SOURCE IN LISTS LIB_SOURCES)
         list(APPEND PLUGIN_LIB_SOURCES "${LIB_NAME}/${SOURCE}")
      endforeach()

      add_library(${LIB_NAME} SHARED ${PLUGIN_LIB_SOURCES} )
      set_target_properties(${LIB_NAME} PROPERTIES PREFIX "")
      target_link_libraries(${LIB_NAME}
         SpectralUtilities # add_library(SpectralUtilities) is in SpectralUtilities/CMakeLists.txt
         ${Opticks_LIBRARIES}
         ${QT_LIBRARIES}
         ${tiff_LIBRARIES}
         ${geotiff_LIBRARIES}
         ${Ossim_LIBRARIES}
         ${proj_LIBRARIES}
         ${Xerces_LIBRARIES}
         ${OpenCv_LIBRARIES}
         ${TBB_LIBRARIES}
         ${pthreads_LIBRARIES}
         )
   endforeach()
   
   if(WIN32)
      install(TARGETS ${SPECTRAL_PLUGINS} RUNTIME DESTINATION "${CMAKE_BINARY_DIR}/PlugIns" CONFIGURATIONS Release;RelWithDebInfo;MinSizeRel)
      install(TARGETS ${SPECTRAL_PLUGINS} RUNTIME DESTINATION "${CMAKE_BINARY_DIR}/PlugIns/debug" CONFIGURATIONS Debug)
   else()
      install(TARGETS ${SPECTRAL_PLUGINS} LIBRARY DESTINATION "PlugIns" CONFIGURATIONS Release;RelWithDebInfo;MinSizeRel)
      install(TARGETS ${SPECTRAL_PLUGINS} LIBRARY DESTINATION "PlugIns/debug" CONFIGURATIONS Debug)
   endif()
endif()
# restore the system SHARED_LIBRARY_PREFIX
set(CMAKE_SHARED_LIBRARY_PREFIX "${OLD_SHARED_LIBRARY_PREFIX}")

# add_executable(Spectral WIN32 ${SOURCE_FILES} ${INTERFACE_HEADER_FILES}) # Spectral is a plugin, not an executable. How does WIN32 work?
source_group(Interfaces FILES ${INTERFACE_HEADER_FILES})

if (EXISTS "CppTests" AND IS_DIRECTORY "CppTests")
   add_subdirectory(CppTests)
endif()

# What do these do?
include(FeatureSummary)
feature_summary(WHAT ALL)

# Mark variables as advanced that the finders should have marked
mark_as_advanced(FORCE QT_QMAKE_EXECUTABLE)
mark_as_advanced(FORCE Boost_LIB_DIAGNOSTIC_DEFINITIONS)

#----- Done adding Spectral PlugIn libraries -----
