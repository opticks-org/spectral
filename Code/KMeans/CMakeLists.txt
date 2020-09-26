set (HEADER_FILES
   KMeansDlg.h
   KMeans.h
   )

set (SOURCE_FILES
   KMeans.cpp
   KMeansDlg.cpp
   ModuleManager.cpp
   )

set(ALL_SOURCES ${SOURCE_FILES} ${HEADER_FILES})

if(NOT CODEDIR_PLUGIN_BUILD)
   add_library(KMeans SHARED ${SOURCE_FILES} ${HEADER_FILES})
endif()
