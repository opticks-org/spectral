set (HEADER_FILES
   CemDlg.h
   Cem.h
   )

set (SOURCE_FILES
   Cem.cpp
   CemDlg.cpp
   ModuleManager.cpp
   )

set(ALL_SOURCES ${SOURCE_FILES} ${HEADER_FILES})

if(NOT CODEDIR_PLUGIN_BUILD)
   add_library(Cem SHARED ${SOURCE_FILES} ${HEADER_FILES})
endif()
