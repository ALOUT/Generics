//
//  GnFrustumCulling.h
//  Generics
//
//  Created by kinksaiz on 2014/05/12.
//
//

#ifndef __Generics__GnFrustumCulling__
#define __Generics__GnFrustumCulling__

#include "ofMain.h"
#include "GnMesh.h"

class GnFrustumCulling{
    
public:
    
    GnFrustumCulling();
    void keyPressed(int key);
    void mouseReleased(int x, int y, int button);
    
    void setup();
    void update();
    void draw();
    
    float nearDis;
    float farDis;
    float fov;
    
    int selectedCamera;
    ofCamera cameraA;
    ofEasyCam  cameraB;
    vector <ofCamera*> cams;
    
    GnMesh mesh;

};

#endif /* defined(__Generics__GnFrustumCulling__) */
