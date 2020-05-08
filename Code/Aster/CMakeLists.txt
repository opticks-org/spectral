set (HEADER_FILES
   AsterSignatureImporter.h
   )

set (SOURCE_FILES
   AsterSignatureImporter.cpp
   ModuleManager.cpp
   )

set (MOC_HEADERS
   AsterSignatureImporter.h
   )

if(ONE_SPECTRAL_LIB)
   set_property(DIRECTORY PROPERTY ALL_SOURCES ${SOURCE_FILES} ${HEADER_FILES})
   set_property(DIRECTORY PROPERTY MOC_HEADERS ${MOC_HEADERS})
else()
   qt4_wrap_cpp(MOC_OUTFILES ${MOC_HEADERS})
   source_group(moc FILES ${MOC_OUTFILES})
   add_library(Aster STATIC ${SOURCE_FILES} ${HEADER_FILES} ${MOC_HEADERS} ${MOC_OUTFILES})
endif()
