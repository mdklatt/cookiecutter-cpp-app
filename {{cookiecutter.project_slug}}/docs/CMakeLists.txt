find_package(Doxygen)
if(DOXYGEN_FOUND)
    set(DOXYGEN_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/doxygen")
    set(DOXYGEN_BUILD_DIR "${DOXYGEN_SOURCE_DIR}")
    message(STATUS "Building Doxygen documentation in ${DOXYGEN_BUILD_DIR}")
    configure_file("${DOXYGEN_SOURCE_DIR}/Doxyfile.in" "${DOXYGEN_BUILD_DIR}/Doxyfile" @ONLY)
    add_custom_target(docs
        COMMAND ${DOXYGEN_EXECUTABLE} Doxyfile
        WORKING_DIRECTORY ${DOXYGEN_BUILD_DIR}
        VERBATIM
    )
endif()
