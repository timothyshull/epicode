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
include cpp/CMakeFiles/Student_sort.dir/depend.make

# Include the progress variables for this target.
include cpp/CMakeFiles/Student_sort.dir/progress.make

# Include the compile flags for this target's objects.
include cpp/CMakeFiles/Student_sort.dir/flags.make

cpp/CMakeFiles/Student_sort.dir/student_sort.cpp.o: cpp/CMakeFiles/Student_sort.dir/flags.make
cpp/CMakeFiles/Student_sort.dir/student_sort.cpp.o: ../cpp/student_sort.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/skull/Programming/Interview/epicode-master/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object cpp/CMakeFiles/Student_sort.dir/student_sort.cpp.o"
	cd /Users/skull/Programming/Interview/epicode-master/cmake-build-debug/cpp && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Student_sort.dir/student_sort.cpp.o -c /Users/skull/Programming/Interview/epicode-master/cpp/student_sort.cpp

cpp/CMakeFiles/Student_sort.dir/student_sort.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Student_sort.dir/student_sort.cpp.i"
	cd /Users/skull/Programming/Interview/epicode-master/cmake-build-debug/cpp && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/skull/Programming/Interview/epicode-master/cpp/student_sort.cpp > CMakeFiles/Student_sort.dir/student_sort.cpp.i

cpp/CMakeFiles/Student_sort.dir/student_sort.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Student_sort.dir/student_sort.cpp.s"
	cd /Users/skull/Programming/Interview/epicode-master/cmake-build-debug/cpp && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/skull/Programming/Interview/epicode-master/cpp/student_sort.cpp -o CMakeFiles/Student_sort.dir/student_sort.cpp.s

cpp/CMakeFiles/Student_sort.dir/student_sort.cpp.o.requires:

.PHONY : cpp/CMakeFiles/Student_sort.dir/student_sort.cpp.o.requires

cpp/CMakeFiles/Student_sort.dir/student_sort.cpp.o.provides: cpp/CMakeFiles/Student_sort.dir/student_sort.cpp.o.requires
	$(MAKE) -f cpp/CMakeFiles/Student_sort.dir/build.make cpp/CMakeFiles/Student_sort.dir/student_sort.cpp.o.provides.build
.PHONY : cpp/CMakeFiles/Student_sort.dir/student_sort.cpp.o.provides

cpp/CMakeFiles/Student_sort.dir/student_sort.cpp.o.provides.build: cpp/CMakeFiles/Student_sort.dir/student_sort.cpp.o


# Object files for target Student_sort
Student_sort_OBJECTS = \
"CMakeFiles/Student_sort.dir/student_sort.cpp.o"

# External object files for target Student_sort
Student_sort_EXTERNAL_OBJECTS =

cpp/Student_sort: cpp/CMakeFiles/Student_sort.dir/student_sort.cpp.o
cpp/Student_sort: cpp/CMakeFiles/Student_sort.dir/build.make
cpp/Student_sort: cpp/CMakeFiles/Student_sort.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/skull/Programming/Interview/epicode-master/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable Student_sort"
	cd /Users/skull/Programming/Interview/epicode-master/cmake-build-debug/cpp && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Student_sort.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
cpp/CMakeFiles/Student_sort.dir/build: cpp/Student_sort

.PHONY : cpp/CMakeFiles/Student_sort.dir/build

cpp/CMakeFiles/Student_sort.dir/requires: cpp/CMakeFiles/Student_sort.dir/student_sort.cpp.o.requires

.PHONY : cpp/CMakeFiles/Student_sort.dir/requires

cpp/CMakeFiles/Student_sort.dir/clean:
	cd /Users/skull/Programming/Interview/epicode-master/cmake-build-debug/cpp && $(CMAKE_COMMAND) -P CMakeFiles/Student_sort.dir/cmake_clean.cmake
.PHONY : cpp/CMakeFiles/Student_sort.dir/clean

cpp/CMakeFiles/Student_sort.dir/depend:
	cd /Users/skull/Programming/Interview/epicode-master/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/skull/Programming/Interview/epicode-master /Users/skull/Programming/Interview/epicode-master/cpp /Users/skull/Programming/Interview/epicode-master/cmake-build-debug /Users/skull/Programming/Interview/epicode-master/cmake-build-debug/cpp /Users/skull/Programming/Interview/epicode-master/cmake-build-debug/cpp/CMakeFiles/Student_sort.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : cpp/CMakeFiles/Student_sort.dir/depend
