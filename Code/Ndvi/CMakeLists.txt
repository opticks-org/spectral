set (HEADER_FILES
   NdviDlg.h
   Ndvi.h
   )

set (SOURCE_FILES
   NdviDlg.cpp
   Ndvi.cpp
   ModuleManager.cpp
   )

set(ALL_SOURCES ${SOURCE_FILES} ${HEADER_FILES})

if(NOT CODEDIR_PLUGIN_BUILD)
   add_library(Ndvi SHARED ${SOURCE_FILES} ${HEADER_FILES} ${MOC_HEADERS} ${MOC_OUTFILES})
endif()
