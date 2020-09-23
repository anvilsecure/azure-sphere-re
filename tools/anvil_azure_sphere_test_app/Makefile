.DEFAULT_GOAL := all

CC=arm-linux-musleabihf-gcc
CFLAGS=-I./azureroot/include/ -g -march=armv7ve -mthumb -mfpu=neon -mfloat-abi=hard -mcpu=cortex-a7 -std=c11 -Wno-pointer-sign -ggdb -O0 -fPIC -ffunction-sections -fdata-sections -fno-strict-aliasing -fno-omit-frame-pointer -fno-exceptions -fstack-protector-strong

LIBS=-L./azureroot/lib -lapplibs

OBJS=main.o shell.o string_util.o

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $< 

main: $(OBJS)
	$(CC) -o main $(OBJS) $(LIBS)

main.imagepackage: main app_manifest.json
	cp main ./approot/bin/app
	cp app_manifest.json ./approot/app_manifest.json
	azsphere -v image-package pack-application -i ./approot -x ./bin/busybox -o main.imagepackage -s 5 -h sample_hardware.json

deploy: main.imagepackage
	azsphere device sideload deploy --imagepackage main.imagepackage

all: main.imagepackage

clean:
	rm -f ./*.o ./main ./main.imagepackage

.PHONY: all clean