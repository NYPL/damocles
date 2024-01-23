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
