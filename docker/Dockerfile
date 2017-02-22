FROM hone/mruby-cli
RUN apt-get update && apt-get install -y mingw-w64-tools cmake cmake-curses-gui apt-file wget
COPY opencv_i686-w64-mingw32.cmake /root/src/
COPY opencv_x86_64-w64-mingw32.cmake /root/src/
COPY OpenCVCompilerOptions.cmake.patch /root/src/

RUN cd /root/src && git clone https://github.com/Itseez/opencv.git && cd opencv && mkdir build \
  && git checkout 3.1.0 \
  && patch -p1 < /root/src/OpenCVCompilerOptions.cmake.patch && cd build \
  && cmake -DCMAKE_TOOLCHAIN_FILE=/root/src/opencv_i686-w64-mingw32.cmake -DWITH_IPP=OFF -DBUILD_SHARED_LIBS=OFF  .. \
  && make -j4 && make install && cp -r install/include/* /usr/i686-w64-mingw32/include/ \
  && cp -r install/lib/* /usr/i686-w64-mingw32/lib/ && cp 3rdparty/lib/* /usr/i686-w64-mingw32/lib
RUN cd /root/src/opencv && rm -rf build && mkdir build \
  && cd build && cmake -DCMAKE_TOOLCHAIN_FILE=/root/src/opencv_x86_64-w64-mingw32.cmake  -DWITH_IPP=OFF -DBUILD_SHARED_LIBS=OFF  .. \
  && make -j4 && make install && cp -r install/include/* /usr/x86_64-w64-mingw32/include/ \
  && cp -r install/lib/* /usr/x86_64-w64-mingw32/lib/ && cp 3rdparty/lib/* /usr/x86_64-w64-mingw32/lib \
  && cd .. && rm -rf build

COPY opencv_x86_64-apple-darwin14.cmake /root/src/
COPY Darwin.cmake /usr/share/cmake-2.8/Modules/Platform/
RUN cd /root/src/opencv && rm -rf build && mkdir build \
  && cd build && cmake -DCMAKE_TOOLCHAIN_FILE=/root/src/opencv_x86_64-apple-darwin14.cmake  -DWITH_IPP=OFF -DBUILD_SHARED_LIBS=OFF  .. \
  && make -j4 && make install \
  && cp 3rdparty/lib/* /usr/x86_64-apple-darwin14/lib \
  && cd .. && rm -rf build
COPY opencv_i386-apple-darwin14.cmake /root/src/
RUN cd /root/src/opencv && rm -rf build && mkdir build \
  && cd build && cmake -DCMAKE_TOOLCHAIN_FILE=/root/src/opencv_i386-apple-darwin14.cmake  -DWITH_IPP=OFF -DBUILD_SHARED_LIBS=OFF  .. \
  && make -j4 && make install \
  && cp 3rdparty/lib/* /usr/i386-apple-darwin14/lib \
  && cd .. && rm -rf build

RUN mkdir -p /usr/i686-pc-linux-gnu/lib && ln -s /usr/include/x86_64-linux-gnu/zconf.h /usr/include
RUN dpkg --add-architecture i386 && apt-get update &&apt-get install libgtk2.0-dev:i386 -y --no-install-recommends
RUN cd /root/src/opencv && rm -rf build && mkdir build \
  && cd build && cmake -DCMAKE_INSTALL_PREFIX=/usr/i686-pc-linux-gnu -DCMAKE_C_FLAGS=-m32 -DCMAKE_CXX_FLAGS=-m32  -DWITH_IPP=OFF -DBUILD_SHARED_LIBS=OFF  .. \
  && make -j4 && make install \
  && cp 3rdparty/lib/* /usr/i686-pc-linux-gnu/lib \
  && cd .. && rm -rf build
RUN apt-get install libgtk2.0-dev -y --no-install-recommends
RUN cd /root/src/opencv && rm -rf build && mkdir build \
  && cd build && cmake -DCMAKE_INSTALL_PREFIX=/usr/x86_64-pc-linux-gnu -DWITH_IPP=OFF -DBUILD_SHARED_LIBS=OFF  .. \
  && make -j4 && make install \
  && cp 3rdparty/lib/* /usr/x86_64-pc-linux-gnu/lib \
  && cd .. && rm -rf build

RUN \
ln -snf /usr/lib/i386-linux-gnu/libgtk-x11-2.0.so.0 /usr/lib/i386-linux-gnu/libgtk-x11-2.0.so \
&& ln -snf /usr/lib/i386-linux-gnu/libgdk-x11-2.0.so.0 /usr/lib/i386-linux-gnu/libgdk-x11-2.0.so \
&& ln -snf /usr/lib/i386-linux-gnu/libatk-1.0.so.0 /usr/lib/i386-linux-gnu/libatk-1.0.so \
&& ln -snf /usr/lib/i386-linux-gnu/libgio-2.0.so.0 /usr/lib/i386-linux-gnu/libgio-2.0.so \
&& ln -snf /usr/lib/i386-linux-gnu/libpangocairo-1.0.so.0 /usr/lib/i386-linux-gnu/libpangocairo-1.0.so \
&& ln -snf /usr/lib/i386-linux-gnu/libcairo.so.2 /usr/lib/i386-linux-gnu/libcairo.so \
&& ln -snf /usr/lib/i386-linux-gnu/libpangoft2-1.0.so.0 /usr/lib/i386-linux-gnu/libpangoft2-1.0.so \
&& ln -snf /usr/lib/i386-linux-gnu/libpango-1.0.so.0 /usr/lib/i386-linux-gnu/libpango-1.0.so \
&& ln -snf /usr/lib/i386-linux-gnu/libgdk_pixbuf-2.0.so.0 /usr/lib/i386-linux-gnu/libgdk_pixbuf-2.0.so \
&& ln -snf /usr/lib/i386-linux-gnu/libfontconfig.so.1 /usr/lib/i386-linux-gnu/libfontconfig.so \
&& ln -snf /lib/i386-linux-gnu/libglib-2.0.so.0 /lib/i386-linux-gnu/libglib-2.0.so \
&& ln -snf /usr/lib/i386-linux-gnu/libfreetype.so.6 /usr/lib/i386-linux-gnu/libfreetype.so \
&& ln -snf /usr/lib/i386-linux-gnu/libfontconfig.so.1 /usr/lib/i386-linux-gnu/libfontconfig.so \
&& ln -snf /usr/lib/i386-linux-gnu/libpng12.so.0 /usr/lib/i386-linux-gnu/libpng12.so \
&& ln -snf /usr/lib/i386-linux-gnu/libpng12.so.0 /usr/lib/i386-linux-gnu/libpng.so \
&& ln -snf /usr/lib/i386-linux-gnu/libgobject-2.0.so.0 /usr/lib/i386-linux-gnu/libgobject-2.0.so
