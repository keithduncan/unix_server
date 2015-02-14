PRODUCT=unix_server

.PHONY: all clean

all:
	cc main.c -o $(PRODUCT)

clean:
	rm $(PRODUCT)
