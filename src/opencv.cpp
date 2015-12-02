#include <opencv2/opencv.hpp>

extern "C" void webcam_start(void);

void webcam_start(void)
{
    cv::VideoCapture cap(0); // open the default camera
    if (!cap.isOpened())  // check if we succeeded
        return;
    for (;;)
    {
        cv::Mat frame;
        cap >> frame; // get a new frame from camera
        //cvtColor(frame, edges, COLOR_BGR2GRAY);
        //GaussianBlur(edges, edges, Size(7, 7), 1.5, 1.5);
        //Canny(edges, edges, 0, 30, 3);
        cv::imshow("Webcam feed", frame);
        if (cv::waitKey(30) >= 0) break;
    }
    // the camera will be deinitialized automatically in VideoCapture destructor

}
