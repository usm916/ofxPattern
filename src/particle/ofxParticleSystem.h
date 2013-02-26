//
//  ofxParticleSystem.h
//  LS_PatternGeenerate
//
//  Created by usm on 12/15/12.
//
//

#ifndef __LS_PatternGeenerate__ofxParticleSystem__
#define __LS_PatternGeenerate__ofxParticleSystem__

#include "ofMain.h"
#include "OSCvalue.h"
#include "ofxValueTransition.h"
#include "ParticleSystem.h"

class ofxParticleSystem : ofBaseApp {
    private:
        //declar value to Particle system
        float timeStep;
        float lineOpacity, pointOpacity;
        float particleNeighborhood, particleRepulsion;
        float centerAttraction;
        float tarTimeStep;
        float tarLineOpacity, tarPointOpacity;
        float tarParticleNeighborhood, tarParticleRepulsion;
        float tarCenterAttraction;
        float r, g, b, tarR, tarG, tarB;
        float edgeR, edgeG, edgeB, tarEdgeR, tarEdgeG, tarEdgeB;
    
        float fluidFboOpacity, tarFluidFboOpacity;
        int kParticles;
    
        ParticleSystem particleSystem;
        bool isMousePressed, slowMotion;
        int behaviaMode;
    
        ofPoint screenSize, margin;
        int *msx, *msy;
        OSCVALUE* oscValue;
        ofColor* baseColor;
    
        bool bInvert;
        ofxValueTransitionPack pack;
    
    public:
        void setup();
        void drawCenter();
        void draw();
        void drawParticles();
        void setForces();
        void updateValue();
        void setMode(int);
        void checkPush();
        //-------------------------------------------------------------------------
        void linearTrasition(float* volume, float _step, float* _target){
            float delta = *_target-*volume;
            if( abs((*volume - *_target)) >= _step ){
                if(delta > 0){
                    *volume += _step;
                    if(*volume > *_target) *volume = *_target;
                }else if(delta < 0){
                    *volume -= _step;
                    if(*volume < *_target) *volume = *_target;
                }
            }
        }
        ofxParticleSystem(){};
        ofxParticleSystem(int* _msx, int* _msy, ofPoint _screenSize, ofVec2f _aspect, ofColor* _baseColor, OSCVALUE* _oscValue){
            msx = _msx;
            msy = _msy;
            baseColor = _baseColor;
            oscValue = _oscValue;
            screenSize.x = _screenSize.x * _aspect.x;
            screenSize.y = _screenSize.y * _aspect.y;
            margin.x = screenSize.x - _screenSize.x;
            margin.y = screenSize.y - _screenSize.y;
            setup();
        };
};

#endif /* defined(__LS_PatternGeenerate__ofxParticleSystem__) */
