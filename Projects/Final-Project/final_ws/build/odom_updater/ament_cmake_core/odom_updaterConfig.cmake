# generated from ament/cmake/core/templates/nameConfig.cmake.in

# prevent multiple inclusion
if(_odom_updater_CONFIG_INCLUDED)
  # ensure to keep the found flag the same
  if(NOT DEFINED odom_updater_FOUND)
    # explicitly set it to FALSE, otherwise CMake will set it to TRUE
    set(odom_updater_FOUND FALSE)
  elseif(NOT odom_updater_FOUND)
    # use separate condition to avoid uninitialized variable warning
    set(odom_updater_FOUND FALSE)
  endif()
  return()
endif()
set(_odom_updater_CONFIG_INCLUDED TRUE)

# output package information
if(NOT odom_updater_FIND_QUIETLY)
  message(STATUS "Found odom_updater: 0.0.0 (${odom_updater_DIR})")
endif()

# warn when using a deprecated package
if(NOT "" STREQUAL "")
  set(_msg "Package 'odom_updater' is deprecated")
  # append custom deprecation text if available
  if(NOT "" STREQUAL "TRUE")
    set(_msg "${_msg} ()")
  endif()
  # optionally quiet the deprecation message
  if(NOT ${odom_updater_DEPRECATED_QUIET})
    message(DEPRECATION "${_msg}")
  endif()
endif()

# flag package as ament-based to distinguish it after being find_package()-ed
set(odom_updater_FOUND_AMENT_PACKAGE TRUE)

# include all config extra files
set(_extras "")
foreach(_extra ${_extras})
  include("${odom_updater_DIR}/${_extra}")
endforeach()
