cmake_minimum_required(VERSION 3.16)

project(action_game VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Quick)

qt_standard_project_setup(REQUIRES 6.8)

qt_add_executable(action_game
    main.cpp
)

qt_add_qml_module(action_game
    URI action_game
    VERSION 1.0
    QML_FILES
        Main.qml
    RESOURCES
        qml.qrc
        images/grass.png
        images/trees.png
        images/sky.png
        QML_FILES Player.qml
        RESOURCES images/elephant.png
        QML_FILES Coin.qml
        RESOURCES images/walking_1.png images/walking_2.png images/walking_3.png images/walking_4.png images/walking_5.png images/walking_6.png images/walking_7.png
        RESOURCES images/sprite.png
        QML_FILES ParallaxScene.qml
        QML_FILES ParallaxLayer.qml
        QML_FILES collisions.js
        QML_FILES coins.js
)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
set_target_properties(action_game PROPERTIES
#    MACOSX_BUNDLE_GUI_IDENTIFIER com.example.action_game
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

target_link_libraries(action_game
    PRIVATE Qt6::Quick
)

include(GNUInstallDirs)
install(TARGETS action_game
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
