cmake_minimum_required(VERSION 3.10)

set (PROJECT_NAME my_text_editor)
project(${PROJECT_NAME} VERSION 0.1.0)

add_executable(${PROJECT_NAME} "src/main.cpp")

set(SFML_DIR "external/SFML/lib/cmake/SFML")
find_package(SFML 2.6.1 COMPONENTS network audio graphics window system REQUIRED)
target_link_libraries(${PROJECT_NAME} sfml-network sfml-audio sfml-graphics sfml-window sfml-system)

install(TARGETS ${PROJECT_NAME} DESTINATION bin)
include(InstallRequiredSystemLibraries)
