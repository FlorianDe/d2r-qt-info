## Build and Run Commands

### macOS

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

NOT WORKING:
You can use Homebrew to install both:

```bash
brew install qt cmake
```

You’ll need to ensure that Qt’s CMake integration is available. The path to the Qt installation should be made available
to CMake (Homebrew installs Qt in /opt/homebrew/opt/qt for Apple Silicon or /usr/local/opt/qt for Intel):

```bash
export Qt6_DIR=$(brew --prefix qt)/lib/cmake/Qt6
````

2. Build the project:

```bash
mkdir build
cd build
cmake .. -DCMAKE_PREFIX_PATH=$(brew --prefix qt) -DCMAKE_BUILD_TYPE=Release
make
```

3. Run the application:

```bash
./D2R-Qt-Info
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

