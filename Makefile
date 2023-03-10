# C/C++ compilation involves two stages:
# - compiling: convert each source (*.cpp) file indepdendently into binary object (.o) files
# - linking: assemble all the object files into a single executable
#
# Since any C++ project contains multiple source files, the above
# process involved firing multiple commands. Makefiles help us
# write all the compilation stages in a single file and run them
# as one big script.
#
# See http://www.cs.colby.edu/maxwell/courses/tutorials/maketutor/
# and many many other tutorials for makefiles


# some variables
BUILD_DIR  :=_build
EXECUTABLE := a9
OUTPUT := Output

# list of headers
HEADERS = $(wildcard *.h)

# the C++ compiler/linker to be used. define here so that we can change
# it easily if needed
CXX := g++ -Wall -g3 -ggdb -std=c++11 -I. -O3

# ------------------------------------------------------------------------------

# 'make' or 'make all' runs the default target 'all' which requires that
# the EXECUTABLE must be available; if the EXECUTABLE is already available
# then nothing happens. see the rules for EXECUTABLE

all: $(EXECUTABLE)

# ------------------------------------------------------------------------------

# 'make run' runs the target 'run' which calls for running the executable
# if the executable is not available, then the rules for creating it are run
# this is a superset of the target 'all' because it creates the executable
# and also runs it

run: $(EXECUTABLE)
	./$(EXECUTABLE)

# ------------------------------------------------------------------------------

# 'make clean' runs the target 'clean' which in turn removes the
# intermediate .o files and the executable

clean:
	rm -rf $(BUILD_DIR) $(EXECUTABLE) $(OUTPUT)

# ------------------------------------------------------------------------------

# once you're ready to submit, run 'make prepare' to prepare a zip file to
# submit to the submission system

prepare:
	mkdir -p asst
	cp *.cpp asst
	cp *.h asst
	cp Makefile asst
	zip -r a$(NUMBER)_submission.zip asst
	rm -rf asst
.PHONY: prepare

# ------------------------------------------------------------------------------

# rule for creating the executable: this "links" the .o files using the g++ linker.
# If .o files are not available, then the rules for creating .o files are run.

$(EXECUTABLE): $(BUILD_DIR)/a9_main.o $(BUILD_DIR)/Image.o $(BUILD_DIR)/lodepng.o $(BUILD_DIR)/a9.o 
	$(CXX) $(BUILD_DIR)/a9_main.o $(BUILD_DIR)/a9.o $(BUILD_DIR)/Image.o $(BUILD_DIR)/lodepng.o -o $(EXECUTABLE)
	mkdir -p $(OUTPUT)

# ------------------------------------------------------------------------------

# rules for creating the .o files:  compile each of the .cpp files and create a
# corresponding .o file. Each .o depends upon the corresponding .cpp and other .h files

$(BUILD_DIR)/%.o: %.cpp $(HEADERS)
	mkdir -p $(BUILD_DIR)
	$(CXX) -c $< -o $@
	

