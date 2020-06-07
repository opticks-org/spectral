set (HEADER_FILES
   CemDlg.h
   Cem.h
   )

set (SOURCE_FILES
   Cem.cpp
   CemDlg.cpp
   ModuleManager.cpp
   )

set (MOC_HEADERS
   CemDlg.h
   Cem.h
   )

if(CODEDIR_PLUGIN_BUILD)
   set_property(DIRECTORY PROPERTY ALL_SOURCES ${SOURCE_FILES} ${HEADER_FILES})
   set_property(DIRECTORY PROPERTY MOC_HEADERS ${MOC_HEADERS})
else()
   qt4_wrap_cpp(MOC_OUTFILES ${MOC_HEADERS})
   source_group(moc FILES ${MOC_OUTFILES})
   add_library(Cem SHARED ${SOURCE_FILES} ${HEADER_FILES} ${MOC_HEADERS} ${MOC_OUTFILES})
endif()
