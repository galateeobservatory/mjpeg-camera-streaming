# MJPEG Raspberry PI streamer

Stream MJpeg from raspberry pi camera to a web page.

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

The executable is named `MJPeg`.

## Create systemd service

Copy executable to `/opt`:

```bash
sudo mkdir /opt/mjpeg_streamer && sudo cp MJPeg /opt/mjpeg_streamer/
```

Add `mjpeg_streamer` user:

```bash
sudo useradd mjpeg_streamer
sudo usermod -aG video mjpeg_streamer
```

Create a systemd service file `/etc/systemd/system/mjpeg-streamer.service`:

```ini
[Unit]
Description=MJpeg HTTP camera streamer
After=network-online.target

[Service]
Type=simple

User=mjpeg_streamer
Group=mjpeg_streamer
UMask=007

Type=simple
ExecStart=/opt/mjpeg_streamer/MJPeg
Restart=always
TimeoutStopSec=300

[Install]
WantedBy=multi-user.target
```

Enable and start the service:

```bash
sudo systemctl enable mjpeg-streamer.service
sudo service mjpeg-streamer start
```

Now you can access the stream at `http://<raspberry_pi_ip>:7777`