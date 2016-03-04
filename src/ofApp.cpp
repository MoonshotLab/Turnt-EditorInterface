#include "ofApp.h"


//--------------------------------------------------------------
void ofApp::setup(){
    threadedTcpClient.makeConnection();
	threadedTcpClient.startThread(false, false);

    videoPosition = 0.0;
    effectStrength = 1.0;

    ofSetVerticalSync(true);
    ofSetCircleResolution(3);
    
    fbo.allocate(1366, 768);

	timerVideo.load("clock.mov");
	timerVideo.setLoopState(OF_LOOP_NONE);
	timerVideo.play();

    videoPlayer.load("recording.mp4");
    videoPlayer.setVolume(0);
    videoPlayer.play();
	threadedTcpClient.setVideoPlayer(videoPlayer);
    
    glitch.setup(&fbo);
    
	ofSetWindowShape(1366, 768);
	ofSetWindowPosition(0, 0);

    recorder.setPrefix(ofToDataPath("recording/frame_"));
    recorder.setFormat("jpg");
    
    recorder.startThread();
    
    record = false;
}


//--------------------------------------------------------------
void ofApp::update(){
    // start effects
    fbo.begin();
    ofClear(255, 255, 255, 255);
    
    // ask for video position
	// if none has been set, let play continue
	float pos = threadedTcpClient.getVideoPosition();
	if (pos != -1) {
		videoPlayer.setPosition(threadedTcpClient.getVideoPosition());
		videoPlayer.setPaused(true);
	}

	// ask for effect strength
    effectStrength = threadedTcpClient.getEffectStrength();
    
    // draw the video before the fbo
    videoPlayer.update();
    videoPlayer.draw(171, 0, 1024, 768);

	timerVideo.update();
	timerVideo.draw(1248, 660, 84, 87);

	// end effects
	fbo.end();

	// record the images
	if (record) {
		ofImage img;
		img.grabScreen(171, 0, 1024, ofGetWindowHeight());
		recorder.addFrame(img);
	}
    
	// start recording after 2 seconds
	if (ofGetElapsedTimeMillis() > 2000) {
		record = true;
	}

    // close after 17 seconds
    if(ofGetElapsedTimeMillis() > 17000){
        threadedTcpClient.sendMessage("{ \"message\" : \"done\" }");
        std::exit(0);
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
}



//--------------------------------------------------------------
void ofApp::exit(){
}