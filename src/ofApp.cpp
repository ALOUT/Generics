#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    ofEnableAlphaBlending();
    ofEnableDepthTest();
    ofEnableSmoothing();
    
    setupGifEncorder();
    
    lighting.setup();
    
    //gnMesh.setup();

    frustum.setup();
    
    

}

//--------------------------------------------------------------
void ofApp::update(){
    
    updateGifEncorder();
    
    //gnMesh.update();

    frustum.update();
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    ofBackgroundGradient(ofColor::white, ofFloatColor(0 / 255.0, 60 / 255.0, 90 / 255.0,1.0));

    //gnMesh.draw();
    frustum.draw();
    
}

//--------------------------------------------------------------
void ofApp::setupGifEncorder(){
    nFrames = 0;
    frameW  = ofGetWindowWidth();
    frameH  = ofGetWindowHeight();
    
    //vid.initGrabber(frameW,frameH);
    grabbedImage.grabScreen(0,0,frameW,frameH);
    gifEncoder.setup(frameW, frameH, .25, 256);
    ofAddListener(ofxGifEncoder::OFX_GIF_SAVE_FINISHED, this, &ofApp::onGifSaved);

}

void ofApp::updateGifEncorder(){
    
    frameW  = ofGetWindowWidth();
    frameH  = ofGetWindowHeight();
    grabbedImage.grabScreen(0,0,frameW,frameH);
    gifEncoder.setup(frameW, frameH, .25, 256);
}

// ofxGifEncorder
void ofApp::onGifSaved(string &fileName) {
    cout << "gif saved as " << fileName << endl;
}

void ofApp::captureFrame() {
    
   // ofLog(OF_LOG_WARNING, ofToString(grabbedImage.getPixels(),0));
    ofLog(OF_LOG_WARNING, ofToString(grabbedImage.getWidth(),0));
    ofLog(OF_LOG_WARNING, ofToString(grabbedImage.getHeight(),0));
    
    gifEncoder.addFrame(
                        grabbedImage.getPixels(),
                        grabbedImage.getWidth(),
                        grabbedImage.getHeight(),
                        grabbedImage.getPixelsRef().getBitsPerPixel(),
                        .1f
                        );
    
    ofTexture * tx = new ofTexture();
    tx->allocate(frameW, frameH, GL_RGB);
    tx->loadData(grabbedImage.getPixels(), frameW, frameH, GL_RGB);
    txs.push_back(tx);
    
    nFrames++;
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    
    switch (key) {
        case 'g':
            captureFrame();
            break;
        case 's':
            cout <<"start saving\n" << endl;
            
            //string dayTime =  ofToString(ofGetYear(), 0) + ofToString(ofGetMonth(), 0) + ofToString(ofGetDay(), 0) + ofToString(ofGetHours(), 0) + ofToString(ofGetMinutes(), 0) + ofToString(ofGetSeconds(), 0);
            
            gifEncoder.save(ofToString(ofToString(ofGetYear(), 0) + ofToString(ofGetMonth(), 0) + ofToString(ofGetDay(), 0) + ofToString(ofGetHours(), 0) + ofToString(ofGetMinutes(), 0) + ofToString(ofGetSeconds(), 0), 0) + ".gif");
            break;
        default:
            break;
    }
 
    frustum.keyPressed(key);
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

    frustum.mouseReleased(x, y, button);
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
    gifEncoder.exit();
}
