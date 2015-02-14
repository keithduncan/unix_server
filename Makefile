PRODUCT=unix_server

.PHONY: all clean

all:
	mkdir -p build
	cc main.c $(CFLAGS) -o build/$(PRODUCT)

check:
	exec build/$(PRODUCT)

clean:
	rm -r build
