# Simple Face Detector using OpenCV
Simple implementation of Face Detector using OpenCV in C++.

## How to Use
1. [Prerequisites](#prerequisites)
2. [Setup in Xcode](#setup-in-xcode)
3. [Compile and Run](#compile-and-run)

### Prerequisites
1. Install Xcode.
2. Download OpenCV, for example OpenCV 4.1.0. Check in this link : https://opencv.org/releases/ .
3. Install Homebrew using following command:
```
$ /usr/bin/ruby -e "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/master/install)"
```
4. Install OpenCV using following command:
```
$ brew install opencv
```
5. Install pkg-config using following command:
```
$ brew install pkg-config
```
6. View OpenCV linker flags using following command:
```
$ pkg-config --cflags --libs path/to/opencv4.pc
```
For example:
```
$ pkg-config --cflags --libs /usr/local/Cellar/opencv/4.1.0_2/lib/pkgconfig/opencv4.pc
```

### Setup in Xcode
1. Set Header Search Paths in "Any Architecture | Any SDK" field at Build Settings, in my case:
```
/usr/local/Cellar/opencv/4.1.0_2/include
```
2. Set Library Search Paths in "Any Architecture | Any SDK" field at Build Settings, in my case:
```
/usr/local/Cellar/opencv/4.1.0_2/lib
```
3. Set Other Linker Flags in "Any Architecture | Any SDK" field at Build Settings after run pkg-config, in my case:
```
-lopencv_gapi -lopencv_stitching -lopencv_aruco -lopencv_bgsegm -lopencv_bioinspired -lopencv_ccalib -lopencv_dnn_objdetect -lopencv_dpm -lopencv_face -lopencv_freetype -lopencv_fuzzy -lopencv_hfs -lopencv_img_hash -lopencv_line_descriptor -lopencv_quality -lopencv_reg -lopencv_rgbd -lopencv_saliency -lopencv_sfm -lopencv_stereo -lopencv_structured_light -lopencv_phase_unwrapping -lopencv_superres -lopencv_optflow -lopencv_surface_matching -lopencv_tracking -lopencv_datasets -lopencv_text -lopencv_dnn -lopencv_plot -lopencv_videostab -lopencv_video -lopencv_xfeatures2d -lopencv_shape -lopencv_ml -lopencv_ximgproc -lopencv_xobjdetect -lopencv_objdetect -lopencv_calib3d -lopencv_features2d -lopencv_highgui -lopencv_videoio -lopencv_imgcodecs -lopencv_flann -lopencv_xphoto -lopencv_photo -lopencv_imgproc -lopencv_core
```
4. Set Framework Search Paths in "Any Architecture | Any SDK" field at Build Settings by using location of opencv2.framework, in my case:
```
/Users/suprapto/OpenCV
```

### Compile and Run
1. Compile using GNU C++ Compiler with following command:
```
$ g++ $(pkg-config --cflags --libs opencv) -std=c++11  yourFile.cpp -o yourFileProgram
```
For example:
```
$ g++ $(pkg-config --cflags --libs /usr/local/Cellar/opencv/4.1.0_2/lib/pkgconfig/opencv4.pc) -std=c++11 /Users/suprapto/simple-face-detector_opencv/simple-face-detector_opencv/main.cpp -o simple-face-detector_opencv
```
2. Run the binary using following command:
```
$ ./yourFileProgram
```
For example:
```
$ ./simple-face-detector_opencv
```
