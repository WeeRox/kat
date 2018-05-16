AUTOMAKE_OPTIONS = foreign

CMDS =
CMDS += src/cmd/help.c

bin_PROGRAMS = kat
kat_SOURCES = src/kat.c src/cmd.c $(CMDS)
kat_CPPFLAGS = -I$(top_srcdir)/src
