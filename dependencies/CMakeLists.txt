# Подключаем библиотеки статически для избежания неожиданных проблем
set(BUILD_SHARED_LIBS FALSE)

include(FetchContent)

# imgui-glfw-glad-glm
FetchContent_Declare(
        imgui-glfw-glad-glm
        GIT_REPOSITORY https://github.com/cmmw/imgui-glfw-glad-glm.git
        GIT_TAG v4.2.0
)
add_subdirectory(imgui-glfw-glad-glm)

# tinyobjloader
FetchContent_Declare(
        tinyobjloader
        GIT_REPOSITORY https://github.com/tinyobjloader/tinyobjloader.git
        GIT_TAG v1.0.6
)
add_subdirectory(tinyobjloader)