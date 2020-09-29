set (HEADER_FILES
   DgFileTile.h
   DgFormatsRasterPager.h
   DgImporter.h
   DgUtilities.h
   OptionsDgImport.h
   )

set (SOURCE_FILES
   DgFileTile.cpp
   DgFormatsRasterPager.cpp
   DgImporter.cpp
   DgUtilities.cpp
   OptionsDgImport.cpp
   ModuleManager.cpp
   )

set(ALL_SOURCES ${SOURCE_FILES} ${HEADER_FILES})

if(NOT CODEDIR_PLUGIN_BUILD)
   add_library(DgFormats SHARED ${SOURCE_FILES} ${HEADER_FILES})
endif()
