set (HEADER_FILES
   ElmBatch.h
   ElmCore.h
   ElmDlg.h
   ElmElement.h
   ElmFile.h
   ElmInteractive.h
   )

set (SOURCE_FILES
   ElmBatch.cpp
   ElmCore.cpp
   ElmDlg.cpp
   ElmElement.cpp
   ElmFile.cpp
   ElmInteractive.cpp
   ModuleManager.cpp
   )

set(ALL_SOURCES ${SOURCE_FILES} ${HEADER_FILES})

if(NOT CODEDIR_PLUGIN_BUILD)
   add_library(Elm SHARED ${SOURCE_FILES} ${HEADER_FILES} ${MOC_HEADERS} ${MOC_OUTFILES})
endif()
