# Get a list of all elements in current dir
file(GLOB SUBDIR_LIST LIST_DIRECTORIES true ${CMAKE_CURRENT_LIST_DIR}/* )

foreach(SUBDIR ${SUBDIR_LIST})
  if(IS_DIRECTORY ${SUBDIR}/)
    add_subdirectory(${SUBDIR})
  endif()
endforeach()
