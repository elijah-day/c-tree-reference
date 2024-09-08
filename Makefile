CC = gcc
CFLAGS = -Wall -Werror -Wextra
LIBS =

src_files = \
	src/main.c

obj_files = $(src_files:.c=.o)

target = c-json-gen
target_dir = build

all: build run

build: $(obj_files)
	mkdir -p $(target_dir)
	$(CC) $(obj_files) -o $(target_dir)/$(target) $(CFLAGS) $(LIBS)

run: build
	cd $(target_dir); ./$(target); cd ../../

clean:
	rm $(obj_files)
