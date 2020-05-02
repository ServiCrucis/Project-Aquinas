project(Catholicus)
add_executable(Catholicus catholicus.c compiler.c error.c memory.c platform.c reference_vm.h reference_vm.c pattern.h pattern.c bit_trie.c bit_trie.h math/bit_math.h associative_array.c associative_array.h)
target_include_directories(Catholicus PRIVATE ./include/ ./math/)