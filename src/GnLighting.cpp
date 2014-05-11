//
//  GnLighting.cpp
//  Generics
//
//  Created by kinksaiz on 2014/05/12.
//
//

#include "GnLighting.h"

GnLighting::GnLighting(){
    
    // init
    
    
    
}

void GnLighting::setup(){
    
    // ライティングを使用可能に
    light.enable();
    // スポットライトを配置
    light.setSpotlight();
    // 照明の位置
    light.setPosition(-100, 200, 200);
    
    // 環境反射光の色
    light.setAmbientColor(ofFloatColor(0.5, 0.2, 0.2, 1.0));
    // 拡散反射光の色
    light.setDiffuseColor(ofFloatColor(0.5, 0.5, 1.0));
    // 鏡面反射光の色
    light.setSpecularColor(ofFloatColor(0.5, 1.0, 0.8));
    
    
}

// getter/setter
ofLight GnLighting::getLight(){ return light; }
void GnLighting::setLight(ofLight _light){ light = _light; }