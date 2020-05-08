set (HEADER_FILES
   RxDialog.h
   Rx.h
   )

set (SOURCE_FILES
   ModuleManager.cpp
   RxDialog.cpp
   Rx.cpp
   )

set (MOC_HEADERS
   RxDialog.h
   Rx.h
   )

set (UI_FILES
   RxDialog.ui
   )

qt4_wrap_ui(UI_OUTFILES ${UI_FILES})

if(Qt_VERSION_MAJOR EQUAL 4)
   execute_process(COMMAND ${QT_UIC_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/RxDialog.ui -o  ${CMAKE_CURRENT_SOURCE_DIR}/ui_RxDialog.h)
endif()
# Otherwise Qt5 QT_AUTOMOC should handle this

if(ONE_SPECTRAL_LIB)
   set_property(DIRECTORY PROPERTY ALL_SOURCES ${SOURCE_FILES} ${HEADER_FILES} ${UI_FILES})
   set_property(DIRECTORY PROPERTY MOC_HEADERS ${MOC_HEADERS})
else()
   qt4_wrap_cpp(MOC_OUTFILES ${MOC_HEADERS})
   source_group(moc FILES ${MOC_OUTFILES})
   add_library(Rx STATIC ${SOURCE_FILES} ${HEADER_FILES} ${MOC_HEADERS} ${MOC_OUTFILES} ${UI_OUTFILES})
endif()
