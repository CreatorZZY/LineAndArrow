project(SDK_Drawer)
find_library(cairo REQUIRED)
find_library(SDK_Core REQUIRED)

aux_source_directory(. srcf)

add_library(${PROJECT_NAME} ${srcf})
target_link_libraries(${PROJECT_NAME} cairo SDK_Core)