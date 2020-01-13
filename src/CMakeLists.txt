project(Catholicus)
add_executable(Catholicus catholicus.c compiler.c error.c memory.c platform.c language/dedicated_parser.h language/dedicated_parser.c)
target_include_directories(Catholicus PRIVATE ./include/)