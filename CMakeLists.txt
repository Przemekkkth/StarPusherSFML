cmake_minimum_required(VERSION 3.16)
project(CMakeSFMLProject LANGUAGES CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
option(BUILD_SHARED_LIBS "Build shared libraries" OFF)

include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 2.6.x)
FetchContent_MakeAvailable(SFML)

add_executable(
    main
    src/main.cpp
    src/application.h
    src/application.cpp

    src/game_data.h
    src/level.h

    src/world.h
    src/world.cpp

    src/const/state_identifiers.h

    src/GUI/button.h
    src/GUI/button.cpp
    src/GUI/component.h
    src/GUI/component.cpp
    src/GUI/container.h
    src/GUI/container.cpp
    src/GUI/label.h
    src/GUI/label.cpp

    src/states/game_state.h
    src/states/game_state.cpp
    src/states/menu_state.h
    src/states/menu_state.cpp
    src/states/options_state.h
    src/states/options_state.cpp
    src/states/state.h
    src/states/state.cpp
    src/states/state_stack.h
    src/states/state_stack.cpp
    src/states/title_state.h
    src/states/title_state.cpp

    src/utils/input.h
    src/utils/resource_holder.h
    src/utils/resource_identifiers.h
)
target_link_libraries(main PRIVATE sfml-graphics)
target_compile_features(main PRIVATE cxx_std_17)

if(WIN32)
    add_custom_command(
        TARGET main
        COMMENT "Copy OpenAL DLL"
        PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${SFML_SOURCE_DIR}/extlibs/bin/$<IF:$<EQUAL:${CMAKE_SIZEOF_VOID_P},8>,x64,x86>/openal32.dll $<TARGET_FILE_DIR:main>
        VERBATIM)
endif()
