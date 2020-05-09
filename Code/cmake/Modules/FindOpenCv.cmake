find_path(OpenCv_INCLUDE_DIR opencv2/opencv.hpp)
if(OpenCv_INCLUDE_DIR AND EXISTS "${OpenCv_INCLUDE_DIR}/opencv2/core/version.hpp")
    file(STRINGS "${OpenCv_INCLUDE_DIR}/opencv2/core/version.hpp" OpenCv_Parsed_Major_Version REGEX "^#define CV_MAJOR_VERSION.*[0-9]+.*$")
    file(STRINGS "${OpenCv_INCLUDE_DIR}/opencv2/core/version.hpp" OpenCv_Parsed_Minor_Version REGEX "^#define CV_MINOR_VERSION.*[0-9]+.*$")
    file(STRINGS "${OpenCv_INCLUDE_DIR}/opencv2/core/version.hpp" OpenCv_Parsed_Subminor_Version REGEX "^#define CV_SUBMINOR_VERSION.*[0-9]+.*$")

    string(REGEX REPLACE "^.*CV_MAJOR_VERSION.*([0-9]+).*$" "\\1" OpenCv_VERSION_MAJOR "${OpenCv_Parsed_Major_Version}")
    string(REGEX REPLACE "^.*CV_MINOR_VERSION.*([0-9]+).*$" "\\1" OpenCv_VERSION_MINOR "${OpenCv_Parsed_Minor_Version}")
    string(REGEX REPLACE "^.*CV_SUBMINOR_VERSION.*([0-9]+).*$" "\\1" OpenCv_VERSION_RELEASE "${OpenCv_Parsed_Subminor_Version}")

    if(NOT OpenCv_Parsed_Major_Version)
       # Because newer opencv2/core/version.cpp can do things like
       #   #define CV_VERSION_MAJOR    3
       #   /* old  style version constants*/
       #   #define CV_MAJOR_VERSION    CV_VERSION_MAJOR
       # which won't be correctly parsed above, as CV_MAJOR_VERSION is not an explicit integer value. That will be set later by the preprocessor
       file(STRINGS "${OpenCv_INCLUDE_DIR}/opencv2/core/version.hpp" OpenCv_Parsed_Major_Version REGEX "^#define CV_VERSION_MAJOR.*[0-9]+.*$")
       file(STRINGS "${OpenCv_INCLUDE_DIR}/opencv2/core/version.hpp" OpenCv_Parsed_Minor_Version REGEX "^#define CV_VERSION_MINOR.*[0-9]+.*$")
       file(STRINGS "${OpenCv_INCLUDE_DIR}/opencv2/core/version.hpp" OpenCv_Parsed_Subminor_Version REGEX "^#define CV_VERSION_REVISION.*[0-9]+.*$")
       string(REGEX REPLACE "^.*CV_VERSION_MAJOR.*([0-9]+).*$" "\\1" OpenCv_VERSION_MAJOR "${OpenCv_Parsed_Major_Version}")
       string(REGEX REPLACE "^.*CV_VERSION_MINOR.*([0-9]+).*$" "\\1" OpenCv_VERSION_MINOR "${OpenCv_Parsed_Minor_Version}")
       string(REGEX REPLACE "^.*CV_VERSION_REVISION.*([0-9]+).*$" "\\1" OpenCv_VERSION_RELEASE "${OpenCv_Parsed_Subminor_Version}")
    endif()
    
    set(OpenCv_VERSION_STRING "${OpenCv_VERSION_MAJOR}.${OpenCv_VERSION_MINOR}.${OpenCv_VERSION_RELEASE}")
    set(OpenCv_COMPACT_VERSION_STRING "${OpenCv_VERSION_MAJOR}${OpenCv_VERSION_MINOR}${OpenCv_VERSION_RELEASE}")
    set(OpenCv_MAJOR_VERSION "${OpenCv_VERSION_MAJOR}")
    set(OpenCv_MINOR_VERSION "${OpenCv_VERSION_MINOR}")
    set(OpenCv_PATCH_VERSION "${OpenCv_VERSION_RELEASE}")
endif()

find_library(OpenCv_LIBRARY_RELEASE NAMES opencv_core${OpenCv_COMPACT_VERSION_STRING} opencv_core)
find_library(OpenCv_LIBRARY_DEBUG NAMES opencv_core${OpenCv_COMPACT_VERSION_STRING}d opencv_cored)

include(SelectLibraryConfigurations)
select_library_configurations(OpenCv) #sets OpenCv_LIBRARY using OpenCv_LIBRARY_DEBUG and OpenCv_LIBRARY_RELEASE

list(FIND OpenCv_FIND_COMPONENTS Ml Ml_FOUND_INDEX)
if(NOT Ml_FOUND_INDEX EQUAL -1)
    if (EXISTS "${OpenCv_INCLUDE_DIR}/opencv2/ml/ml.hpp")
        set(OpenCv_FOUND_Ml_HEADER 1)
    endif()
    find_library(OpenCv_Ml_LIBRARY_RELEASE NAMES opencv_ml${OpenCv_COMPACT_VERSION_STRING} opencv_ml)
    find_library(OpenCv_Ml_LIBRARY_DEBUG NAMES opencv_ml${OpenCv_COMPACT_VERSION_STRING}d opencv_mld)
    select_library_configurations(OpenCv_Ml)
endif()

list(FIND OpenCv_FIND_COMPONENTS ImgProc ImgProc_FOUND_INDEX)
if(NOT ImgProc_FOUND_INDEX EQUAL -1)
    if (EXISTS "${OpenCv_INCLUDE_DIR}/opencv2/imgproc/imgproc.hpp")
        set(OpenCv_FOUND_ImgProc_HEADER 1)
    endif()
    find_library(OpenCv_ImgProc_LIBRARY_RELEASE NAMES opencv_imgproc${OpenCv_COMPACT_VERSION_STRING} opencv_imgproc)
    find_library(OpenCv_ImgProc_LIBRARY_DEBUG NAMES opencv_imgproc${OpenCv_COMPACT_VERSION_STRING}d opencv_imgprocd)
    select_library_configurations(OpenCv_ImgProc)
endif()

include(FindPackageHandleStandardArgs)
if(OpenCv_FIND_REQUIRED_Ml)
    set(OpenCv_LIBRARIES ${OpenCv_LIBRARIES} ${OpenCv_Ml_LIBRARIES})
    find_package_handle_standard_args(OpenCv REQUIRED_VARS OpenCv_INCLUDE_DIR OpenCv_FOUND_Ml_HEADER OpenCv_LIBRARY OpenCv_Ml_LIBRARY OpenCv_VERSION_STRING VERSION_VAR OpenCv_VERSION_STRING)
else()
    find_package_handle_standard_args(OpenCv REQUIRED_VARS OpenCv_INCLUDE_DIR OpenCv_LIBRARY OpenCv_VERSION_STRING VERSION_VAR OpenCv_VERSION_STRING)
endif()
if(OpenCv_FIND_REQUIRED_ImgProc)
    set(OpenCv_LIBRARIES ${OpenCv_LIBRARIES} ${OpenCv_ImgProc_LIBRARIES})
    find_package_handle_standard_args(OpenCv REQUIRED_VARS OpenCv_INCLUDE_DIR OpenCv_FOUND_ImgProc_HEADER OpenCv_LIBRARY OpenCv_ImgProc_LIBRARY OpenCv_VERSION_STRING VERSION_VAR OpenCv_VERSION_STRING)
else()
    find_package_handle_standard_args(OpenCv REQUIRED_VARS OpenCv_INCLUDE_DIR OpenCv_LIBRARY OpenCv_VERSION_STRING VERSION_VAR OpenCv_VERSION_STRING)
endif()
set(OpenCv_INCLUDE_DIRS ${OpenCv_INCLUDE_DIR})
mark_as_advanced(OpenCv_INCLUDE_DIR)
set(OpenCv_FOUND ${OPENCV_FOUND})
