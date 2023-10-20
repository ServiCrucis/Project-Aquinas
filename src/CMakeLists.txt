project(Project-Aquinas)
add_executable(Project-Aquinas aquinas.c compiler.c include/state.c platform.c reference_vm.h reference_vm.c constructs/pattern_tree.h constructs/pattern_tree.c bit_trie.c bit_trie.h math/bit_math.h constructs/binary_tree.c constructs/binary_tree.h include/asm.h math/frc_math.c math/frc_math.h constructs/dynarray.c constructs/dynarray.h tests.h constructs/map.c constructs/map.h include/memory/memory.h math/fp_math.c math/fp_math.h include/memory/m_context.h include/data.c include/data.h include/memory/windows/m_windows.c include/memory/windows/m_windows.h include/memory/array.c include/memory/array.h math/base_n_math.h math/computation.h include/memory/m_pointer_offset.h constructs/tree.c constructs/tree.h
        include/type.h
        include/memory/windows/m_windows_ImperfectUnitStackAllocator.c
        include/memory/windows/m_windows_ImperfectUnitStackAllocator.h
        include/memory/windows/m_windows_ImperfectUnitAllocator.c
        include/memory/windows/m_windows_ImperfectUnitAllocator.h
)
target_include_directories(Project-Aquinas PRIVATE ./include/ ./math/ constructs/)