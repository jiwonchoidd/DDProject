add_library(common
Common.h
Common.cpp
Define.h
)

target_include_directories(common 
	PUBLIC 
		${CMAKE_CURRENT_SOURCE_DIR}
)