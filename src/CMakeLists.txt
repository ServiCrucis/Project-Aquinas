project(Pax)
add_executable(Pax pax.c compiler.c error.c memory.c platform.c)
target_include_directories(Pax PRIVATE ./include/)