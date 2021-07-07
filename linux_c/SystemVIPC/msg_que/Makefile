TARGET = send recv
OBJECTS = send.o recv.o
 
CROSS = arm-linux-gnueabihf-
CC = $(CROSS)gcc 
STRIP = $(CROSS)strip
CFLAGS = -Wall -std=gnu99 -g -O2
LDFLAGS = 
 
all:$(TARGET)
$(TARGET):%:%.c
	$(CC) $(CFLAGS) $(LDFLAGS) $< -o $@
	$(STRIP) $@

.PHONY:clean
clean:
	-rm -f $(TARGET) *.o

# 以下也可用
# CC= arm-linux-gnueabihf-gcc
# CFLAGE= -Wall -O2 -g
# ALL= readfifo writefifo
# all:$(ALL)

# %.o:%.c
# 	$(CC) $(CFLAGE) -c $< -o $@
# .PHONY:clean
# clean:
# 	rm -rf $(ALL) *.o
