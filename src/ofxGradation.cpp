//
//  ofxGradation.cpp
//  LS_PatternGeenerate
//
//  Created by usm on 12/9/12.
//
//

#include "ofxGradation.h"

void ofxGradationGenerator::draw(float _width){
    int repetitionX = ofGetWidth()/_width;
    for(int i=0;i<(int)repetitionX;i++){
        ofPushMatrix();
        ofSetColor(255, 255, 255);
//        ofTranslate(i*_width, 0);
        gradation.draw(0,0,300,64);
//        gradation.bind();
//        ofRect(0,0,1920,68);
//        mesh.drawPlane();
//        gradation.unbind();
        ofPopMatrix();
    }
}

void ofxGradationGenerator::setup(int w, int h){
    gradation.allocate(w,h,GL_RGB);
    colorPixels 		= new unsigned char [w*h*3];

    // color pixels, use w and h to control red and green
	for (int i = 0; i < w; i++){
		for (int j = 0; j < h; j++){
			colorPixels[(j*w+i)*3 + 0] = ofMap(i, 0, w, 0, 255);	// r
			colorPixels[(j*w+i)*3 + 1] = ofMap(j, 0, h, 255, 0);	// g
			colorPixels[(j*w+i)*3 + 2] = 0; // b
		}
	}
    gradation.loadData(colorPixels, w,h, GL_RGB);

    buildMesh(w, h);
}

void ofxGradationGenerator::buildMesh(int _width, int _height){
    mesh.buildPlaneCenter(_width, _height);
}
//////////////////////////////////////////////////

void ofxGradation::draw(){
    ofPushMatrix();
//    ofTranslate(0, 17);
    gg.draw(1920);
    ofPopMatrix();
}

void ofxGradation::setup(int _width, int _height){
    gg.setup(_width, _height);
}

/*
void testApp::drawNodeCursor(float _x, float _y, float _px, float _py, float _size){
    
    ofColor(255);
    ofPushMatrix();
    ofTranslate( _x, _y);
    ofLine(-20, 0, 20, 0);
    ofLine(0, -20, 0, 20);
    ofCircle(0, 0, _size);
    ofCircle(0, 0, _size*1.1);
    
    ofVec2f rote = ofVec2f(_x-_px, _y-_py);
    float scalar = rote.distance(ofVec2f(.0,.0));
    
    rote.normalize();
    if(rote.y<0){
        ofRotateZ( -acos(rote.x)*180/PI );
    }else{
        ofRotateZ( acos(rote.x)*180/PI );
    }
    
    if(scalar>4.0){
        ofFill();
        ofRect(40-15, -5, 30, 10);
        ofNoFill();
    }
    ofPopMatrix();
}

void testApp::drawControlWire(float _x, float _y){
    int blur = 30;
    ofSetColor(255);
    ofPushMatrix();
    
    ofTranslate( _x, _y);
    ofLine( 0,0, ofRandom(-blur,blur), ofGetHeight()*2);
    ofSetColor(255, 128);
    ofLine( 0,0, ofRandom(-blur,blur), ofGetHeight()*2);
    ofLine( 0,0, ofRandom(-blur,blur), ofGetHeight()*2);
    
    ofPopMatrix();
}

void testApp::setScreenMeshVertex(){
    for(int i=0;i<scrVboMesh.getNumVertices();i++){
        ofSetColor(255);
        ofPoint vi = scrVboMesh.getVertex(i);
        ofCircle(vi, 10);
        if(isMouseDragged && checkAreaRect(mouseX, mouseY, vi, ofVec2f(50,50) ) ){
            scrVboMesh.setVertex(i, ofPoint(mouseX, mouseY, 0.0));
        }
    }
    scrVboMesh.disableTextures();
    scrVboMesh.drawWireframe();
    scrVboMesh.enableTextures();
}
*/
