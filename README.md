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
p Webcam.hi
#=> "hi!!"
t = Webcam.new "hello"
p t.hello
#=> "hello"
p t.bye
#=> "hello bye"
```

## License
under the MIT License:
- see LICENSE file
