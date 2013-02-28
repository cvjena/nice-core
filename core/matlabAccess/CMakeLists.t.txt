if(BUILD_CORE_MATLABACCESS)
ocv_add_module(matlabAccess)

ocv_module_include_directories()
ocv_glob_module_sources()
ocv_create_module()
endif()