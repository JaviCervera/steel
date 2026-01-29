cmake_minimum_required(VERSION 3.0)
project(steel)
file(
	GLOB
	STEEL_FILES
	"lib/lua/*.c"
	"lib/soloud/src/audiosource/wav/*.cpp"
	"lib/soloud/src/audiosource/wav/stb_vorbis.c"
	"lib/soloud/src/backend/alsa/soloud_alsa.cpp"
	"lib/soloud/src/backend/coreaudio/soloud_coreaudio.cpp"
	"lib/soloud/src/backend/winmm/soloud_winmm.cpp"
	"lib/soloud/src/core/*.cpp"
	"src/*.cpp"
	"src/procedural/*.cpp"
	"src/steel.rc")
include_directories(
	${INCLUDE_DIRECTORIES}
	${CMAKE_CURRENT_SOURCE_DIR}/lib/lua
	${CMAKE_CURRENT_SOURCE_DIR}/lib/irrlicht_svn/include
	${CMAKE_CURRENT_SOURCE_DIR}/lib/soloud/include)
link_directories(${LINK_DIRECTORIES} ${CMAKE_CURRENT_SOURCE_DIR}/_CMAKE/_IRRLICHT)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++98 -fno-rtti")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -s -static -mwindows")
add_definitions(-D_IRR_STATIC_LIB_ -DWITH_WINMM -DDISABLE_SIMD)
add_executable(steel ${STEEL_FILES})
target_link_libraries(steel -lIrrlicht -lopengl32 -lglu32 -lwinmm ${TARGET_LINK_LIBRARIES})
