# QR reader
Linux C++ library and application to read bar and QR code

# Build
The QR reader needs opencv and zbar library
Build the app with
```
make
```
The executable is located at build/bin/

# Usage
You can use it with your video device (/dev/video0)
```
QRapp
```
or with a video file instead of a camera
```
QRapp test.mp4
```
