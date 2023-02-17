# CMakeList.txt : CMake project for Bates_Advanced_Operatin_Systems, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

project ("Bates_Advanced_Operating_Systems")
# Below is how the professor's website said to create the cmakelist. I have # out everything
# because as of now VS Studio has this premade approach to linux. Still unsure if this even works or not
#CXX = g++
#BIN=disk1

#Bates_Advanced_Operating_Systems: main.o filesys.o sdisk.o table.o shell.o block.o
#g++ main.o filesys.o sdisk.o table.o shell.o block.o -o BatesCSE4610

#table.o: table.cpp table.h
#g++ -c table.cpp

#shell.o: shell.cpp shell.h
#g++ -c shell.cpp

#filesys.o: filesys.cpp filesys.h
#g++ -c table.cpp

#sdisk.o: sdisk.cpp sdisk.h
#g++ -c sdisk.cpp

#block.o: block.cpp block.h
#g++ -c block.cpp

#main.o: main.cpp
#g++ -c table.cpp

#clean:
#rm *.o

# Add source to this project's executable.
add_subdirectory ( "Bates_Advanced_Operating_Systems.cpp" 
"Bates_Advanced_Operating_Systems.h" ".filesys.cpp" "block.h" 
"block.cpp" "shell.h" "shell.cpp" "table.h" "table.cpp")