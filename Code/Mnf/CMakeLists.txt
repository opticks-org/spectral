set (HEADER_FILES
   DifferenceImageDlg.h
   EigenPlotDlg.h
   MnfDlg.h
   Mnf.h
   MnfInverse.h
   StatisticsDlg.h
   )

set (SOURCE_FILES
   DifferenceImageDlg.cpp
   EigenPlotDlg.cpp
   Mnf.cpp
   MnfDlg.cpp
   MnfInverse.cpp
   ModuleManager.cpp
   StatisticsDlg.cpp
   )

set (MOC_HEADERS
   DifferenceImageDlg.h
   EigenPlotDlg.h
   MnfDlg.h
   Mnf.h
   MnfInverse.h
   StatisticsDlg.h
   )

if(ONE_SPECTRAL_LIB)
   set_property(DIRECTORY PROPERTY ALL_SOURCES ${SOURCE_FILES} ${HEADER_FILES})
   set_property(DIRECTORY PROPERTY MOC_HEADERS ${MOC_HEADERS})
else()
   qt4_wrap_cpp(MOC_OUTFILES ${MOC_HEADERS})
   source_group(moc FILES ${MOC_OUTFILES})
   add_library(Mnf STATIC ${SOURCE_FILES} ${HEADER_FILES} ${MOC_HEADERS} ${MOC_OUTFILES})
endif()
