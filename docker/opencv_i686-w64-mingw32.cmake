set(CMAKE_SYSTEM_NAME Windows)

# specify the cross compiler
set(CMAKE_C_COMPILER   /usr/bin/i686-w64-mingw32-gcc)
set(CMAKE_CXX_COMPILER /usr/bin/i686-w64-mingw32-g++)
set(CMAKE_RC_COMPILER /usr/bin/i686-w64-mingw32-windres)

# set PKG_CONFIG_PATH for MinGW Cross Compile Environment
set(ENV{PKG_CONFIG_PATH} /usr/i686-w64-mingw32/lib/pkgconfig)

# where is the target environment
set(CMAKE_FIND_ROOT_PATH /usr/i686-w64-mingw32/)
