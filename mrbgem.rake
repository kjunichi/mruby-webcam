MRuby::Gem::Specification.new('mruby-webcam') do |spec|
  spec.license = 'MIT'
  spec.authors = 'Junichi Kajiwara'
  if build.kind_of?(MRuby::CrossBuild)
    if %w(x86_64-w64-mingw32 i686-w64-mingw32).include?(build.host_target)
      spec.cxx.flags << "-I/usr/#{build.host_target}/include"
      spec.linker.flags_before_libraries << "/usr/#{build.host_target}/lib/libopencv_objdetect310.a"
      spec.linker.flags_before_libraries << "/usr/#{build.host_target}/lib/libopencv_highgui310.a"
      spec.linker.flags_before_libraries << "/usr/#{build.host_target}/lib/libopencv_videoio310.a"
      spec.linker.flags_before_libraries << "/usr/#{build.host_target}/lib/libopencv_imgcodecs310.a"
      spec.linker.flags_before_libraries << "/usr/#{build.host_target}/lib/libopencv_imgproc310.a"
      spec.linker.flags_before_libraries << "/usr/#{build.host_target}/lib/libopencv_core310.a"
      #spec.linker.flags_before_libraries << "/usr/#{build.host_target}/lib/libopencv_hal310.a"
      spec.linker.flags_before_libraries << "/usr/#{build.host_target}/lib/libIlmImf.a"
      spec.linker.flags_before_libraries << "/usr/#{build.host_target}/lib/libzlib.a"
      spec.linker.flags_before_libraries << "/usr/#{build.host_target}/lib/liblibjasper.a"
      spec.linker.flags_before_libraries << "/usr/#{build.host_target}/lib/liblibjpeg.a"
      spec.linker.flags_before_libraries << "/usr/#{build.host_target}/lib/liblibtiff.a"
      spec.linker.flags_before_libraries << "/usr/#{build.host_target}/lib/liblibwebp.a"
      spec.linker.flags_before_libraries << "/usr/#{build.host_target}/lib/liblibpng.a"
      spec.linker.flags_before_libraries << "-lvfw32 -lole32 -loleaut32 -lgdi32 -lcomdlg32 -luuid"
      spec.linker.flags_before_libraries << "/usr/#{build.host_target}/lib/libwinpthread.a"
      spec.linker.flags_before_libraries << "-static-libgcc -static-libstdc++"
    end
    if %w(i686-pc-linux-gnu x86_64-pc-linux-gnu).include?(build.host_target)
      spec.cxx.flags << "-I/usr/#{build.host_target}/include"

      spec.linker.flags_before_libraries << "/usr/#{build.host_target}/lib/libopencv_objdetect.a"
      spec.linker.flags_before_libraries << "/usr/#{build.host_target}/lib/libopencv_highgui.a"
      spec.linker.flags_before_libraries << "/usr/#{build.host_target}/lib/libopencv_videoio.a"
      spec.linker.flags_before_libraries << "/usr/#{build.host_target}/lib/libopencv_imgcodecs.a"
      spec.linker.flags_before_libraries << "/usr/#{build.host_target}/lib/libopencv_imgproc.a"
      spec.linker.flags_before_libraries << "/usr/#{build.host_target}/lib/libopencv_core.a"

      spec.linker.flags_before_libraries << "/usr/#{build.host_target}/lib/libIlmImf.a"
      spec.linker.flags_before_libraries << "/usr/#{build.host_target}/lib/liblibjasper.a"
      spec.linker.flags_before_libraries << "/usr/#{build.host_target}/lib/liblibjpeg.a"
      spec.linker.flags_before_libraries << "/usr/#{build.host_target}/lib/liblibtiff.a"
      spec.linker.flags_before_libraries << "/usr/#{build.host_target}/lib/liblibwebp.a"

      spec.linker.flags_before_libraries << "-lgtk-x11-2.0 -lgdk-x11-2.0 -latk-1.0 -lgio-2.0 -lpangoft2-1.0 -lpangocairo-1.0 -lgdk_pixbuf-2.0 -lcairo -lpango-1.0 -lfontconfig -lgobject-2.0 -lglib-2.0 -lfreetype -lpng"
      spec.linker.flags_before_libraries << "-ldl -lpthread -lz -static-libgcc -static-libstdc++"
    end
    if %w(x86_64-apple-darwin14 i386-apple-darwin14).include?(build.host_target)
      spec.cxx.flags << "-I/usr/#{build.host_target}/include"

      spec.linker.flags_before_libraries << "/usr/#{build.host_target}/lib/libopencv_objdetect.a"
      spec.linker.flags_before_libraries << "/usr/#{build.host_target}/lib/libopencv_highgui.a"
      spec.linker.flags_before_libraries << "/usr/#{build.host_target}/lib/libopencv_videoio.a"
      spec.linker.flags_before_libraries << "/usr/#{build.host_target}/lib/libopencv_imgcodecs.a"
      spec.linker.flags_before_libraries << "/usr/#{build.host_target}/lib/libopencv_imgproc.a"
      spec.linker.flags_before_libraries << "/usr/#{build.host_target}/lib/libopencv_core.a"

      spec.linker.flags_before_libraries << "/usr/#{build.host_target}/lib/libIlmImf.a"
      spec.linker.flags_before_libraries << "/usr/#{build.host_target}/lib/libzlib.a"
      spec.linker.flags_before_libraries << "/usr/#{build.host_target}/lib/liblibjasper.a"
      spec.linker.flags_before_libraries << "/usr/#{build.host_target}/lib/liblibjpeg.a"
      spec.linker.flags_before_libraries << "/usr/#{build.host_target}/lib/liblibtiff.a"
      spec.linker.flags_before_libraries << "/usr/#{build.host_target}/lib/liblibwebp.a"
      spec.linker.flags_before_libraries << "/usr/#{build.host_target}/lib/liblibpng.a"

      spec.linker.flags_before_libraries << "-framework OpenCL -framework Cocoa -framework QTKit"
      spec.linker.flags_before_libraries << "-framework QuartzCore -framework AppKit"
    end
  else
    if ENV['VisualStudioVersion'] || ENV['VSINSTALLDIR'] then
      spec.linker.flags_before_libraries << "opencv_highgui320.lib"
      spec.linker.flags_before_libraries << "opencv_videoio320.lib"
      spec.linker.flags_before_libraries << "opencv_imgcodecs320.lib"
      spec.linker.flags_before_libraries << "opencv_objdetect320.lib"
      spec.linker.flags_before_libraries << "opencv_imgproc320.lib"
      spec.linker.flags_before_libraries << "opencv_core320.lib"
      #spec.linker.flags_before_libraries << "stdc++"
    else
      if RUBY_PLATFORM =~ /darwin/i
        if File.exists?("/usr/local/opt/opencv3") then
          spec.cxx.flags << "-I/usr/local/opt/opencv3/include"
          spec.linker.flags_before_libraries << "-Wl,-rpath /usr/local/opt/opencv3/lib -L/usr/local/opt/opencv3/lib"
          spec.linker.flags_before_libraries << "-lopencv_videoio"
          spec.linker.flags_before_libraries << "-lopencv_imgcodecs"
        else
          spec.cxx.flags << "-I/usr/local/opt/opencv/include"
          spec.linker.flags_before_libraries << "-L/usr/local/opt/opencv/lib"
        end
      end
      spec.linker.flags_before_libraries << "-lopencv_objdetect"

      spec.linker.flags_before_libraries << "-lopencv_highgui"
      if File.exists?("/usr/local/lib/libopencv_videoio.so") then
        spec.linker.flags_before_libraries << "-lopencv_videoio"
        spec.linker.flags_before_libraries << "-lopencv_imgcodecs"      
      end
      spec.linker.flags_before_libraries << "-lopencv_imgproc"
      spec.linker.flags_before_libraries << "-lopencv_core"
      spec.linker.flags_before_libraries << "-lstdc++"
    end
  end
end
