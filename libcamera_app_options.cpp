#include "libcamera_app_options.h"

void Options::Print() const
{
    std::cout << "Options:" << std::endl;
    std::cout << "    verbose: " << verbose << std::endl;
    std::cout << "    info_text:" << info_text << std::endl;
    std::cout << "    timeout: " << timeout << std::endl;
    std::cout << "    photo resolution: " << photo_width << " x "<< photo_height << std::endl;
    std::cout << "    video resolution: " << video_width << " x " << video_height << std::endl;
    std::cout << "    rawfull: " << rawfull << std::endl;
    std::cout << "    transform: " << transformToString(transform) << std::endl;
    if (roi_width == 0 || roi_height == 0)
    {
        std::cout << "    roi: all" << std::endl;
    }
    else
    {
        std::cout << "    roi: " << roi_x << "," << roi_y << "," << roi_width << "," << roi_height << std::endl;
    }
    if (shutter)
    {
        std::cout << "    shutter: " << shutter << std::endl;
    }
    if (gain)
    {
        std::cout << "    gain: " << gain << std::endl;
    }
    std::cout << "    metering: " << metering_index << std::endl;
    std::cout << "    exposure: " << exposure_index << std::endl;
    std::cout << "    ev: " << ev << std::endl;
    std::cout << "    awb: " << awb_index << std::endl;
    if (awb_gain_r && awb_gain_b)
    {
        std::cout << "    awb gains: red " << awb_gain_r << " blue " << awb_gain_b << std::endl;
    }
    std::cout << "    brightness: " << brightness << std::endl;
    std::cout << "    contrast: " << contrast << std::endl;
    std::cout << "    saturation: " << saturation << std::endl;
    std::cout << "    sharpness: " << sharpness << std::endl;
    std::cout << "    framerate: " << framerate << std::endl;
    std::cout << "    denoise: " << denoise << std::endl;
}