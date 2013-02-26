//
//  Storke.h
//  audioInputExample
//
//  Created by Takuto Usami on 11/10/31.
//  Copyright (c) 2011 _MyCompanyName__. All rights reserved.
//

#ifndef Storke_h
#define Storke_h
#include "ofMain.h"
#include "OSCvalue.h"

#define _NUMPARTICLE 18
#define _TAILLEN 39

class SPointObj {
    
public: 
    float x, y, z, speedX, speedY, defX, defY, defZ, trgtX, trgtY, trgtZ, distX, distY,
            distZ, acX, acY, acZ, spX, spY, spZ;
    float vx[_TAILLEN], vy[_TAILLEN], vz[_TAILLEN];
    float pvx, pvy, pvz;
    
    SPointObj() {}
    SPointObj(float posX, float posY, float posZ, float tvx, float tvy, float tvz) {
        x = posX;
        y = posY;
        z = posZ;
        vx[0] = tvx;
        vy[0] = tvy;
        vz[0] = tvz;
    }
    
};

class Storke : ofBaseApp {

public :
    Storke() {}
    Storke(float* _scaledVol, float* _magSqrt,  ofColor* _baseColor, OSCVALUE* _oscValue) {
        magSqrt = _magSqrt;
        scaledVol = _scaledVol;
        baseColor = _baseColor;
        oscValue = _oscValue;
        pmX = 0.0;
        pmY = 0.0;
        orx = ofGetWidth()/2;
        ory = ofGetHeight()/2;
        orz = 0;
        
        for(int i=0;i<_NUMPARTICLE;i++){
            tpoint = SPointObj(0.0f, 0.0f, 0.0f,  0.0f, 0.0f, 0.0f );
            stPos.push_back(tpoint);
        }
        setup();
    };
    
    void setup();
    void move(float mX, float mY, float macX, float macY);
    void drawOwn(int imgMode);
    void drawOwnBillboard(int imgMode);
    void setPos(float tvx, float tvy, float tvz);
    void calcConf();
    
private:
    float* scaledVol;
    float* magSqrt;
    OSCVALUE* oscValue;
    float posx, posy, posz, fricX, fricY, fricZ;
    float vx, vy, vz;
    float orx, ory, orz, rndXX;
    float pmX, pmY;
    vector <SPointObj> stPos;
    SPointObj tpoint;
    ofImage imgTemp;
    vector <ofImage> pLight;
    ofPoint* screenSize;
    ofColor w240, w255;
    ofColor* baseColor;
};

class ofxStorkerSystem : ofBaseApp {

private:
    int numOfStkr;
    int stkrSpeed;
    vector<Storke* > stkr;
    OSCVALUE* oscValue;
    ofColor* baseColor;
    float* magSqrt;
    float* scaledVol;
    ofPoint fboSize;
    
public:
    void draw();
    void targetUpdate();
//    void setup();
    
    ofxStorkerSystem() {}
    ofxStorkerSystem(int num, float* _scaledVol, float* _magSqrt, ofPoint _size, ofColor* _baseColor, OSCVALUE* _oscValue) {
        oscValue = _oscValue;
        baseColor = _baseColor;
        magSqrt = _magSqrt;
        scaledVol = _scaledVol;
        stkrSpeed = 2;
        numOfStkr = num;
        fboSize = _size;
        for(int i=0;i<numOfStkr;i++){
            stkr.push_back( new Storke(scaledVol, magSqrt, baseColor, oscValue));
        }
    }
    
};

#endif
