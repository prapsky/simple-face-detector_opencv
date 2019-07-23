//
//  main.cpp
//  simple-face-detector_opencv
//
//  Created by Suprapto on 23/07/19.
//  Copyright © 2019 Suprapto. All rights reserved.
//

#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

int main(int argc, const char * argv[]) {
    //Capture stream from webcam
    VideoCapture capture(0);
    
    //Check if we can get the webcam stream
    if (!capture.isOpened()) {
        cout << "Could not open camera!" << endl;
        return -1;
    }
    
    double dWidth = capture.get(CAP_PROP_FRAME_WIDTH);
    double dHeight = capture.get(CAP_PROP_FRAME_HEIGHT);
    
    cout << "Frame size: " << dWidth << "x" << dHeight << endl;
    
    namedWindow("FaceDetector", WINDOW_AUTOSIZE);
    
    /*
     OpenCV saves detection rules as something called a CascadeClassifier
     which can be used to detect object in images
     */
    CascadeClassifier faceCascade;
    
    /*
     Load the lbpcascade_frontalface.xml containing the rules to detect faces.
     The file should be right next to the binary.
     */
    if (!faceCascade.load("lbpcascade_frontalface.xml")) {
        cout << "Failed to load cascade classfier!" << endl;
        return -1;
    }
    
    while (true) {
        //This variable will hold the image from webcam
        Mat cameraFrame;
        
        //Read an image from webcam
        capture.read(cameraFrame);
        
        //This vector will hold the rectangles coordinates to a detection inside the image
        vector<Rect> faces;
        
        /*
         This function detects the faces in the image and
         place the rectangles of the faces in the vector.
         See the detectMultiScale() documentation for more details
         about the rest of the parameters.
         */
        faceCascade.detectMultiScale(
                                     cameraFrame,
                                     faces,
                                     1.09,
                                     3,
                                     0 | CASCADE_SCALE_IMAGE,
                                     Size(30, 30));
        
        /*
         Draw the rectangles onto the image
         with a red border of thickness 2.
         */
        for (size_t i = 0; i < faces.size(); i++) {
            rectangle(cameraFrame, faces[i], Scalar(0, 0, 255), 2);
        }
        
        //Here we show the drawn image in a named window called output
        imshow("FaceDetector", cameraFrame);
        
        /*
         Wait 50 ms for key pressed
         returns -1 if no key is pressed during that time
         */
        if (waitKey(50) >= 0) {
            break;
        }
    }
    
    return 0;
}
