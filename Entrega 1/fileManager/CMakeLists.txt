cmake_minimum_required (VERSION 2.8.11)

project (fileManager)

project(serverFilemanager LANGUAGES CXX)
add_executable(serverFilemanager serverFileManager.cpp operaciones.h utils.h utils.cpp fileManager.h fileManager_Imp.h)
target_link_libraries(serverFilemanager pthread)

project(clientFilemanager LANGUAGES CXX)
add_executable(clientFilemanager clientFileManager.cpp operaciones.h utils.h utils.cpp fileManager_Stub.h)
target_link_libraries(clientFilemanager pthread)
