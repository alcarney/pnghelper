WARN= -Wall -Wextra -Werror
#HEAD_PATH=-I/home/alex/.myheaders
#LIB_PATH=/home/alex/.mylibs
.PHONY: clean

DATA_OBJ=png_data.o
IO_OBJ=io/png_reader.o io/png_writer.o
UTIL_OBJ=util/pixel_iterator.o

library: $(DATA_OBJ) $(IO_OBJ) $(UTIL_OBJ)
	gcc -fPIC $(WARN) $(DATA_OBJ) $(IO_OBJ) $(UTIL_OBJ) -o libpnghelper.so -lpng

png_data.o:
	gcc -c -fPIC $(WARN) png_data.c -o png_data.o -lpng

png_reader.o:
	gcc -c -fPIC $(WARN) io/png_reader.c -o io/png_reader.o -lpng

png_writer.o:
	gcc -c -fPIC $(WARN) io/png_writer.c -o io/png_writer.o -lpng

pixel_iterator.o:
	gcc -c -fPIC $(WARN) util/pixel_iterator.c -o util/pixel_iterator.o -lpng

clean:
	rm *.o
