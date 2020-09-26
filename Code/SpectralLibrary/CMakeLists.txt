set (HEADER_FILES
   LibraryBuilder.h
   SpectralLibraryDlg.h
   )

set (SOURCE_FILES
   ModuleManager.cpp
   LibraryBuilder.cpp
   SpectralLibraryDlg.cpp
   )

set(ALL_SOURCES ${SOURCE_FILES} ${HEADER_FILES})

if(NOT CODEDIR_PLUGIN_BUILD)
   add_library(SpectralLibrary SHARED ${SOURCE_FILES} ${HEADER_FILES})
endif()
