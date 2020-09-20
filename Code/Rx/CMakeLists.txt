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

execute_process(COMMAND ${QT_UIC_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/RxDialog.ui -o  ${CMAKE_CURRENT_SOURCE_DIR}/ui_RxDialog.h)
# Otherwise Qt5 QT_AUTOUIC should handle this

if(CODEDIR_PLUGIN_BUILD)
   set_property(DIRECTORY PROPERTY ALL_SOURCES ${SOURCE_FILES} ${HEADER_FILES} ${UI_FILES})
   set_property(DIRECTORY PROPERTY MOC_HEADERS ${MOC_HEADERS})
else()
   qt4_wrap_cpp(MOC_OUTFILES ${MOC_HEADERS})
   source_group(moc FILES ${MOC_OUTFILES})
   add_library(Rx SHARED ${SOURCE_FILES} ${HEADER_FILES} ${MOC_HEADERS} ${MOC_OUTFILES} ${UI_OUTFILES})
endif()
