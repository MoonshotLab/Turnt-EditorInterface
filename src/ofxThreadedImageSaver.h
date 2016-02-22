//
//  ofxThreadedImageSaver.h
//  Turnt-EditorInterface
//
//  Created by Joe Longstreet on 2/17/16.
//
//

#ifndef ofxThreadedImageSaver_h
#define ofxThreadedImageSaver_h


#endif /* ofxThreadedImageSaver_h */



#include "ofMain.h"
#include "ofThread.h"

class ofThreadedImageSaver : public ofThread, public ofImage {
public:
    string fileName;
    
    void threadedFunction() {
        if(lock()) {
            save(fileName);
            cout << fileName << endl;
            unlock();
        } else {
            printf("ofxThreadedImageSaver - cannot save %s cos I'm locked", fileName.c_str());
        }
        stopThread();
    }
    
    void saveThreaded(string fileName) {
        this->fileName = fileName;
        startThread();
    }  
};  
