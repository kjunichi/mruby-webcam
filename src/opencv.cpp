#include "mruby.h"
#include "mruby/data.h"
#include "mruby/string.h"
#include "mruby/variable.h"

#include "mrb_webcam.h"

#include <opencv2/opencv.hpp>

#include <opencv2/videoio/legacy/constants_c.h>
#include <opencv2/imgcodecs/legacy/constants_c.h>

using namespace std;

MRB_BEGIN_DECL
int
webcam_snap(mrb_state *, mrb_value, mrb_value);
int
webcam_start(mrb_state *, mrb_value);
int
webcam_each(mrb_state *, mrb_value);
int
webcam_close(mrb_state *, mrb_value);
MRB_END_DECL

#define CAM_WINDOW_NAME "Webcam window"

static void
setCamSize(mrb_state *mrb, mrb_value self, cv::VideoCapture &cap)
{
  int width = -1;
  int height = -1;
  mrb_value v = mrb_iv_get(mrb, self, mrb_intern_lit(mrb, "@width"));
  if (mrb_fixnum_p(v)) {
    width = mrb_fixnum(v);
  }
  v = mrb_iv_get(mrb, self, mrb_intern_lit(mrb, "@height"));
  if (mrb_fixnum_p(v)) {
    height = mrb_fixnum(v);
  }
  if (width > 0) {
    cap.set(CV_CAP_PROP_FRAME_WIDTH, width);
  }
  if (height > 0) {
    cap.set(CV_CAP_PROP_FRAME_HEIGHT, height);
  }
}

static mrb_value
getimage(mrb_state *mrb, cv::Mat mat)
{
  vector<uchar> buff; // buffer for coding
  vector<int> param = vector<int>(2);
  param[0] = CV_IMWRITE_JPEG_QUALITY;
  param[1] = 95; // default(95) 0-100

  imencode(".jpg", mat, buff, param);
  return mrb_str_new(mrb, (const char *)&buff[0], buff.size());
}

static mrb_value
getimageByType(mrb_state *mrb, cv::Mat mat, string type)
{
  vector<uchar> buff; // buffer for coding
  vector<int> param = vector<int>(2);
  param[0] = CV_IMWRITE_JPEG_QUALITY;
  param[1] = 95; // default(95) 0-100

  imencode(type.c_str(), mat, buff, param);
  return mrb_str_new(mrb, (const char *)&buff[0], buff.size());
}

static bool gIsOpenCap = false;
static cv::VideoCapture gCap;

int
webcam_close(mrb_state *mrb, mrb_value self)
{
  if (gIsOpenCap) {
    gCap.release();
    gIsOpenCap = false;
  }

  return 0;
}

int
webcam_snap(mrb_state *mrb, mrb_value self, mrb_value block)
{
  if (!gIsOpenCap) {
    gCap.open(0); // open the default camera
    setCamSize(mrb, self, gCap);
    if (!gCap.isOpened()) // check if we succeeded
      return -1;

    gIsOpenCap = true;
  }
  cv::Mat frame;
  gCap >> frame; // get a new frame from camera

  // decide image type
  mrb_value fmtVal = mrb_iv_get(mrb, self, mrb_intern_lit(mrb, "@fmt"));
  string fmt(RSTRING_PTR(fmtVal), RSTRING_LEN(fmtVal));

  // ブロックを呼び出す。
  mrb_yield(mrb, block, getimageByType(mrb, frame, fmt));

  return 0;
}

int
faceLoop(mrb_state *mrb, mrb_value self, mrb_value block, mrb_value faceBlock, mrb_value smileBlock,
         string haarcascade_path)
{
  cv::CascadeClassifier cascade, smileCascade;

  if (!cascade.load(haarcascade_path)) {
    cerr << "ERROR: Could not load face cascade" << endl;
    return -1;
  }
  if (!mrb_nil_p(smileBlock)) {
    mrb_value smileVal = mrb_iv_get(mrb, self, mrb_intern_lit(mrb, "@smile_cascade_path"));
    string smile_cascade_path(RSTRING_PTR(smileVal), RSTRING_LEN(smileVal));

    if (!smileCascade.load(smile_cascade_path)) {
      cerr << "ERROR: Could not load smile cascade" << endl;
      return -1;
    }
  }
  cv::VideoCapture cap;
  mrb_webcam_data *data = (mrb_webcam_data*) DATA_PTR(self);
  if (data != nullptr)
    cap = cv::VideoCapture(data->str);
  else
    cap = cv::VideoCapture(0); // open the default camera
  if (!cap.isOpened())     // check if we succeeded
    return -1;

  for (;;) {
    cv::Mat frame;
    cap >> frame; // get a new frame from camera

    cv::imshow(CAM_WINDOW_NAME, frame);

    int keyCode = cv::waitKey(30);
    if (keyCode == 0x1b) {
      cv::destroyWindow(CAM_WINDOW_NAME);
      cv::waitKey(1);
      break;
    }
    if (keyCode == 0x20) {
      // save image to buffer in JPEG format.
      // ブロックを呼び出す。
      mrb_yield(mrb, block, getimage(mrb, frame));
      // return 0;
    }
    // face detect
    cv::Mat gray, smallImg;
    cvtColor(frame, gray, cv::COLOR_BGR2GRAY);
    double fx = 0.5;
    cv::resize(gray, smallImg, cv::Size(), fx, fx, cv::INTER_LINEAR);
    cv::equalizeHist(smallImg, smallImg);
    vector<cv::Rect> faces;
    cascade.detectMultiScale(smallImg, faces, 1.1, 2,
                             0
                               //|CASCADE_FIND_BIGGEST_OBJECT
                               //|CASCADE_DO_ROUGH_SEARCH
                               | cv::CASCADE_SCALE_IMAGE,
                             cv::Size(30, 30));
    for (size_t i = 0; i < faces.size(); i++) {
      cv::Rect r = faces[i];
      cout << r.x << ", " << r.width << endl;
      cout << r.y << ", " << r.height << endl;

      if (!mrb_nil_p(faceBlock)) {
        // 顔検出のコールバックが定義されている場合
        cv::Mat roi(frame, cv::Rect(cvRound(r.x * (1 / fx)), cvRound(r.y * (1 / fx)),
                                    cvRound(r.width * (1 / fx)), cvRound((r.height) * (1 / fx))));

        // ブロックを呼び出す。
        mrb_yield(mrb, faceBlock, getimage(mrb, roi));
      }
      if (!mrb_nil_p(smileBlock)) {
        // 笑顔検出のコールバックが登録されている場合
        cv::Mat smallImgROI;
        vector<cv::Rect> smileObjects;
        const int half_height = cvRound((float)r.height / 2);
        r.y = r.y + half_height;
        r.height = half_height - 1;
        smallImgROI = smallImg(r);
        smileCascade.detectMultiScale(smallImgROI, smileObjects, 1.1, 0,
                                      0
                                        //|CASCADE_FIND_BIGGEST_OBJECT
                                        //|CASCADE_DO_ROUGH_SEARCH
                                        //|CASCADE_DO_CANNY_PRUNING
                                        | cv::CASCADE_SCALE_IMAGE,
                                      cv::Size(30, 30));
        const int smile_neighbors = (int)smileObjects.size();
        static int max_neighbors = -1;
        static int min_neighbors = -1;
        if (min_neighbors == -1)
          min_neighbors = smile_neighbors;
        max_neighbors = MAX(max_neighbors, smile_neighbors);

        float intensityZeroOne =
          ((float)smile_neighbors - min_neighbors) / (max_neighbors - min_neighbors + 1);
        cout << "intensityZeroOne = " << intensityZeroOne << endl;
        if (intensityZeroOne > 0.8) {
          mrb_yield(mrb, smileBlock, getimage(mrb, frame));
        }
      }
    }
  }
  // the camera will be deinitialized automatically in VideoCapture destructor
  return 0;
}

int
simpleLoop(mrb_state *mrb, mrb_value block, mrb_value self)
{
  cv::VideoCapture cap;

  mrb_webcam_data *data = (mrb_webcam_data*) DATA_PTR(self);
  if (data != nullptr)
    cap = cv::VideoCapture(data->str);
  else
    cap = cv::VideoCapture(0); // open the default camera
  setCamSize(mrb, self, cap);
  if (!cap.isOpened()) // check if we succeeded
    return -1;
  for (;;) {
    cv::Mat frame;
    cap >> frame; // get a new frame from camera
    // cvtColor(frame, edges, COLOR_BGR2GRAY);
    // GaussianBlur(edges, edges, Size(7, 7), 1.5, 1.5);
    // Canny(edges, edges, 0, 30, 3);
    if(!frame.empty()) {
      cv::imshow(CAM_WINDOW_NAME, frame);
    }
    int keyCode = cv::waitKey(30);
    if (keyCode == 0x1b) {
      cap.release();
      cv::waitKey(10);
      cv::destroyWindow(CAM_WINDOW_NAME);
      cv::waitKey(1);
      break;
    }
    if (keyCode == 0x20) {
      // decide image type
      mrb_value fmtVal = mrb_iv_get(mrb, self, mrb_intern_lit(mrb, "@fmt"));
      string fmt(RSTRING_PTR(fmtVal), RSTRING_LEN(fmtVal));

      // save image to buffer in JPEG format.

      // ブロックを呼び出す。
      mrb_yield(mrb, block, getimageByType(mrb, frame, fmt));
      // return 0;
    }
  }
  // the camera will be deinitialized automatically in VideoCapture destructor
  return 0;
}

int
webcam_start(mrb_state *mrb, mrb_value self)
{

  mrb_value block = mrb_iv_get(mrb, self, mrb_intern_lit(mrb, "@capture_cb"));
  mrb_value faceBlock = mrb_iv_get(mrb, self, mrb_intern_lit(mrb, "@face_cb"));
  mrb_value smileBlock = mrb_iv_get(mrb, self, mrb_intern_lit(mrb, "@smile_cb"));
  mrb_value haarVal = mrb_iv_get(mrb, self, mrb_intern_lit(mrb, "@haarcascade_path"));
  string haarcascade_path(RSTRING_PTR(haarVal), RSTRING_LEN(haarVal));

  if (!mrb_nil_p(faceBlock)) {
    return faceLoop(mrb, self, block, faceBlock, smileBlock, haarcascade_path);
  }
  if (!mrb_nil_p(smileBlock)) {
    return faceLoop(mrb, self, block, faceBlock, smileBlock, haarcascade_path);
  }
  return simpleLoop(mrb, block, self);
}

int
webcam_each(mrb_state *mrb, mrb_value self)
{
  mrb_value block = mrb_iv_get(mrb, self, mrb_intern_lit(mrb, "@capture_cb"));

  cv::VideoCapture cap;

  mrb_webcam_data *data = (mrb_webcam_data*) DATA_PTR(self);
  if (data != nullptr)
    cap = cv::VideoCapture(data->str);
  else
    cap = cv::VideoCapture(0); // open the default camera
  setCamSize(mrb, self, cap);
  if (!cap.isOpened()) // check if we succeeded
    return -1;
  for (;;) {
    cv::Mat frame;
    cap >> frame; // get a new frame from camera
    if(!frame.empty()) {
      cv::imshow(CAM_WINDOW_NAME, frame);
    }
    // decide image type
    mrb_value fmtVal = mrb_iv_get(mrb, self, mrb_intern_lit(mrb, "@fmt"));
    string fmt(RSTRING_PTR(fmtVal), RSTRING_LEN(fmtVal));
    // ブロックを呼び出す。
    mrb_value ret = mrb_yield(mrb, block, getimageByType(mrb, frame, fmt));
	if (mrb_type(ret) == MRB_TT_FALSE) {
      break;
    }
  }
  return 0;
}
