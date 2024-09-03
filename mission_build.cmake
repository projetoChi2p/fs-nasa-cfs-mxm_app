###########################################################
#
# MXM_APP mission build setup
#
# This file is evaluated as part of the "prepare" stage
# and can be used to set up prerequisites for the build,
# such as generating header files
#
###########################################################

# The list of header files that control the MXM_APP configuration
set(MXM_APP_MISSION_CONFIG_FILE_LIST
  mxm_app_fcncodes.h
  mxm_app_interface_cfg.h
  mxm_app_mission_cfg.h
  mxm_app_perfids.h
  mxm_app_msg.h
  mxm_app_msgdefs.h
  mxm_app_msgstruct.h
  mxm_app_tbl.h
  mxm_app_tbldefs.h
  mxm_app_tblstruct.h
  mxm_app_topicids.h
)

if (CFE_EDS_ENABLED_BUILD)

  # In an EDS-based build, these files come generated from the EDS tool
  set(MXM_APP_CFGFILE_SRC_MXM_APP_interface_cfg "mxm_app_eds_designparameters.h")
  set(MXM_APP_CFGFILE_SRC_MXM_APP_tbldefs       "mxm_app_eds_typedefs.h")
  set(MXM_APP_CFGFILE_SRC_MXM_APP_tblstruct     "mxm_app_eds_typedefs.h")
  set(MXM_APP_CFGFILE_SRC_MXM_APP_msgdefs       "mxm_app_eds_typedefs.h")
  set(MXM_APP_CFGFILE_SRC_MXM_APP_msgstruct     "mxm_app_eds_typedefs.h")
  set(MXM_APP_CFGFILE_SRC_MXM_APP_fcncodes      "mxm_app_eds_cc.h")

endif(CFE_EDS_ENABLED_BUILD)

# Create wrappers around the all the config header files
# This makes them individually overridable by the missions, without modifying
# the distribution default copies
foreach(MXM_APP_CFGFILE ${MXM_APP_MISSION_CONFIG_FILE_LIST})
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
