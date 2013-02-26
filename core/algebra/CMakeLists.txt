if(BUILD_CORE_ALGEBRA)
ocv_add_module(algebra INTERNAL nice_core_basics)


ocv_clear_vars(ADDITIONAL_CORE_ALGEBRA_LIBS)
if(IPP_FOUND) #NICE_USELIB_IPP
endif()

ocv_module_include_directories()
ocv_glob_module_sources()
ocv_create_module()
endif()