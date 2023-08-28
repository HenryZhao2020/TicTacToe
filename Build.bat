@echo off
mkdir Build
cd Build
qmake "../TicTacToe.pro"
mingw32-make
"release/Tic Tac Toe"