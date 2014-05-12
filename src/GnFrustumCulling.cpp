//
//  GnFrustumCulling.cpp
//  Generics
//
//  Created by kinksaiz on 2014/05/12.
//
//

#include "GnFrustumCulling.h"


GnFrustumCulling::GnFrustumCulling(){
    
}

void GnFrustumCulling::setup(){
    
    nearDis = 10.0;
    farDis = 600.0;
    fov = 80.0;
    
    selectedCamera = 1;
    cams.push_back(&cameraA);
    cams.push_back(&cameraB);
    cams.push_back(&cameraC);
    cams.push_back(&cameraD);
    cams.push_back(&cameraE);
    
    cameraA.setPosition(ofVec3f() + (200 * cameraA.getZAxis()));
    cameraB.setPosition(ofVec3f() + (200 * cameraA.getZAxis()));;
    cameraB.setDistance(500);
    
    cameraC.setPosition(ofVec3f() + (200 * cameraC.getZAxis()));
    cameraD.setPosition(ofVec3f() + (200 * cameraD.getZAxis()));
    cameraE.setPosition(ofVec3f() + (200 * cameraE.getZAxis()));

    
    mesh.setup();
    
    pafume.setup();
    
}

void GnFrustumCulling::update(){
    
    cameraA.rotateAround(0.8, ofVec3f(2, 1, 2), ofVec3f());
    cameraA.lookAt(ofVec3f());
    cameraA.setNearClip(nearDis);
    cameraA.setFarClip(farDis);
    cameraA.setFov(fov);
    
    cameraC.rotateAround(0.3, ofVec3f(0, 5, 2), ofVec3f());
    cameraC.lookAt(ofVec3f());
    cameraC.setNearClip(nearDis);
    cameraC.setFarClip(farDis);
    cameraC.setFov(fov);
    
    cameraD.rotateAround(0.5, ofVec3f(4, 2, 0), ofVec3f());
    cameraD.lookAt(ofVec3f());
    cameraD.setNearClip(nearDis);
    cameraD.setFarClip(farDis);
    cameraD.setFov(fov);
    
    cameraE.rotateAround(1.0, ofVec3f(2, 4, 9), ofVec3f());
    cameraE.lookAt(ofVec3f());
    cameraE.setNearClip(nearDis);
    cameraE.setFarClip(farDis);
    cameraE.setFov(fov);
    
    mesh.update();
    
    pafume.update();
    
}

//--------------------------------------------------------------
void drawBox(ofPoint tr, ofPoint tl, ofPoint br, ofPoint bl) {
    
    // a box for space...
    ofSetColor(255);
    ofLine(tl, tr);
    ofLine(tr, br);
    ofLine(br, bl);
    ofLine(bl, tl);
}

void GnFrustumCulling::drawFrustum(ofCamera _camera) {
    
    ofRectangle viewport = ofGetCurrentViewport();
    
    float ratio     = viewport.width / viewport.height;
    float nearH     = 2 * tan(_camera.getFov() / 2.0) * -_camera.getNearClip();
	float nearW     = nearH * ratio;
    float farH      = 2 * tan(_camera.getFov() / 2.0) * -_camera.getFarClip();
	float farW      = farH * ratio;
    
    ofVec3f p  = _camera.getPosition();
    ofVec3f l  = _camera.getLookAtDir();
    ofVec3f u  = _camera.getUpDir();
    
    ofVec3f fc = p + l * _camera.getFarClip();
	ofVec3f nc = p + l * _camera.getNearClip();
    
    ofSetColor(255);
    ofLine(nc, fc);
    
    ofVec3f up  = _camera.getUpDir();
    ofVec3f right = _camera.getXAxis();
    
    ofVec3f ftl = fc + (up * farH/2) - (right * farW/2);
    ofVec3f ftr = fc + (up * farH/2) + (right * farW/2);
	ofVec3f fbl = fc - (up * farH/2) - (right * farW/2);
	ofVec3f fbr = fc - (up * farH/2) + (right * farW/2);
    ofVec3f ntl = nc + (up * nearH/2) - (right * nearW/2);
	ofVec3f ntr = nc + (up * nearH/2) + (right * nearW/2);
	ofVec3f nbl = nc - (up * nearH/2) - (right * nearW/2);
	ofVec3f nbr = nc - (up * nearH/2) + (right * nearW/2);
    
    drawBox(ftl, ftr, fbl, fbr);    // draw far plane
    drawBox(ntl, ntr, nbl, nbr);    // draw near plane
    ofLine(ftl, ntl);
    ofLine(ftr, ntr);
    ofLine(fbl, nbl);
    ofLine(fbr, nbr);
    

    
}

void GnFrustumCulling::draw(){
    
    cams[selectedCamera]->begin();
    
    
    ofSetColor(255);
    // draw cameras
    for(int i=0; i<cams.size(); i++) {
        //drawFrustum(*cams[i]);
        cams[i]->draw();
    }
    
    
    mesh.draw();
    
    pafume.draw();
    
    //ofDrawBox(0,0,0,100);
    
    cams[selectedCamera]->end();
    
}


//--------------------------------------------------------------
void GnFrustumCulling::keyPressed(int key){
    
    if(key == '1') selectedCamera = 0;
    if(key == '2') selectedCamera = 1;
    if(key == '3') selectedCamera = 2;
    if(key == '4') selectedCamera = 3;
    if(key == '5') selectedCamera = 4;
    
    if(key == OF_KEY_DOWN) cameraB.setDistance(cameraB.getDistance()+2 * 10);
    if(key == OF_KEY_UP) cameraB.setDistance(cameraB.getDistance()-2 * 10);
    if(key == OF_KEY_RIGHT) cameraA.move(ofVec3f(1 * 10, 0, 0));
    if(key == OF_KEY_LEFT) cameraA.move(ofVec3f(-1 * 10, 0, 0));
}
//--------------------------------------------------------------
void GnFrustumCulling::mouseReleased(int x, int y, int button){
    cameraB.enableMouseInput();
}