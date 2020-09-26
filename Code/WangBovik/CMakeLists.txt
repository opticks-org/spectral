set (HEADER_FILES
   WangBovikDlg.h
   WangBovikErr.h
   WangBovik.h
   )

set (SOURCE_FILES
   ModuleManager.cpp
   WangBovikDlg.cpp
   WangBovik.cpp
   )

set(ALL_SOURCES ${SOURCE_FILES} ${HEADER_FILES})

if(NOT CODEDIR_PLUGIN_BUILD)
   add_library(WangBovik SHARED ${SOURCE_FILES} ${HEADER_FILES} ${MOC_HEADERS} ${MOC_OUTFILES})
endif()
