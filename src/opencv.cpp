#include "mruby.h"
#include <opencv2/opencv.hpp>

using namespace std;

extern "C" int webcam_snap(mrb_state *, mrb_value);
extern "C" int webcam_start(mrb_state *, mrb_value);

#define CAM_WINDOW_NAME "Webcam window"

int webcam_snap(mrb_state *mrb, mrb_value block) {
  cv::VideoCapture cap(0); // open the default camera
  if (!cap.isOpened())     // check if we succeeded
    return -1;

  cv::Mat frame;
  cap >> frame; // get a new frame from camera

  vector<uchar> buff; // buffer for coding
  vector<int> param = vector<int>(2);
  param[0] = CV_IMWRITE_JPEG_QUALITY;
  param[1] = 95; // default(95) 0-100

  imencode(".jpg", frame, buff, param);
  mrb_value imgdata = mrb_str_new(mrb, (const char *)&buff[0], buff.size());

  // ブロックを呼び出す。
  mrb_yield(mrb, block, imgdata);

  return 0;
  // the camera will be deinitialized automatically in VideoCapture destructor
}

int webcam_start(mrb_state *mrb, mrb_value block) {
  cv::VideoCapture cap(0); // open the default camera
  if (!cap.isOpened())     // check if we succeeded
    return -1;
  for (;;) {
    cv::Mat frame;
    cap >> frame; // get a new frame from camera
    // cvtColor(frame, edges, COLOR_BGR2GRAY);
    // GaussianBlur(edges, edges, Size(7, 7), 1.5, 1.5);
    // Canny(edges, edges, 0, 30, 3);
    cv::imshow(CAM_WINDOW_NAME, frame);
    int keyCode = cv::waitKey(30);
    if (keyCode == 0x1b) {
      cv::destroyWindow(CAM_WINDOW_NAME);
      cv::waitKey(1);
      break;
    }
    if (keyCode == 0x20) {
      // save image to buffer in JPEG format.
      vector<uchar> buff; // buffer for coding
      vector<int> param = vector<int>(2);
      param[0] = CV_IMWRITE_JPEG_QUALITY;
      param[1] = 95; // default(95) 0-100

      imencode(".jpg", frame, buff, param);
      mrb_value imgdata = mrb_str_new(mrb, (const char *)&buff[0], buff.size());

      // ブロックを呼び出す。
      mrb_yield(mrb, block, imgdata);
      // return 0;
    }
  }
  return 0;
  // the camera will be deinitialized automatically in VideoCapture destructor
}
