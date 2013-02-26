//
//  Particle.h
//  audioInputExample
//
//

#ifndef Particle_h
#define Particle_h

#include "ofMain.h"    
class Particle : public ofBaseApp {

    public: 
//        void draw();
//        void update();
//        void resetPosition();
//        float applyFlockingForce();
//        void applyCenteringForce();
//        void applyViscosityForce();

        ofVec3f position, velocity, force, avg;
        ofVec3f localOffset;
        ofVec3f centeringForce;
    
        ofVec3f *globalOffset;
        ofImage *emiTex;
    
        float* neighborhood;
        float* viscosity;
        float* speed;
        float* turbulence;
        float* cameraRate;
        float* rebirthRadius;
        float* spread;
        float* independence;
        float* dofRatio;
        float* wnum;
        float* tF02;
        int* n;
        int* rebirth;
        bool  *averageRebirth, *paused;
    
    Particle(){}
    Particle(float* _neighborhood,
             float* _viscosity,
             float* _speed,
             float* _turbulence,
             float* _cameraRate,
             float* _rebirthRadius,
             float* _spread,
             float* _independence,
             float* _dofRatio,
             float* _wnum,
             int* _n,
             int* _rebirth,
             bool* _averageRebirth,
             bool* _paused,
             ofVec3f* _globalOffset,
             ofImage* _emiTex,
             float* _tF02)
    {
            n = _n;
            tF02 = _tF02;
            dofRatio = _dofRatio;
            neighborhood = _neighborhood;
            speed = _speed;
            viscosity = _viscosity;
            spread = _spread;
            independence = _independence;
            rebirth = _rebirth;
            rebirthRadius = _rebirthRadius;
            turbulence = _turbulence;
            cameraRate = _cameraRate;
            averageRebirth = _averageRebirth;
            paused = _paused;
            globalOffset = _globalOffset;
            wnum = _wnum;
            emiTex = _emiTex;
        
            resetPosition();
            velocity = ofVec3f();
            force = ofVec3f();
            float rand = ofRandom(-1,1);
            float rand2 = ofRandom(-1,1);
            localOffset = ofVec3f(rand, rand2, rand+rand2/2);
            
    }
    
    void resetPosition(){
        position = ofVec3f(ofRandom(-1,1),
                           ofRandom(-1,1),
                           ofRandom(-1,1) );
        position = position * ofRandom( *rebirthRadius );
        
        if(*n == 0){
            position = position + avg;
        }else{
            position = position + position;
        }
    }
    
    void draw(){
        glVertex3f(position.x, position.y, position.z);
    }
    
    float applyFlockingForce() {
        force = force + ofVec3f(
                                ofNoise(
                                        position.x / *neighborhood + globalOffset->x + localOffset.x  * *independence,
                                        position.y / *neighborhood,
                                        position.z / *neighborhood,
                                        *wnum)
                                - .5,
                                ofNoise(
                                        position.x / *neighborhood,
                                        position.y / *neighborhood + globalOffset->y  + localOffset.y * *independence,
                                        position.z / *neighborhood,
                                        *wnum)
                                - .5,
                                ofNoise(
                                        position.x / *neighborhood,
                                        position.y / *neighborhood,
                                        position.z / *neighborhood + globalOffset->z + localOffset.z  * *independence,
                                        *wnum)
                                - .5);
    }
    
    void applyCenteringForce() {
        centeringForce.set(position);
        centeringForce = centeringForce - avg;
        float distanceToCenter = centeringForce.length();
        centeringForce.normalize();
        centeringForce = centeringForce * ( -distanceToCenter / (*spread * *spread) );
        force = force + centeringForce;
        
    }
    
    void applyViscosityForce() {
        force = force + (velocity * -*viscosity);
        
    }
    
    void update() {
        force.set(0.0, 0.0, 0.0);
        applyFlockingForce();
        applyViscosityForce();
        applyCenteringForce();
        velocity = velocity + force; // mass = 1
        position = position + velocity * *speed;
    }
};

#endif
