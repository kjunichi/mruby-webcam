# mruby-webcam   [![Build Status](https://travis-ci.org/kjunichi/mruby-webcam.png?branch=master)](https://travis-ci.org/kjunichi/mruby-webcam) [![Build status](https://ci.appveyor.com/api/projects/status/mowcb3ggp4bne9aq/branch/master?svg=true)](https://ci.appveyor.com/project/kjunichi/mruby-webcam/branch/master)


[![mruby-webcam](http://img.youtube.com/vi/_YFswQSockw/0.jpg)](http://www.youtube.com/watch?v=_YFswQSockw)

## install by mrbgems
- add conf.gem line to `build_config.rb`

```ruby
MRuby::Build.new do |conf|

    # ... (snip) ...

    conf.gem :github => 'kjunichi/mruby-webcam'
end
```
## example
```ruby
cam = Webcam.new

cam.capture {|img|
  # img : JPEG format(default)
  puts img.length
}

# SPC : capture
# ESC : exit
cam.start
```

### how to put ppm image

```ruby
cam = Webcam.new
cam.setFmt "ppm"
cam.capture {|img|
  # img : PPM format(P6)
  puts img
}

# SPC : capture
# ESC : exit
cam.start
```

## License
under the MIT License:
- see LICENSE file
