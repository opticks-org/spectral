set (HEADER_FILES
   SamDlg.h
   SamErr.h
   Sam.h
   )

set (SOURCE_FILES
   ModuleManager.cpp
   SamDlg.cpp
   Sam.cpp
   )

set(ALL_SOURCES ${SOURCE_FILES} ${HEADER_FILES})

if(NOT CODEDIR_PLUGIN_BUILD)
   add_library(Sam SHARED ${SOURCE_FILES} ${HEADER_FILES})
endif()
