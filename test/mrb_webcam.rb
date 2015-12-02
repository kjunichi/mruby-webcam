##
## Webcam Test
##

assert("Webcam#hello") do
  t = Webcam.new "hello"
  assert_equal("hello", t.hello)
end

assert("Webcam#bye") do
  t = Webcam.new "hello"
  assert_equal("hello bye", t.bye)
end

assert("Webcam.hi") do
  assert_equal("hi!!", Webcam.hi)
end
