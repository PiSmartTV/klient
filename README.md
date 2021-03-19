# PiTV Klient
GUI client for PiTV to stream video

## Dependencies
- QtWidgets
- LibAV

## Using prebuilt binaries
- go to the https://github.com/PiSmartTV/klient/actions
- go to the latest build
- scroll down and download artifact for your OS

## Building from source

### On Linux

#### Debian-based
```
sudo apt install build-essential cmake libavformat-dev libavcodec-dev libavutil-dev qt-default qttools5 qttools5-dev qt5-default
```
#### Arch-based
```
doas/sudo pacman -S ffmpeg qt cmake qt5-tools
```

#### RPM-based
Also not sure for this
```
sudo dnf install ffmpeg
```

#### Gentoo
```
doas/sudo emerge -av media-video/ffmpeg dev-util/cmake dev-qt/linguist dev-qt/qtwidgets dev-qt/qtconcurrent
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

### Windows

Install FFmpeg from their website or chocolatey.
Install Qt SDK (Online installer) from Qt's website.
Open QtCreator and build.