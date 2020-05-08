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

set (MOC_HEADERS
   GaussianResampler.h
   Interpolator.h
   LinearInterpolator.h
   ResamplerImp.h
   ResamplerOptions.h
   ResamplerPlugInDlg.h
   ResamplerPlugIn.h
   SplineInterpolator.h
   )

if(ONE_SPECTRAL_LIB)
   set_property(DIRECTORY PROPERTY ALL_SOURCES ${SOURCE_FILES} ${HEADER_FILES})
   set_property(DIRECTORY PROPERTY MOC_HEADERS ${MOC_HEADERS})
else()
   qt4_wrap_cpp(MOC_OUTFILES ${MOC_HEADERS})
   source_group(moc FILES ${MOC_OUTFILES})
   add_library(Resampler STATIC ${SOURCE_FILES} ${HEADER_FILES} ${MOC_HEADERS} ${MOC_OUTFILES})
endif()
