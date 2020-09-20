project(SDK_Dataloader)
find_library(SDK_Core REQUIRED)

aux_source_directory(. srcf)

add_library(${PROJECT_NAME} ${srcf})
target_link_libraries(${PROJECT_NAME} SDK_Core)