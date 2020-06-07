set (HEADER_FILES
   LibraryBuilder.h
   SpectralLibraryDlg.h
   )

set (SOURCE_FILES
   ModuleManager.cpp
   LibraryBuilder.cpp
   SpectralLibraryDlg.cpp
   )

set (MOC_HEADERS
   LibraryBuilder.h
   SpectralLibraryDlg.h
   )

if(CODEDIR_PLUGIN_BUILD)
   set_property(DIRECTORY PROPERTY ALL_SOURCES ${SOURCE_FILES} ${HEADER_FILES})
   set_property(DIRECTORY PROPERTY MOC_HEADERS ${MOC_HEADERS})
else()
   qt4_wrap_cpp(MOC_OUTFILES ${MOC_HEADERS})
   source_group(moc FILES ${MOC_OUTFILES})
   add_library(SpectralLibrary SHARED ${SOURCE_FILES} ${HEADER_FILES} ${MOC_HEADERS} ${MOC_OUTFILES})
endif()
