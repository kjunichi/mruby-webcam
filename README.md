# mruby-webcam   [![Build Status](https://travis-ci.org/kjunichi/mruby-webcam.png?branch=master)](https://travis-ci.org/kjunichi/mruby-webcam)
Webcam class
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
cam.start
```

## License
under the MIT License:
- see LICENSE file
