set (HEADER_FILES
   AsterSignatureImporter.h
   )

set (SOURCE_FILES
   AsterSignatureImporter.cpp
   ModuleManager.cpp
   )

set(ALL_SOURCES ${SOURCE_FILES} ${HEADER_FILES})

if(NOT CODEDIR_PLUGIN_BUILD)
   add_library(Aster SHARED ${SOURCE_FILES} ${HEADER_FILES} ${MOC_HEADERS} ${MOC_OUTFILES})
endif()
