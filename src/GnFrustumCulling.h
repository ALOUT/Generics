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

#include "GnMotionPafume.h"

// 透視投射影クラス
class GnFrustumCulling{
    
public:
    
    GnFrustumCulling();
    void keyPressed(int key);
    void mouseReleased(int x, int y, int button);
    
    void setup();
    void update();
    void draw();
    void drawFrustum(ofCamera _camera);
    
    float nearDis;
    float farDis;
    float fov; // 視野の垂直方向画角（角度）大きいほど広角レンズ、小さいほど望遠レンズになる
    
    int selectedCamera;
    ofCamera cameraA;
    ofEasyCam  cameraB;
    ofCamera cameraC;
    ofCamera cameraD;
    ofCamera cameraE;
    vector <ofCamera*> cams;
    
    GnMesh mesh;
    
    GnMotionPafume pafume;

};

#endif /* defined(__Generics__GnFrustumCulling__) */
