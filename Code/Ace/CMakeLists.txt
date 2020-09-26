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

set(ALL_SOURCES ${SOURCE_FILES} ${HEADER_FILES})

if(NOT CODEDIR_PLUGIN_BUILD)
   add_library(Ace SHARED ${SOURCE_FILES} ${HEADER_FILES})
   target_link_libraries(Ace SpectralUtilities)
endif()
