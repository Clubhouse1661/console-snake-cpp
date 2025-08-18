cmake_minimum_required(VERSION 3.10)

# Project configuration
project(ConsoleSnakeCpp 
    VERSION 1.0.0
    DESCRIPTION "Classic Snake game in C++ for Windows console - zero dependencies"
    LANGUAGES CXX)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Compiler-specific options
if(MSVC)
    # Windows-specific settings for console application
    add_compile_options(/W4)
    add_compile_definitions(_CRT_SECURE_NO_WARNINGS)
else()
    # GCC/Clang settings (for cross-compilation testing)
    add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# Source files (to be added when source code is implemented)
set(SOURCES
    # src/main.cpp
    # src/game.cpp
    # src/snake.cpp
    # src/food.cpp
    # src/console.cpp
    # src/utils.cpp
)

set(HEADERS
    # src/game.h
    # src/snake.h
    # src/food.h
    # src/console.h
    # src/utils.h
)

# Create executable (commented out until source files exist)
# add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})

# Windows console subsystem
# if(WIN32)
#     set_target_properties(${PROJECT_NAME} PROPERTIES
#         WIN32_EXECUTABLE FALSE  # Console application
#     )
# endif()

# No external dependencies required - using only:
# - Standard C++ library
# - Windows Console API (windows.h)

# Installation (optional)
# install(TARGETS ${PROJECT_NAME}
#     RUNTIME DESTINATION bin
# )

# Package configuration
set(CPACK_PACKAGE_NAME "Console Snake C++")
set(CPACK_PACKAGE_VERSION "${PROJECT_VERSION}")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "${PROJECT_DESCRIPTION}")
set(CPACK_PACKAGE_VENDOR "Console Snake C++ Project")

include(CPack)