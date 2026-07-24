CC=gcc
CROSS_CC=aarch64-none-linux-gnu-gcc

writer: writer.c
	$(CC) -o writer writer.c
CROSS_COMPILE: writer.c
	$(CROSS_CC) -o writer writer.c
.PHONY : clean
clean:
	rm writer
