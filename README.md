# MJPEG Raspberry PI streamer

Stream MJpeg from raspberry pi camera to a web page.

---

Thanks https://github.com/kbarni/LCCV and https://github.com/JPery/MJPEGWriter

## Install dependencies

```bash
sudo apt install git cmake build-essential libinih-dev libopencv-core-dev libopencv-calib3d-dev libopencv-dnn-dev libopencv-objdetect-dev libopencv-photo-dev libopencv-stitching-dev libopencv-video-dev libcamera-dev
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
make -j8
```

The executable is named `MJPeg`.

## Configuration

You can find an example configuration file [example_config.ini](./example_config.ini) in the repository.

Here is an example configuration, containing the default values if you don't provide a config file:
```ini
[server]
port=7777
width=640
height=480
fps=30
```

(For HQ camera, you can set width=4056 and height=3040)

To run the streamer with a custom configuration file:

```bash
./MJPeg /path/to/your/config.ini
```

## Create systemd service

Copy executable to `/opt`:

```bash
sudo mkdir /opt/mjpeg_streamer && sudo cp MJPeg /opt/mjpeg_streamer/
```

Create a configuration file in `/opt/mjpeg_streamer/config.ini` (you can copy the example configuration file and modify it as needed).

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
ExecStart=/opt/mjpeg_streamer/MJPeg /opt/mjpeg_streamer/config.ini
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

Now you can access the stream at `http://<raspberry_pi_ip>:7777` (or the port you specified in the config file).