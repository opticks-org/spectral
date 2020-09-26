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

set(QRC_FILES
   Plotting.qrc
   )

set(ALL_SOURCES ${SOURCE_FILES} ${HEADER_FILES} ${QRC_FILES})

if(NOT CODEDIR_PLUGIN_BUILD)
   add_library(Plotting SHARED ${SOURCE_FILES} ${HEADER_FILES} ${QRC_FILES})
endif()
