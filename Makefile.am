AUTOMAKE_OPTIONS = foreign

CMDS =
CMDS += src/cmd/help.c
CMDS += src/cmd/login.c

bin_PROGRAMS = kat
kat_SOURCES = src/kat.c src/cmd.c src/auth.c src/prompt.c $(CMDS)
kat_CPPFLAGS = -I$(top_srcdir)/src
kat_LDADD = -lconfigr
