CFLAGS=-Wall -std=c99 -Wall -pedantic

DEBUG ?=1
ifeq ($(DEBUG), 1)
	CFLAGS += -g -D DEBUG
else
	CFLAGS += -U DEBUG
endif

all:
	mkdir -p ./bin
	make koenig_dewitz-main
	mv ./koenig_dewitz-main ./bin/main

clean:
	rm -f ./bin/main
