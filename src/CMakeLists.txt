project(Catholicus)
add_executable(Catholicus catholicus.c compiler.c error.c memory.c platform.c)
target_include_directories(Catholicus PRIVATE ./include/)