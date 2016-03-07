//
//  threadedTcpClient.h
//  Turnt-EditorInterface
//
//  Created by Joe Longstreet on 3/3/16.
//
//


#include "ofxNetwork.h"


class threadedTcpClient : public ofThread{
    ofxTCPClient tcpClient;
	ofVideoPlayer videoPlayer;
    string tcpGuid;

    float videoPosition = -1.0;
    float effectStrength = -1.0;
    
    public:
    void makeConnection(){
        tcpClient.setup("127.0.0.1", 3001);
    }

	void setVideoPlayer(ofVideoPlayer player) {
		videoPlayer = player;
	}

    float getEffectStrength(){
        return effectStrength;
    }

    float getVideoPosition(){
        return videoPosition;
    }

    void parseTcpMessages(){
        // read tcp input from node server
        if(tcpClient.isConnected()){
            
            string tcpMessage = tcpClient.receiveRaw();
            vector<string> tokens = ofSplitString(tcpMessage, "|");
            
            // sometimes multiple messages get queued and get stuck, just ignore these
            if(tokens.size() == 3){
                // check to make shere the guid isn't already used
                if(tcpGuid.compare(tokens[0]) != 0){
                    
                    tcpGuid         = tokens[0];
                    string tcpInput = tokens[1];
                    int tcpValue    = stoi(tokens[2]);
                    
                    // jog wheel manipulation
                    if(tcpInput.compare("jog-wheel") == 0){
						// if no position is yet set, set one
						if (videoPosition == -1) {
							videoPosition = videoPlayer.getPosition();
						}

                        if(tcpValue == 1) videoPosition += .01;
                        else videoPosition -= .01;
                        
                        if(videoPosition <= 0) videoPosition = 1;
                        if(videoPosition >= 1) videoPosition = 0;
                    }
                    
                    // slider manipulation
                    if(tcpInput.compare("slide") == 0){
                        if(tcpValue < 1) tcpValue = 1;
                        effectStrength = float(tcpValue)*0.25;
                    }
                }
            }
        }
    }
    
    void sendMessage(string message){
        tcpClient.sendRaw(message);
    }

    void threadedFunction(){
        while(isThreadRunning()){
            parseTcpMessages();
        }
    }
};