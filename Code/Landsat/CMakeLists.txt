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

set (MOC_HEADERS
   BandResamplePager.h
   LandsatEtmPlusImporter.h
   LandsatGeotiffImporter.h
   LandsatGeotiffRasterPager.h
   LandsatTmImporter.h
   LandsatUtilities.h
   OptionsLandsatImport.h
   )

if(ONE_SPECTRAL_LIB)
   set_property(DIRECTORY PROPERTY ALL_SOURCES ${SOURCE_FILES} ${HEADER_FILES})
   set_property(DIRECTORY PROPERTY MOC_HEADERS ${MOC_HEADERS})
else()
   qt4_wrap_cpp(MOC_OUTFILES ${MOC_HEADERS})
   source_group(moc FILES ${MOC_OUTFILES})
   add_library(Landsat STATIC ${SOURCE_FILES} ${HEADER_FILES} ${MOC_HEADERS} ${MOC_OUTFILES})
endif()
