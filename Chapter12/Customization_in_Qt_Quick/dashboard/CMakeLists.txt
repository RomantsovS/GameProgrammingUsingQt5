cmake_minimum_required(VERSION 3.16)

project(dashboard VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Quick Widgets)
find_package(Qt6 REQUIRED COMPONENTS Core)
find_package(Qt6 REQUIRED COMPONENTS Core)

qt_standard_project_setup(REQUIRES 6.8)

qt_add_executable(appdashboard
    main.cpp
)

qt_add_qml_module(appdashboard
    URI dashboard
    VERSION 1.0
    QML_FILES
        Main.qml
        Needle.qml
        Label.qml
    SOURCES
        carinfo.h
        carinfo.cpp
        carinfoengine.h
        carinfoengine.cpp
        carinfoproxy.h
        carinfoproxy.cpp
    RESOURCES
        carinfo.ui
        qml.qrc
        dashboard.png
)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
set_target_properties(appdashboard PROPERTIES
#    MACOSX_BUNDLE_GUI_IDENTIFIER com.example.appdashboard
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

target_link_libraries(appdashboard
    PRIVATE Qt6::Quick Qt6::Widgets
)
target_link_libraries(appdashboard PRIVATE Qt6::Core)
target_link_libraries(appdashboard PRIVATE Qt6::Core)

include(GNUInstallDirs)
install(TARGETS appdashboard
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
