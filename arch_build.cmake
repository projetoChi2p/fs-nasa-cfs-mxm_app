###########################################################
#
# MXM_APP platform build setup
#
# This file is evaluated as part of the "prepare" stage
# and can be used to set up prerequisites for the build,
# such as generating header files
#
###########################################################

# The list of header files that control the MXM_APP configuration
set(MXM_APP_PLATFORM_CONFIG_FILE_LIST
  mxm_app_internal_cfg.h
  mxm_app_platform_cfg.h
  mxm_app_perfids.h
  mxm_app_msgids.h
)

# Create wrappers around the all the config header files
# This makes them individually overridable by the missions, without modifying
# the distribution default copies
foreach(MXM_APP_CFGFILE ${MXM_APP_PLATFORM_CONFIG_FILE_LIST})
  get_filename_component(CFGKEY "${MXM_APP_CFGFILE}" NAME_WE)
  if (DEFINED MXM_APP_CFGFILE_SRC_${CFGKEY})
    set(DEFAULT_SOURCE GENERATED_FILE "${MXM_APP_CFGFILE_SRC_${CFGKEY}}")
  else()
    set(DEFAULT_SOURCE FALLBACK_FILE "${CMAKE_CURRENT_LIST_DIR}/config/default_${MXM_APP_CFGFILE}")
  endif()
  generate_config_includefile(
    FILE_NAME           "${MXM_APP_CFGFILE}"
    ${DEFAULT_SOURCE}
  )
endforeach()
