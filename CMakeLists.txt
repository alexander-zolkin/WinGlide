cmake_minimum_required(VERSION 3.16)

project(WinGlide VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Quick)

qt_standard_project_setup(REQUIRES 6.5)

qt_add_executable(appWinGlide
    main.cpp
)

qt_add_qml_module(appWinGlide
    URI WinGlide
    VERSION 1.0
    QML_FILES
        Main.qml
        SOURCES hotkeyhandler.h hotkeyhandler.cpp
        SOURCES windowpositioncontroller.h windowpositioncontroller.cpp
)

set_target_properties(appWinGlide PROPERTIES
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

target_link_libraries(appWinGlide
    PRIVATE Qt6::Quick
)

include(GNUInstallDirs)
install(TARGETS appWinGlide
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
