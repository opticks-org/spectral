set (HEADER_FILES
   PropertiesSignaturePlotObject.h
   SignaturePlotObject.h
   SignatureWindow.h
   SignatureWindowIcons.h
   SignatureWindowOptions.h
   )

set (SOURCE_FILES
   ModuleManager.cpp
   PropertiesSignaturePlotObject.cpp
   SignaturePlotObject.cpp
   SignatureWindow.cpp
   SignatureWindowIcons.cpp
   SignatureWindowOptions.cpp
   )

set(ALL_SOURCES ${SOURCE_FILES} ${HEADER_FILES})

if(NOT CODEDIR_PLUGIN_BUILD)
   add_library(SignatureWindow STATIC ${SOURCE_FILES} ${HEADER_FILES} ${MOC_HEADERS} ${MOC_OUTFILES})
endif()
