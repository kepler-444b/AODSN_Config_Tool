cmake_minimum_required(VERSION 3.21)

project(ConfigTool VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(Qt6 REQUIRED COMPONENTS Core Gui Widgets SerialPort)

qt_standard_project_setup()

qt_add_executable(ConfigTool
    main.cpp
    mainwindow.cpp
    mainwindow.h
    mainwindow.ui

    app/app_all_list.cpp
    app/app_all_list.h
    app/app_all_list.ui
    app/app_display.cpp
    app/app_display.h
    app/app_display.ui
    app/app_protocol_set_addr.cpp
    app/app_protocol_set_addr.h
    app/app_protocol_set_config.cpp
    app/app_protocol_set_config.h
    app/app_protocol_set_net.cpp
    app/app_protocol_set_net.h
    app/app_protocol_sim_state.cpp
    app/app_protocol_sim_state.h
    app/app_sel_extend.cpp
    app/app_sel_extend.h
    app/app_sel_extend.ui
    app/app_sel_panel.cpp
    app/app_sel_panel.h
    app/app_sel_panel.ui
    app/app_sel_set_scene.cpp
    app/app_sel_set_scene.h
    app/app_sel_set_scene.ui
    app/app_sel_timer.cpp
    app/app_sel_timer.h
    app/app_sel_timer.ui
    app/app_serial.cpp
    app/app_serial.h
    app/app_serial.ui
    app/app_set_addr.cpp
    app/app_set_addr.h
    app/app_set_addr.ui
    app/app_set_config.cpp
    app/app_set_config.h
    app/app_set_config.ui
    app/app_set_net.cpp
    app/app_set_net.h
    app/app_set_net.ui
    app/common_types.h

    flow/flowlayout.cpp
    flow/flowlayout.h

    model/model_led_ex.cpp
    model/model_led_ex.h
    model/model_led_ex.ui
    model/model_panel_1key.cpp
    model/model_panel_1key.h
    model/model_panel_1key.ui
    model/model_panel_2key.cpp
    model/model_panel_2key.h
    model/model_panel_2key.ui
    model/model_panel_3key.cpp
    model/model_panel_3key.h
    model/model_panel_3key.ui
    model/model_panel_4key.cpp
    model/model_panel_4key.h
    model/model_panel_4key.ui
    model/model_panel_6key.cpp
    model/model_panel_6key.h
    model/model_panel_6key.ui
    model/model_relay_ex.cpp
    model/model_relay_ex.h
    model/model_relay_ex.ui

    resources/app.qrc
    resources/app.rc

)

target_link_libraries(ConfigTool PRIVATE
    Qt6::Core
    Qt6::Gui
    Qt6::Widgets
    Qt6::SerialPort
)

if(WIN32)
    set_target_properties(ConfigTool PROPERTIES
        WIN32_EXECUTABLE TRUE
    )
endif()

target_include_directories(ConfigTool PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})


include(GNUInstallDirs)
install(TARGETS ConfigTool
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    BUNDLE DESTINATION .
)
