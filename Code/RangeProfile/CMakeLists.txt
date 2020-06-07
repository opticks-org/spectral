set (HEADER_FILES
   RangeProfileImporter.h
   RangeProfilePlotManager.h
)

set (SOURCE_FILES
   ModuleManager.cpp
   RangeProfileImporter.cpp
   RangeProfilePlotManager.cpp
   )

set (MOC_HEADERS
   RangeProfileImporter.h
   RangeProfilePlotManager.h
   )

if(CODEDIR_PLUGIN_BUILD)
   set_property(DIRECTORY PROPERTY ALL_SOURCES ${SOURCE_FILES} ${HEADER_FILES})
   set_property(DIRECTORY PROPERTY MOC_HEADERS ${MOC_HEADERS})
else()
   qt4_wrap_cpp(MOC_OUTFILES ${MOC_HEADERS})
   source_group(moc FILES ${MOC_OUTFILES})
   add_library(RangeProfile SHARED ${SOURCE_FILES} ${HEADER_FILES} ${MOC_HEADERS} ${MOC_OUTFILES})
endif()
