﻿# CMakeList.txt: projekt CMake dla elementu warframe_tool, dołącz źródło i zdefiniuj
# tutaj logikę specyficzną dla projektu.
#
cmake_minimum_required (VERSION 3.8)

# Włącz przeładowywanie kodu XAML na gorąco dla kompilatorów MSVC, jeśli jest to obsługiwane.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project ("warframe_tool")

set(CMAKE_CXX_STANDARD 17)
find_package(cpr CONFIG REQUIRED)
find_package(nlohmann_json CONFIG REQUIRED)
set(CMAKE_CXX_STANDARD 17)
find_package(SFML COMPONENTS system window graphics CONFIG REQUIRED)
find_package(OpenGl REQUIRED)
find_package(imgui CONFIG REQUIRED)
find_package(ImGui-SFML CONFIG REQUIRED)






# Dodaj źródło do pliku wykonywalnego tego projektu.
add_executable (${PROJECT_NAME} "warframe_tool.cpp" "warframe_tool.h" "functions.cpp" "trim.cpp" "utilities/guiUtilities.cpp" "utilities/keyBindings.cpp" "utilities/configUtilities.cpp" "utilities/readingItems.cpp")
target_link_libraries(${PROJECT_NAME} PRIVATE cpr::cpr)
target_link_libraries(${PROJECT_NAME} PRIVATE sfml-system sfml-network sfml-graphics sfml-window)
target_link_libraries(${PROJECT_NAME} PRIVATE ${OPENGL_LIBRARY})
target_link_libraries(${PROJECT_NAME} PRIVATE imgui::imgui)
target_link_libraries(${PROJECT_NAME} PRIVATE ImGui-SFML::ImGui-SFML)
target_link_libraries( ${PROJECT_NAME} PRIVATE "Dwmapi.lib") 






if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET warframe_tool PROPERTY CXX_STANDARD 20)
endif()

# TODO: Dodaj testy i zainstaluj elementy docelowe w razie potrzeby.
