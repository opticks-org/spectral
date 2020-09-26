set (HEADER_FILES
   BandResamplePager.h
   LandsatEtmPlusImporter.h
   LandsatGeotiffImporter.h
   LandsatGeotiffRasterPager.h
   LandsatTmImporter.h
   LandsatUtilities.h
   OptionsLandsatImport.h
   )

set (SOURCE_FILES
   BandResamplePager.cpp
   LandsatEtmPlusImporter.cpp
   LandsatGeotiffImporter.cpp
   LandsatGeotiffRasterPager.cpp
   LandsatTmImporter.cpp
   LandsatUtilities.cpp
   ModuleManager.cpp
   OptionsLandsatImport.cpp
   )

set(ALL_SOURCES ${SOURCE_FILES} ${HEADER_FILES})

if(NOT CODEDIR_PLUGIN_BUILD)
   add_library(Landsat SHARED ${SOURCE_FILES} ${HEADER_FILES})
endif()
