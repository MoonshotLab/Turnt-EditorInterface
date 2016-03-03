#pragma once

#include "ofMain.h"
#include "ofxPostGlitch.h"
#include "ofxNetwork.h"
#include "ofxImageSequenceRecorder.h"

#define TCP_PORT 3001

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
    ofxTCPClient tcpClient;
    ofxImageSequenceRecorder recorder;
    
    string tcpGuid;
    string tcpInput;
    int tcpValue;
    float effectStrength;
    
    bool record;
};
