cam = Webcam.new
cam.smile({haarcascades_path: "/usr/local/opt/opencv3/share/OpenCV/haarcascades/haarcascade_frontalface_alt.xml",
  smile_cascade_path: "/usr/local/opt/opencv3/share/OpenCV/haarcascades/haarcascade_smile.xml"}) {|img|
   File.open("#{Time.now.to_s.gsub!(' ','').gsub!(':','')}_smile.jpg","wb") {
     |f| f.write img
   }
 }
cam.start
