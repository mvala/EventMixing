# Top level CMakeList.txt file for the AliRsnLite

cmake_minimum_required(VERSION 2.8.4 FATAL_ERROR)

#------------------------------------------------------------------------------#
# Set Basic CMake Configuration                                                #
#------------------------------------------------------------------------------#

project(AliRsnLite CXX C Fortran)

get_filename_component(PROJECT_SOURCE_DIR "${PROJECT_SOURCE_DIR}" REALPATH)
set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake" "${PROJECT_SOURCE_DIR}/cmake/cmake_AliRoot")

if (CMAKE_INSTALL_PREFIX STREQUAL "/usr/local")
  set(CMAKE_INSTALL_PREFIX ${PROJECT_SOURCE_DIR})
endif (CMAKE_INSTALL_PREFIX STREQUAL "/usr/local")

set(ALICE_ROOT $ENV{ALICE_ROOT})
include(AliRsnLite_CMake)
ALIROOT_CMAKE_Sync()

include(ALICE_CMake)

#------------------------------------------------------------------------------#
# Find Packages                                                                #
#------------------------------------------------------------------------------#

find_package(ROOT REQUIRED)

#------------------------------------------------------------------------------#
# Environment/Compiler Configuration                                           #
#------------------------------------------------------------------------------#

ALICE_CheckOutOfSourceBuild()
ALICE_RootConfig(CMAKE_CXX_COMPILER --cxx)
ALICE_RootConfig(CMAKE_C_COMPILER --cc)
ALICE_RootConfig(CMAKE_Fortran_COMPILER --f77)
ALICE_ConfigurePlatform()
ALICE_ConfigureCompiler()
ALICE_RootConfig(CMAKE_ALICE_TARGET --arch)

#------------------------------------------------------------------------------#
# AliRoot Path Settings                                                        #
#------------------------------------------------------------------------------#

ALICE_DevFlagsOutput()
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}/bin/tgt_${CMAKE_ALICE_TARGET}")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}/lib/tgt_${CMAKE_ALICE_TARGET}")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}/lib/tgt_${CMAKE_ALICE_TARGET}")
set(CMAKE_INCLUDE_EXPORT_DIRECTORY "${PROJECT_BINARY_DIR}/include")
file(MAKE_DIRECTORY ${CMAKE_INCLUDE_EXPORT_DIRECTORY})
set(EXPORTDIRS "${ROOTSYS}/include")
set(BINLIBDIRS "-L${CMAKE_LIBRARY_OUTPUT_DIRECTORY}")

set (EXTRA_INCLUDE "${ALICE_ROOT}/include")

#------------------------------------------------------------------------------#
# AliRoot Modules                                                              #
#------------------------------------------------------------------------------#

# AliRsnLite Standard Modules
set(ALIROOTMODULES ANALYSIS)

# Set Final list of modules
set(MODULES ${ALIROOTMODULES})

# Set Module directories
set(MODDIRS ${MODULES})

# Libraries for Linking
set(LIBS ${ROOTCLIBS} ${ROOTPLIBS} ${SYSLIBS})

#------------------------------------------------------------------------------#
# Build Modules                                                                #
#------------------------------------------------------------------------------#

# Module Variables
set(ALLLIBS)
set(ALLEXECS)
set(INCLUDEFILES)
set(BINLIBS)
set(EXPORTFILES)
set(DEPLIB)

add_custom_target(alilibs-static)
add_custom_target(include-headers ALL)
add_custom_target(par-all)
add_custom_target(test-par-all)

# Add Modules
foreach(MODULE ${MODDIRS})
  set(${MODULE}ALIBS)
  configure_file(${PROJECT_SOURCE_DIR}/cmake/cmake_AliRoot/Module.tmp ${PROJECT_SOURCE_DIR}/${MODULE}/CMakeLists.txt @ONLY)
  add_custom_target(${MODULE}-all ALL)
  add_custom_target(${MODULE}-par-all)
  add_custom_target(test-${MODULE}-par-all)
  add_custom_target(${MODULE}-all-static)
  add_dependencies(alilibs-static "${MODULE}-static")
  add_subdirectory(${MODULE})
endforeach(MODULE)
