# Yahtzee Game Build Recipe
# Author: Kenneth Onulak Jr
# Tested on Windows 11

################################################################################
# basic settings
cmake_minimum_required( VERSION 3.20 ) # cmake version
set( PROJECT Yahtzee )                 # project name
project( ${PROJECT} )                  # set the project
set( CMAKE_CXX_STANDARD 20 )           # C++ version

################################################################################
#set( EXAMPLE_DIR examples/empty )     # simple sample of the project

################################################################################
# GLOB build files
# engine files
file( GLOB_RECURSE ENGINE CONFIG_DEPENDS include/*h include/*.cpp )
# project files
#file( GLOB_RECURSE EXAMPLE CONFIG_DEPENDS ${EXAMPLE_DIR}/*.h ${EXAMPLE_DIR}/*.cpp )

################################################################################
# add the executable with all globbed files (project and engine)
add_executable( ${PROJECT}
                # ${EXAMPLE}
                ${ENGINE}
                )

################################################################################
# link dependencies
target_link_libraries( ${PROJECT} PRIVATE
                       )