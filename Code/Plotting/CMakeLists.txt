set (HEADER_FILES
   GetSubsetDialog.h
   PlotSpatialProfile.h
   PlottingManager.h
   ProfilePlotUtilities.h
)

set (SOURCE_FILES
   GetSubsetDialog.cpp
   PlotSpatialProfile.cpp
   PlottingManager.cpp
   ProfilePlotUtilities.cpp
   ModuleManager.cpp
   )

set (MOC_HEADERS
   GetSubsetDialog.h
   PlotSpatialProfile.h
   PlottingManager.h
   ProfilePlotUtilities.h
   )

if(ONE_SPECTRAL_LIB)
   set_property(DIRECTORY PROPERTY ALL_SOURCES ${SOURCE_FILES} ${HEADER_FILES})
   set_property(DIRECTORY PROPERTY MOC_HEADERS ${MOC_HEADERS})
else()
   qt4_wrap_cpp(MOC_OUTFILES ${MOC_HEADERS})
   source_group(moc FILES ${MOC_OUTFILES})
   add_library(Plotting STATIC ${SOURCE_FILES} ${HEADER_FILES} ${MOC_HEADERS} ${MOC_OUTFILES})
endif()
