set (HEADER_FILES
   AceDlg.h
   AceErr.h
   Ace.h
   )

set (SOURCE_FILES
   Ace.cpp
   AceDlg.cpp
   ModuleManager.cpp
   )

set (MOC_HEADERS
   AceDlg.h
   AceErr.h
   Ace.h
   )

if(CODEDIR_PLUGIN_BUILD)
   set_property(DIRECTORY PROPERTY ALL_SOURCES ${SOURCE_FILES} ${HEADER_FILES})
   set_property(DIRECTORY PROPERTY MOC_HEADERS ${MOC_HEADERS})
else()
   qt4_wrap_cpp(MOC_OUTFILES ${MOC_HEADERS})
   source_group(moc FILES ${MOC_OUTFILES})
   add_library(Ace SHARED ${SOURCE_FILES} ${HEADER_FILES} ${MOC_HEADERS} ${MOC_OUTFILES})
endif()
