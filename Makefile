
CFLAGS=-O2

all : raidzz_mktable raidzz_table.o raidzz_impl.o raidzz_test

clean :
		rm -f *.o raidzz_table.c raidzz_mktable raidzz_test *.BAK

raidzz_test : raidzz_test.c raidzz_table.o raidzz_impl.o
		$(CC) $(CFLAGS) -o raidzz_test raidzz_test.c raidzz_table.o raidzz_impl.o

raidzz_impl.o : raidzz_if.h

raidzz_mktable : raidzz_mktable.c

raidzz_table.c : raidzz_mktable
		./raidzz_mktable > raidzz_table.c

.PHONY : test
test: raidzz_table.o
		cc raidzz_mktable.c -DTEST=1 -o Traidzz_mktable raidzz_table.o
		./Traidzz_mktable > jnk
		cmp jnk raidzz_table.c

