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
CMAKE_COMMAND = "C:\Program Files\JetBrains\CLion 2022.3.2\bin\cmake\win\x64\bin\cmake.exe"

# The command to remove a file.
RM = "C:\Program Files\JetBrains\CLion 2022.3.2\bin\cmake\win\x64\bin\cmake.exe" -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = C:\ASD\L04\E01

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = C:\ASD\L04\E01\cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/E01.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/E01.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/E01.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/E01.dir/flags.make

CMakeFiles/E01.dir/main.c.obj: CMakeFiles/E01.dir/flags.make
CMakeFiles/E01.dir/main.c.obj: C:/ASD/L04/E01/main.c
CMakeFiles/E01.dir/main.c.obj: CMakeFiles/E01.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\ASD\L04\E01\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/E01.dir/main.c.obj"
	C:\PROGRA~1\JETBRA~1\CLION2~1.2\bin\mingw\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/E01.dir/main.c.obj -MF CMakeFiles\E01.dir\main.c.obj.d -o CMakeFiles\E01.dir\main.c.obj -c C:\ASD\L04\E01\main.c

CMakeFiles/E01.dir/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/E01.dir/main.c.i"
	C:\PROGRA~1\JETBRA~1\CLION2~1.2\bin\mingw\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E C:\ASD\L04\E01\main.c > CMakeFiles\E01.dir\main.c.i

CMakeFiles/E01.dir/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/E01.dir/main.c.s"
	C:\PROGRA~1\JETBRA~1\CLION2~1.2\bin\mingw\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S C:\ASD\L04\E01\main.c -o CMakeFiles\E01.dir\main.c.s

# Object files for target E01
E01_OBJECTS = \
"CMakeFiles/E01.dir/main.c.obj"

# External object files for target E01
E01_EXTERNAL_OBJECTS =

E01.exe: CMakeFiles/E01.dir/main.c.obj
E01.exe: CMakeFiles/E01.dir/build.make
E01.exe: CMakeFiles/E01.dir/linkLibs.rsp
E01.exe: CMakeFiles/E01.dir/objects1.rsp
E01.exe: CMakeFiles/E01.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=C:\ASD\L04\E01\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable E01.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\E01.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/E01.dir/build: E01.exe
.PHONY : CMakeFiles/E01.dir/build

CMakeFiles/E01.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\E01.dir\cmake_clean.cmake
.PHONY : CMakeFiles/E01.dir/clean

CMakeFiles/E01.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" C:\ASD\L04\E01 C:\ASD\L04\E01 C:\ASD\L04\E01\cmake-build-debug C:\ASD\L04\E01\cmake-build-debug C:\ASD\L04\E01\cmake-build-debug\CMakeFiles\E01.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/E01.dir/depend
