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

set(ALL_SOURCES ${SOURCE_FILES} ${HEADER_FILES})

set_property(DIRECTORY PROPERTY ALL_SOURCES ${SOURCE_FILES} ${HEADER_FILES})
add_library(SpectralUtilities STATIC ${SOURCE_FILES} ${HEADER_FILES})
