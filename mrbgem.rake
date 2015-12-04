MRuby::Gem::Specification.new('mruby-webcam') do |spec|
  spec.license = 'MIT'
  spec.authors = 'Junichi Kajiwara'
  if build.kind_of?(MRuby::CrossBuild) && %w(x86_64-w64-mingw32 i686-w64-mingw32).include?(build.host_target)
    spec.cxx.flags << "-I/usr/#{build.host_target}/include"
    spec.linker.flags_before_libraries << "/usr/#{build.host_target}/lib/libopencv_highgui300.a"
    spec.linker.flags_before_libraries << "/usr/#{build.host_target}/lib/libopencv_videoio300.a" 
    spec.linker.flags_before_libraries << "/usr/#{build.host_target}/lib/libopencv_imgcodecs300.a"
    spec.linker.flags_before_libraries << "/usr/#{build.host_target}/lib/libopencv_imgproc300.a" 
    spec.linker.flags_before_libraries << "/usr/#{build.host_target}/lib/libopencv_core300.a" 
    spec.linker.flags_before_libraries << "/usr/#{build.host_target}/lib/libopencv_hal300.a" 
    spec.linker.flags_before_libraries << "/usr/#{build.host_target}/lib/libIlmImf.a" 
    spec.linker.flags_before_libraries << "/usr/#{build.host_target}/lib/libzlib.a" 
    spec.linker.flags_before_libraries << "/usr/#{build.host_target}/lib/liblibjasper.a"
    spec.linker.flags_before_libraries << "/usr/#{build.host_target}/lib/liblibjpeg.a" 
    spec.linker.flags_before_libraries << "/usr/#{build.host_target}/lib/liblibtiff.a"
    spec.linker.flags_before_libraries << "/usr/#{build.host_target}/lib/liblibwebp.a" 
    spec.linker.flags_before_libraries << "/usr/#{build.host_target}/lib/liblibpng.a" 
    spec.linker.flags_before_libraries << "-lvfw32 -lole32 -loleaut32 -lgdi32 -lcomdlg32 -luuid"
    spec.linker.flags_before_libraries << "-static-libgcc -static-libstdc++"
  else
    if RUBY_PLATFORM =~ /darwin/i
      if File.exists?("/usr/local/opt/opencv3") then
        spec.cxx.flags << "-I/usr/local/opt/opencv3/include"
        spec.linker.flags_before_libraries << "-L/usr/local/opt/opencv3/lib"
        spec.linker.flags_before_libraries << "-lopencv_videoio"
        spec.linker.flags_before_libraries << "-lopencv_imgcodecs"
      else
        spec.cxx.flags << "-I/usr/local/opt/opencv/include"
        spec.linker.flags_before_libraries << "-L/usr/local/opt/opencv/lib"
      end
    end 
    spec.linker.flags_before_libraries << "-lopencv_imgproc"
    spec.linker.flags_before_libraries << "-lopencv_highgui"
    #spec.linker.flags_before_libraries << "-lopencv_videoio"
    #spec.linker.flags_before_libraries << "-lpencv_imgproc"
    spec.linker.flags_before_libraries << "-lopencv_core"
  end
end
