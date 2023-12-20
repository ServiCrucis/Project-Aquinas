project(Project-Aquinas)
add_executable(Project-Aquinas aquinas.c compiler.c include/state.c platform.c reference_vm.h reference_vm.c constructs/pattern_tree.h constructs/pattern_tree.c bit_trie.c bit_trie.h math/bit_math.h constructs/binary_tree.c constructs/binary_tree.h include/asm.h math/frc_math.c math/frc_math.h constructs/dynarray.c constructs/dynarray.h tests.h constructs/map.c constructs/map.h include/state/allocating.h math/fp_math.c math/fp_math.h include/data.c include/data.h include/state/windows/m_windows.c include/state/windows/m_windows.h include/state/array.c include/state/array.h math/base_n_math.h math/computation.h include/state/m_pointer_offset.h constructs/tree.c constructs/tree.h
        include/type.h
        include/state/windows/m_windows_ImperfectUnitStackAllocator.c
        include/state/windows/m_windows_ImperfectUnitStackAllocator.h
        include/state/windows/m_windows_ImperfectUnitAllocator.c
        include/state/windows/m_windows_ImperfectUnitAllocator.h
        include/state/StateholdSource.h
        include/state/windows/m_windows_StateholdSource.c
        include/state/windows/m_windows_StateholdSource.h
)
target_include_directories(Project-Aquinas PRIVATE ./include/ ./math/ constructs/)