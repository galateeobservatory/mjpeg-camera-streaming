# MJPEG streamer

Stream MJpeg from a camera to a web page.

---

Thanks https://github.com/kbarni/LCCV and https://github.com/JPery/MJPEGWriter

## Install dependencies

```bash
sudo apt install git cmake build-essential libopencv-core-dev libopencv-calib3d-dev libopencv-dnn-dev libopencv-objdetect-dev libopencv-photo-dev libopencv-stitching-dev libopencv-video-dev libcamera-dev
```

## For HQ camera:

Enable driver: 

In `/boot/firmware/config.txt`: set `camera_auto_detect=0` and append `dtoverlay=imx477,cam0`

## Install

```bash
git clone https://github.com/galateeobservatory/mjpeg-camera-streaming.git
cd mjpeg-camera-streaming
mkdir build
cd build
cmake ..
make -j4
```
