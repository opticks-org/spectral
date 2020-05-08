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
if(ONE_OPTICKS_LIB)
    set_property(DIRECTORY PROPERTY ALL_SOURCES ${SOURCE_FILES} ${HEADER_FILES})
else()
    add_library(SpectralUtilities STATIC ${SOURCE_FILES} ${HEADER_FILES})
endif()
