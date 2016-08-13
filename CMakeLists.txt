# Minimum required CMake version
cmake_minimum_required(VERSION 2.8)
 
# Project name
project(object_categorization)
 
# Find the OpenCV installation
find_package(OpenCV REQUIRED)
# Find the Boost installation, specifically the components 'system' and 'filesystem'
find_package(Boost COMPONENTS system filesystem REQUIRED)
 
# ${PROJECT_SOURCE_DIR} is the name of the root directory of the project
# TO_NATIVE_PATH converts the path ${PROJECT_SOURCE_DIR}/data/ to a full path and the file()command stores it in DATA_FOLDER
#file(TO_NATIVE_PATH "./data/" DATA_FOLDER)
set(DATA_FOLDER "./data/train_images/")
# set TRAIN_FOLDER to DATA_FOLDER/train_images - this is where we will put our templates forconstructing the vocabulary
set(TRAIN_FOLDER "./data/train_images/")
# set TEMPLATE_FOLDER to DATA_FOLDER/templates - this is where we will put our traininfg images,in folders organized by category
set(TEMPLATE_FOLDER "./data/templates/")
 
# set the configuration input file to ${PROJECT_SOURCE_DIR}/Config.h.in and the includable header file holding configuration information to${PROJECT_SOURCE_DIR}/include/Config.h
configure_file("./Config.h.in" "./include/Config.h")
 
# Other directories where header files for linked libraries can be found
include_directories("./include" ${Boost_INCLUDE_DIRS})

# executable produced as a result of compilation
add_executable(code src2/code2.cpp)
# libraries to be linked with this executable - OpenCV and Boost (system and filesystem components)
target_link_libraries(code ${OpenCV_LIBS} ${Boost_SYSTEM_LIBRARY} ${Boost_FILESYSTEM_LIBRARY})
