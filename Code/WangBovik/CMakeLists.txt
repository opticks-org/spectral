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

set (MOC_HEADERS
   WangBovikDlg.h
   WangBovikErr.h
   WangBovik.h
   )

if(ONE_SPECTRAL_LIB)
   set_property(DIRECTORY PROPERTY ALL_SOURCES ${SOURCE_FILES} ${HEADER_FILES})
   set_property(DIRECTORY PROPERTY MOC_HEADERS ${MOC_HEADERS})
else()
   qt4_wrap_cpp(MOC_OUTFILES ${MOC_HEADERS})
   source_group(moc FILES ${MOC_OUTFILES})
   add_library(WangBovik STATIC ${SOURCE_FILES} ${HEADER_FILES} ${MOC_HEADERS} ${MOC_OUTFILES})
endif()
