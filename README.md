# PiTV Klient
GUI client for PiTV to stream video

## Dependencies
- QtWidgets
- LibAV

## Building from source

### On Linux

#### Debian-based
```
sudo apt install build-essential cmake libavformat-dev libavcodec-dev libavutil-dev
```
#### Arch-based
I am not sure for this
```
doas/sudo pacman -S ffmpeg
```

#### RPM-based
Also not sure for this
```
sudo dnf install ffmpeg
```

#### Gentoo
```
doas/sudo emerge -av media-video/ffmpeg
```

Finally build it:
```
git clone https://github.com/PiSmartTV/klient
cd klient
mkdir build
cd build
cmake ..
make -j2
```