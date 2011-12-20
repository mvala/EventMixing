# AliRsnLite build system utility macro and fixes

cmake_minimum_required(VERSION 2.8.4 FATAL_ERROR)

macro(ALIROOT_CMAKE_Sync)

    # append AliRoot cmake dir
    file(COPY ${ALICE_ROOT}/cmake/ DESTINATION ${CMAKE_SOURCE_DIR}/cmake/cmake_AliRoot/ PATTERN *.cmake)
    file(COPY ${ALICE_ROOT}/cmake/ DESTINATION ${CMAKE_SOURCE_DIR}/cmake/cmake_AliRoot/ PATTERN *.tmp)
    file(REMOVE_RECURSE ${CMAKE_SOURCE_DIR}/cmake/cmake_AliRoot/.svn)

endmacro(ALIROOT_CMAKE_Sync)

macro(ALICE_CheckModule)
  # dummy ALICE_CheckModule
endmacro(ALICE_CheckModule)