# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.29

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Disable VCS-based implicit rules.
% : %,v

# Disable VCS-based implicit rules.
% : RCS/%

# Disable VCS-based implicit rules.
% : RCS/%,v

# Disable VCS-based implicit rules.
% : SCCS/s.%

# Disable VCS-based implicit rules.
% : s.%

.SUFFIXES: .hpux_make_needs_suffix_list

# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /Applications/CMake.app/Contents/bin/cmake

# The command to remove a file.
RM = /Applications/CMake.app/Contents/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/lukas/Documents/vscode/projects/go_arcade/datas_tructure_test

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/lukas/Documents/vscode/projects/go_arcade/datas_tructure_test/build

# Include any dependencies generated for this target.
include CMakeFiles/a.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/a.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/a.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/a.dir/flags.make

CMakeFiles/a.dir/main.cpp.o: CMakeFiles/a.dir/flags.make
CMakeFiles/a.dir/main.cpp.o: /Users/lukas/Documents/vscode/projects/go_arcade/datas_tructure_test/main.cpp
CMakeFiles/a.dir/main.cpp.o: CMakeFiles/a.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/lukas/Documents/vscode/projects/go_arcade/datas_tructure_test/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/a.dir/main.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/a.dir/main.cpp.o -MF CMakeFiles/a.dir/main.cpp.o.d -o CMakeFiles/a.dir/main.cpp.o -c /Users/lukas/Documents/vscode/projects/go_arcade/datas_tructure_test/main.cpp

CMakeFiles/a.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/a.dir/main.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/lukas/Documents/vscode/projects/go_arcade/datas_tructure_test/main.cpp > CMakeFiles/a.dir/main.cpp.i

CMakeFiles/a.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/a.dir/main.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/lukas/Documents/vscode/projects/go_arcade/datas_tructure_test/main.cpp -o CMakeFiles/a.dir/main.cpp.s

CMakeFiles/a.dir/Board.cpp.o: CMakeFiles/a.dir/flags.make
CMakeFiles/a.dir/Board.cpp.o: /Users/lukas/Documents/vscode/projects/go_arcade/datas_tructure_test/Board.cpp
CMakeFiles/a.dir/Board.cpp.o: CMakeFiles/a.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/lukas/Documents/vscode/projects/go_arcade/datas_tructure_test/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/a.dir/Board.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/a.dir/Board.cpp.o -MF CMakeFiles/a.dir/Board.cpp.o.d -o CMakeFiles/a.dir/Board.cpp.o -c /Users/lukas/Documents/vscode/projects/go_arcade/datas_tructure_test/Board.cpp

CMakeFiles/a.dir/Board.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/a.dir/Board.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/lukas/Documents/vscode/projects/go_arcade/datas_tructure_test/Board.cpp > CMakeFiles/a.dir/Board.cpp.i

CMakeFiles/a.dir/Board.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/a.dir/Board.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/lukas/Documents/vscode/projects/go_arcade/datas_tructure_test/Board.cpp -o CMakeFiles/a.dir/Board.cpp.s

CMakeFiles/a.dir/Node.cpp.o: CMakeFiles/a.dir/flags.make
CMakeFiles/a.dir/Node.cpp.o: /Users/lukas/Documents/vscode/projects/go_arcade/datas_tructure_test/Node.cpp
CMakeFiles/a.dir/Node.cpp.o: CMakeFiles/a.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/lukas/Documents/vscode/projects/go_arcade/datas_tructure_test/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/a.dir/Node.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/a.dir/Node.cpp.o -MF CMakeFiles/a.dir/Node.cpp.o.d -o CMakeFiles/a.dir/Node.cpp.o -c /Users/lukas/Documents/vscode/projects/go_arcade/datas_tructure_test/Node.cpp

CMakeFiles/a.dir/Node.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/a.dir/Node.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/lukas/Documents/vscode/projects/go_arcade/datas_tructure_test/Node.cpp > CMakeFiles/a.dir/Node.cpp.i

CMakeFiles/a.dir/Node.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/a.dir/Node.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/lukas/Documents/vscode/projects/go_arcade/datas_tructure_test/Node.cpp -o CMakeFiles/a.dir/Node.cpp.s

# Object files for target a
a_OBJECTS = \
"CMakeFiles/a.dir/main.cpp.o" \
"CMakeFiles/a.dir/Board.cpp.o" \
"CMakeFiles/a.dir/Node.cpp.o"

# External object files for target a
a_EXTERNAL_OBJECTS =

a : CMakeFiles/a.dir/main.cpp.o
a : CMakeFiles/a.dir/Board.cpp.o
a : CMakeFiles/a.dir/Node.cpp.o
a : CMakeFiles/a.dir/build.make
a : /Library/Frameworks/SDL2.framework/Versions/A/SDL2
a : CMakeFiles/a.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/Users/lukas/Documents/vscode/projects/go_arcade/datas_tructure_test/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Linking CXX executable a"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/a.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/a.dir/build: a
.PHONY : CMakeFiles/a.dir/build

CMakeFiles/a.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/a.dir/cmake_clean.cmake
.PHONY : CMakeFiles/a.dir/clean

CMakeFiles/a.dir/depend:
	cd /Users/lukas/Documents/vscode/projects/go_arcade/datas_tructure_test/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/lukas/Documents/vscode/projects/go_arcade/datas_tructure_test /Users/lukas/Documents/vscode/projects/go_arcade/datas_tructure_test /Users/lukas/Documents/vscode/projects/go_arcade/datas_tructure_test/build /Users/lukas/Documents/vscode/projects/go_arcade/datas_tructure_test/build /Users/lukas/Documents/vscode/projects/go_arcade/datas_tructure_test/build/CMakeFiles/a.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/a.dir/depend

