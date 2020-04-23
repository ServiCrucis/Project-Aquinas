project(Catholicus)
add_executable(Catholicus catholicus.c compiler.c error.c memory.c platform.c reference_vm.h reference_vm.c pattern.h pattern.c binary_trie.c binary_trie.h)
target_include_directories(Catholicus PRIVATE ./include/)