# generated from ament/cmake/core/templates/nameConfig.cmake.in

# prevent multiple inclusion
if(_av_camera_CONFIG_INCLUDED)
  # ensure to keep the found flag the same
  if(NOT DEFINED av_camera_FOUND)
    # explicitly set it to FALSE, otherwise CMake will set it to TRUE
    set(av_camera_FOUND FALSE)
  elseif(NOT av_camera_FOUND)
    # use separate condition to avoid uninitialized variable warning
    set(av_camera_FOUND FALSE)
  endif()
  return()
endif()
set(_av_camera_CONFIG_INCLUDED TRUE)

# output package information
if(NOT av_camera_FIND_QUIETLY)
  message(STATUS "Found av_camera: 0.0.0 (${av_camera_DIR})")
endif()

# warn when using a deprecated package
if(NOT "" STREQUAL "")
  set(_msg "Package 'av_camera' is deprecated")
  # append custom deprecation text if available
  if(NOT "" STREQUAL "TRUE")
    set(_msg "${_msg} ()")
  endif()
  # optionally quiet the deprecation message
  if(NOT ${av_camera_DEPRECATED_QUIET})
    message(DEPRECATION "${_msg}")
  endif()
endif()

# flag package as ament-based to distinguish it after being find_package()-ed
set(av_camera_FOUND_AMENT_PACKAGE TRUE)

# include all config extra files
set(_extras "")
foreach(_extra ${_extras})
  include("${av_camera_DIR}/${_extra}")
endforeach()
