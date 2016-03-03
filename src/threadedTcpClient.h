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
    string tcpGuid;

    float videoPosition;
    float effectStrength;
    
    public:
    void makeConnection(){
        tcpClient.setup("127.0.0.1", 3001);
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
                        if(tcpValue == 1) videoPosition += .01;
                        else videoPosition -= .01;
                        
                        if(videoPosition < 0) videoPosition = 0;
                        if(videoPosition > 1) videoPosition = 1;
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