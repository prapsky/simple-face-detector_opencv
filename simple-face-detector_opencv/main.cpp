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
    VideoCapture capture(0);
    if (!capture.isOpened()) {
        cout << "Could not open camera!" << endl;
        return -1;
    }
    
    double dWidth = capture.get(CAP_PROP_FRAME_WIDTH);
    double dHeight = capture.get(CAP_PROP_FRAME_HEIGHT);
    cout << "Frame size: " << dWidth << "x" << dHeight << endl;
    namedWindow("FaceDetector", WINDOW_AUTOSIZE);
    
    CascadeClassifier faceCascade, eyeCascade;
    
    if (!faceCascade.load("lbpcascade_frontalface.xml")) {
        cout << "Failed to load cascade classfier for face!" << endl;
        return -1;
    }
    
    if (!eyeCascade.load("haarcascade_eye.xml")) {
        cout << "Failed to load cascade classfier for eyes!" << endl;
        return -1;
    }
    
    while (true) {
        Mat cameraFrame, grayImage;
        vector<Rect> faces, eyes;
        
        capture.read(cameraFrame);
        cvtColor(cameraFrame, grayImage, COLOR_BGR2GRAY);
        equalizeHist(grayImage, grayImage);
        
        faceCascade.detectMultiScale(
                                     cameraFrame,
                                     faces,
                                     1.09,
                                     3,
                                     0 | CASCADE_SCALE_IMAGE,
                                     Size(30, 30));
        
        for (size_t i = 0; i < faces.size(); i++) {
            Mat faceROI = grayImage(faces[i]);
            eyeCascade.detectMultiScale(
                                         faceROI,
                                         eyes,
                                         1.1,
                                         2,
                                         0 | CASCADE_SCALE_IMAGE,
                                         Size(30, 30));
            
            for (size_t j = 0; j < eyes.size(); j++) {
                Point center(faces[i].x + eyes[j].x + eyes[j].width * 0.5,
                             faces[i].y + eyes[j].y + eyes[j].height * 0.5);
                int radius = cvRound((eyes[j].width + eyes[j].height) * 0.25);
                circle(cameraFrame, center, radius, Scalar(0, 255, 0), 2, 8, 0);
            }
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
}
