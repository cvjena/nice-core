$(call PKG_DEPEND_INT,core/basics)
$(call PKG_DEPEND_INT,core/vector)
# we need the optimization library for our linear solvers
$(call PKG_DEPEND_INT,core/optimization)
# this is just an optional package
$(call PKG_DEPEND_INT,cholesky-gpu/niceinterface)
# this is an additional external optional package
$(call PKG_DEPEND_EXT,TRLAN)
