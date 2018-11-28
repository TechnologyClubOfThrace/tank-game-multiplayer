TEMPLATE = app
CONFIG += console c++14
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        main.cpp \
    game_engine.cpp \
    texture_wrapper.cpp \
    tile.cpp \
    sprite_sheet.cpp \
    tile_map.cpp \
    sprite.cpp \
    level.cpp \
    snake.cpp \
    snake_food.cpp \
    vector2d.cpp \
    vector2d_angle.cpp \
    bullet.cpp \
    fpscounter.cpp \
    keystate.cpp \
    game_object.cpp \
    camera.cpp \
    game.cpp \
    viewport.cpp


mac: LIBS += -L$$/usr/local/Cellar/sdl2/2.0.8/lib -lSDL2
mac: LIBS += -L$$/usr/local/Cellar/sdl2_image/2.0.4/lib -lSDL2_image
mac: LIBS += -L$$/usr/local/Cellar/sdl2_ttf/2.0.14/lib -lSDL2_ttf
#mac: LIBS += -L$$/usr/local/Cellar/sdl2_mixer/2.0.4/lib -lSDL2_mixer

INCLUDEPATH += /usr/local/Cellar/sdl2/2.0.8/include/SDL2
INCLUDEPATH += /usr/local/Cellar/sdl2_image/2.0.4/include/SDL2
INCLUDEPATH += /usr/local/Cellar/sdl2_ttf/2.0.14/include/SDL2
#INCLUDEPATH += /usr/local/Cellar/sdl2_mixer/2.0.4/include/SDL2

HEADERS += \
    game_engine.h \
    texture_wrapper.h \
    tile.h \
    sprite_sheet.h \
    tile_map.h \
    sprite.h \
    level.h \
    snake.h \
    snake_food.h \
    vector2d.h \
    vector2d_angle.h \
    bullet.h \
    fpscounter.h \
    keystate.h \
    game_object.h \
    camera.h \
    game.h \
    viewport.h
