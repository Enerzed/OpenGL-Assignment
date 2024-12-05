# Кодировка Unicode
add_compile_definitions(_UNICODE UNICODE)

# Минимальная версия CMake
cmake_minimum_required (VERSION 3.8)

# Включение горячей перезагрузки для компиляторов MSVC, если поддерживается.
if (POLICY CMP0141)
	cmake_policy(SET CMP0141 NEW)
		set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

# Имя проекта
project ("KG131")

# Файлы проекта .hpp .cpp
file(GLOB SRC "*.hpp" "*.cpp" "*.h" ".c" "*.frag" "*.vert" "*.glsl")
file(COPY ${SRC} DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

# Добавьте источник в исполняемый файл этого проекта.
add_executable (${PROJECT_NAME} ${SRC})

# Если CMake версии 3.12 и новее то используем стандарт C++17
if (CMAKE_VERSION VERSION_GREATER 3.12)
	set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 17)
endif()

# Подключаем зависимости
add_subdirectory(dependencies)

# Подключаем необходимые библиотеки
target_link_libraries(${PROJECT_NAME} PUBLIC imgui glm)
target_link_libraries(${PROJECT_NAME} PUBLIC glfw glad glm)
target_link_libraries(${PROJECT_NAME} PUBLIC tinyobjloader)