add_executable(worldserver 
main.cpp
)

target_link_libraries(worldserver PRIVATE shared)