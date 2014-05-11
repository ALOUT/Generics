//
//  GnMesh.cpp
//  Generics
//
//  Created by kinksaiz on 2014/05/12.
//
//

#include "GnMesh.h"

GnMesh::GnMesh(){
    
    // init
    widthMesh = WIDTH;
    heightMesh = HEIGHT;

    
}

void GnMesh::setup(){
    
    // メッシュ頂点色を初期化
    for (int i = 0; i < widthMesh; i++) {
        for (int j = 0; j < heightMesh; j++) {
            mesh.addColor(ofFloatColor(0 / 255.0, 60/255.0, 90/255.0));
        }
    }
}

void GnMesh::update(){
    
    mesh.clearVertices(); // まず全ての頂点情報を削除
    
    // 全ての頂点の位置を更新して頂点情報として追加
    for (int i=0; i<widthMesh; i++) {
        for (int j=0; j<heightMesh; j++) {
            
            float x = sin(i * 0.1 + ofGetElapsedTimef()) * 50.0;
            float y = sin(j * 0.15 + ofGetElapsedTimef()) * 50.0;
            float z = x + y;
            mesh.addVertex(ofVec3f(i - widthMesh/2, j - heightMesh/2, z));
        }
    }
    
    
}

void GnMesh::draw(){
    
    // メッシュ頂点情報を描画
    glPointSize(1.0);
    glEnable(GL_POINT_SMOOTH);
    ofTranslate(ofGetWidth() / 2, ofGetHeight() / 2);
    mesh.drawVertices();
    
}

// getter/setter
ofMesh GnMesh::getMesh(){ return mesh; }
void GnMesh::setMesh(ofMesh _mesh){ mesh = _mesh;}

int GnMesh::getWidthMesh(){ return widthMesh; }
void GnMesh::setWidthMesh(int _widthMesh){ widthMesh = _widthMesh;}

int GnMesh::getHeightMesh(){ return heightMesh; }
void GnMesh::setHeightMesh(int _heightMesh){ heightMesh = _heightMesh;}



