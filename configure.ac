
AC_INIT([damocles], [0.1], [anthonypaulfischetti@nypl.org])
AM_INIT_AUTOMAKE([])

AC_CHECK_PROGS(CC, [gcc clang], [""])
AC_PROG_CC
AC_SUBST(CC)

AM_CONDITIONAL([HAS_DLOG_SO_P], [test -f bin/dlog-make.so && test -f bin/dlog-r.so])

AC_CONFIG_FILES([Makefile])
AC_OUTPUT
