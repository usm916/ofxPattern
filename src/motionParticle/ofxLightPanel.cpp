//
//  ofxPanelLighting.cpp
//  LS_PatternGeenerate
//
//  Created by usm on 12/22/12.
//
// FF00FF00FF00FF00FF00FF00FF

#include "ofxLightPanel.h"

///////////////////////////////////////////////////////////////////////////////////////// ofxLightPanel

void ofxLightPanel::setup(){
    panel.loadImage("images/panel.png");
    noise.loadImage("images/panelNoise.png");
    lightLine.loadImage("images/slitLine.png");
    fftNum = (int)ofRandom(1,40);
}

void ofxLightPanel::draw(){
    if(oscValue->mToggle[1][5][0]) drawLine();
    if(oscValue->mToggle[1][4][0]){
        drawNoise();
        drawPanel();
    }
}

void ofxLightPanel::drawPanel(){
//    ofSetColor(255, 255 * oscValue->tFader[2][2] * ofMap(scale*magSqrt[fftNum],0,3.0,0,1.0));
    ofSetColor(*elementColor, 255 * oscValue->tFader[2][2] * ofMap(scale*magSqrt[fftNum],0,3.0,0,1.0));
    panel.draw(0,0,50,50);
}

void ofxLightPanel::drawNoise(){
    float size = 20;
    ofPushMatrix();
    ofRectMode(OF_RECTMODE_CENTER);
//    ofSetColor(255, 255 * oscValue->tFader[2][2] * ofMap(scale*magSqrt[fftNum],0,3.0,0,1.0));
    ofSetColor(*elementColor, 255 * oscValue->tFader[2][2] * ofMap(scale*magSqrt[fftNum],0,3.0,0,1.0));
    ofRotateZ(ofRandom(360));
    ofTranslate(-size/2, -size/2);
    noise.draw(0,0,70,70);
    ofRotateZ(ofRandom(360));
    ofTranslate(0, -size+ofRandom(60));
    noise.draw(0,0,70+ofRandom(size/4),70+ofRandom(size/4));
    ofRectMode(OF_RECTMODE_CORNER);
    ofPopMatrix();
//    cout << (float)magSqrt[10] << endl;
}

void ofxLightPanel::drawLine(){
    float jitter = 10.0;
    ofSetColor(*elementColor, 255 * oscValue->tFader[2][2] * ofMap(scale*magSqrt[fftNum-1],0,3.0,0,1.0));
    ofPushMatrix();
    for(int i=0;i<10;i++){
        ofTranslate(ofRandom(-jitter,jitter)*50, ofRandom(-jitter,jitter));
        lightLine.draw(0,0);
    }
    ofPopMatrix();
}

void ofxLightPanel::reSetNum(){
    fftNum = (int)ofRandom(10,55);
}

void ofxLightPanelSystem::setup(){
    for(int i=0;i<LightPanel.size();i++){
        LightPanel[i]->setup();
    }
}

///////////////////////////////////////////////////////////////////////////////////////// ofxLightPanelSystem

void ofxLightPanelSystem::draw(){
    checkPush();
    ofEnableBlendMode(OF_BLENDMODE_ADD);
    for (int i=0;i<LightPanel.size();i++){
        ofPushMatrix();
        ofTranslate(50*i,0);
        LightPanel[i]->draw();
        ofPopMatrix();
    }
    ofEnableBlendMode(OF_BLENDMODE_ALPHA);
}

void ofxLightPanelSystem::reSetNumSystem(){
    for (int i=0;i<LightPanel.size();i++){
        LightPanel[i]->reSetNum();
    }
}

void ofxLightPanelSystem::checkPush(){
    if(oscValue->mPush[7][1][0]==1){
        reSetNumSystem();
    }
    
}

