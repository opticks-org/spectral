set (HEADER_FILES
   TadDialog.h
   Tad.h
   )

set (SOURCE_FILES
   ModuleManager.cpp
   TadDialog.cpp
   Tad.cpp
   )

set (UI_FILES
   TadDialog.ui
   )

set(ALL_SOURCES ${SOURCE_FILES} ${HEADER_FILES} ${UI_FILES})

if(NOT CODEDIR_PLUGIN_BUILD)
   add_library(Tad SHARED ${SOURCE_FILES} ${HEADER_FILES} ${MOC_HEADERS} ${MOC_OUTFILES} ${UI_FILES})
endif()
