
CC = gcc-4.6.2

GCCPLUGINS_DIR:= $(shell $(CC) -print-file-name=plugin)
INCLUDE= -I$(GCCPLUGINS_DIR)/include

FLAGS= -fPIC -O2

plugin.so: plugin.c
	$(CC) $(INCLUDE) $(FLAGS) -shared $^ -o $@

test: plugin.so test.c
	$(CC) -fplugin=./plugin.so test.c -fdump-tree-all

clean:
	\rm -f plugin.so test *.c.* *~ *.o a.out


