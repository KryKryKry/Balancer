/***************************************************************
 * Name:      BalancerProg.h
 * Purpose:   Main source of aplication
 * Author:    Dawid P, Krystian L
 * Created:   2019-07-24
 **************************************************************/
#ifndef BALANCERPROG_H
#define BALANCERPROG_H

#include <string> // Console
#include <vector> // Console

/* OpenCV library */ /// !!! SPRAWDZIĆ CZY WSZYSTKIE SĄ POTRZEBNE !!! ///
#include "opencv2/opencv.hpp"   // Camera
#include "opencv2/core.hpp"     // Camera
#include "opencv2/highgui.hpp"  // Camera
#include "opencv2/imgproc.hpp"  // Camera

/// !!! SPRAWDZIĆ CZY WSZYSTKIE SĄ POTRZEBNE !!! ///
// #include <stdio.h>		//SerialPort
// #include <stdlib.h>		//SerialPort
// #include <stdint.h>		//SerialPort
// #include <string.h>		//SerialPort
#include <unistd.h>		//SerialPort
#include <fcntl.h>		//SerialPort
// #include <errno.h>		//SerialPort
#include <termios.h>	//SerialPort
// #include <sys/ioctl.h>	//SerialPort
// #include <getopt.h>		//SerialPort

namespace Color {

    struct HSV{unsigned char h; unsigned char s; unsigned char v; };
    struct RGB{unsigned char r; unsigned char g; unsigned char b; };

    Color::HSV toHSV( int red, int green, int blue );
    //Color::HSV toHSV( Color::RGB );
    //Color::RGB toRGB( int hue, int saturation, int value );
    Color::RGB toRGB( Color::HSV );
}

class Console{
protected:
    unsigned int                hSpace;
    unsigned int                vSpace;
    std::vector<std::string>    consoleLog;
private:
    void makeCommand(std::string newCommand);
public:
    void sendSpace(unsigned int h, unsigned int v);
    void sendCommand(std::string newCommand);
    std::string pickLogToDisplay();
};

class Camera{
public:
    int videoWidth;
    int videoHeight;
    unsigned char *videoData;

    cv::Mat imgBin2; //Lorenzo

protected:
    cv::Mat frame;
    cv::VideoCapture cam;
    Color::HSV rangeLow;
    Color::HSV rangeHigh;
    int filterWidh;
    int filterHeight;
    cv::Mat imgBin;

private:
    cv::Point findCenter( cv:: Mat img );
    void videoAnalyzis();
public:
    bool connect(int index);
    bool good();
    void pickFrame(int type );
    void sendHSV( int h, int s, int v, unsigned char type );
    void sendFilter( int value, unsigned char type );
};

class SerialPort {
public: enum Error{
	OPEN_GOOD, OPEN_ERROR,
	GET_CONFIG_ERROR, SET_CONFIG_ERROR,
	SEND_ERROR, SEND_GOOD,
	CLOSED};
private:
	speed_t bound;
	char* port;
	int status;
	struct termios config;
public:
    bool good();
	SerialPort();
	~SerialPort();
	void serialPortClose();
	SerialPort::Error serialPortInit(char* port, speed_t bound);
	SerialPort::Error serialPortWrite(int valueX, int valueY);
};


#endif // BALANCERPROG_H
