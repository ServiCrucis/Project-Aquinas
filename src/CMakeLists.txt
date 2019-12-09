project(Modulus)
add_executable(Modulus modulus.c compiler.c error.c memory.c platform.c)
target_include_directories(Modulus PRIVATE ./include/)