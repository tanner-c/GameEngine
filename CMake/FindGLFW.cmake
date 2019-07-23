find_path(GLFW_INCLUDE_DIR NAMES GLFW/glfw3.h GLFW/glfw3native.h HINTS /usr/include/GLFW)
find_library(GLFW_LIBRARY NAMES glfw glfw3 HINTS /usr/lib)

if (GLFW_INCLUDE_DIR AND GLFW_LIBRARY)
    set(GLFW_FOUND TRUE)
    add_library(GLFW::GLFW UNKNOWN IMPORTED)
    set_target_properties(GLFW::GLFW PROPERTIES IMPORTED_LOCATION ${GLFW_LIBRARY})
    set_target_properties(GLFW::GLFW PROPERTIES INTERFACE_INCLUDE_DIRECTORIES ${GLFW_INCLUDE_DIR})
endif()

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(GLFW DEFAULT_MSG GLFW_LIBRARY GLFW_INCLUDE_DIR)