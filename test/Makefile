WARN= -Wall -Wextra -Werror
HEADERS= -I ~/.myheaders
LIBS= -L ~/.mylibs
.PHONY: clean

# Object files sorted by dir
DATA_OBJ= ../src/png_data.o
IO_OBJ=../src/io/png_reader.o ../src/io/png_writer.o
UTIL_OBJ=../src/util/pixel_iterator.o

test: $(DATA_OBJ) $(IO_OBJ)
	gcc $(WARN) ../src/png_data.o ../src/png_reader.o ../src/png_writer.o test.c -o test -lpng

test_pixel_iterator: $(DATA_OBJ) $(IO_OBJ) $(UTIL_OBJ)
	gcc $(WARN) $(DATA_OBJ) $(IO_OBJ) $(UTIL_OBJ) test_pixel_iterator.c -o test_pixel_iterator -lpng

test_lib: 
	gcc $(WARN) $(HEADERS) $(LIBS) test_lib.c -o test_lib -lpng -lpnghelper

test_params:
	gcc $(WARN) $(HEADERS) $(LIBS) test_params.c -o test_params -lpng -lpnghelper 

png_data.o: 
	gcc -c $(WARN) ../src/png_data.c -o ../src/png_data.o

png_writer.o:
	gcc -c $(WARN) ../src/io/png_writer.c -o ../src/io/png_writer.o

png_reader.o: 
	gcc -c $(WARN) ../src/io/png_reader.c -o ../src/io/png_reader.o

pixel_iterator.o: $(DATA_OBJ)
	gcc -c $(WARN) $(DATA_OBJ) ../src/util/pixel_iterator.c -o ../src/util/pixel_iterator.o

clean:
	cd ../src ; rm *.o
	cd ../src/io ; rm *.o
	cd ../src/util ; rm *.o
