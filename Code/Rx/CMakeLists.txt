set (HEADER_FILES
   RxDialog.h
   Rx.h
   )

set (SOURCE_FILES
   ModuleManager.cpp
   RxDialog.cpp
   Rx.cpp
   )

set (UI_FILES
   RxDialog.ui
   )

set(ALL_SOURCES ${SOURCE_FILES} ${HEADER_FILES} ${UI_FILES})

if(NOT CODEDIR_PLUGIN_BUILD)
   add_library(Rx SHARED ${SOURCE_FILES} ${HEADER_FILES})
endif()
