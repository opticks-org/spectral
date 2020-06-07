set (HEADER_FILES
   ElmBatch.h
   ElmCore.h
   ElmDlg.h
   ElmElement.h
   ElmFile.h
   ElmInteractive.h
   )

set (SOURCE_FILES
   ElmBatch.cpp
   ElmCore.cpp
   ElmDlg.cpp
   ElmElement.cpp
   ElmFile.cpp
   ElmInteractive.cpp
   ModuleManager.cpp
   )

set (MOC_HEADERS
   ElmBatch.h
   ElmCore.h
   ElmDlg.h
   ElmElement.h
   ElmFile.h
   ElmInteractive.h
   )

if(CODEDIR_PLUGIN_BUILD)
   set_property(DIRECTORY PROPERTY ALL_SOURCES ${SOURCE_FILES} ${HEADER_FILES})
   set_property(DIRECTORY PROPERTY MOC_HEADERS ${MOC_HEADERS})
else()
   qt4_wrap_cpp(MOC_OUTFILES ${MOC_HEADERS})
   source_group(moc FILES ${MOC_OUTFILES})
   add_library(Elm SHARED ${SOURCE_FILES} ${HEADER_FILES} ${MOC_HEADERS} ${MOC_OUTFILES})
endif()
