#include "ofApp.h"


//--------------------------------------------------------------
void ofApp::setup(){
    tcpClient.setup("127.0.0.1", TCP_PORT);
    
    videoPosition = 0.0;

    ofSetVerticalSync(true);
    ofSetFrameRate(60);
    ofSetCircleResolution(3);
    
    fbo.allocate(1280, 720);

    videoPlayer.load("sample.mov");
    videoPlayer.setVolume(0);
    videoPlayer.play();
    
    glitch.setup(&fbo);
    
    record = false;
}

//--------------------------------------------------------------
void ofApp::update(){
    
    // read tcp input from node server
    if(tcpClient.isConnected()){

        string tcpMessage = tcpClient.receiveRaw();
        vector<string> tokens = ofSplitString(tcpMessage, "|");
        
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
                    
                }
            }
        }
    }

    fbo.begin();
    ofClear(0, 0, 0, 255);
    
    // update the video position
    videoPlayer.setPosition(videoPosition);
    videoPlayer.update();
    videoPlayer.draw(0, 0);
    
    fbo.end();
    
    if(record){
        string fileName = ofToString(ofGetFrameNum()) + ".png";
        threadedImageSaver.grabScreen(0, 0, 1280, 720);
        threadedImageSaver.saveThreaded(fileName);
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofSetColor(255);

    glitch.generateFx();
    
    fbo.draw(0, 0);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if (key == '1') glitch.setFx(OFXPOSTGLITCH_CONVERGENCE      , true);
    if (key == '2') glitch.setFx(OFXPOSTGLITCH_GLOW             , true);
    if (key == '3') glitch.setFx(OFXPOSTGLITCH_SHAKER			, true);
    if (key == '4') glitch.setFx(OFXPOSTGLITCH_CUTSLIDER		, true);
    if (key == '5') glitch.setFx(OFXPOSTGLITCH_TWIST			, true);
    if (key == '6') glitch.setFx(OFXPOSTGLITCH_OUTLINE          , true);
    if (key == '7') glitch.setFx(OFXPOSTGLITCH_NOISE			, true);
    if (key == '8') glitch.setFx(OFXPOSTGLITCH_SLITSCAN         , true);
    if (key == '9') glitch.setFx(OFXPOSTGLITCH_SWELL			, true);
    if (key == '0') glitch.setFx(OFXPOSTGLITCH_INVERT			, true);
    
    if (key == 'q') glitch.setFx(OFXPOSTGLITCH_CR_HIGHCONTRAST  , true);
    if (key == 'w') glitch.setFx(OFXPOSTGLITCH_CR_BLUERAISE     , true);
    if (key == 'e') glitch.setFx(OFXPOSTGLITCH_CR_REDRAISE      , true);
//    if (key == 'r') glitch.setFx(OFXPOSTGLITCH_CR_GREENRAISE	, true);
    if (key == 't') glitch.setFx(OFXPOSTGLITCH_CR_BLUEINVERT	, true);
    if (key == 'y') glitch.setFx(OFXPOSTGLITCH_CR_REDINVERT     , true);
    if (key == 'u') glitch.setFx(OFXPOSTGLITCH_CR_GREENINVERT	, true);
    if (key == 'r') record = true;
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    if (key == '1') glitch.setFx(OFXPOSTGLITCH_CONVERGENCE      , false);
    if (key == '2') glitch.setFx(OFXPOSTGLITCH_GLOW             , false);
    if (key == '3') glitch.setFx(OFXPOSTGLITCH_SHAKER			, false);
    if (key == '4') glitch.setFx(OFXPOSTGLITCH_CUTSLIDER		, false);
    if (key == '5') glitch.setFx(OFXPOSTGLITCH_TWIST			, false);
    if (key == '6') glitch.setFx(OFXPOSTGLITCH_OUTLINE          , false);
    if (key == '7') glitch.setFx(OFXPOSTGLITCH_NOISE			, false);
    if (key == '8') glitch.setFx(OFXPOSTGLITCH_SLITSCAN         , false);
    if (key == '9') glitch.setFx(OFXPOSTGLITCH_SWELL			, false);
    if (key == '0') glitch.setFx(OFXPOSTGLITCH_INVERT			, false);
    
    if (key == 'q') glitch.setFx(OFXPOSTGLITCH_CR_HIGHCONTRAST  , false);
    if (key == 'w') glitch.setFx(OFXPOSTGLITCH_CR_BLUERAISE     , false);
    if (key == 'e') glitch.setFx(OFXPOSTGLITCH_CR_REDRAISE      , false);
//    if (key == 'r') glitch.setFx(OFXPOSTGLITCH_CR_GREENRAISE	, false);
    if (key == 't') glitch.setFx(OFXPOSTGLITCH_CR_BLUEINVERT	, false);
    if (key == 'y') glitch.setFx(OFXPOSTGLITCH_CR_REDINVERT     , false);
    if (key == 'u') glitch.setFx(OFXPOSTGLITCH_CR_GREENINVERT	, false);
    
    if (key == 'a') glitch.setFx("original"                     , false);
    if (key == 'r') record = false;
    
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
//    if(x > 0 && x<= 1280){
//        videoPosition = x/float(ofGetWidth());
//    }
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){
    
}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){
    
}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){
    
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){
    
}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){
    
}


//--------------------------------------------------------------
void ofApp::exit(){
//    screenGrabber.stopThread();
}