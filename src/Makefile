# Compiler and flags
CC := g++
CFLAGS := -Wall -std=c++17

# Source files
SRCS := findByName.cpp ThreadPool.cpp

# Object files
OBJS := $(SRCS:.cpp=.o)

# Static library
LIBNAME := search.a

# Default target
all: $(LIBNAME) 

# Compile source files into object files
%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

# Create static library
$(LIBNAME): $(OBJS)
	$(AR) rcs $(LIBNAME) $(OBJS)

# Link main executable
main: main.o $(LIBNAME)
	$(CC) $(CFLAGS) $< -o $@ -L$(CURDIR) -l:$(LIBNAME) -I$(CURDIR)

# Clean target
clean:
	rm -f $(OBJS) $(LIBNAME) main
