
CC = ~/eclipse-workspace/gcc-install/bin/g++

GCCPLUGINS_DIR:= /home/xinyu/eclipse-workspace/gcc-install/lib/gcc/x86_64-pc-linux-gnu/13.0.0/plugin
#$(shell $(CC) -print-file-name=plugin)
INCLUDE= -I$(GCCPLUGINS_DIR)/include

FLAGS= -fPIC -O2

plugin.so: plugin.c
	$(CC) $(INCLUDE) $(FLAGS) -shared -fno-rtti $^ -o $@

test: plugin.so test.c
	$(CC) -fplugin=./plugin.so test.c -fdump-tree-all

clean:
	\rm -f plugin.so test *.c.* *~ *.o a.out


