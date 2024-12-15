bin_PROGRAMS = disasm

disasm_SOURCES = disasm.h disasm.c disasm-i386.c junk.c main.c

dist-hook:
	mkdir $(distdir)/digraphs
	cp -p $(srcdir)/spec/istats  $(distdir)/digraphs/istats
