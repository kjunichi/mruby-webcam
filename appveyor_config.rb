MRuby::Build.new do |conf|
  toolchain :visualcpp
  conf.gembox 'default'
  conf.gem '../mruby-webcam'
  conf.enable_test
end
