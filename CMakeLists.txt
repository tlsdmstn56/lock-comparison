project(lock-comparison)

add_executable(lock_comparison
    src/main.cpp
)

target_link_libraries(lock_comparison
PRIVATE pthread
)