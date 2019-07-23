find_path(GLM_INCLUDE_DIR NAMES glm/glm.hpp glm/common.hpp HINTS /usr/include/glm)

if (GLM_INCLUDE_DIR)
    set(GLM_FOUND TRUE)
endif()

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(GLM DEFAULT_MSG GLM_INCLUDE_DIR)