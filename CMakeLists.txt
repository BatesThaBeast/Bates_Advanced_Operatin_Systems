# CMakeList.txt : CMake project for Bates_Advanced_Operatin_Systems, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

project ("Bates_Advanced_Operating_Systems")

# Add source to this project's executable.
add_executable (Bates_Advanced_Operating_Systems "Bates_Advanced_Operating_Systems.cpp" "Bates_Advanced_Operating_Systems.h" "passwordfile.cpp" "passwordfile.h"
"sdisk.cpp" "sdisk.h" "filesys.h" "filesys.cpp")

# TODO: Add tests and install targets if needed.
