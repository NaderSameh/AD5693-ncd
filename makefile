# Specify the target file and the object files that need to be created
# In this case, the target file is main and the object files are main.o, foo.o, and bar.o
# main depends on main.o, foo.o, and bar.o, so if any of these files are modified, main will be recompiled
main: main.o AD5693.o I2C_wrapper.o
	gcc -o main main.o AD5693.o I2C_wrapper.o

# Compile main.c into main.o
main.o: src/main.c header/AD5693.h header/I2C_wrapper.h
	gcc -I header -c src/main.c

# Compile foo.c into foo.o
AD5693.o: src/AD5693.c header/AD5693.h
	gcc -I header -c src/AD5693.c

# Compile bar.c into bar.o
I2C_wrapper.o: src/I2C_wrapper.c header/I2C_wrapper.h
	gcc -I header -c src/I2C_wrapper.c

# Clean up the object files and the target file
clean:
	rm -f *.o main

# Specify any compiler flags and libraries
#CFLAGS = -std=c99 -O2 
#LDFLAGS = -lm


# Use the built-in rules to build the target executable
#$(TARGET): $(SOURCES)
#	$(CC) $(CFLAGS) $(SOURCES) $(LDFLAGS) -o $(TARGET)

