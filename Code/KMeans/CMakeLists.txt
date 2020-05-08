set (HEADER_FILES
   KMeansDlg.h
   KMeans.h
   )

set (SOURCE_FILES
   KMeans.cpp
   KMeansDlg.cpp
   ModuleManager.cpp
   )

set (MOC_HEADERS
   KMeansDlg.h
   KMeans.h
   )

if(ONE_SPECTRAL_LIB)
   set_property(DIRECTORY PROPERTY ALL_SOURCES ${SOURCE_FILES} ${HEADER_FILES})
   set_property(DIRECTORY PROPERTY MOC_HEADERS ${MOC_HEADERS})
else()
   qt4_wrap_cpp(MOC_OUTFILES ${MOC_HEADERS})
   source_group(moc FILES ${MOC_OUTFILES})
   add_library(KMeans STATIC ${SOURCE_FILES} ${HEADER_FILES} ${MOC_HEADERS} ${MOC_OUTFILES})
endif()
