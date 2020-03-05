#include "BalancerProg.h"



/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                                                        Console
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
void Console::makeCommand(std::string newCommand){

    consoleLog.push_back(newCommand);

    if( newCommand[0] == '$' )
    {
        if( newCommand == "$ help" )
        {
            consoleLog.push_back("There is No help");
        }
        else
        {
            consoleLog.push_back("Command not found");
        }
    }
}
void Console::sendSpace(unsigned int h, unsigned int v){
    hSpace = h;
    vSpace = v;
}
void Console::sendCommand(std::string newCommand){
    /* # make the command */
    makeCommand(newCommand);
}
std::string Console::pickLogToDisplay(){

    std::string toDisplay = "";
    for( int i=0 ; i<consoleLog.size() ; i++ )
    {
        toDisplay += consoleLog[i];
        toDisplay += '\n';
        /* # zabezpiecznie nie horisontal oraz vertical*/
    }
    return toDisplay;
}
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                                                        Camera
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
bool Camera::connect(int index){
    cam.open(index);
    return good();
}
bool Camera::good(){
    return cam.isOpened();
}
void Camera::pickFrame(int type ){


     cam >> frame; // with Bufer

    // Należy sprawdzać czy img nie jest puste
    switch( type )
    {
        case 0:
            videoData = frame.data;
        break;

        case 1:
            videoData = imgBin.data;
        break;

        default:
        break;
    }
    videoWidth = cam.get(3);
    videoHeight = cam.get(4);

    videoAnalyzis();    //Lorenzo
    // 4-CV_BGR2RGB // 2-BGR2RGBA // 6-BGR2GRAY // 8-GRAY2RGB
    // CV_CAP_PROP_POS_MSEC 0 // CV_CAP_PROP_POS_FRAME 1 // CV_CAP_PROP_POS_AVI_RATIO 2
    // CV_CAP_PROP_FRAME_WIDTH 3 // CV_CAP_PROP_FRAME_HEIGHT 4 // CV_CAP_PROP_FPS 5
    // CV_CAP_PROP_FOURCC 6 // CV_CAP_PROP_FRAME_COUNT 7
    // If on Windows, set as BGR //If on Linux, set as RGB
}
cv::Point Camera::findCenter(cv::Mat img){

    cv::Mat bin;
    cv::Point center(-1,-1);

    cv::threshold(img,bin,100,255, 0);

    cv::Moments m = cv::moments(bin, true);

    if(m.m00 != 0)
    {
        center.x = m.m10/m.m00;
        center.y = m.m01/m.m00;
    }

    return center;
}
void Camera::videoAnalyzis(){

    cv::Mat imgHSV; // dać do .h
    cv::cvtColor(frame, imgHSV, 40); //Convert from BGR to HSV

    cv::Scalar low( rangeLow.h, rangeLow.s, rangeLow.v );
    cv::Scalar height( rangeHigh.h, rangeHigh.s, rangeHigh.v );
    cv::inRange(imgHSV, low, height, imgBin);

 /* Filters */
    if(filterWidh != 0 && filterHeight !=0)
    {
        // morphological opening (remove small objects from the foreground)
        cv::erode( imgBin, imgBin, getStructuringElement(2, cv::Size(filterWidh, filterHeight)) );
        cv::dilate( imgBin, imgBin, getStructuringElement(2, cv::Size(filterWidh, filterHeight)) );

        // morphological closing (fill small holes in the foreground)
        cv::dilate( imgBin, imgBin, getStructuringElement(2, cv::Size(filterWidh, filterHeight)) );
        cv::erode( imgBin, imgBin, getStructuringElement(2, cv::Size(filterWidh, filterHeight)) );
    }

/* Moment */
    findCenter( imgBin );
    imgBin2 = imgBin;

}
Color::HSV Color::toHSV( int red, int green, int blue ){

    float hue = 0.0; // 0 - 360
    float sat = 0.0; // 0 - 1
    float val = 0.0; // 0 - 1

    float r = red / 255.0;
    float g = green / 255.0;
    float b = blue / 255.0;

    float max = r;
    float min = r;

    if( g > max ) max = g;
    if( b > max ) max = b;

    if( g < min ) min = g;
    if( b < min ) min = b;

    if( max != min )
    {
        if( r == max ) hue = ( g - b ) / ( max - min );
        else if( g == max ) hue = 2.0 + ( b - r ) / ( max - min );
        else if( b == max ) hue = 4.0 + ( r - g ) / ( max - min );

        hue *= 60;
        if( hue < 0 ) hue +=360;
        sat = ( max - min ) / max;


    }
    val = max;

    /* toBytes */
    hue = ( 255 * hue ) / 360;
    sat = sat * 255;
    val = val * 255;

    HSV out;
    out.h = (int)( hue + 0.5 );
    out.s = (int)( sat + 0.5 );
    out.v = (int)( val + 0.5 );

    return out;
}
Color::RGB Color::toRGB( Color::HSV ){

    RGB out;

    out.r = 120;
    out.g = 122;
    out.b = 123;

    return out;
}
void Camera::sendFilter( int value, unsigned char type ){

    switch(type)
    {
        case 'W':
            filterWidh = value;
        break;

        case 'H':
            filterHeight = value;
        break;

        default:
        break;
    }
}
void Camera::sendHSV( int h, int s, int v, unsigned char type ){

    switch(type)
    {
        case 'L':
            rangeLow.h = h;
            rangeLow.s = s;
            rangeLow.v = v;
        break;

        case 'H':
            rangeHigh.h = h;
            rangeHigh.s = s;
            rangeHigh.v = v;
        break;

        default:
        break;
    }
}
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                                                        SerialPort
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
SerialPort::SerialPort() : port(nullptr) {}
SerialPort::~SerialPort() { delete port; }
void SerialPort::serialPortClose() {
	close(status);
}
SerialPort::Error SerialPort::serialPortInit(char* port, speed_t bound) {

	this->port = port;
	this->bound = bound;

	status = open(port, O_RDWR | O_NOCTTY);

	if (status == -1)  {
		return OPEN_ERROR;
	}

	if (tcgetattr(status, &config) < 0) {
		return GET_CONFIG_ERROR;
	}

	cfsetispeed(&config, bound);
	cfsetospeed(&config, bound);


	config.c_cflag &= ~PARENB;
	config.c_cflag &= ~CSTOPB;
	config.c_cflag &= ~CSIZE;
	config.c_cflag |= CS8;
	config.c_cflag &= ~CRTSCTS;
	config.c_cflag |= CREAD | CLOCAL;  // turn on READ & ignore ctrl lines
	config.c_iflag &= ~(IXON | IXOFF | IXANY); // turn off s/w flow ctrl
	config.c_lflag &= ~(ICANON | ECHO | ECHOE | ISIG); // make raw
	config.c_oflag &= ~OPOST; // make raw
	config.c_cc[VMIN]  = 0;
	config.c_cc[VTIME] = 20;

	if( tcsetattr(status, TCSANOW, &config) < 0) {
		return SET_CONFIG_ERROR;
	}

	return OPEN_GOOD;

}

SerialPort::Error SerialPort::serialPortWrite(int valueX, int valueY) {

	std::string message = "";
	message += "X";
	message += std::to_string(valueX);
	message += "Y";
	message += std::to_string(valueY);
	int len = strlen(message.c_str());
	int n = write(status, message.c_str(), len);

	if(n != len) {
		return SerialPort::Error::SEND_ERROR;
	}
	return SerialPort::Error::SEND_GOOD;

}

bool SerialPort::good() {
    return(status != -1);
}




/*
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <termios.h>
#include <sys/ioctl.h>

#include <getopt.h>

int serialport_init(const char* serialport, int baud);
int serialport_writebyte(int fd, uint8_t b);
int serialport_write(int fd, const char* str);
int serialport_read_until(int fd, char* buf, char until);

using namespace std;

int main(int argc, char *argv[])
{

	int fd = 0;
	int baudrate = 9600;
	char data[4];

	fd = serialport_init("/dev/ttyACM0", baudrate);
	usleep(3000 * 1000 );

	while(fd != -1) {

	printf("Podaj servo i wychylenie: ");
	scanf("%s", data);

	if(serialport_write(fd, data) != -1 ) {
		printf("Wysłano: %s\n", data);
	}


	}

}

int serialport_writebyte( int fd, uint8_t b)

{

   int n = write(fd,&b,1);

   if( n!=1)

       return -1;

   return 0;

}



int serialport_write(int fd, const char* str)

{

   int len = strlen(str);

   printf("len: %d\n str: %s\n", len, str);

   int n = write(fd, str, len);

   if( n!=len )

       return -1;

   return n;

}



int serialport_read_until(int fd, char* buf, char until)

{

   char b[1];

   int i=0;

   do {

       int n = read(fd, b, 1);  // read a char at a time

       if( n==-1) return -1;    // couldn't read

       if( n==0 ) {

           usleep( 10 * 1000 ); // wait 10 msec try again

           continue;

       }

       buf[i] = b[0]; i++;

   } while( b[0] != until );



   buf[i] = 0;  // null terminate the string

   return i;

}



// takes the string name of the serial port (e.g. "/dev/tty.usbserial","COM1")

// and a baud rate (bps) and connects to that port at that speed and 8N1.

// opens the port in fully raw mode so you can send binary data.

// returns valid fd, or -1 on error

int serialport_init(const char* serialport, int baud)

{

   struct termios toptions;

   int fd;



   //fprintf(stderr,"init_serialport: opening port %s @ %d bps\n",

   //        serialport,baud);



   //fd = open(serialport, O_RDWR | O_NOCTTY | O_NDELAY);

   fd = open(serialport, O_RDWR | O_NOCTTY);

   if (fd == -1)  {

       perror("init_serialport: Unable to open port ");

       return -1;

   }



   if (tcgetattr(fd, &toptions) < 0) {

       perror("init_serialport: Couldn't get term attributes");

       return -1;

   }

   speed_t brate = baud; // let you override switch below if needed

   switch(baud) {

   case 4800:   brate=B4800;   break;

   case 9600:   brate=B9600;   break;

// if you want these speeds, uncomment these and set #defines if Linux

//#ifndef OSNAME_LINUX

//    case 14400:  brate=B14400;  break;

//#endif

   case 19200:  brate=B19200;  break;

//#ifndef OSNAME_LINUX

//    case 28800:  brate=B28800;  break;

//#endif

   //case 28800:  brate=B28800;  break;

   case 38400:  brate=B38400;  break;

   case 57600:  brate=B57600;  break;

   case 115200: brate=B115200; break;

   }

   cfsetispeed(&toptions, brate);

   cfsetospeed(&toptions, brate);



   // 8N1

   toptions.c_cflag &= ~PARENB;

   toptions.c_cflag &= ~CSTOPB;

   toptions.c_cflag &= ~CSIZE;

   toptions.c_cflag |= CS8;

   // no flow control

   toptions.c_cflag &= ~CRTSCTS;



   toptions.c_cflag |= CREAD | CLOCAL;  // turn on READ & ignore ctrl lines

   toptions.c_iflag &= ~(IXON | IXOFF | IXANY); // turn off s/w flow ctrl



   toptions.c_lflag &= ~(ICANON | ECHO | ECHOE | ISIG); // make raw

   toptions.c_oflag &= ~OPOST; // make raw



   // see: http://unixwiz.net/techtips/termios-vmin-vtime.html

   toptions.c_cc[VMIN]  = 0;

   toptions.c_cc[VTIME] = 20;



   if( tcsetattr(fd, TCSANOW, &toptions) < 0) {

       perror("init_serialport: Couldn't set term attributes");

       return -1;

   }



   return fd;

}

*/
