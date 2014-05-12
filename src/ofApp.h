#pragma once

#include "ofMain.h"
#include "GnLfo.h"
#include "GnMesh.h"
#include "Gn3DObject.h"
#include "GnTextObject.h"
#include "GnLighting.h"
#include "GnFrustumCulling.h"

// addons
#include "ofxGifEncoder.h"
#include "ofxVideoRecorder.h"




class ofApp : public ofBaseApp{
    
public:
    void setup();
    void update();
    void draw();
    
    void keyPressed(int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y );
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);
    
    GnMesh gnMesh;
    GnLighting lighting;
    GnFrustumCulling frustum;
    
    // addons (ofxGifEncoder)
    void setupGifEncorder();
    void updateGifEncorder();
    void onGifSaved(string & fileName);
    void gifEncorderKeyPress(int key);
    void exit();
    void captureFrame();
    vector <ofTexture *> txs; // for previewing
    vector <ofxGifFrame *> pxs;
    int frameW, frameH;
    int nFrames;
    ofImage grabbedImage; //画面をキャプチャーしたイメージデータ

    ofxGifEncoder gifEncoder;
    
    // addons (ofxVideoRecorder)
    void audioIn(float * input, int bufferSize, int nChannels);
    ofVideoGrabber      vidGrabber;
    
    void setupVideoRecorder();
    void updateVideoRecorder();
    void drawVideoRecorder();
    void videoRecorderKeyPressed(int key);
    
    ofxVideoRecorder    vidRecorder;
    ofSoundStream       soundStream;
    bool bRecording;
    int sampleRate;
    int channels;
    string fileName;
    string fileExt;
    
    ofFbo recordFbo;
    ofPixels recordPixels;
    
};
