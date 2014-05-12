#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    ofEnableAlphaBlending();
    ofEnableDepthTest();
    ofEnableSmoothing();
    
    setupGifEncorder();
    setupVideoRecorder();
    
    lighting.setup();
    
    frustum.setup();
    
}

//--------------------------------------------------------------
void ofApp::update(){
    
    updateGifEncorder();
    updateVideoRecorder();
    
    frustum.update();
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    ofBackgroundGradient(ofColor::white, ofFloatColor(0 / 255.0, 60 / 255.0, 90 / 255.0,1.0));

    frustum.draw();
    drawVideoRecorder();
    
}


//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    
    gifEncorderKeyPress(key);
    videoRecorderKeyPressed(key);
    frustum.keyPressed(key);
    
    if (key == 'f') {
        ofToggleFullscreen();
    }
    
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
    vidRecorder.close();
}

//--------------------------------------------------------------
void ofApp::audioIn(float *input, int bufferSize, int nChannels){
    if(bRecording)
        vidRecorder.addAudioSamples(input, bufferSize, nChannels);
}

void ofApp::setupVideoRecorder(){
    sampleRate = 44100;
    channels = 2;
    
    frameW  = ofGetWindowWidth();
    frameH  = ofGetWindowHeight();
    grabbedImage.grabScreen(0,0,frameW,frameH);

    vidRecorder.setFfmpegLocation(ofFilePath::getAbsolutePath("/usr/local/bin/ffmpeg")); // use this is you have ffmpeg installed in your data folder
        
    fileName = "testMovie2";
    fileExt = ".mp4"; // ffmpeg uses the extension to determine the container type. run 'ffmpeg -formats' to see supported formats
    
    // override the default codecs if you like
    // run 'ffmpeg -codecs' to find out what your implementation supports (or -formats on some older versions)
    vidRecorder.setVideoCodec("mpeg4");
    vidRecorder.setVideoBitrate("25000k");
    vidRecorder.setAudioCodec("mp3");
    vidRecorder.setAudioBitrate("192k");
    
    //    soundStream.listDevices();
    //    soundStream.setDeviceID(11);
    soundStream.setup(this, 0, channels, sampleRate, 256, 4);
    
    ofSetWindowShape(grabbedImage.getWidth(), grabbedImage.getHeight()	);
    bRecording = false;
    ofEnableAlphaBlending();
}

void ofApp::updateVideoRecorder(){
    
    frameW  = ofGetWindowWidth();
    frameH  = ofGetWindowHeight();
    
    if(bRecording){

        grabbedImage.grabScreen(0,0,frameW,frameH);
        vidRecorder.addFrame(grabbedImage.getPixelsRef());
    }
    
}

void ofApp::drawVideoRecorder(){
    
    stringstream ss;
    ss << "video queue size: " << vidRecorder.getVideoQueueSize() << endl
    << "audio queue size: " << vidRecorder.getAudioQueueSize() << endl
    << "FPS: " << ofGetFrameRate() << endl
    << (bRecording?"pause":"start") << " recording: r" << endl
    << (bRecording?"close current video file: c":"") << endl;

    ofSetColor(0,0,0,100);
    ofRect(0, 0, 260, 75);
    ofSetColor(255, 255, 255);
    ofDrawBitmapString(ss.str(),15,15);
}

void ofApp::videoRecorderKeyPressed(int key){
    
    if(key=='r'){
        bRecording = !bRecording;
        if(bRecording && !vidRecorder.isInitialized()) {
            //vidRecorder.setup(fileName+ofGetTimestampString()+fileExt, grabbedImage.getWidth(), grabbedImage.getHeight(), 30, sampleRate, channels);
            vidRecorder.setup(fileName+ofGetTimestampString()+fileExt, grabbedImage.getWidth(), grabbedImage.getHeight(), 30); // no audio
            //            vidRecorder.setup(fileName+ofGetTimestampString()+fileExt, 0,0,0, sampleRate, channels); // no video
            //          vidRecorder.setupCustomOutput(vidGrabber.getWidth(), vidGrabber.getHeight(), 30, sampleRate, channels, "-vcodec mpeg4 -b 1600k -acodec mp2 -ab 128k -f mpegts udp://localhost:1234"); // for custom ffmpeg output string (streaming, etc)
        }
    }
    if(key=='c'){
        bRecording = false;
        vidRecorder.close();
    }
    
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
    
    //ofLog(OF_LOG_NOTICE, ofToString(grabbedImage.getWidth(),0));
    //ofLog(OF_LOG_NOTICE, ofToString(grabbedImage.getHeight(),0));
    
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

void ofApp::gifEncorderKeyPress(int key){
    switch (key) {
        case 'g':
            captureFrame();
            break;
        case 's':
            cout <<"start saving\n" << endl;
            gifEncoder.save(ofToString(ofToString(ofGetYear(), 0) + ofToString(ofGetMonth(), 0) + ofToString(ofGetDay(), 0) + ofToString(ofGetHours(), 0) + ofToString(ofGetMinutes(), 0) + ofToString(ofGetSeconds(), 0), 0) + ".gif");
            break;
        default:
            break;
    }
}

