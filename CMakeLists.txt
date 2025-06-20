cmake_minimum_required(VERSION 3.0)
project(steel)
file(GLOB STEEL_FILES "src/*.cpp" "src/steel.rc")
include_directories(
	${INCLUDE_DIRECTORIES}
	${CMAKE_CURRENT_SOURCE_DIR}/lib/lua
	${CMAKE_CURRENT_SOURCE_DIR}/lib/irrlicht131/include)
link_directories(${LINK_DIRECTORIES} ${CMAKE_CURRENT_SOURCE_DIR}/_CMAKE/_IRRLICHT)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++98 -fno-exceptions -fno-rtti")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -s -static -mwindows")
add_definitions(-D_IRR_STATIC_LIB_)
add_executable(steel ${STEEL_FILES})
target_link_libraries(steel -lIrrlicht -lopengl32 -lglu32 -lwinmm ${TARGET_LINK_LIBRARIES})
