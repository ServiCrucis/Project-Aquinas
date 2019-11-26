project(Modulus)
# external project includes
# set this value to the location of libcpuid headers for your particular environment
set(LIBCPUID_PATH ../../libcpuid/libcpuid)
add_executable(Modulus modulus.c compiler.c debug.c memory.c platform.c)
target_include_directories(Modulus PRIVATE ./include/ ${LIBCPUID_PATH})
# imported libraries
find_library(LIBCPUID libcpuid)
find_path(LIBCPUID_A libcpuid HINTS ${LIBCPUID_PATH})
if (LIBCPUID AND LIBCPUID_A)
    target_link_directories(Modulus PUBLIC ${LIBCPUID_PATH}/.libs)
    add_library(libcpuid STATIC IMPORTED GLOBAL)
    set_property(TARGET libcpuid PROPERTY IMPORTED_LOCATION "${LIBCPUID_A}")
endif ()