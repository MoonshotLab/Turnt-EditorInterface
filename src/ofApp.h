#pragma once

#include "ofMain.h"
#include "ofxPostGlitch.h"
#include "ofxImageSequenceRecorder.h"
#include "threadedTcpClient.h"

class ofApp : public ofBaseApp{
    
public:
    void setup();
    void update();
    void draw();
    void exit();
    
    void keyPressed(int key);
    void keyReleased(int key);
    
    float videoPosition;
    
    ofxPostGlitch glitch;
    ofVideoPlayer videoPlayer;
    ofFbo fbo;
    ofxImageSequenceRecorder recorder;
    threadedTcpClient threadedTcpClient;

    float effectStrength;
    
    bool record;
};
