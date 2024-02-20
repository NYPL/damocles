

### TODO TODO:
##    - Check...
##      - for rsync
##      - IP address??


#############################################################################
###   M4 MACROS                                                           ###

m4_include([./m4/acinclude.m4])

#############################################################################

AC_INIT([damocles],[0.1],[anthonypaulfischetti@nypl.org],
        [damocles], [https://github.com/NYPL/damocles])

AC_PROG_CC
AC_PROG_CXX
AC_PROG_INSTALL
AC_PROG_LN_S
AC_PROG_RANLIB

TF_EZ_CHECK_PROG(R)
TF_EZ_CHECK_PROG(Rscript)

TF_CHECK_R_PACKAGE([data.table], [1.14.0])
TF_CHECK_R_PACKAGE([libbib],      [0.6.4])
TF_CHECK_R_PACKAGE([assertr],     [3.0.0])
TF_CHECK_R_PACKAGE([scriptName],  [1.0.0])
TF_CHECK_R_PACKAGE([stringr],     [1.5.0])
TF_CHECK_R_PACKAGE([magrittr],    [2.0.0])
TF_CHECK_R_PACKAGE([pbapply],     [1.7.0])

AC_FUNC_MALLOC
AC_TYPE_SIZE_T
AC_C_CONST
AC_C_INLINE


## TODO: check for needed headers.... (e.g. fmt, fcntl.h, etc...



AC_SUBST(CC)
AC_SUBST(CXX)

# TODO: remove... this is just a test
AC_SUBST(Rscript)


##### setting options #####

TF_CONFIG_ARG_REQ_DIR(NYPL_RAW_DATA_LOC, [The directory to hold the raw data needed for the pipeline])
AC_SUBST(NYPL_RAW_DATA_LOC)

TF_CONFIG_ARG_OPT_SUBDIR(EZPROXY_LOGS_LOC, [\$\(NYPL_RAW_DATA_LOC\)/ezproxy],
                      [The directory to hold the EZproxy raw data logs])
AC_SUBST(EZPROXY_LOGS_LOC)



AC_CONFIG_HEADERS([config.h])
AC_CONFIG_FILES([Makefile])

# TODO: remove... this is just a test
AC_CONFIG_FILES([test.sh], [chmod +x test.sh])

AC_OUTPUT
