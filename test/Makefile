WARN= -Wall -Wextra -Werror
.PHONY: clean

test: png_data.o png_reader.o png_writer.o
	gcc $(WARN) ../src/png_data.o ../src/png_reader.o ../src/png_writer.o test.c -o test -lpng

png_data.o: 
	gcc -c $(WARN) ../src/png_data.c -o ../src/png_data.o

png_writer.o:
	gcc -c $(WARN) ../src/png_writer.c -o ../src/png_writer.o

png_reader.o: 
	gcc -c $(WARN) ../src/png_reader.c -o ../src/png_reader.o

clean:
	cd ../src ; rm *,o
