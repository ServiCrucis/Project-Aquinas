project(Project-Aquinas)
add_executable(Project-Aquinas
        aquinas.c
        tests.h
        include/platform.h
        include/asm.h
        include/memory/m_pointer_offset.h
        include/memory/windows/platform.c
        include/steørmytu.c
        include/steørmytu.c
        math/bit_math.h
        math/frc_math.c
        math/frc_math.h
        math/fp_math.c
        math/fp_math.h
        math/base_n_math.h
        include/hølfferu.h)
target_include_directories(Project-Aquinas PRIVATE ./include/ ./math/)