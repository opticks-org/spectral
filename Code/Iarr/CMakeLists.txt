set (HEADER_FILES
   IarrDlg.h
   Iarr.h
   )

set (SOURCE_FILES
   Iarr.cpp
   IarrDlg.cpp
   ModuleManager.cpp
   )

set(ALL_SOURCES ${SOURCE_FILES} ${HEADER_FILES})

if(NOT CODEDIR_PLUGIN_BUILD)
   add_library(Iarr SHARED ${SOURCE_FILES} ${HEADER_FILES})
endif()
