define(TF_EZ_CHECK_PROG, [
    AC_PATH_PROG([$1], [$1], [nope])
    if test "$$1" = nope; then
       AC_MSG_ERROR([$1 (required) is not installed])
    fi
])

define(TF_CHECK_R_PACKAGE, [
    AC_MSG_CHECKING([if $1 version >= $2])
    $("$Rscript" --vanilla -e 'hasPkg <- "$1" %in% rownames(installed.packages()); q(save="no", status=if (hasPkg) packageVersion("$1") >= "$2" else FALSE)')
    if test x"$?" = x"1"; then
        AC_MSG_RESULT([yes])
    else
        AC_MSG_RESULT([no])
        AC_MSG_ERROR([must have $1])
    fi
])

# TODO: check if sane
define(TF_CONFIG_ARG_REQ_DIR, [
    AC_ARG_VAR($1, $2)
    if test x"$$1" = x; then
        AC_MSG_ERROR([Required environment variable 'NYPL_RAW_DATA_LOC' not specified])
    fi
])

# TODO: check if sane
define(TF_CONFIG_ARG_OPT_SUBDIR, [
    AC_ARG_VAR($1, $3)
    if test x"$$1" = x; then
        AC_MSG_RESULT([$1 not specified... using default])
        EZPROXY_LOGS_LOC=$2
    fi
])
