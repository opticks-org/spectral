set (HEADER_FILES
   RangeProfileImporter.h
   RangeProfilePlotManager.h
)

set (SOURCE_FILES
   ModuleManager.cpp
   RangeProfileImporter.cpp
   RangeProfilePlotManager.cpp
   )

set(ALL_SOURCES ${SOURCE_FILES} ${HEADER_FILES})

if(NOT CODEDIR_PLUGIN_BUILD)
   add_library(RangeProfile SHARED ${SOURCE_FILES} ${HEADER_FILES})
endif()
