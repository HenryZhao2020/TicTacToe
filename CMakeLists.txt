cmake_minimum_required(VERSION 4.0)
project(TicTacToe)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(CMAKE_PREFIX_PATH "/Users/henry/Qt/6.9.2/macos/lib/cmake")

find_package(Qt6 COMPONENTS
        Core
        Gui
        Widgets
        REQUIRED
)

add_executable(TicTacToe main.cpp
        core/AppInfo.h
        core/Board.h
        core/Board.cpp
        core/Cell.h
        core/Cell.cpp
        core/GameChecker.h
        core/GameChecker.cpp
        core/GameStats.h
        core/GameStats.cpp
        core/Observer.h
        core/Serializable.h
        core/Serializable.cpp
        core/TicTacToe.h
        core/TicTacToe.cpp

        textgame/TextGame.h
        textgame/TextGame.cpp
        textgame/TextInput.h
        textgame/TextInput.cpp

        qtgame/BoardView.cpp
        qtgame/BoardView.h
        qtgame/CellView.cpp
        qtgame/CellView.h
        qtgame/GameBar.cpp
        qtgame/GameBar.h
        qtgame/QtGame.cpp
        qtgame/QtGame.h
        qtgame/Scalable.h
        qtgame/StatsView.cpp
        qtgame/StatsView.h
        qtgame/TicTacToe.qrc
        qtgame/HelpDialog.cpp
        qtgame/HelpDialog.h
)

target_include_directories(TicTacToe PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/core
        ${CMAKE_CURRENT_SOURCE_DIR}/textgame
        ${CMAKE_CURRENT_SOURCE_DIR}/qtgame
)

target_link_libraries(TicTacToe
        Qt::Core
        Qt::Gui
        Qt::Widgets
)

set_target_properties(TicTacToe PROPERTIES
        OUTPUT_NAME "Tic Tac Toe"
)
