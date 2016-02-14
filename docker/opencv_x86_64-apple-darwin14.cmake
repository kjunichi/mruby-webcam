include(CMakeForceCompiler)

SET(CMAKE_SYSTEM_NAME Darwin)

SET(CMAKE_SIZEOF_VOID_P 8)

# specify the cross compiler
SET(CMAKE_C_COMPILER   /opt/osxcross/target/bin/o64-clang)
SET(CMAKE_CXX_COMPILER /opt/osxcross/target/bin/o64-clang++)

SET(CMAKE_AR /opt/osxcross/target/bin/x86_64-apple-darwin14-ar CACHE FILEPATH "Archiver")

SET(CMAKE_OSX_SYSROOT /opt/osxcross/target/SDK/MacOSX10.10.sdk)

# set PKG_CONFIG_PATH for osxcross Compile Environment
SET(ENV{PKG_CONFIG_PATH} /opt/osxcross/target/macports/pkgs/opt/local/lib/pkgconfig)

# where is the target environment
SET(CMAKE_FIND_ROOT_PATH /usr/x86_64-apple-darwin14/ /opt/osxcross/target/macports/pkgs/opt/local ${CMAKE_OSX_SYSROOT} ${CMAKE_OSX_SYSROOT}/usr/bin )

# adjust the default behaviour of the FIND_XXX() commands:
# search headers and libraries in the target environment, search
# programs in the host environment
set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
SET(CMAKE_INSTALL_PREFIX /usr/x86_64-apple-darwin14/)
