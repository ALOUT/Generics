//
//  GnMesh.h
//  Generics
//
//  Created by kinksaiz on 2014/05/12.
//
//

#ifndef __Generics__GnMesh__
#define __Generics__GnMesh__

#include "ofMain.h"

#define WIDTH 500
#define HEIGHT 500
#define NUM_PARTICLES WIDTH * HEIGHT

class GnMesh{
    
private:
    ofMesh mesh;
    int widthMesh;
    int heightMesh;
    
public:
    
    GnMesh();
    
    void setup();
    void update();
    void draw();
    
    // getter/setter
    void setMesh(ofMesh _mesh);
    ofMesh getMesh();
    void setWidthMesh(int _widthMesh);
    int getWidthMesh();
    void setHeightMesh(int _heightMesh);
    int getHeightMesh();

};

#endif /* defined(__Generics__GnMesh__) */
