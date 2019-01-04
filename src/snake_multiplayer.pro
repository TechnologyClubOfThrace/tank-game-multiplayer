TEMPLATE = app
CONFIG += console c++14
CONFIG -= app_bundle
CONFIG -= qt
CONFIG += exceptions_off #disable c++ exceptions handling to gain memory, speed and code simplicity. http://doc.qt.io/qt-5/qmake-variable-reference.html

DEFINES += PUGIXML_NO_EXCEPTIONS

HEADERS += \
    game_engine.h \
    vector2d.h \
    camera.h \
    game.h \
    viewport.h \
    scene_manager.h \
    collider2d.h \
    entity.h \
    transform_component.h \
    tank_entity.h \
    sprite_component.h \
    render_system.h \
    tank_input_component.h \
    tank_input_system.h \
    rigid_body2d_component.h \
    physics_system.h \
    shared_sprite_component.h \
    rectangle_collider2d.h \
    convex_polygon_collider2d.h \
    collider2d_collection_component.h \
    tileset.h \
    tile_entity.h \
    fps_entity.h \
    fps_system.h \
    fps_component.h \
    viewport_component.h \
    render_utils.h \
    viewport_target.h \
    zoom_input_component.h \
    zoom_input_system.h \
    bullet_entity.h

SOURCES += \
        main.cpp \
    game_engine.cpp \
    vector2d.cpp \
    camera.cpp \
    game.cpp \
    viewport.cpp \
    scene_manager.cpp \
    collider2d.cpp \
    entity.cpp \
    transform_component.cpp \
    tank_entity.cpp \
    sprite_component.cpp \
    render_system.cpp \
    tank_input_component.cpp \
    tank_input_system.cpp \
    rigid_body2d_component.cpp \
    physics_system.cpp \
    shared_sprite_component.cpp \
    rectangle_collider2d.cpp \
    convex_polygon_collider2d.cpp \
    collider2d_collection_component.cpp \
    tileset.cpp \
    tile_entity.cpp \
    fps_entity.cpp \
    fps_system.cpp \
    fps_component.cpp \
    viewport_component.cpp \
    render_utils.cpp \
    viewport_target.cpp \
    zoom_input_component.cpp \
    zoom_input_system.cpp \
    bullet_entity.cpp


win32-g++:contains(QMAKE_HOST.arch, x86_64) {
#64bit mingw selected kit
windows: LIBS += -LC:\\libs\\SDL2_mingw-2.0.9\\x86_64-w64-mingw32\\lib -lmingw32 -lSDL2main -lSDL2
windows: LIBS += -LC:\\libs\\SDL2_ttf-2.0.14-mingw\\x86_64-w64-mingw32\\lib -lSDL2_ttf
windows: LIBS += -LC:\\libs\\SDL2_image-2.0.4-mingw\\x86_64-w64-mingw32\\lib -lSDL2_image

windows: INCLUDEPATH += C:\\libs\\SDL2_mingw-2.0.9\\x86_64-w64-mingw32\\include\\SDL2
windows: INCLUDEPATH += C:\\libs\\SDL2_ttf-2.0.14-mingw\\x86_64-w64-mingw32\\include\\SDL2
windows: INCLUDEPATH += C:\\libs\\SDL2_image-2.0.4-mingw\\x86_64-w64-mingw32\\include\\SDL2
} else {
win32-g++:{
#32bit mingw selected kit
windows: LIBS += -LC:\\libs\\SDL2_mingw-2.0.9\\i686-w64-mingw32\\lib -lmingw32 -lSDL2main -lSDL2
windows: LIBS += -LC:\\libs\\SDL2_ttf-2.0.14-mingw\\i686-w64-mingw32\\lib -lSDL2_ttf
windows: LIBS += -LC:\\libs\\SDL2_image-2.0.4-mingw\\i686-w64-mingw32\\lib -lSDL2_image

windows: INCLUDEPATH += C:\\libs\\SDL2_mingw-2.0.9\\i686-w64-mingw32\\include\\SDL2
windows: INCLUDEPATH += C:\\libs\\SDL2_ttf-2.0.14-mingw\\i686-w64-mingw32\\include\\SDL2
windows: INCLUDEPATH += C:\\libs\\SDL2_image-2.0.4-mingw\\i686-w64-mingw32\\include\\SDL2
}
}


win32-msvc*:contains(QMAKE_HOST.arch, x86_64) {
#64bit msvc selected kit
windows: LIBS += -LC:\\libs\\SDL2-2.0.9\\lib\\x64 -lSDL2
windows: LIBS += -LC:\\libs\\SDL2_ttf-2.0.14\\lib\\x64 -lSDL2_ttf
windows: LIBS += -LC:\\libs\\SDL2_image-2.0.4\\lib\\x64 -lSDL2_image
CONFIG(debug, debug|release): LIBS += -LC:\\libs\\pugixml-1.9\\x64\\Debug -lpugixml
CONFIG(release, debug|release): LIBS += -LC:\\libs\\pugixml-1.9\\x64\\Release -lpugixml
} else {
#32bit msvc selected kit
windows: LIBS += -LC:\\libs\\SDL2-2.0.9\\lib\\x86 -lSDL2
windows: LIBS += -LC:\\libs\\SDL2_ttf-2.0.14\\lib\\x86 -lSDL2_ttf
windows: LIBS += -LC:\\libs\\SDL2_image-2.0.4\\lib\\x86 -lSDL2_image
CONFIG(debug, debug|release): LIBS += -LC:\\libs\\pugixml-1.9\\Debug_x86 -lpugixml
CONFIG(release, debug|release): LIBS += -LC:\\libs\\pugixml-1.9\\Release_x86 -lpugixml
}

win32-msvc*{
#32bit or 64bit msvc selected kit
windows: INCLUDEPATH += C:\\libs\\SDL2-2.0.9\\include
windows: INCLUDEPATH += C:\\libs\\SDL2_ttf-2.0.14\\include
windows: INCLUDEPATH += C:\\libs\\SDL2_image-2.0.4\\include
windows: INCLUDEPATH += C:\\libs\\pugixml-1.9\\src
}


mac: LIBS += -L$$/usr/local/Cellar/sdl2/2.0.9/lib -lSDL2
mac: LIBS += -L$$/usr/local/Cellar/sdl2_image/2.0.4/lib -lSDL2_image
mac: LIBS += -L$$/usr/local/Cellar/sdl2_ttf/2.0.14/lib -lSDL2_ttf
mac: LIBS += -L$$/usr/local/Cellar/pugixml/1.9/lib/pugixml-1.9 -lpugixml
#mac: LIBS += -L$$/usr/local/Cellar/sdl2_mixer/2.0.4/lib -lSDL2_mixer

mac:INCLUDEPATH += /usr/local/Cellar/sdl2/2.0.9/include/SDL2
mac:INCLUDEPATH += /usr/local/Cellar/sdl2_image/2.0.4/include/SDL2
mac:INCLUDEPATH += /usr/local/Cellar/sdl2_ttf/2.0.14/include/SDL2
mac:INCLUDEPATH += /usr/local/Cellar/pugixml/1.9/include/pugixml-1.9
#INCLUDEPATH += /usr/local/Cellar/sdl2_mixer/2.0.4/include/SDL2
