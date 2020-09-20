set (HEADER_FILES
   LibraryEditDlg.h
   LocateDialog.h
   MatchIdDlg.h
   ResultsItem.h
   ResultsItemModel.h
   ResultsPage.h
   ResultsSortFilter.h
   SpectralLibraryManager.h
   SpectralLibraryMatch.h
   SpectralLibraryMatchId.h
   SpectralLibraryMatchMetrics.h
   SpectralLibraryMatchOptions.h
   SpectralLibraryMatchResults.h
   SpectralLibraryMatchTools.h
   )

set (SOURCE_FILES
   LibraryEditDlg.cpp
   LocateDialog.cpp
   MatchIdDlg.cpp
   ModuleManager.cpp
   ResultsItem.cpp
   ResultsItemModel.cpp
   ResultsPage.cpp
   ResultsSortFilter.cpp
   SpectralLibraryManager.cpp
   SpectralLibraryMatch.cpp
   SpectralLibraryMatchId.cpp
   SpectralLibraryMatchOptions.cpp
   SpectralLibraryMatchResults.cpp
   SpectralLibraryMatchTools.cpp
   )

set (MOC_HEADERS
   LibraryEditDlg.h
   LocateDialog.h
   MatchIdDlg.h
   ResultsItem.h
   ResultsItemModel.h
   ResultsPage.h
   ResultsSortFilter.h
   SpectralLibraryManager.h
   SpectralLibraryMatchId.h
   SpectralLibraryMatchOptions.h
   SpectralLibraryMatchResults.h
   SpectralLibraryMatchTools.h
   )

if(CODEDIR_PLUGIN_BUILD)
   set_property(DIRECTORY PROPERTY ALL_SOURCES ${SOURCE_FILES} ${HEADER_FILES})
   set_property(DIRECTORY PROPERTY MOC_HEADERS ${MOC_HEADERS})
else()
   qt4_wrap_cpp(MOC_OUTFILES ${MOC_HEADERS})
   source_group(moc FILES ${MOC_OUTFILES})
   add_library(SpectralLibraryMatch SHARED ${SOURCE_FILES} ${HEADER_FILES} ${MOC_HEADERS} ${MOC_OUTFILES})
endif()
