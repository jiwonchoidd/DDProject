add_library(shared 
	Packets/ByteBuffer.cpp
)

target_include_directories(shared PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})