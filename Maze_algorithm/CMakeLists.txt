# CMakeList.txt : CMake project for Maze_algorithm, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project ("Maze_algorithm")

set(lista_archivos

  main.cpp
  Maze_algorithm.h  
  MazeCell.h  
  SolvingAlgorithm.h 
  MazeCreation.h 
  Menu.h 
  MazesManager.h 
  Timer.h

) 

# Add source to this project's executable.
add_executable (Maze_algorithm ${lista_archivos} )

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET Maze_algorithm PROPERTY CXX_STANDARD 20)
endif()

# TODO: Add tests and install targets if needed.
