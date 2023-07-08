target = ./app
source = $(wildcard  *.c)
LIBS = -lpthread -lssl -lcrypto  -I./ -g -o
obj = $(patsubst %.c,%.o,$(source))
$(target):$(obj)
	cc $(obj) $(LIBS)  $(target)
.PHONY:clean
clean:
	-rm $(target) $(obj)

