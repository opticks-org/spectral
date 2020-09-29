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

set(ALL_SOURCES ${SOURCE_FILES} ${HEADER_FILES})

if(NOT CODEDIR_PLUGIN_BUILD)
   add_library(SpectralLibraryMatch SHARED ${SOURCE_FILES} ${HEADER_FILES} ${MOC_HEADERS})
endif()
