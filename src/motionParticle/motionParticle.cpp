//
//  motionParticle.cpp
//  testMotionGraphics
//
//  Created by Takuto Usami on 9/29/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//
#include "motionParticle.h"
#include "billboard.h"

//-----------------------------
void MotionParticle::setup(){
    snow0.loadImage("images/snow0.png");
    snow1.loadImage("images/snow1.png");
    
    times = 0;
    timesCount = 0;
    timing = 12+ofRandom(-6,6);
    tDelay = ofRandom(20);
    tRotate = ofRandom(-10,10);
    tRotateT = ofRandom(-10,10);
    tRotMlt = ofRandom(30,60);
    
    posff = 0.3;
//    radius = 25;
    timeRandomSeed = ofRandom(5000,12000);
    randomTimeScale = ofRandom(0,2);
    scaleSize = ofRandom(90,260);
    size = 1.0;
    
    assignFreq = (int)ofRandom(0,70);
    set = 2.0;
    flow = ofPoint(ofRandom(-set,set),ofRandom(-set,set),ofRandom(-set,set));

    targetPos = pos = ofPoint( ofRandom(-screenSize->x, screenSize->x), ofRandom(-screenSize->y, screenSize->y) , ofRandom(-screenSize->y, screenSize->y) );
}

//-----------------------------
void MotionParticle::updatePos(){    
    timeCount();
    if(looseQaualyValue(amr(timeInFrame*tRotate,90),
                        amr(timeInFrame*tRotateT,90),
                        0.1)
        )rippleLife = 0;
    rippleLife += 1;
    if(times >= 0 && timesCount<2 && (times%timing)==(timing-1)){
        timesCount += 1;
        setTarget(90);
    }
    frameCounter += 1;
//    float ss = 1.7;
    if( -screenSize->x > pos.x){
        int posd;
        posd = screenSize->x - pos.x;
        pos.x = posd%(int)screenSize->x;
    }
    if( screenSize->x < pos.x)pos.x = -screenSize->x;
    if( -screenSize->y > pos.y)pos.y = screenSize->y;
    if( screenSize->y < pos.y)pos.y = -screenSize->y;
    if( -screenSize->y/9 > pos.z)pos.z = screenSize->y;
    if( screenSize->y/9 < pos.z)pos.z = -screenSize->y;
}

void MotionParticle::updateToTarget(){
    pos = targetPos*posff + pos*(1-posff);
}

void MotionParticle::updateToRandomWalk(){
    pos = pos + ofPoint(ofRandom(-set,set),ofRandom(-set,set),ofRandom(-set/15,set/15));;
}

void MotionParticle::reSetPos(){
    vt.addValue(&pos, ofPoint( ofRandom(- screenSize->x, screenSize->x), ofRandom(- screenSize->y, screenSize->y) , ofRandom(-screenSize->y, screenSize->y) ), 200, 0);
}

//-----------------------------
void MotionParticle::draw(float _opacity){
    ofSetColor(*baseColor,_opacity);
    timeInFrame = frameCounter%1080;
    ofNoFill();
    ofPushMatrix();
    ofSetRectMode(OF_RECTMODE_CENTER);
    ofSetLineWidth(1);
    ofTranslate(pos);
//    ofCircle(ofPoint(0,0,0), radius);
    
    int x = ofRandom(0,1.5);
    size = sqrt(magSqrt[20]) * scaleSize * ofMap(ofNoise(elapsedTime, timeRandomSeed), 0.1, 1, 0.5, 1.0);
    if(size>400)size=400;
    if(x==0){
        snow0.draw(0,0,0, 30+size, 30+size);
//        snow0->draw(0,0,0, 20+size, 20+size);
    }else{
        snow1.draw(0,0,0, 30+size, 30+size);
//        snow1->draw(0,0,0, 20+size, 20+size);
    }
//    cout << assignFreq <<" : "<< (float)magSqrt[assignFreq] << ", " << (float)scaledVol[4] << endl;
    ofPushMatrix();
    ofRotateZ(timeInFrame/tRotate);
    ofLine(0,radius+10,0,radius*2.3);
    ofPopMatrix();
    ofRotateZ(timeInFrame/tRotateT);
    ofPushMatrix();
    ofLine(0,-radius-10,0,-radius*2.3);
    ofPopMatrix();
    
    ofSetRectMode(OF_RECTMODE_CORNER);
    ofSetLineWidth(1);
    ofPopMatrix();
    
    elapsedTime += randomTimeScale*ofRandom(1.5,3.3);;
}

//-----------------------------
void MotionParticle::drawBill(float _opacity){
    ofSetColor(*baseColor, _opacity);
    timeInFrame = frameCounter%1080;
    ofNoFill();
    ofPushMatrix();
    
    ofSetLineWidth(1);
    ofTranslate(pos);
    billboard();
    ofCircle(ofPoint(0,0,0), radius);
    
    ofPushMatrix();
    ofRotateZ(timeInFrame/tRotate);
    ofLine(0,radius+10,0,radius*2.3);
    ofPopMatrix();
    ofRotateZ(timeInFrame/tRotateT);
    ofPushMatrix();
    ofLine(0,-radius-10,0,-radius*2.3);
    ofPopMatrix();
    
    ofSetLineWidth(1);
    drawRipple();
    ofPopMatrix();
}

//-----------------------------
void MotionParticle::setTarget(){
//    setTargetWide(200);
    setTarget(200);
    times = -tDelay;
    timesCount = 0;
}

//-----------------------------
void MotionParticle::setTargetWide(float valueRange){
    targetPos = ofPoint( ofRandom(-screenSize->x, screenSize->x), ofRandom(-screenSize->y, screenSize->y), ofRandom(-screenSize->x/5, screenSize->x/5) );
}

//-----------------------------
void MotionParticle::setTarget(float valueRange){
    targetPos = pos + ofPoint( ofRandom(-valueRange, valueRange), ofRandom(-valueRange,valueRange) , ofRandom(-valueRange,valueRange) );
}

//-----------------------------
void MotionParticle::setZero(){
    targetPos = ofPoint(0,0,0);
}

//-----------------------------
void MotionParticle::setTargetRandomPos(){
    targetPos = ofPoint(ofRandom(-screenSize->x,screenSize->x),ofRandom(-screenSize->y,screenSize->y),ofRandom(-screenSize->y,screenSize->y));
}

//-----------------------------
void MotionParticle::timeCount(){
    times += 1;
}

//-----------------------------
float MotionParticle::moveHalf(float _pos, float _TargetPos){
    float posVal = _TargetPos*posff + _pos*(1-posff);
    return posVal;
}

//----------------------------
void MotionParticle::drawRipple(){
    ofCircle(0, 0, rippleLife);
}

//
float MotionParticle::amr(float _value1, float _value2){
    float ttt = abs(_value1)/abs(_value2);
    float eee = abs(_value1)-(int(ttt)*abs(_value2));
    return eee;
}

bool MotionParticle::looseQaualyValue(float _v1, float _v2, float _range){
    if(abs(_v1-_v2)<_range)return true;
    return false;
}

ofPoint MotionParticle::getFlow(){
    return flow;
}

