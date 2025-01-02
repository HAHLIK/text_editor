cmake_minimum_required(VERSION 3.10)

set (PROJECT_NAME Rim)
project(${PROJECT_NAME} VERSION 0.1.0 LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)

add_executable(${PROJECT_NAME} "src/main.cpp"
							   "src/settings.h"
							   "src/fileObject.h"
							   "src/fileObject.cpp"
							   "src/editorViewer.cpp"
							   "src/editorViewer.h"
							   "src/inputController.cpp"
							   "src/inputController.h"
							   "src/editorContent.h"
							   "src/editorContent.cpp")


set(SFML_DIR "external/SFML/lib/cmake/SFML")
find_package(SFML 2.6.1 COMPONENTS graphics window system REQUIRED)
target_link_libraries(${PROJECT_NAME} sfml-graphics sfml-window sfml-system)

install(TARGETS ${PROJECT_NAME} DESTINATION bin)
include(InstallRequiredSystemLibraries)

set_target_properties(${PROJECT_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/)

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
					COMMAND ${CMAKE_COMMAND} -E copy_directory
					${CMAKE_SOURCE_DIR}/resours $<TARGET_FILE_DIR:${PROJECT_NAME}>/resours)