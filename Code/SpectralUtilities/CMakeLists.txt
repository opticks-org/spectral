set(HEADER_FILES
   BuildRevision.h
   CommonPlugInArgs.h
   CommonSignatureMetadataKeys.h
   SpectralContextMenuActions.h
   SpectralSignatureSelector.h
   SpectralUtilities.h
   )
set(SOURCE_FILES
   CommonPlugInArgs.cpp
   CommonSignatureMetadataKeys.cpp
   SpectralSignatureSelector.cpp
   SpectralUtilities.cpp
   )
set(MOC_HEADERS
   BuildRevision.h
   CommonPlugInArgs.h
   CommonSignatureMetadataKeys.h
   SpectralContextMenuActions.h
   SpectralSignatureSelector.h
   SpectralUtilities.h
   )
if(ONE_SPECTRAL_LIB)
   set_property(DIRECTORY PROPERTY ALL_SOURCES ${SOURCE_FILES} ${HEADER_FILES})
else()
   qt4_wrap_cpp(MOC_OUTFILES ${MOC_HEADERS})
   source_group(moc FILES ${MOC_OUTFILES})
   add_library(SpectralUtilities STATIC ${SOURCE_FILES} ${HEADER_FILES} ${MOC_HEADERS} ${MOC_OUTFILES})
endif()
