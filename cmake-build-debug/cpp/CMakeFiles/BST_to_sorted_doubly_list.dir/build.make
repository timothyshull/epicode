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
CMAKE_COMMAND = "/Users/skull/Library/Application Support/JetBrains/Toolbox/apps/CLion/ch-0/163.9166.31/CLion.app/Contents/bin/cmake/bin/cmake"

# The command to remove a file.
RM = "/Users/skull/Library/Application Support/JetBrains/Toolbox/apps/CLion/ch-0/163.9166.31/CLion.app/Contents/bin/cmake/bin/cmake" -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/skull/Programming/Interview/epicode-master

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/skull/Programming/Interview/epicode-master/cmake-build-debug

# Include any dependencies generated for this target.
include cpp/CMakeFiles/bst_to_sorted_doubly_list.dir/depend.make

# Include the progress variables for this target.
include cpp/CMakeFiles/bst_to_sorted_doubly_list.dir/progress.make

# Include the compile flags for this target's objects.
include cpp/CMakeFiles/bst_to_sorted_doubly_list.dir/flags.make

cpp/CMakeFiles/bst_to_sorted_doubly_list.dir/bst_to_sorted_doubly_list.cpp.o: cpp/CMakeFiles/bst_to_sorted_doubly_list.dir/flags.make
cpp/CMakeFiles/bst_to_sorted_doubly_list.dir/bst_to_sorted_doubly_list.cpp.o: ../cpp/bst_to_sorted_doubly_list.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/skull/Programming/Interview/epicode-master/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object cpp/CMakeFiles/bst_to_sorted_doubly_list.dir/bst_to_sorted_doubly_list.cpp.o"
	cd /Users/skull/Programming/Interview/epicode-master/cmake-build-debug/cpp && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/bst_to_sorted_doubly_list.dir/bst_to_sorted_doubly_list.cpp.o -c /Users/skull/Programming/Interview/epicode-master/cpp/bst_to_sorted_doubly_list.cpp

cpp/CMakeFiles/bst_to_sorted_doubly_list.dir/bst_to_sorted_doubly_list.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/bst_to_sorted_doubly_list.dir/bst_to_sorted_doubly_list.cpp.i"
	cd /Users/skull/Programming/Interview/epicode-master/cmake-build-debug/cpp && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/skull/Programming/Interview/epicode-master/cpp/bst_to_sorted_doubly_list.cpp > CMakeFiles/bst_to_sorted_doubly_list.dir/bst_to_sorted_doubly_list.cpp.i

cpp/CMakeFiles/bst_to_sorted_doubly_list.dir/bst_to_sorted_doubly_list.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/bst_to_sorted_doubly_list.dir/bst_to_sorted_doubly_list.cpp.s"
	cd /Users/skull/Programming/Interview/epicode-master/cmake-build-debug/cpp && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/skull/Programming/Interview/epicode-master/cpp/bst_to_sorted_doubly_list.cpp -o CMakeFiles/bst_to_sorted_doubly_list.dir/bst_to_sorted_doubly_list.cpp.s

cpp/CMakeFiles/bst_to_sorted_doubly_list.dir/bst_to_sorted_doubly_list.cpp.o.requires:

.PHONY : cpp/CMakeFiles/bst_to_sorted_doubly_list.dir/bst_to_sorted_doubly_list.cpp.o.requires

cpp/CMakeFiles/bst_to_sorted_doubly_list.dir/bst_to_sorted_doubly_list.cpp.o.provides: cpp/CMakeFiles/bst_to_sorted_doubly_list.dir/bst_to_sorted_doubly_list.cpp.o.requires
	$(MAKE) -f cpp/CMakeFiles/bst_to_sorted_doubly_list.dir/build.make cpp/CMakeFiles/bst_to_sorted_doubly_list.dir/bst_to_sorted_doubly_list.cpp.o.provides.build
.PHONY : cpp/CMakeFiles/bst_to_sorted_doubly_list.dir/bst_to_sorted_doubly_list.cpp.o.provides

cpp/CMakeFiles/bst_to_sorted_doubly_list.dir/bst_to_sorted_doubly_list.cpp.o.provides.build: cpp/CMakeFiles/bst_to_sorted_doubly_list.dir/bst_to_sorted_doubly_list.cpp.o


# Object files for target bst_to_sorted_doubly_list
bst_to_sorted_doubly_list_OBJECTS = \
"CMakeFiles/bst_to_sorted_doubly_list.dir/bst_to_sorted_doubly_list.cpp.o"

# External object files for target bst_to_sorted_doubly_list
bst_to_sorted_doubly_list_EXTERNAL_OBJECTS =

cpp/bst_to_sorted_doubly_list: cpp/CMakeFiles/bst_to_sorted_doubly_list.dir/bst_to_sorted_doubly_list.cpp.o
cpp/bst_to_sorted_doubly_list: cpp/CMakeFiles/bst_to_sorted_doubly_list.dir/build.make
cpp/bst_to_sorted_doubly_list: cpp/CMakeFiles/bst_to_sorted_doubly_list.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/skull/Programming/Interview/epicode-master/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable bst_to_sorted_doubly_list"
	cd /Users/skull/Programming/Interview/epicode-master/cmake-build-debug/cpp && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/bst_to_sorted_doubly_list.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
cpp/CMakeFiles/bst_to_sorted_doubly_list.dir/build: cpp/bst_to_sorted_doubly_list

.PHONY : cpp/CMakeFiles/bst_to_sorted_doubly_list.dir/build

cpp/CMakeFiles/bst_to_sorted_doubly_list.dir/requires: cpp/CMakeFiles/bst_to_sorted_doubly_list.dir/bst_to_sorted_doubly_list.cpp.o.requires

.PHONY : cpp/CMakeFiles/bst_to_sorted_doubly_list.dir/requires

cpp/CMakeFiles/bst_to_sorted_doubly_list.dir/clean:
	cd /Users/skull/Programming/Interview/epicode-master/cmake-build-debug/cpp && $(CMAKE_COMMAND) -P CMakeFiles/bst_to_sorted_doubly_list.dir/cmake_clean.cmake
.PHONY : cpp/CMakeFiles/bst_to_sorted_doubly_list.dir/clean

cpp/CMakeFiles/bst_to_sorted_doubly_list.dir/depend:
	cd /Users/skull/Programming/Interview/epicode-master/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/skull/Programming/Interview/epicode-master /Users/skull/Programming/Interview/epicode-master/cpp /Users/skull/Programming/Interview/epicode-master/cmake-build-debug /Users/skull/Programming/Interview/epicode-master/cmake-build-debug/cpp /Users/skull/Programming/Interview/epicode-master/cmake-build-debug/cpp/CMakeFiles/bst_to_sorted_doubly_list.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : cpp/CMakeFiles/bst_to_sorted_doubly_list.dir/depend

