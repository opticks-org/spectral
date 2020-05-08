set (HEADER_FILES
   TadDialog.h
   Tad.h
   )

set (SOURCE_FILES
   ModuleManager.cpp
   TadDialog.cpp
   Tad.cpp
   )

set (MOC_HEADERS
   TadDialog.h
   Tad.h
   )

set (UI_FILES
   TadDialog.ui
   )
qt4_wrap_ui(UI_OUTFILES ${UI_FILES})

if(Qt_VERSION_MAJOR EQUAL 4)
   execute_process(COMMAND ${QT_UIC_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/TadDialog.ui -o  ${CMAKE_CURRENT_SOURCE_DIR}/ui_TadDialog.h)
endif()
# Otherwise Qt5 QT_AUTOMOC should handle this


if(ONE_SPECTRAL_LIB)
   set_property(DIRECTORY PROPERTY ALL_SOURCES ${SOURCE_FILES} ${HEADER_FILES} ${UI_FILES})
   set_property(DIRECTORY PROPERTY MOC_HEADERS ${MOC_HEADERS})
else()
   qt4_wrap_cpp(MOC_OUTFILES ${MOC_HEADERS})
   source_group(moc FILES ${MOC_OUTFILES})
   add_library(Tad STATIC ${SOURCE_FILES} ${HEADER_FILES} ${MOC_HEADERS} ${MOC_OUTFILES})
endif()
