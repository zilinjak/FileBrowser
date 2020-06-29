cmake_minimum_required(VERSION 3.16)
project(Browser)

set(CMAKE_CXX_STANDARD 17)

set(-Wall -pedantic)

add_executable(Browser src/main.cpp src/CData.cpp src/CData.h src/CBrowser.cpp src/CBrowser.h src/CFolder.cpp src/CFolder.h src/CInterface.cpp src/CInterface.h src/CFile.cpp src/CFile.h src/CDelete.cpp src/CDelete.h src/COperations.cpp src/COperations.h src/CMove.cpp src/CMove.h src/CCopy.cpp src/CCopy.h src/CRegExp.cpp src/CRegExp.h src/CSymlink.cpp src/CSymlink.h)