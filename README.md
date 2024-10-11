
[![CI Build](https://github.com/FlorianDe/d2r-qt-info/actions/workflows/build.yml/badge.svg)](https://github.com/FlorianDe/d2r-qt-info/actions/workflows/build.yml)

[![GitHub Release](https://img.shields.io/github/v/release/FlorianDe/d2r-qt-info?label=Version)](https://github.com/FlorianDe/d2r-qt-info/releases)
[![GitHub commits since latest release](https://img.shields.io/github/commits-since/FlorianDe/d2r-qt-info/latest)
](https://github.com/FlorianDe/d2r-qt-info/commits/main/)

# D2R-Qt-Info

D2R-Qt-Info is a proof-of-concept project built to explore and familiarize with Qt6 using C++, as well as the
development tooling and GitHub’s CI/CD workflow integration with C++ on multiple platforms. The project implements basic
functionality related to handling and displaying data from Diablo 2: Resurrected, focusing on experimenting with Qt’s
framework and features. While it
includes some Diablo 2-specific components, the primary aim is to gain practical experience with modern C++ development
and continuous integration/deployment pipelines within a Qt6/C++ environment.

This project can be seen and used as a good starter to set up a desktop cross-platform Qt/C++ project.

## Problems

### [MacOS] App Is Damaged and Can’t Be Opened. You Should Move It To The Trash

This is due to the App not being Signed currently, you have to remove the quarantine flag from the .app and its content
by using the following command:

```bash
xattr -rd com.apple.quarantine /path/to/D2R-Qt-Info.app
```

## Build and Run Commands

### macOS

1. You can use Homebrew to install both:

```bash
brew install qt cmake
```

You’ll need to ensure that Qt’s CMake integration is available. The path to the Qt installation should be made available
to CMake (Homebrew installs Qt in /opt/homebrew/opt/qt for Apple Silicon or /usr/local/opt/qt for Intel):

```bash
export Qt6_DIR=$(brew --prefix qt)/lib/cmake/Qt6
````

or if you want to try to build qt from source e.g. for static linking:

1. Install Qt and CMake:

Build from source since universal installer needed of QT, for universal builds:

1.1 Download QT Offline installer https://download.qt.io/archive/qt/
1.2 Extract

```bash
tar -xf qt-everywhere-src-6.7.2.tar.xz
```

1.3 Create a folder for the configuration

```bash
mkdir -p ~/Downloads/qt-build
cd ~/Downloads/qt-build
```

1.4. Run the configure script inside the folder
Documentation: https://doc.qt.io/qt-6/configure-options.html

```bash
~/Downloads/qt-everywhere-src-6.7.2/configure -nomake tests -nomake examples -skip qtwebengine -prefix /usr/local/qt6 -- -DCMAKE_OSX_ARCHITECTURES="x86_64;arm64"
```

2. Build the project:

```bash
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release -DCMAKE_PREFIX_PATH=$(brew --prefix qt)
cmake --build build --config Release --parallel
```

3. Run the application:

```bash
./build/D2R-Qt-Info.app/Contents/MacOS/D2R-Qt-Info
```

### Windows (Native Windows Build)

```bash
mkdir build-windows
cd build-windows
cmake .. -G "MinGW Makefiles" -DCMAKE_PREFIX_PATH=C:/path/to/Qt6
mingw32-make
```

## Misc

### Create AppIcon.icns

1. Install ImageMagick (if not already installed):

You can install ImageMagick using Homebrew:

```bash
brew install imagemagick
```

2. Convert the .webp to multiple PNG sizes:

You need to convert your AppIcon.webp to different sizes for the macOS iconset. The required sizes are: 16x16, 32x32,
64x64, 128x128, 256x256, 512x512, and 1024x1024.

Use the following ImageMagick command to create PNGs in each of the needed sizes:

```bash
mkdir AppIcon.iconset

# Convert the .webp file to the required PNG sizes
magick convert AppIcon.webp -resize 16x16   AppIcon.iconset/icon_16x16.png
magick convert AppIcon.webp -resize 32x32   AppIcon.iconset/icon_16x16@2x.png
magick convert AppIcon.webp -resize 32x32   AppIcon.iconset/icon_32x32.png
magick convert AppIcon.webp -resize 64x64   AppIcon.iconset/icon_32x32@2x.png
magick convert AppIcon.webp -resize 128x128 AppIcon.iconset/icon_128x128.png
magick convert AppIcon.webp -resize 256x256 AppIcon.iconset/icon_128x128@2x.png
magick convert AppIcon.webp -resize 256x256 AppIcon.iconset/icon_256x256.png
magick convert AppIcon.webp -resize 512x512 AppIcon.iconset/icon_256x256@2x.png
magick convert AppIcon.webp -resize 512x512 AppIcon.iconset/icon_512x512.png
magick convert AppIcon.webp -resize 1024x1024 AppIcon.iconset/icon_512x512@2x.png
```

3. Convert the iconset to .icns using iconutil:

Once you have the different PNG sizes, you can now use Apple’s iconutil tool to create the .icns file from the
AppIcon.iconset folder:

```bash
iconutil -c icns AppIcon.iconset
```

4. Clean up (optional):

After creating the .icns file, you can remove the intermediate AppIcon.iconset folder if you no longer need it:

```bash
rm -rf AppIcon.iconset
```

### Create AppIcon.ico

```
magick AppIcon.webp -define icon:auto-resize=256,128,64,48,32,16 AppIcon.ico
```

### Convert *.webp files to *.png (install imagemagick first)

To convert all .webp files in a folder to .png files using a one-liner in a Unix-based shell (like macOS or Linux), you
can use the following command:

```bash
for file in *.webp; do magick "$file" "${file%.webp}.png"; done
```

Delete the old .webp files:

```bash
rm *.webp
```

If you have multiple file ending, you can get rid of like this (example .png.png):

```bash
for file in *.png.png; do mv "$file" "${file%.png.png}.png"; done
```



