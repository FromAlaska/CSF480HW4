// Jim Samson
// CSF480 Homework 4
// Video Latency Homework

/* Pseudocode for the homework assignment

    open camera
    int64 last_colorchange = cv::getTickCount();
    bool lastframe_black = true;
    while (true) {
        read camera frame
        compute average brightness of camera pixels
        bool camera_sees_black = brightness < threshold;
        if (lastframe_black != camera_sees_black) {
            lastframe_black = camera_sees_black
            print time since last change as latency
            last_colorchange=cv::getTickCount();
            
        // Create an output image with the opposite color:
        create an output image
        if (camera_sees_black) fill output image with white
        else fill output image with black
        show output image
        }
    }
*/
#include <opencv2/opencv.hpp>

using namespace cv;

double t_last=0.0; // last frame time
double t_last_print=1.0; // last framerate printout time

/* Return the current wall clock time, in seconds */
double time_in_seconds(void) {
  static double first=-1;
  double cur=cv::getTickCount()/cv::getTickFrequency();
  if (first<0) first=cur;
        return cur-first;
}

int main(int argc,char *argv[])
{
    cv::VideoCapture *cap=0;
    long framecount=0;
    double time_start=-1.0;

    int argi=1; // command line argument index
    while (argc>=argi+2) { /* keyword-value pairs */
        char *key=argv[argi++];
        char *value=argv[argi++];
        if (0==strcmp(key,"--cam")) cap=new cv::VideoCapture(atoi(value));
            else if (0==strcmp(key,"--file")) cap=new cv::VideoCapture(value);
        else printf("Unrecognized command line argument '%s'!\n",key);
    }
  // Initialize capturing live feed from the camera
  if (!cap) cap=new cv::VideoCapture(0);

  // Couldn't get a device? Throw an error and quit
  if(!cap->isOpened())
  {
    printf("Could not initialize capturing...\n");
    return -1;
  }

  // Make the windows we'll be using
  cv::namedWindow("video");

  cv::Mat frame,gray,gradX,gradY;
  cv::Mat accum;
  
  double t_last=0.0; // last frame time
  double t_last_print=1.0; // last framerate printout time

  // 
  bool lastframe_black = true;
  int64 last_colorchange = cv::getTickCount();

  // An infinite loop
  while(true)
  {
    double t_cur=time_in_seconds();
    double dt=t_cur-t_last;
    t_last=t_cur;
    if (t_cur>t_last_print+1.0) {
      std::cout<<"Framerate: "<<1.0/dt<<" fps\n";
      t_last_print=t_cur;
    }
  
    (*cap)>>frame; // grab next frame from camera

    // If we couldn't grab a frame... quit
    if(frame.empty())
      break;

    frame = frame * 2.3; // scale the pixel brightness

    bool camera_sees_black = true; //TODO FIGURE OUT HOW THIS WORKS

    if(lastframe_black != camera_sees_black) {
        lastframe_black = camera_sees_black;
    }

    cv::imshow("video", frame);
    
    framecount++;

    // Wait for a keypress (for up to 1ms)
    int c = cv::waitKey(1);
    if(c=='q')
    {
      break;
    }
  }
    return 0;
}