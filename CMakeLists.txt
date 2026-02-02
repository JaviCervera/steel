cmake_minimum_required(VERSION 3.0...3.5)
project(steel)
file(
	GLOB
	STEEL_FILES
	"lib/lua/*.c"
	"src/*.cpp"
	"src/procedural/*.cpp"
	"src/steel.rc")
include_directories(
	${INCLUDE_DIRECTORIES}
	${CMAKE_CURRENT_SOURCE_DIR}/lib/lua
	${CMAKE_CURRENT_SOURCE_DIR}/lib/irrlicht_svn/include
	${CMAKE_CURRENT_SOURCE_DIR}/lib/openal/include)
link_directories(${LINK_DIRECTORIES} ${CMAKE_CURRENT_SOURCE_DIR}/_CMAKE/_IRRLICHT ${CMAKE_CURRENT_SOURCE_DIR}/_build)
add_executable(steel ${STEEL_FILES})

#Add platform specific options
add_definitions(-D_IRR_STATIC_LIB_)
if (${CMAKE_SYSTEM_NAME} MATCHES "Windows")
	add_definitions(-DWIN32 -DWITH_WINMM -DDISABLE_SIMD)
	if (MSVC)
		message("Platform is Windows (MSVC)")
		#add_definitions(-D_CRT_SECURE_NO_WARNINGS)
	else (MSVC)
		message("Platform is Windows (MinGW)")
		set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++98 -fno-exceptions -fno-rtti")
		set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -s -static -mwindows")
	endif (MSVC)
	target_link_libraries(steel -lIrrlicht -l:OpenAL32.dll -lopengl32 -lwinmm ${TARGET_LINK_LIBRARIES})
elseif (${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
	message("Platform is macOS")
	add_definitions(-DWITH_COREAUDIO)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++98 -fno-exceptions -fno-rtti")
	set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -s")
	set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -s")
	target_link_libraries(steel -lIrrlicht "-framework AudioToolbox" "-framework Cocoa" "-framework IOKit" "-framework OpenAL" "-framework OpenGL" ${TARGET_LINK_LIBRARIES})
elseif (${CMAKE_SYSTEM_NAME} MATCHES "Linux")
	message("Platform is Linux")
	add_definitions(-DWITH_ALSA)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++98 -fno-exceptions -fno-rtti -fPIC")
	set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -s")
	set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -s")
	target_link_libraries(steel -lIrrlicht -lasound -lGL -lopenal -lX11 -lXxf86vm ${TARGET_LINK_LIBRARIES})
elseif (${CMAKE_SYSTEM_NAME} MATCHES "Emscripten")
	message("Platform is Emscripten")
	add_definitions(-DWITH_OPENAL)
	target_compile_definitions(steel PRIVATE ${COMPILE_DEFINITIONS} -DLUA_USE_LONGJMP)
	set(CMAKE_EXECUTABLE_SUFFIX ".html")
	set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-fno-exceptions -fno-rtti -fstrict-aliasing	-U__STRICT_ANSI__")
	set(CMAKE_EXE_LINKER_FLAGS ${CMAKE_EXE_LINKER_FLAGS} "-lIrrlicht -lGL -lopenal --preload-file ../../main.dat@/ -s ALLOW_MEMORY_GROWTH=1 -s NO_EXIT_RUNTIME=1 -s ASYNCIFY")
else (${CMAKE_SYSTEM_NAME} MATCHES "Windows")
	message("Unrecognized platform " ${CMAKE_SYSTEM_NAME})
endif(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
