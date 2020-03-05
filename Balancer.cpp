
#include "Balancer.h"

#include <iostream>
#include <vector>

using namespace std;


void ballDetect(){

    cv::VideoCapture cam(0);
    cv::Mat frame, image, imgHSV, imgRGB;

    int low_H = 45 , high_H = 85;
    int low_S = 40 , high_S = 255;
    int low_V = 55  , high_V = 255;

        cv::namedWindow("Control"); //create a window called "Control"

    //Create trackbars in "Control" window
     cv::createTrackbar("LowH", "Control", &low_H, 179); //Hue (0 - 179)
     cv::createTrackbar("HighH", "Control", &high_H, 179);

     cv::createTrackbar("LowS", "Control", &low_S, 255); //Saturation (0 - 255)
     cv::createTrackbar("HighS", "Control", &high_S, 255);

     cv::createTrackbar("LowV", "Control", &low_V, 255); //Value (0 - 255)
     cv::createTrackbar("HighV", "Control", &high_V, 255);

    while(cam.isOpened())
    {
        cam >> frame;

        cv::cvtColor(frame, imgHSV, 40); //Convert the captured frame from BGR to HSV
        cvtColor(frame, imgRGB, 2);

        cv::Mat mask1, mask2;
        cv::inRange(imgHSV, cv::Scalar(low_H,low_S,low_V), cv::Scalar(high_H,high_S,high_V), image);

        //morphological opening (remove small objects from the foreground)
        cv::erode(image, image, getStructuringElement(2, cv::Size(5, 5)) );
        cv::dilate( image, image, getStructuringElement(2, cv::Size(5, 5)) );

        //morphological closing (fill small holes in the foreground)
        cv::dilate( image, image, getStructuringElement(2, cv::Size(5, 5)) );
        cv::erode(image, image, getStructuringElement(2, cv::Size(5, 5)) );

        cv::circle(image, findCenter(image), 50, cv::Scalar(255,0,0),3);


        //cv::imshow("RGB", imgRGB);
        cv::imshow("HSV", imgHSV);
        cv::imshow("Img", image);
        //cv::imshow("Cam", frame);
        cv::waitKey(10);
    }


}
cv::Mat camera(){

    cv::VideoCapture cam(0);
    cv::Mat frame;

    //while(cam.isOpened())
    {
        cam >> frame;

    }

    return frame;
}

cv::Point findCenter(cv::Mat img){

    cv::Mat bin;
    cv::Point center(-1,-1);

    cv::threshold(img,bin,100,255, 0);

    cv::Moments m = cv::moments(bin, true);

    if(m.m00 != 0)
    {
        center.x = m.m10/m.m00;
        center.y = m.m01/m.m00;
    }
    cout << center.x << "x" <<center.y <<endl;

    return center;
}



