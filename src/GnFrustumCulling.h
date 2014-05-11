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

// 透視投射影クラス
class GnFrustumCulling{
    
public:
    
    GnFrustumCulling();
    void keyPressed(int key);
    void mouseReleased(int x, int y, int button);
    
    void setup();
    void update();
    void draw();
    void drawFrustum();
    
    float nearDis;
    float farDis;
    float fov; // 視野の垂直方向画角（角度）大きいほど広角レンズ、小さいほど望遠レンズになる
    
    int selectedCamera;
    ofCamera cameraA;
    ofEasyCam  cameraB;
    vector <ofCamera*> cams;
    
    GnMesh mesh;

};

#endif /* defined(__Generics__GnFrustumCulling__) */
