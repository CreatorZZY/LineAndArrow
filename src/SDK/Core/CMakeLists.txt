project(SDK_Core)

aux_source_directory(. srcf)

add_library(${PROJECT_NAME} ${srcf})