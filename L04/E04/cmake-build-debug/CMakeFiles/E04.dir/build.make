# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.26

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

SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = "C:\Program Files\JetBrains\CLion 2023.2.2\bin\cmake\win\x64\bin\cmake.exe"

# The command to remove a file.
RM = "C:\Program Files\JetBrains\CLion 2023.2.2\bin\cmake\win\x64\bin\cmake.exe" -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = "C:\Users\alebe\Documents\UNI Polito\ASD\L04\E04"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "C:\Users\alebe\Documents\UNI Polito\ASD\L04\E04\cmake-build-debug"

# Include any dependencies generated for this target.
include CMakeFiles/E04.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/E04.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/E04.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/E04.dir/flags.make

CMakeFiles/E04.dir/main.c.obj: CMakeFiles/E04.dir/flags.make
CMakeFiles/E04.dir/main.c.obj: C:/Users/alebe/Documents/UNI\ Polito/ASD/L04/E04/main.c
CMakeFiles/E04.dir/main.c.obj: CMakeFiles/E04.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="C:\Users\alebe\Documents\UNI Polito\ASD\L04\E04\cmake-build-debug\CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/E04.dir/main.c.obj"
	C:\PROGRA~1\JETBRA~1\CLION2~1.2\bin\mingw\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/E04.dir/main.c.obj -MF CMakeFiles\E04.dir\main.c.obj.d -o CMakeFiles\E04.dir\main.c.obj -c "C:\Users\alebe\Documents\UNI Polito\ASD\L04\E04\main.c"

CMakeFiles/E04.dir/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/E04.dir/main.c.i"
	C:\PROGRA~1\JETBRA~1\CLION2~1.2\bin\mingw\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E "C:\Users\alebe\Documents\UNI Polito\ASD\L04\E04\main.c" > CMakeFiles\E04.dir\main.c.i

CMakeFiles/E04.dir/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/E04.dir/main.c.s"
	C:\PROGRA~1\JETBRA~1\CLION2~1.2\bin\mingw\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S "C:\Users\alebe\Documents\UNI Polito\ASD\L04\E04\main.c" -o CMakeFiles\E04.dir\main.c.s

# Object files for target E04
E04_OBJECTS = \
"CMakeFiles/E04.dir/main.c.obj"

# External object files for target E04
E04_EXTERNAL_OBJECTS =

E04.exe: CMakeFiles/E04.dir/main.c.obj
E04.exe: CMakeFiles/E04.dir/build.make
E04.exe: CMakeFiles/E04.dir/linkLibs.rsp
E04.exe: CMakeFiles/E04.dir/objects1.rsp
E04.exe: CMakeFiles/E04.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir="C:\Users\alebe\Documents\UNI Polito\ASD\L04\E04\cmake-build-debug\CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable E04.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\E04.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/E04.dir/build: E04.exe
.PHONY : CMakeFiles/E04.dir/build

CMakeFiles/E04.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\E04.dir\cmake_clean.cmake
.PHONY : CMakeFiles/E04.dir/clean

CMakeFiles/E04.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" "C:\Users\alebe\Documents\UNI Polito\ASD\L04\E04" "C:\Users\alebe\Documents\UNI Polito\ASD\L04\E04" "C:\Users\alebe\Documents\UNI Polito\ASD\L04\E04\cmake-build-debug" "C:\Users\alebe\Documents\UNI Polito\ASD\L04\E04\cmake-build-debug" "C:\Users\alebe\Documents\UNI Polito\ASD\L04\E04\cmake-build-debug\CMakeFiles\E04.dir\DependInfo.cmake" --color=$(COLOR)
.PHONY : CMakeFiles/E04.dir/depend

