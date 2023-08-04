# qt-gui-test
To start, build your buildroot with Qt5 or Qt6 and enable GUI/Widgets.

From there, the easiest way to work with this is using CMake presets.

Adjust the CmakePresets.json file, adjust the CMAKE_TOOLCHAIN_FILE to point to your buildroot folder to get the correct toolchain file.

Now run "cmake --preset debug" and then "cmake --build build-debug" and your executable should be ready!
