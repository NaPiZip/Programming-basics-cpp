# Get a list of all elements in current dir
file(GLOB SUBDIR_LIST LIST_DIRECTORIES true ${CMAKE_CURRENT_LIST_DIR}/* )

foreach(SUBDIR ${SUBDIR_LIST})
  if(NOT (${SUBDIR} STREQUAL  ${CMAKE_CURRENT_LIST_DIR}/thirdparty) AND (IS_DIRECTORY ${SUBDIR}/))
      add_subdirectory(${SUBDIR})
  endif()
endforeach()
