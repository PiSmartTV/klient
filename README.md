# PiTV Klient
GUI client for PiTV to stream video

## Dependencies
- QtWidgets
- LibAV

## Using prebuilt binaries
- go to the https://nightly.link/PiSmartTV/klient/workflows/build/master
- click on the link for your OS

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

To package installer NSIS is required.

### MacOS (WIP)
Firstly, you have to install homebrew.

Install dependencies:
```
brew install qt@5 ffmpeg cmake
```

Then configure the project:
```
mkdir build && cd build
cmake ..
```

Finally, build:
```
make
```

CPack is still in progress