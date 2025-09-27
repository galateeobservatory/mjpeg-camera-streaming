#include "lccv.h"
#include "MJPEGWriter.h"
#include "libcamera_app.h"
#include <ini.h>

using namespace std;
using namespace cv;
using namespace libcamera;


struct Config
{
    uint16_t port;
    uint32_t width;
    uint32_t height;
    uint32_t fps;
};

// Callback pour inih
static int iniHandler(void* user, const char* section, const char* name, const char* value)
{
    Config* config = (Config*)user;

    if (strcmp(section, "server") == 0)
    {
        if (strcmp(name, "port") == 0)
            config->port = static_cast<uint16_t>(stoi(value));
        else if (strcmp(name, "width") == 0)
            config->width = static_cast<uint32_t>(stoi(value));
        else if (strcmp(name, "height") == 0)
            config->height = static_cast<uint32_t>(stoi(value));
        else if (strcmp(name, "fps") == 0)
            config->fps = static_cast<uint32_t>(stoi(value));
    }
    return 1;
}

int main(int argc, char* argv[])
{
    Config config{7777, 640, 480, 30};

    if (argc < 2)
    {
        cerr << "Usage: " << argv[0] << " <config.ini>" << endl;
        cerr << "Using default values." << endl;
    }
    else
    {
        const char* iniPath = argv[1];
        if (ini_parse(iniPath, iniHandler, &config) < 0)
        {
            cerr << "Can't load '" << iniPath << "', using default values." << endl;
        }
    }

    cout << "Using port=" << config.port << ", width=" << config.width << ", height=" << config.height << ", fps=" << config.fps << endl;
    MJPEG server(config.port);

    uint32_t num_cams = LibcameraApp::GetNumberCameras();
    if (num_cams == 0)
    {
        cerr << "No cameras found." << endl;
        return 1;
    }

    cout << "Found " << num_cams << " cameras." << endl;

    lccv::PiCamera cam;
    cam.options->video_width = config.width;
    cam.options->video_height = config.height;
    cam.options->framerate = config.fps;
    cam.options->verbose = true;
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