#include "lccv.h"
#include "MJPEGWriter.h"
#include "libcamera_app.h"

using namespace std;
using namespace cv;
using namespace libcamera;


int main()
{
    MJPEG server(7777);

    uint32_t num_cams = LibcameraApp::GetNumberCameras();
    if (num_cams == 0)
    {
        std::cerr << "No cameras found." << std::endl;
        return 1;
    }

    std::cout << "Found " << num_cams << " cameras." << std::endl;

    uint32_t height = 3040;
    uint32_t width = 4056;

    /*uint32_t height = 480;
    uint32_t width = 640;*/

    lccv::PiCamera cam;
    cam.options->video_width=width;
    cam.options->video_height=height;
    cam.options->framerate=30;
    cam.options->verbose=true;
    cam.startVideo();

    Mat frame;
    cam.getVideoFrame(frame,1000);

    server.write(frame);
    server.start();
    while (cam.getVideoFrame(frame,1000))
    {
        server.write(frame);
        mySleep(40);
    }
    cout << "Camera shutdown" << endl;
    frame.release();
    cam.stopVideo();
    server.stop();
    return 0;
}