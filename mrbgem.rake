MRuby::Gem::Specification.new('mruby-webcam') do |spec|
  spec.license = 'MIT'
  spec.authors = 'Junichi Kajiwara'
  if RUBY_PLATFORM =~ /darwin/i
    if File.exists?("/usr/local/opt/opencv3") then
      spec.cxx.flags << "-I/usr/local/opt/opencv3/include"
      spec.linker.flags_before_libraries << "-L/usr/local/opt/opencv3/lib"
      spec.linker.flags_before_libraries << "-lopencv_videoio"
    else
      spec.cxx.flags << "-I/usr/local/opt/opencv/include"
      spec.linker.flags_before_libraries << "-L/usr/local/opt/opencv/lib"
    end
  end
  spec.linker.flags_before_libraries << "-lopencv_highgui"
  #spec.linker.flags_before_libraries << "-lopencv_videoio"
  #spec.linker.flags_before_libraries << "-lopencv_imgcodecs"
  #spec.linker.flags_before_libraries << "-lpencv_imgproc"
  spec.linker.flags_before_libraries << "-lopencv_core"
end
