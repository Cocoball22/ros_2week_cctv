# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.16

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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/cona/camera_ws/src

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/cona/camera_ws/build

# Utility rule file for orbbec_camera_geneus.

# Include the progress variables for this target.
include OrbbecSDK_ROS1/CMakeFiles/orbbec_camera_geneus.dir/progress.make

orbbec_camera_geneus: OrbbecSDK_ROS1/CMakeFiles/orbbec_camera_geneus.dir/build.make

.PHONY : orbbec_camera_geneus

# Rule to build all files generated by this target.
OrbbecSDK_ROS1/CMakeFiles/orbbec_camera_geneus.dir/build: orbbec_camera_geneus

.PHONY : OrbbecSDK_ROS1/CMakeFiles/orbbec_camera_geneus.dir/build

OrbbecSDK_ROS1/CMakeFiles/orbbec_camera_geneus.dir/clean:
	cd /home/cona/camera_ws/build/OrbbecSDK_ROS1 && $(CMAKE_COMMAND) -P CMakeFiles/orbbec_camera_geneus.dir/cmake_clean.cmake
.PHONY : OrbbecSDK_ROS1/CMakeFiles/orbbec_camera_geneus.dir/clean

OrbbecSDK_ROS1/CMakeFiles/orbbec_camera_geneus.dir/depend:
	cd /home/cona/camera_ws/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/cona/camera_ws/src /home/cona/camera_ws/src/OrbbecSDK_ROS1 /home/cona/camera_ws/build /home/cona/camera_ws/build/OrbbecSDK_ROS1 /home/cona/camera_ws/build/OrbbecSDK_ROS1/CMakeFiles/orbbec_camera_geneus.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : OrbbecSDK_ROS1/CMakeFiles/orbbec_camera_geneus.dir/depend

