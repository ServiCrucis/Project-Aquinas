project(Catholicus)
add_executable(Catholicus catholicus.c compiler.c error.c memory.c platform.c reference_vm.h reference_vm.c permutation.h permutation.c bit_trie.c bit_trie.h math/bit_math.h objects/binary_trie.c objects/binary_trie.h include/asm.c include/asm.h math/frac_math.c math/frac_math.h)
target_include_directories(Catholicus PRIVATE ./include/ ./math/ ./objects/)