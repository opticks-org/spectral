set (HEADER_FILES
   SamDlg.h
   SamErr.h
   Sam.h
   )

set (SOURCE_FILES
   ModuleManager.cpp
   SamDlg.cpp
   Sam.cpp
   )

set (MOC_HEADERS
   SamDlg.h
   SamErr.h
   Sam.h
   )

if(ONE_SPECTRAL_LIB)
   set_property(DIRECTORY PROPERTY ALL_SOURCES ${SOURCE_FILES} ${HEADER_FILES})
   set_property(DIRECTORY PROPERTY MOC_HEADERS ${MOC_HEADERS})
else()
   qt4_wrap_cpp(MOC_OUTFILES ${MOC_HEADERS})
   source_group(moc FILES ${MOC_OUTFILES})
   add_library(Sam STATIC ${SOURCE_FILES} ${HEADER_FILES} ${MOC_HEADERS} ${MOC_OUTFILES})
endif()
