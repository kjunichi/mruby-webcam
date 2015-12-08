# mruby-webcam   [![Build Status](https://travis-ci.org/kjunichi/mruby-webcam.png?branch=master)](https://travis-ci.org/kjunichi/mruby-webcam)

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
  # img : JPEG format
  puts img.length
}

# SPC : capture
# ESC : exit
cam.start
```

## License
under the MIT License:
- see LICENSE file
