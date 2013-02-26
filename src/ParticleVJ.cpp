//
//  Particle.cpp
//  audioInputExample
//
/*
#include "Particle.h"

// -----------------------------------------------------------------------------     
void Particle::resetPosition(){
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


//-----------------------------------------------------------------------------
void Particle::draw(){
//    float distanceToFocalPlane = focalPlane.getDistanceToPoint(position);
//    distanceToFocalPlane *= 1 / dofRatio;
//    distanceToFocalPlane = constrain(distanceToFocalPlane, 1, 15);
//    strokeWeight(distanceToFocalPlane);
//    stroke(255, constrain(255 / (distanceToFocalPlane * distanceToFocalPlane), 1, 255));
    
//    ofFill();
//    ofSetColor(255,180);
//    ofLine(position.x, position.y, position.z, position.x+ofRandom(-2,2), position.y+ofRandom(-2,2), position.z+ofRandom(-2,2) );
//    ofRect(position.x, position.y, position.z, 4, 4);
   glVertex3f(position.x, position.y, position.z);
}

// -----------------------------------------------------------------------------     
float Particle::applyFlockingForce() {
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

// -----------------------------------------------------------------------------     
void Particle::applyCenteringForce() {
    centeringForce.set(position);
    centeringForce = centeringForce - avg;
    float distanceToCenter = centeringForce.length();
    centeringForce.normalize();
    centeringForce = centeringForce * ( -distanceToCenter / (*spread * *spread) );
    force = force + centeringForce;
    
}

// -----------------------------------------------------------------------------     
void Particle::applyViscosityForce() {
    force = force + (velocity * -*viscosity);
    
}

//-----------------------------------------------------------------------------
void Particle::update() {
    force.set(0.0, 0.0, 0.0);
    applyFlockingForce();
    applyViscosityForce();
    applyCenteringForce();
    velocity = velocity + force; // mass = 1
    position = position + velocity * *speed;
}
*/

