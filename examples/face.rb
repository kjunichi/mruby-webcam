cam = Webcam.new
cam.face({haarcascades_path: "/usr/local/opt/opencv3/share/OpenCV/haarcascades/haarcascade_frontalface_alt.xml"}) {|img|
   File.open("#{Time.now.to_s.gsub!(' ','').gsub!(':','')}_face.jpg","wb") {
     |f| f.write img
   }
 }
cam.start
