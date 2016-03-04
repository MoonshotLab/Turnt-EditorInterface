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
    
    ofxPostGlitch glitch;
    ofVideoPlayer videoPlayer;
	ofVideoPlayer timerVideo;
    ofFbo fbo;
    ofxImageSequenceRecorder recorder;
    threadedTcpClient threadedTcpClient;

    float effectStrength;
    bool record;
};
