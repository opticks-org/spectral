set (HEADER_FILES
   SignatureExporter.h
   SignatureImporter.h
   SignatureSetExporter.h
   SignatureSetImporter.h
   )

set (SOURCE_FILES
   ModuleManager.cpp
   SignatureExporter.cpp
   SignatureImporter.cpp
   SignatureSetExporter.cpp
   SignatureSetImporter.cpp
   )

set(ALL_SOURCES ${SOURCE_FILES} ${HEADER_FILES})

if(NOT CODEDIR_PLUGIN_BUILD)
   add_library(Signature SHARED ${SOURCE_FILES} ${HEADER_FILES} ${MOC_HEADERS} ${MOC_OUTFILES})
endif()
