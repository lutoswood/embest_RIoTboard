TARGET = write read
OBJECTS = write.o read.o sem.o
 
CROSS = arm-linux-gnueabihf-
CC = $(CROSS)gcc 
STRIP = $(CROSS)strip
CFLAGS = -I ./ -Wall -std=gnu99 -g -O2
LDFLAGS = 
 
all:write read
write:write.o sem.o
	$(CC) $(CFLAGS) $(LDFLAGS) $^ -o $@
	$(STRIP) $@
read:read.o sem.o 
	$(CC) $(CFLAGS) $(LDFLAGS) $^ -o $@
	$(STRIP) $@

.PHONY:clean
clean:
	-rm -f $(TARGET) *.o
