project(SDK_Package)

add_subdirectory(SDK)

find_library(SDK_Core REQUIRED)
find_library(SDK_Drawer REQUIRED)
find_library(SDK_Dataloader REQUIRED)

add_executable(LineAndArrow main.cpp)
target_link_libraries(LineAndArrow SDK_Core SDK_Drawer SDK_Dataloader)