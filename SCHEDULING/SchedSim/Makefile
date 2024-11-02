# Define source files and executable
TASK1_SRC := schedsim.c util.c
EXE := schedsim

# Default target to build the executable
all: $(EXE)

# Rule to build the executable from source files
$(EXE): $(TASK1_SRC)
	gcc -Wall -std=c99 -Werror -pedantic -g $^ -o $@

# Clean up by removing the executable
clean:
	rm -f $(EXE)