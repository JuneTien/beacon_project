TARGET=test.cgi

CFLAGS= -Wall -I./cgi -I./include

SRCS=$(foreach DIR, $(DIRS), $(wildcard $(DIR)/*.c))
OBJS=$(patsubst %.c, %.o, $(SRCS))
OBJS+=cgi_main.o

all: cgi_lib ${OBJS}
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS) cgi/cgi-lib.a

cgi_lib: 
	make -C cgi

install:
	cp -a ./test.cgi ../


clean: 
	make -C cgi clean
	rm -rf ${TARGET} $(OBJS) *.bak
	rm -rf ../test.cgi

%.o: %.c
	$(CC) $(CFLAGS) -o $@ -c $<

