include(FetchContent)

FetchContent_Declare(
    glfw
    GIT_REPOSITORY https://github.com/glfw/glfw.git
    GIT_TAG        latest
)
FetchContent_MakeAvailable(glfw)

FetchContent_Declare(
    glm
    GIT_REPOSITORY https://github.com/g-truc/glm.git
    GIT_TAG        0af55ccecd98d4e5a8d1fad7de25ba429d60e863
)
FetchContent_MakeAvailable(glm)

find_package(OpenGL REQUIRED)

add_executable (pong-cpp 
    "src/main.cpp"  
    "src/Game.cpp" 
    "include/glad/glad.h" 
    "include/KHR/khrplatform.h" 
    "src/glad.c"
    "include/Game.h"
 "include/Shader.h" "src/Shader.cpp" "include/Player.h" "src/Player.cpp")

target_include_directories(pong-cpp PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries(pong-cpp PRIVATE glm::glm-header-only)

target_link_libraries(pong-cpp
    PRIVATE
    glfw
    ${OpenGL_LIBRARIES}
)

add_custom_command(TARGET pong-cpp POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    "${CMAKE_CURRENT_SOURCE_DIR}/res"
    "$<TARGET_FILE_DIR:pong-cpp>/res"
)