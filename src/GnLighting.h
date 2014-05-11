//
//  GnLighting.h
//  Generics
//
//  Created by kinksaiz on 2014/05/12.
//
//

#ifndef __Generics__GnLighting__
#define __Generics__GnLighting__

#include "ofMain.h"

class GnLighting{
    
private:
    
    ofLight light;
    
public:
    
    GnLighting();
    void setup();
    
    ofLight getLight();
    void setLight(ofLight _light);
    
};

#endif /* defined(__Generics__GnLighting__) */
