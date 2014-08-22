WARN= -Wall -Wextra -Werror
#HEAD_PATH=-I/home/alex/.myheaders
#LIB_PATH=/home/alex/.mylibs
.PHONY: clean

DATA_OBJ=png_data.o
IO_OBJ=io/png_reader.o io/png_writer.o
UTIL_OBJ=util/pixel_iterator.o

ALL_OBJ=png_data.o png_reader.o png_writer.o pixel_iterator.o

library: $(ALL_OBJ)
	gcc -shared $(WARN) $(DATA_OBJ) $(IO_OBJ) $(UTIL_OBJ) -o libpnghelper.so -lpng

png_data.o:
	gcc -c -fPIC $(WARN) -o png_data.o png_data.c  

png_reader.o:
	gcc -c -fPIC $(WARN) -o io/png_reader.o io/png_reader.c  

png_writer.o:
	gcc -c -fPIC $(WARN) -o io/png_writer.o io/png_writer.c  

pixel_iterator.o:
	gcc -c -fPIC $(WARN) -o util/pixel_iterator.o util/pixel_iterator.c  

clean:
	rm *.o
	cd io ; rm *.o
	cd util ; rm *.o
