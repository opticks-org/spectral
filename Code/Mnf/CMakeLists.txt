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

set(ALL_SOURCES ${SOURCE_FILES} ${HEADER_FILES})

if(NOT CODEDIR_PLUGIN_BUILD)
   add_library(Mnf SHARED ${SOURCE_FILES} ${HEADER_FILES})
endif()
