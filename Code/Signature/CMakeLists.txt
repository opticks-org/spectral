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

set (MOC_HEADERS
   SignatureExporter.h
   SignatureImporter.h
   SignatureSetExporter.h
   SignatureSetImporter.h
   )

if(ONE_SPECTRAL_LIB)
   set_property(DIRECTORY PROPERTY ALL_SOURCES ${SOURCE_FILES} ${HEADER_FILES})
   set_property(DIRECTORY PROPERTY MOC_HEADERS ${MOC_HEADERS})
else()
   qt4_wrap_cpp(MOC_OUTFILES ${MOC_HEADERS})
   source_group(moc FILES ${MOC_OUTFILES})
   add_library(Signature STATIC ${SOURCE_FILES} ${HEADER_FILES} ${MOC_HEADERS} ${MOC_OUTFILES})
endif()
