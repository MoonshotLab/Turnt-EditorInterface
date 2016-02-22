#pragma once

#include "ofMain.h"
#include "ofxPostGlitch.h"
#include "ofxNetwork.h"
#include "ofxThreadedImageSaver.h"

#define TCP_PORT 3000

class ofApp : public ofBaseApp{
    
public:
    void setup();
    void update();
    void draw();
    void exit();
    
    void keyPressed(int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y );
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void mouseEntered(int x, int y);
    void mouseExited(int x, int y);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);
    
    float videoPosition;
    
    ofxPostGlitch glitch;
    ofVideoPlayer videoPlayer;
    ofFbo fbo;
    ofxTCPClient tcpClient;
    ofThreadedImageSaver threadedImageSaver;
    
    string tcpGuid;
    string tcpInput;
    int tcpValue;
    
    bool record;
};
