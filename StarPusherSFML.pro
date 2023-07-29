linux {
    CONFIG += link_pkgconfig
    PKGCONFIG += sfml-window sfml-graphics sfml-system
}


SOURCES += \
    src/GUI/button.cpp \
    src/GUI/component.cpp \
    src/GUI/container.cpp \
    src/GUI/label.cpp \
    src/application.cpp \
    src/main.cpp \
    src/states/game_state.cpp \
    src/states/menu_state.cpp \
    src/states/options_state.cpp \
    src/states/state.cpp \
    src/states/state_stack.cpp \
    src/states/title_state.cpp \
    src/world.cpp

HEADERS += \
    src/GUI/button.h \
    src/GUI/component.h \
    src/GUI/container.h \
    src/GUI/label.h \
    src/level.h \
    src/application.h \
    src/circle.h \
    src/const/state_identifiers.h \
    src/game_data.h \
    src/states/game_state.h \
    src/states/menu_state.h \
    src/states/options_state.h \
    src/states/state.h \
    src/states/state_stack.h \
    src/states/title_state.h \
    src/unit.h \
    src/utils/input.h \
    src/utils/resource_holder.h \
    src/utils/resource_identifiers.h \
    src/world.h
