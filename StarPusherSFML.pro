linux {
    CONFIG += link_pkgconfig
    PKGCONFIG += sfml-window sfml-graphics sfml-system
}


SOURCES += \
    src/application.cpp \
    src/main.cpp \
    src/states/game_state.cpp \
    src/states/state.cpp \
    src/states/state_stack.cpp \
    src/world.cpp

HEADERS += \
    src/level.h \
    src/application.h \
    src/circle.h \
    src/const/state_identifiers.h \
    src/game_data.h \
    src/states/game_state.h \
    src/states/state.h \
    src/states/state_stack.h \
    src/unit.h \
    src/utils/resource_holder.h \
    src/utils/resource_identifiers.h \
    src/world.h
