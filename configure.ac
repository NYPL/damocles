

#############################################################################
###   M4 MACROS                                                           ###

define(AC_EZ_CHECK_PROG, [
    AC_PATH_PROG([$1], [$1], [nope])
    if test "$$1" = nope; then
       AC_MSG_ERROR([$1 (required) is not installed])
    fi
])

define(AC_CHECK_R_PACKAGE, [
    AC_MSG_CHECKING([if $1 version >= $2])
    $("$Rscript" --vanilla -e 'hasPkg <- "$1" %in% rownames(installed.packages()); q(save="no", status=if (hasPkg) packageVersion("$1") >= "$2" else FALSE)')
    if test x"$?" == x"1"; then
        AC_MSG_RESULT([yes])
    else
        AC_MSG_RESULT([no])
        AC_MSG_ERROR([must have $1])
    fi
])

#############################################################################



AC_INIT([damocles],[0.1],[anthonypaulfischetti@nypl.org])

AC_PROG_CC
AC_PROG_CXX
AC_PROG_INSTALL
AC_PROG_LN_S
AC_PROG_RANLIB

# AC_PATH_PROG([R], [R], [nope])
# if test "$R" = nope; then
#    AC_MSG_ERROR([No R installed in this system])
# fi
# AC_PATH_PROG([Rscript], [Rscript], [nope])
# if test "$Rscript" = nope; then
#     AC_MSG_ERROR([Couldn't find Rscript])
# fi

AC_EZ_CHECK_PROG(R)
AC_EZ_CHECK_PROG(Rscript)

AC_CHECK_R_PACKAGE([data.table], [1.14.0])
AC_CHECK_R_PACKAGE([libbib],      [0.6.4])
AC_CHECK_R_PACKAGE([assertr],     [3.0.0])
AC_CHECK_R_PACKAGE([scriptName],  [1.0.0])
AC_CHECK_R_PACKAGE([stringr],     [1.5.0])
AC_CHECK_R_PACKAGE([magrittr],    [2.0.0])
AC_CHECK_R_PACKAGE([pbapply],     [1.7.0])

AC_FUNC_MALLOC
AC_TYPE_SIZE_T
AC_C_CONST
AC_C_INLINE

AC_SUBST(CC)
AC_SUBST(CXX)

# TODO: remove... this is just a test
AC_SUBST(Rscript)

AC_CONFIG_HEADERS([config.h])
AC_CONFIG_FILES([Makefile])

# TODO: remove... this is just a test
AC_CONFIG_FILES([test.sh], [chmod +x test.sh])

AC_OUTPUT
