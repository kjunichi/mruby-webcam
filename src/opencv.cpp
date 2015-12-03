#include <opencv2/opencv.hpp>

using namespace std;

extern "C" unsigned char *webcam_start(void);

unsigned char *webcam_start(void) {
  cv::VideoCapture cap(0); // open the default camera
  if (!cap.isOpened())     // check if we succeeded
    return NULL;
  for (;;) {
    cv::Mat frame;
    cap >> frame; // get a new frame from camera
    // cvtColor(frame, edges, COLOR_BGR2GRAY);
    // GaussianBlur(edges, edges, Size(7, 7), 1.5, 1.5);
    // Canny(edges, edges, 0, 30, 3);
    cv::imshow("Webcam feed", frame);
    int keyCode = cv::waitKey(30);
    if (keyCode == 0x1b)
      break;
    if (keyCode == 0x20) {
      // save image to buffer in JPEG format.
      vector<uchar> buff; // buffer for coding
      vector<int> param = vector<int>(2);
      param[0] = CV_IMWRITE_JPEG_QUALITY;
      param[1] = 95; // default(95) 0-100

      imencode(".jpg", frame, buff, param);
      unsigned char *imageBuf = (unsigned char *)malloc(buff.size());
      memcpy(imageBuf, &buff[0], buff.size());
      return imageBuf;
    }
  }
  return NULL;
  // the camera will be deinitialized automatically in VideoCapture destructor
}
