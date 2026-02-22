cmake_minimum_required(VERSION 3.29)
project(c-linked-list LANGUAGES C)
add_executable(${PROJECT_NAME})
target_sources(${PROJECT_NAME} PRIVATE main.c)
target_compile_features(${PROJECT_NAME} PRIVATE c_std_23)
set_target_properties(
  ${PROJECT_NAME}
  PROPERTIES C_STANDARD 23
             C_STANDARD_REQUIRED YES
             C_EXTENSIONS NO)
