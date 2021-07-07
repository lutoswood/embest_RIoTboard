TARGET = detach
OBJECTS = detach.o
 
CROSS = arm-linux-gnueabihf-
CC = $(CROSS)gcc 
STRIP = $(CROSS)strip
CFLAGS = -Wall -std=gnu99 -g -O2
LDFLAGS = 
 
all:$(TARGET)
$(TARGET):$(OBJECTS)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $(OBJECTS) -lpthread
	$(STRIP) $@
	

.PHONY:clean
clean:
	-rm -f $(TARGET) *.o
