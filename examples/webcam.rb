cam = Webcam.new
cam.capture {|img|
   File.open("#{Time.now.to_s.gsub!(' ','').gsub!(':','')}.jpg","wb") {
     |f| f.write img
   }
 }
cam.start
