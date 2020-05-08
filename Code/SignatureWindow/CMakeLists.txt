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

set (MOC_HEADERS
   PropertiesSignaturePlotObject.h
   SignaturePlotObject.h
   SignatureWindow.h
   SignatureWindowIcons.h
   SignatureWindowOptions.h
   )

if(ONE_SPECTRAL_LIB)
   set_property(DIRECTORY PROPERTY ALL_SOURCES ${SOURCE_FILES} ${HEADER_FILES})
   set_property(DIRECTORY PROPERTY MOC_HEADERS ${MOC_HEADERS})
else()
   qt4_wrap_cpp(MOC_OUTFILES ${MOC_HEADERS})
   source_group(moc FILES ${MOC_OUTFILES})
   add_library(SignatureWindow STATIC ${SOURCE_FILES} ${HEADER_FILES} ${MOC_HEADERS} ${MOC_OUTFILES})
endif()
