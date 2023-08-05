cmake_minimum_required(VERSION 3.16)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_COLOR_DIAGNOSTICS ON)

project(
	widget-test
	VERSION 1.0.0
	DESCRIPTION "Qt Widget example to show cross-compiling an app with BR"
	LANGUAGES CXX
)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core Gui Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core Gui Widgets)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTORCC ON)

add_executable(${CMAKE_PROJECT_NAME}
	main.cpp
	MainWindow.cpp
	MainWindow.hpp
)

qt_add_resources(widget-test "test"
	PREFIX
	"/"
	FILES
	"images/F_dial_background_0105.png"
	"images/dial_background_b4.png"
	"images/dial_background_fuel.png"
	"images/font.ttf"
	"images/background.png"
	"images/dial_background_fe1805.png"
	"images/dial_background_hybridfuel.png"
	"images/needle.png"
	"images/dial_background.png"
	"images/dial_background_ff1202.png"
	"images/dial_background_oil_temperature.png"
	"images/needle2.png"
	"images/dial_background_0c.png"
	"images/dial_background_ff1226.png"
	"images/dial_background_water_temperature.png"
	"images/valueFont.ttf"
	"images/dial_background_5b.png"
	"images/dial_background_ff126b.png"
	"images/display_background.png"
)

target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE
	Qt${QT_VERSION_MAJOR}::Core
	Qt${QT_VERSION_MAJOR}::Gui
	Qt${QT_VERSION_MAJOR}::Widgets
)

install(TARGETS ${CMAKE_PROJECT_NAME}
	RUNTIME DESTINATION bin
)
