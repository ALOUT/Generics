//
//  GnMotionPafume.h
//  Generics
//
//  Created by kinksaiz on 2014/05/12.
//
//

#ifndef __Generics__GnMotionPafume__
#define __Generics__GnMotionPafume__

#include "ofMain.h"

#include "ofxBvh.h"

class GnMotionPafume{
    
public:
    
    GnMotionPafume();
    
    void setup();
    void update();
    void draw();
    void exit();
    
	ofSoundPlayer track;
	vector<ofxBvh> bvh;
	
	float rotate;
	
	float play_rate, play_rate_t;
    
};

#endif /* defined(__Generics__GnMotionPafume__) */
