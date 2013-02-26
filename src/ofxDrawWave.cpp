//
//  drawWave.cpp
//  VJ
//
//  Created by usm on 11/26/12.
//
//

#include "ofxDrawWave.h"
#include "billboard.h"
#include <iostream>
#include <vector>
#include <sstream>
#include <math.h>

//----------------------------------------------------------
void ofxWave::setup(){
    imgTemp.loadImage("images/emitter_.png");
    pLight.push_back(imgTemp);
    imgTemp.loadImage("images/1.png");
    pLight.push_back(imgTemp);
    imgTemp.loadImage("images/4.png");
    pLight.push_back(imgTemp);
    imgTemp.loadImage("images/2.png");
//    waveColor = ofColor(128,170,255);
    for(int i=0;i<BuSIZE;i++){
        ssff[i] = 0.0f;
    }
}

//----------------------------------------------------------
void ofxWave::update(){
    
}
//----------------------------------------------------------
void ofxWave::drawWaveCircle(){
}

//----------------------------------------------------------
void ofxWave::drawWaveLine(float _x, float _y, float _z, float _space){
    ofSetColor(*waveColor, oscValue->tFader[3][1]*255);
    glBegin(GL_LINE_STRIP);
    if(!bFiltering){
        for (int i = 0; i < BuSIZE; i++){
            glVertex3d( _space*i+_x, -soundStream[i]*scaleSize*oscValue->tFader[3][0]*2+_y, _z);
        }
    }else{
        for (int i = 0; i < BuSIZE; i++){
            ssff[i] = soundStream[i]*(1.0f-filterFacter) + ssff[i]*filterFacter;
            glVertex3d( _space*i+_x, -ssff[i]*scaleSize*oscValue->tFader[3][0]*2+_y, _z);
        }
    }
    glEnd();
}

//--------
void ofxWave::drawWaveLineCircleBill(float _x, float _y, float _z, float _space){
    ofNoFill();
    ofSetColor(*waveColor, oscValue->tFader[3][1]*255);
    ofBeginShape();
    if(!bFiltering){
        for (int i = 0; i < BuSIZE; i++){
            if(i%2==1){
                ofPushMatrix();
                ofTranslate( _space*i+_x, -soundStream[i]*scaleSize*oscValue->tFader[3][0]*2+_y, _z);
                billboard();
                ofCircle(0,0,0, soundStream[i]*scaleSize);
                ofPopMatrix();
            }
        }
    }else{
        for (int i = 0; i < BuSIZE; i++){
            if(i%2==1){
                ofPushMatrix();
                ofTranslate( _space*i+_x, -soundStream[i]*scaleSize*oscValue->tFader[3][0]*2+_y, _z);
                billboard();
                ofCircle(0,0,0, ssff[i]*scaleSize);
                ofPopMatrix();
            }
        }
    }
    ofEndShape();
}

//--------
void ofxWave::drawWaveLineCircle(float _x, float _y, float _z, float _space){
    ofNoFill();
    ofSetColor(*waveColor, oscValue->tFader[3][1]*255);
    ofBeginShape();
    if(!bFiltering){
        for (int i = 0; i < BuSIZE; i++){
            if(i%2==1){
                ofPushMatrix();
                ofTranslate( _space*i+_x, -soundStream[i]*scaleSize*oscValue->tFader[3][0]*2+_y, _z);
                ofCircle(0,0,0, soundStream[i]*scaleSize*oscValue->tFader[3][2]);
                ofPopMatrix();
            }
        }
    }else{
        for (int i = 0; i < BuSIZE; i++){
            if(i%2==1){
                ofPushMatrix();
                ofTranslate( _space*i+_x, -soundStream[i]*scaleSize*oscValue->tFader[3][0]*2+_y, _z);
                ofCircle(0,0,0, ssff[i]*scaleSize*oscValue->tFader[3][2]);
                ofPopMatrix();
            }
        }
    }
    ofEndShape();
}

//--------
void ofxWave::drawWaveLineParticle(float _x, float _y, float _z, float _space, int _step){
    ofFill();
    ofSetRectMode(OF_RECTMODE_CENTER);
//    ofColor parC = ofColor(waveColor->r +30, waveColor->g +20, waveColor->b -10);
    ofSetColor(*waveColor, oscValue->tFader[3][1]*255);
    ofBeginShape();
    if(!bFiltering){
        for (int i = 0; i < BuSIZE; i++){
            if(i%_step==0){
                ofPushMatrix();
                ofTranslate( _space*i+_x, -soundStream[i]*scaleSize*oscValue->tFader[3][0]*2+_y, _z);
                pLight[int(oscValue->tFader[4][2]*patMax)].draw(0,0,0, soundStream[i]*scaleSize*scalepl*oscValue->tFader[3][2], soundStream[i]*scaleSize*scalepl*oscValue->tFader[3][2]);
                ofPopMatrix();
            }
        }
    }else{
        for (int i = 0; i < BuSIZE; i++){
            if(i%_step==0){
                ofPushMatrix();
                ofTranslate( _space*i+_x, -soundStream[i]*scaleSize*oscValue->tFader[3][0]*2+_y, _z);
                pLight[int(oscValue->tFader[4][2]*patMax)].draw(0,0,0, ssff[i]*scaleSize*scalepl*oscValue->tFader[3][2], ssff[i]*scaleSize*scalepl*oscValue->tFader[3][2]);
                ofPopMatrix();
            }
        }
    }
    ofEndShape();
    ofSetRectMode(OF_RECTMODE_CORNER);
}

//--------
void ofxWave::drawWaveLineParticleBill(float _x, float _y, float _z, float _space, int _step){
    ofColor parC = ofColor(waveColor->r+30, waveColor->g+20, waveColor->b-10);
    ofSetColor(parC, oscValue->tFader[3][1]*255);
    ofBeginShape();
    if(!bFiltering){
        for (int i = 0; i < BuSIZE; i++){
            if(i%_step==0){
                ofPushMatrix();
                ofTranslate( _space*i+_x, -soundStream[i]*scaleSize*oscValue->tFader[3][0]*2+_y, _z);
                billboard();
                pLight[int(oscValue->tFader[4][2]*patMax)].draw(0,0,0, soundStream[i]*scaleSize*scalepl*oscValue->tFader[3][2], soundStream[i]*scaleSize*scalepl*oscValue->tFader[3][2]);
                ofPopMatrix();
//            if(i%_rand==0)pLight[0].draw( _space*i+_x, -soundStream[i]*scaleSize*_tF30+_y, _z, soundStream[i]*3000.0f, soundStream[i]*3000.0f);
            }
        }
    }else{
        for (int i = 0; i < BuSIZE; i++){
            if(i%_step==0){
                ofPushMatrix();
                ofTranslate( _space*i+_x, -soundStream[i]*scaleSize*oscValue->tFader[3][0]*2+_y, _z);
                billboard();
                pLight[int(oscValue->tFader[4][2]*patMax)].draw(0,0,0, ssff[i]*scaleSize*4*oscValue->tFader[3][2], ssff[i]*scaleSize*4*oscValue->tFader[3][2]);
                ofPopMatrix();
//                pLight[0].draw( _space*i+_x, -ssff[i]*scaleSize*_tF30+_y, _z, ssff[i]*3000.0f, ssff[i]*3000.0f);
            }
        }
    }
    ofEndShape();
}

//----------------------------------------------------------
void ofxWave::drawWaveLineY(float _x, float _y, float _z, float _space){
    ofColor parC = ofColor(waveColor->r+20, waveColor->g+10, waveColor->b-10);
    ofSetColor(parC, oscValue->tFader[3][1]*255);
    //    ofBeginShape();
    ofPushMatrix();
    ofRotateX(90);
    glBegin(GL_LINE_STRIP);
    for (int i = 0; i < BuSIZE; i++){
        //        ofVertex(i*space, -soundStream[i]*scaleSize*_tF30 + ofGetHeight()/2);
        glVertex3d( _space*i+_x, -soundStream[i]*scaleSize*oscValue->tFader[3][0]*2+_y, _z);
    }
    glEnd();
    ofPopMatrix();
    //    ofEndShape();
}

//----------------------------------------------------------
void ofxWave::drawWaveLineCircleY(float _x, float _y, float _z, float _space){
    ofSetColor(*waveColor, oscValue->tFader[3][1]*255);
    ofPushMatrix();
    ofRotateX(90);
    ofBeginShape();
    for (int i = 0; i < BuSIZE; i++){
        if(i%2==1){
            ofPushMatrix();
            ofTranslate( _space*i+_x, -soundStream[i]*scaleSize*oscValue->tFader[3][0]*2+_y, _z);
            billboard();
            ofCircle(0,0,0, soundStream[i]*scaleSize);
            ofPopMatrix();
            //            ofCircle(_space*i+_x, -soundStream[i]*scaleSize*_tF30+_y, _z, soundStream[i]*scaleSize);
        }
    }
    ofEndShape();
    ofPopMatrix();
    
}

//----------------------------------------------------------
void ofxWave::drawWaveLineParticleY(float _x, float _y, float _z, float _space){
    ofColor parC = ofColor(waveColor->r+20, waveColor->g+10, waveColor->b-10);
    ofPushMatrix();
    ofRotateX(90);
    ofBeginShape();
    int vv = 2;
    
    if(!bFiltering){
        for (int i = 0; i < BuSIZE; i++){
            ofSetColor(parC, oscValue->tFader[3][1]*255);
            pLight[int(oscValue->tFader[4][2]*patMax)].draw(par[i].x*_space, par[i].y*_space, par[i].z, soundStream[i]*3000.0f, soundStream[i]*3000.0f);
            
            ofSetColor(*waveColor, oscValue->tFader[3][1]*255);
            ofCircle(par[i].x*_space, par[i].y*_space, par[i].z, soundStream[i]*scaleSize);
            
            par[i].x = checkNum(par[i].x + ofRandom(-vv,vv) );
            par[i].y = checkNum(par[i].y + ofRandom(-vv,vv) );
            
        }
    }else{
        for (int i = 0; i < BuSIZE; i++){
            ssff[i] = soundStream[i]*(1.0-filterFacter) + ssff[i]*filterFacter;
            
            ofSetColor(parC, oscValue->tFader[3][1]*255);
            pLight[int(oscValue->tFader[4][2]*patMax)].draw(par[i].x*_space, par[i].y*_space, par[i].z, ssff[i]*3000.0f, ssff[i]*3000.0f);
            
            ofSetColor(*waveColor, oscValue->tFader[3][1]*255);
            ofCircle(par[i].x*_space, par[i].y*_space, par[i].z, ssff[i]*scaleSize);
            //          ofCircle(par[i].x*_space, par[i].y*_space, par[i].z, soundStream[i]*900.0f);
            
            par[i].x = checkNum(par[i].x + ofRandom(-vv,vv) );
            par[i].y = checkNum(par[i].y + ofRandom(-vv,vv) );
            
        }
    }
    ofEndShape();
    ofPopMatrix();
}

//----------------------------------------------------------
void ofxWave::drawWaveFields(){
    
}

//----------------------------------------------------------
float ofxWave::checkNum(float _value){
    if(_value < -ofGetWidth()){
        _value = _value + 2*ofGetWidth();
    }else if(_value > ofGetWidth()){
        _value = _value - 2*ofGetWidth();
    }
    return _value;
}

//----------------------------------------------------------
void ofxWave::drawWaveSphere(float _x, float _y, float _z, float _baseRad, ofColor _flowerColor){
    //    ofRotateY(ofGetElapsedTimeMillis()/10000);
    //    ofRotateZ(ofGetElapsedTimeMillis()/10000);
    float radiusSp = 1;
    float degSph = PI;
    float scale = 3600.0*oscValue->tFader[3][0];
    ofSetColor(_flowerColor, oscValue->tFader[3][1]*255);
    glBegin(GL_LINE_STRIP);
    for(int i=0;i<BuSIZE;i++){
        glVertex3d(_x + (radiusSp+(soundStream[i])*scale) * cos(PI * i/BuSIZE * 18) * sin(PI * i/BuSIZE),
                   _y + (radiusSp+(soundStream[i])*scale) * sin(PI * i/BuSIZE * 18) * sin(PI * i/BuSIZE),
                   _z + (radiusSp+(soundStream[i])*scale) * cos(PI * i/BuSIZE) );
    }
    glEnd();
    for(int i=0;i<BuSIZE;i++){
        ofPushMatrix();
        ofTranslate(_x+(radiusSp+(soundStream[i])*scale) * cos(PI * i/BuSIZE * 18) * sin(PI * i/BuSIZE),
                    _y+(radiusSp+(soundStream[i])*scale) * sin(PI * i/BuSIZE * 18) * sin(PI * i/BuSIZE),
                    _z+(radiusSp+(soundStream[i])*scale) * cos(PI * i/BuSIZE));
        billboard();
        pLight[int(oscValue->tFader[4][2]*patMax)].draw(0,0,0,10+abs(soundStream[i])*180, 10+abs(soundStream[i])*180);
        //        pLight[0].draw(_x+(radiusSp+(soundStream[i])*600) * cos(PI * i/BuSIZE * 18) * sin(PI * i/BuSIZE),
        //                 _y+(radiusSp+(soundStream[i])*600) * sin(PI * i/BuSIZE * 18) * sin(PI * i/BuSIZE),
        //                 _z+(radiusSp+(soundStream[i])*600) * cos(PI * i/BuSIZE), 10+abs(soundStream[i])*180, 10+abs(soundStream[i])*180);
        ofPopMatrix();
    }
}
