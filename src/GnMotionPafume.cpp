//
//  GnMotionPafume.cpp
//  Generics
//
//  Created by kinksaiz on 2014/05/12.
//
//

#include "GnMotionPafume.h"

class Tracker
{
public:
	
	const ofxBvhJoint *joint;
	deque<ofVec3f> points;
	
	void setup(const ofxBvhJoint *o)
	{
		joint = o;
	}
	
	void update()
	{
		if (joint->getBvh()->isFrameNew())
		{
			const ofVec3f &p = joint->getPosition();
			
			points.push_front(joint->getPosition());
			
			if (points.size() > 15)
				points.pop_back();
		}
	}
	
	void draw()
	{
		if (points.empty()) return;
		
		glBegin(GL_TRIANGLE_STRIP);
		for (int i = 0; i < points.size() - 1; i++)
		{
			float a = ofMap(i, 0, points.size() - 1, 1, 0, true);
			
			ofVec3f &p0 = points[i];
			ofVec3f &p1 = points[i + 1];
			
			float d = p0.distance(p1);
			a *= ofMap(d, 3, 5, 0, 1, true);
			
			glColor4f(cos(0.5 * ofGetElapsedTimef()) * 255 / 255.0, 90 / 255.0, 60 / 255.0, a);
			glVertex3fv(points[i].getPtr());
		}
		glEnd();
	}
};

vector<Tracker*> trackers;
const float trackDuration = 64.28;

GnMotionPafume::GnMotionPafume(){
    
    
}

void GnMotionPafume::setup(){
    
	play_rate = play_rate_t = 1;
	rotate = 0;
    
	bvh.resize(10);
	
	// You have to get motion and sound data from http://www.perfume-global.com
	
	// setup bvh
	bvh[0].load("aachan.bvh");
	bvh[1].load("kashiyuka.bvh");
	bvh[2].load("nocchi.bvh");
    //bvh[3].load("buyou_web02.bvh");
	
	for (int i = 0; i < bvh.size(); i++)
	{
		bvh[i].setFrame(1);
	}
	
	track.loadSound("Perfume_globalsite_sound.wav");
	track.play();
	track.setLoop(true);
	
	// setup tracker
	for (int i = 0; i < bvh.size(); i++)
	{
		ofxBvh &b = bvh[i];
		
		for (int n = 0; n < b.getNumJoints(); n++)
		{
			const ofxBvhJoint *o = b.getJoint(n);
			Tracker *t = new Tracker;
			t->setup(o);
			trackers.push_back(t);
		}
	}
    
}

void GnMotionPafume::update(){
    
	rotate += 0.1;
	
	play_rate += (play_rate_t - play_rate) * 0.3;
	track.setSpeed(play_rate);
	
	float t = (track.getPosition() * trackDuration);
	t = t / bvh[0].getDuration();
	
	for (int i = 0; i < bvh.size(); i++)
	{
		bvh[i].setPosition(t);
		bvh[i].update();
	}
	
	for (int i = 0; i < trackers.size(); i++)
	{
		trackers[i]->update();
	}
}

void GnMotionPafume::draw(){
    
	glEnable(GL_DEPTH_TEST);
	
	ofEnableBlendMode(OF_BLENDMODE_ALPHA);
	
	ofPushMatrix();
	{

		// draw actor
		for (int i = 0; i < bvh.size(); i++)
		{
			bvh[i].draw();
		}
        
		// draw tracker
		glDisable(GL_DEPTH_TEST);
		ofEnableBlendMode(OF_BLENDMODE_ALPHA);
		
		//ofSetColor(ofColor::white, 80);
		for (int i = 0; i < trackers.size(); i++)
		{
			trackers[i]->draw();
		}
	}
	ofPopMatrix();
}

void GnMotionPafume::exit(){
    
    bvh.end();
    
}


