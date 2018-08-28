PROG = checksyn
OBJ = main.o io.o escape.o util.o comment.o literal.o text.o
$(PROG): $(OBJ)
	cc $(LDFLAGS) -o $@ $> $(LIBS)
escape.o: escape.c escape.h io.h util.h main.h
io.o: io.c main.h io.h
util.o: util.c util.h
comment.o: comment.c comment.h io.h util.h main.h
literal.o: literal.c literal.h escape.h io.h util.h main.h
text.o: text.c text.h comment.h io.h literal.h main.h util.h
.PHONY: clean
clean:
	-rm -f $(PROG) $(OBJ)
