# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.6

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = "/Users/skull/Library/Application Support/JetBrains/Toolbox/apps/CLion/ch-0/163.10154.43/CLion.app/Contents/bin/cmake/bin/cmake"

# The command to remove a file.
RM = "/Users/skull/Library/Application Support/JetBrains/Toolbox/apps/CLion/ch-0/163.10154.43/CLion.app/Contents/bin/cmake/bin/cmake" -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/skull/Programming/Interview/epicode-master

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/skull/Programming/Interview/epicode-master/cmake-build-debug

# Include any dependencies generated for this target.
include cpp/CMakeFiles/binary_tree_postorder_traversal_iterative_alternative.dir/depend.make

# Include the progress variables for this target.
include cpp/CMakeFiles/binary_tree_postorder_traversal_iterative_alternative.dir/progress.make

# Include the compile flags for this target's objects.
include cpp/CMakeFiles/binary_tree_postorder_traversal_iterative_alternative.dir/flags.make

cpp/CMakeFiles/binary_tree_postorder_traversal_iterative_alternative.dir/binary_tree_postorder_traversal_iterative_alternative.cpp.o: cpp/CMakeFiles/binary_tree_postorder_traversal_iterative_alternative.dir/flags.make
cpp/CMakeFiles/binary_tree_postorder_traversal_iterative_alternative.dir/binary_tree_postorder_traversal_iterative_alternative.cpp.o: ../cpp/binary_tree_postorder_traversal_iterative_alternative.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/skull/Programming/Interview/epicode-master/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object cpp/CMakeFiles/binary_tree_postorder_traversal_iterative_alternative.dir/binary_tree_postorder_traversal_iterative_alternative.cpp.o"
	cd /Users/skull/Programming/Interview/epicode-master/cmake-build-debug/cpp && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/binary_tree_postorder_traversal_iterative_alternative.dir/binary_tree_postorder_traversal_iterative_alternative.cpp.o -c /Users/skull/Programming/Interview/epicode-master/cpp/binary_tree_postorder_traversal_iterative_alternative.cpp

cpp/CMakeFiles/binary_tree_postorder_traversal_iterative_alternative.dir/binary_tree_postorder_traversal_iterative_alternative.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/binary_tree_postorder_traversal_iterative_alternative.dir/binary_tree_postorder_traversal_iterative_alternative.cpp.i"
	cd /Users/skull/Programming/Interview/epicode-master/cmake-build-debug/cpp && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/skull/Programming/Interview/epicode-master/cpp/binary_tree_postorder_traversal_iterative_alternative.cpp > CMakeFiles/binary_tree_postorder_traversal_iterative_alternative.dir/binary_tree_postorder_traversal_iterative_alternative.cpp.i

cpp/CMakeFiles/binary_tree_postorder_traversal_iterative_alternative.dir/binary_tree_postorder_traversal_iterative_alternative.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/binary_tree_postorder_traversal_iterative_alternative.dir/binary_tree_postorder_traversal_iterative_alternative.cpp.s"
	cd /Users/skull/Programming/Interview/epicode-master/cmake-build-debug/cpp && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/skull/Programming/Interview/epicode-master/cpp/binary_tree_postorder_traversal_iterative_alternative.cpp -o CMakeFiles/binary_tree_postorder_traversal_iterative_alternative.dir/binary_tree_postorder_traversal_iterative_alternative.cpp.s

cpp/CMakeFiles/binary_tree_postorder_traversal_iterative_alternative.dir/binary_tree_postorder_traversal_iterative_alternative.cpp.o.requires:

.PHONY : cpp/CMakeFiles/binary_tree_postorder_traversal_iterative_alternative.dir/binary_tree_postorder_traversal_iterative_alternative.cpp.o.requires

cpp/CMakeFiles/binary_tree_postorder_traversal_iterative_alternative.dir/binary_tree_postorder_traversal_iterative_alternative.cpp.o.provides: cpp/CMakeFiles/binary_tree_postorder_traversal_iterative_alternative.dir/binary_tree_postorder_traversal_iterative_alternative.cpp.o.requires
	$(MAKE) -f cpp/CMakeFiles/binary_tree_postorder_traversal_iterative_alternative.dir/build.make cpp/CMakeFiles/binary_tree_postorder_traversal_iterative_alternative.dir/binary_tree_postorder_traversal_iterative_alternative.cpp.o.provides.build
.PHONY : cpp/CMakeFiles/binary_tree_postorder_traversal_iterative_alternative.dir/binary_tree_postorder_traversal_iterative_alternative.cpp.o.provides

cpp/CMakeFiles/binary_tree_postorder_traversal_iterative_alternative.dir/binary_tree_postorder_traversal_iterative_alternative.cpp.o.provides.build: cpp/CMakeFiles/binary_tree_postorder_traversal_iterative_alternative.dir/binary_tree_postorder_traversal_iterative_alternative.cpp.o


# Object files for target binary_tree_postorder_traversal_iterative_alternative
binary_tree_postorder_traversal_iterative_alternative_OBJECTS = \
"CMakeFiles/binary_tree_postorder_traversal_iterative_alternative.dir/binary_tree_postorder_traversal_iterative_alternative.cpp.o"

# External object files for target binary_tree_postorder_traversal_iterative_alternative
binary_tree_postorder_traversal_iterative_alternative_EXTERNAL_OBJECTS =

cpp/binary_tree_postorder_traversal_iterative_alternative: cpp/CMakeFiles/binary_tree_postorder_traversal_iterative_alternative.dir/binary_tree_postorder_traversal_iterative_alternative.cpp.o
cpp/binary_tree_postorder_traversal_iterative_alternative: cpp/CMakeFiles/binary_tree_postorder_traversal_iterative_alternative.dir/build.make
cpp/binary_tree_postorder_traversal_iterative_alternative: cpp/CMakeFiles/binary_tree_postorder_traversal_iterative_alternative.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/skull/Programming/Interview/epicode-master/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable binary_tree_postorder_traversal_iterative_alternative"
	cd /Users/skull/Programming/Interview/epicode-master/cmake-build-debug/cpp && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/binary_tree_postorder_traversal_iterative_alternative.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
cpp/CMakeFiles/binary_tree_postorder_traversal_iterative_alternative.dir/build: cpp/binary_tree_postorder_traversal_iterative_alternative

.PHONY : cpp/CMakeFiles/binary_tree_postorder_traversal_iterative_alternative.dir/build

cpp/CMakeFiles/binary_tree_postorder_traversal_iterative_alternative.dir/requires: cpp/CMakeFiles/binary_tree_postorder_traversal_iterative_alternative.dir/binary_tree_postorder_traversal_iterative_alternative.cpp.o.requires

.PHONY : cpp/CMakeFiles/binary_tree_postorder_traversal_iterative_alternative.dir/requires

cpp/CMakeFiles/binary_tree_postorder_traversal_iterative_alternative.dir/clean:
	cd /Users/skull/Programming/Interview/epicode-master/cmake-build-debug/cpp && $(CMAKE_COMMAND) -P CMakeFiles/binary_tree_postorder_traversal_iterative_alternative.dir/cmake_clean.cmake
.PHONY : cpp/CMakeFiles/binary_tree_postorder_traversal_iterative_alternative.dir/clean

cpp/CMakeFiles/binary_tree_postorder_traversal_iterative_alternative.dir/depend:
	cd /Users/skull/Programming/Interview/epicode-master/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/skull/Programming/Interview/epicode-master /Users/skull/Programming/Interview/epicode-master/cpp /Users/skull/Programming/Interview/epicode-master/cmake-build-debug /Users/skull/Programming/Interview/epicode-master/cmake-build-debug/cpp /Users/skull/Programming/Interview/epicode-master/cmake-build-debug/cpp/CMakeFiles/binary_tree_postorder_traversal_iterative_alternative.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : cpp/CMakeFiles/binary_tree_postorder_traversal_iterative_alternative.dir/depend

