set (HEADER_FILES
   GaussianResampler.h
   Interpolator.h
   LinearInterpolator.h
   ResamplerImp.h
   ResamplerOptions.h
   ResamplerPlugInDlg.h
   ResamplerPlugIn.h
   SplineInterpolator.h
   )

set (SOURCE_FILES
   GaussianResampler.cpp
   Interpolator.cpp
   LinearInterpolator.cpp
   ModuleManager.cpp
   ResamplerImp.cpp
   ResamplerOptions.cpp
   ResamplerPlugIn.cpp
   ResamplerPlugInDlg.cpp
   SplineInterpolator.cpp
   )

set(ALL_SOURCES ${SOURCE_FILES} ${HEADER_FILES})

if(NOT CODEDIR_PLUGIN_BUILD)
   add_library(Resampler SHARED ${SOURCE_FILES} ${HEADER_FILES} ${MOC_HEADERS} ${MOC_OUTFILES})
endif()
