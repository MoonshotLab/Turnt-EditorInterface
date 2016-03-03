#include "ofApp.h"


//--------------------------------------------------------------
void ofApp::setup(){
    tcpClient.setup("127.0.0.1", TCP_PORT);
    
    videoPosition = 0.0;
    effectStrength = 1.0;

    ofSetVerticalSync(true);
    ofSetFrameRate(60);
    ofSetCircleResolution(3);
    
    fbo.allocate(1280, 720);

    videoPlayer.load("recording.mp4");
    videoPlayer.setVolume(0);
    videoPlayer.play();
    
    glitch.setup(&fbo);
    
	ofSetWindowShape(1366, 768);
	ofSetWindowPosition(1366, 0);

    recorder.setPrefix(ofToDataPath("recording/frame_"));
    recorder.setFormat("jpg");
    
    recorder.startThread();
    
    record = false;
    shouldQuit = false;
}


//--------------------------------------------------------------
void ofApp::update(){
	// this is required, do not know why
	videoPlayer.setPaused(true);

    // read tcp input from node server
    if(tcpClient.isConnected()){

        string tcpMessage = tcpClient.receiveRaw();
        vector<string> tokens = ofSplitString(tcpMessage, "|");
        
        if(shouldQuit){
            tcpClient.sendRaw("{ \"message\" : \"done\" }");
            std::exit(0);
        }
        
        // sometimes multiple messages get queued and get stuck, just ignore these
        if(tokens.size() == 3){
            // check to make shere the guid isn't already used
            if(tcpGuid.compare(tokens[0]) != 0){

                tcpGuid  = tokens[0];
                tcpInput = tokens[1];
                tcpValue = stoi(tokens[2]);
                
                // jog wheel manipulation
                if(tcpInput.compare("jog-wheel") == 0){
                    if(tcpValue == 1) videoPosition += .01;
                    else videoPosition -= .01;
                    
                    if(videoPosition < 0) videoPosition = 0;
                    if(videoPosition > 1) videoPosition = 1;
                }
                
                if(tcpInput.compare("slide") == 0){
                    if(tcpValue < 1) tcpValue = 1;
                    effectStrength = float(tcpValue)*0.25;
                }
            }
        }
    }
    
    // start effects
    fbo.begin();
    ofClear(0, 0, 0, 255);
    
    // update the video position
    videoPlayer.setPosition(videoPosition);
    videoPlayer.update();
    videoPlayer.draw(0, 0);
    
    // end effects
    fbo.end();

    // record the images
    if(record){
        ofImage img;
        img.grabScreen(0, 0, ofGetWindowWidth(), ofGetWindowHeight());
        recorder.addFrame(img);
    }
}


//--------------------------------------------------------------
void ofApp::draw(){
    // draw effects and video
    ofSetColor(255);
    glitch.generateFx(effectStrength);
    fbo.draw(0, 0);
}


//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if (key == '1') glitch.setFx(OFXPOSTGLITCH_CONVERGENCE      , true);
    if (key == '2') glitch.setFx(OFXPOSTGLITCH_GLOW             , true);
    if (key == '3') glitch.setFx(OFXPOSTGLITCH_SHAKER			, true);
    if (key == '4') glitch.setFx(OFXPOSTGLITCH_CUTSLIDER		, true);
    if (key == '5') glitch.setFx(OFXPOSTGLITCH_TWIST			, true);
    if (key == '6') glitch.setFx(OFXPOSTGLITCH_NOISE			, true);
    if (key == '7') glitch.setFx(OFXPOSTGLITCH_SLITSCAN         , true);
    if (key == '8') glitch.setFx(OFXPOSTGLITCH_SWELL			, true);
    
    if (key == 'r') record = true;
}



//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    if (key == '1') glitch.setFx(OFXPOSTGLITCH_CONVERGENCE      , false);
    if (key == '2') glitch.setFx(OFXPOSTGLITCH_GLOW             , false);
    if (key == '3') glitch.setFx(OFXPOSTGLITCH_SHAKER			, false);
    if (key == '4') glitch.setFx(OFXPOSTGLITCH_CUTSLIDER		, false);
    if (key == '5') glitch.setFx(OFXPOSTGLITCH_TWIST			, false);
    if (key == '6') glitch.setFx(OFXPOSTGLITCH_NOISE			, false);
    if (key == '7') glitch.setFx(OFXPOSTGLITCH_SLITSCAN         , false);
    if (key == '8') glitch.setFx(OFXPOSTGLITCH_SWELL			, false);

    if (key == 'r') record = false;
    if (key == 'q') shouldQuit = true;
    
}



//--------------------------------------------------------------
void ofApp::exit(){
}