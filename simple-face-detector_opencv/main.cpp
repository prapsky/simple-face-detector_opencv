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
    
    CascadeClassifier faceCascade, eyeCascade, smileCascade;
    
    if (!faceCascade.load("lbpcascade_frontalface.xml")) {
        cout << "Failed to load cascade classfier for face!" << endl;
        return -1;
    }
    
    if (!eyeCascade.load("haarcascade_eye.xml")) {
        cout << "Failed to load cascade classfier for eyes!" << endl;
        return -1;
    }
    
    if (!smileCascade.load("haarcascade_smile.xml")) {
        cout << "Failed to load cascade classfier for smile!" << endl;
        return -1;
    }
    
    while (true) {
        Mat cameraFrame, grayImage;
        vector<Rect> faces, eyes, smiles;
        
        capture.read(cameraFrame);
        cvtColor(cameraFrame, grayImage, COLOR_BGR2GRAY);
        equalizeHist(grayImage, grayImage);
        
        faceCascade.detectMultiScale(
                                     cameraFrame,
                                     faces,
                                     1.3,
                                     5,
                                     0 | CASCADE_SCALE_IMAGE,
                                     Size(30, 30));
        
        for (size_t i = 0; i < faces.size(); i++) {
            Mat faceROI = grayImage(faces[i]);
            eyeCascade.detectMultiScale(
                                         faceROI,
                                         eyes,
                                         1.1,
                                         22,
                                         0 | CASCADE_SCALE_IMAGE,
                                         Size(30, 30));
            
            smileCascade.detectMultiScale(
                                        faceROI,
                                        smiles,
                                        5,
                                        22,
                                        0 | CASCADE_SCALE_IMAGE,
                                        Size(30, 30));
            
            for (size_t j = 0; j < eyes.size(); j++) {
                Point center(faces[i].x + eyes[j].x + eyes[j].width * 0.5,
                             faces[i].y + eyes[j].y + eyes[j].height * 0.5);
                int radius = cvRound((eyes[j].width + eyes[j].height) * 0.25);
                circle(cameraFrame, center, radius, Scalar(0, 255, 0), 2, 8, 0);
            }
            
            for (size_t k = 0; k < smiles.size(); k++) {
                Point center(faces[i].x + smiles[k].x + smiles[k].width * 0.5,
                             faces[i].y + smiles[k].y + smiles[k].height * 0.5);
                ellipse(cameraFrame, center, Size(smiles[k].width * 0.5, smiles[k].height * 0.5), 0, 0, 360, Scalar(255, 0, 0), 2, 8, 0);
            }
            
            rectangle(cameraFrame, faces[i], Scalar(0, 0, 255), 2);
        }
        
        imshow("FaceDetector", cameraFrame);
        
        if (waitKey(50) >= 0) {
            break;
        }
    }
}
