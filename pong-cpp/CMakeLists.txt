include(FetchContent)
FetchContent_Declare(
    glfw
    GIT_REPOSITORY https://github.com/glfw/glfw.git
    GIT_TAG        latest
)
FetchContent_MakeAvailable(glfw)

find_package(OpenGL REQUIRED)

add_executable (pong-cpp 
    "src/main.cpp"  
    "src/Game.cpp" 
    "include/glad/glad.h" 
    "include/KHR/khrplatform.h" 
    "src/glad.c"
    "include/Game.h"
 "include/Shader.h" "src/Shader.cpp")

target_include_directories(pong-cpp PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

target_link_libraries(pong-cpp
    PRIVATE
    glfw
    ${OpenGL_LIBRARIES}
)