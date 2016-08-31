#include "ofApp.h"

string effectsLibrary[6] = { OFXPOSTGLITCH_CONVERGENCE, OFXPOSTGLITCH_CUTSLIDER, OFXPOSTGLITCH_TWIST, OFXPOSTGLITCH_NOISE, OFXPOSTGLITCH_SLITSCAN, OFXPOSTGLITCH_SWELL };

//--------------------------------------------------------------
void ofApp::setup(){

	// shuffle the array of effects
	random_shuffle(&effectsLibrary[0], &effectsLibrary[5]);

    threadedTcpClient.makeConnection();
	threadedTcpClient.startThread();

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
    
    record = false;
    recorder.startThread();
}


//--------------------------------------------------------------
void ofApp::update() {
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

	// ask for effect strength and apply accordingly
	effectStrength = threadedTcpClient.getEffectStrength();
	if (effectStrength > 5) {
		glitch.setFx(effectsLibrary[0], true);
	}
	else {
		glitch.setFx(effectsLibrary[1], false);
		glitch.setFx(effectsLibrary[2], false);
	}

	if (effectStrength > 15) {
		glitch.setFx(effectsLibrary[1], true);
	}
	else {
		glitch.setFx(effectsLibrary[2], false);
	}

	if (effectStrength > 25) {
		glitch.setFx(effectsLibrary[2], true);
	}


    // draw the video before within the fbo
    videoPlayer.update();
    videoPlayer.draw(171, 0, 1024, 768);

	// end effects
	fbo.end();
    

    
    // update the timer video
	timerVideo.update();

    

	// record the images
    if (record && recorder.isThreadRunning()){
        ofImage img;
        img.grabScreen(171, 0, 1024, ofGetWindowHeight());
        recorder.addFrame(img);
	}
    
	// start recording after a few milliseconds
	if (ofGetElapsedTimeMillis() > 1000) {
		record = true;
	}

	// stop recording after 17 seconds
	if (ofGetElapsedTimeMillis() > 17000) {
		record = false;
        ofApp::exit();
	}
}


//--------------------------------------------------------------
void ofApp::draw(){
    // draw effects and video
    ofSetColor(255);
    glitch.generateFx(effectStrength);
    fbo.draw(0, 0);
    
    // draw the timer video
    timerVideo.draw(1248, 660, 84, 87);
}


//--------------------------------------------------------------
void ofApp::exit(){
    recorder.waitForThread();
    threadedTcpClient.sendMessage("{ \"message\" : \"done\" }");
    std::exit(0);
}