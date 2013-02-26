//
//  ofxParticleSystem.cpp
//  LS_PatternGeenerate
//
//  Created by usm on 12/15/12.
//
//

#include "ofxParticleSystem.h"

//------------------------------------------------------------------
void ofxParticleSystem::setup(){
    // this number describes how many bins are used
	// on my machine, 2 is the ideal number (2^2 = 4x4 pixel bins)
	// if this number is too high, binning is not effective
	// because the screen is not subdivided enough. if
	// it's too low, the bins take up so much memory as to
	// become inefficient.
	int binPower = 5;
    
    behaviaMode = 4;
//    mouseCheck = false;
    bInvert = false;
    
	particleSystem.setup(screenSize.x, screenSize.y, binPower);
    
	kParticles = 2;
    float paddingFrame = 100;
	float padding = 0;
	float maxVelocity = .5;
    //1024 >> 512
	for(int i = 0; i < kParticles * 512; i++) {
		float x = ofRandom(padding, screenSize.x - padding);
		float y = ofRandom(padding, screenSize.y - padding);
		float xv = ofRandom(-maxVelocity, maxVelocity);
		float yv = ofRandom(-maxVelocity, maxVelocity);
		Particle particle(x, y, xv, yv);
		particleSystem.add(particle);
	}
	timeStep = 0.2;
	lineOpacity = 96;
	pointOpacity = 255;
	isMousePressed = false;
	slowMotion = false;
	particleNeighborhood = 18;
	particleRepulsion = 0.06;
	centerAttraction = 1.0;//.01
}

// behave to particle system;
void ofxParticleSystem::setMode(int _mode){
    int dt = 15;
    switch (_mode) {
        case 1:
            pack.addValue(&timeStep, 0.32, dt, 0);
            pack.addValue(&particleNeighborhood, 29, dt, 0);//18
            pack.addValue(&particleRepulsion, 11.2, dt, 0);
            pack.addValue(&centerAttraction, 2, dt, 0);//.01
            break;
        case 2:
            pack.addValue(&timeStep, 0.3, dt, 0);
            pack.addValue(&particleNeighborhood, 23, dt, 0);//22
            pack.addValue(&particleRepulsion,3.9, dt, 0);
            pack.addValue(&centerAttraction,0.9, dt, 0);//.01
//            tarTimeStep = 0.05;
//            tarParticleNeighborhood = 10;//18
//            tarParticleRepulsion = 0.01;
//            tarCenterAttraction = 0.9;//.01
            break;
        case 3:
//            tarTimeStep = 0.1;
            pack.addValue(&timeStep, 0.25, dt, 0);
            pack.addValue(&particleNeighborhood, 24, dt, 0);//22
            pack.addValue(&particleRepulsion,0.7, dt, 0);
            pack.addValue(&centerAttraction,0.4, dt, 0);//.01
            break;
        case 4://default
            pack.addValue(&timeStep, 0.2, dt, 0);
            pack.addValue(&particleNeighborhood,18, dt, 0);//18
            pack.addValue(&particleRepulsion,0.06, dt, 0);
            pack.addValue(&centerAttraction,1.0, dt, 0);//.01
            break;
        case 5:
            tarTimeStep = 0.6;
            tarParticleNeighborhood = 12;//12
            tarParticleRepulsion = 0.01;
            tarCenterAttraction = 3.9;//.01
            break;
        default:
            break;
    }
}

//------------------------------------------------------------------
void ofxParticleSystem::draw(){
//    setMode(mode);
    checkPush();
    pack.update();
    ofEnableBlendMode(OF_BLENDMODE_ADD);
    updateValue();
    drawParticles();
    
}

//------------------------------------------------------------------
void ofxParticleSystem::drawCenter(){
    ofPushMatrix();
        ofTranslate(-margin.x/2, -margin.y/2);
        draw();
    ofPopMatrix();
}

//------------------------------------------------------------------
void ofxParticleSystem::setForces(){
    particleSystem.addAttractionForce(oscValue->msY[0] * screenSize.x/2, oscValue->msX[0] * screenSize.y, screenSize.x/2, centerAttraction);
    particleSystem.addAttractionForce( (1- oscValue->msY[0]) * screenSize.x/2, (1- oscValue->msX[0]) * screenSize.y, screenSize.x/2, centerAttraction);
    particleSystem.addAttractionForce(oscValue->msY[0] * screenSize.x/2 + screenSize.x/2, oscValue->msX[0] * screenSize.y, screenSize.x/2, centerAttraction);
    particleSystem.addAttractionForce( (1- oscValue->msY[0]) * screenSize.x/2 + screenSize.x/2, (1- oscValue->msX[0]) * screenSize.y, screenSize.x/2, centerAttraction);
//    particleSystem.addAttractionForce(*msx, *msy, screenSize.x/2, centerAttraction);
//    particleSystem.addAttractionForce((screenSize.x - *msx), (screenSize.y - *msy), screenSize.x/2, centerAttraction);
//    particleSystem.addAttractionForce(screenSize.x + *msx, *msy, screenSize.x/2, centerAttraction);
//    particleSystem.addAttractionForce(screenSize.x + (screenSize.x - *msx), (screenSize.y - *msy), screenSize.x/2, centerAttraction);
	if(isMousePressed){particleSystem.addRepulsionForce(*msx, *msy, 100, 20);}
}

//------------------------------------------------------------------
void ofxParticleSystem::updateValue(){
//    tarPointOpacity = 255;
//    tarLineOpacity = 64;
    if(bInvert){
        tarR = 0;
        tarG = 0;
        tarB = 0;
        tarEdgeR = 75;
        tarEdgeG = 65;
        tarEdgeB = 95;
    } else {
        tarR = 60;
        tarG = 0;
        tarR = 100;
        tarEdgeR = 10;
        tarEdgeG = 0;
        tarEdgeB = 10;
    }
}

//------------------------------------------------------------------
void ofxParticleSystem::drawParticles(){
    
//    ofEnableBlendMode(OF_BLENDMODE_ALPHA);
    ofEnablePointSprites();
    
    if(lineOpacity>0.1){
        ofSetColor(*baseColor, lineOpacity);
        particleSystem.setTimeStep(timeStep);
        particleSystem.setupForces();
        // apply per-particle forces
        int cntLine = 0;
        glBegin(GL_LINES);
        for(int i = 0; i < particleSystem.size(); i++) {
            Particle& cur = particleSystem[i];
            // global force on other particles
            particleSystem.addRepulsionForce(cur, particleNeighborhood, particleRepulsion);
            // forces on this particle
            cur.bounceOffWalls(0, 0, screenSize.x, screenSize.y);
            cur.addDampingForce();
        }
        glEnd();
    }
    
    setForces();
	particleSystem.update();
        
    if(pointOpacity>0.1){
        ofSetColor(*baseColor, pointOpacity);
        particleSystem.draw();
    }
}

//--------------------------------------------
void ofxParticleSystem::checkPush(){
    // flash images
    // check frame
    if(oscValue->mPush[7][2][0]==1){
        setMode(1);
    }else if(oscValue->mPush[7][3][0]==1){
        setMode(2);
    }else if(oscValue->mPush[7][4][0]==1){
        setMode(3);
    }else if(oscValue->mPush[7][5][0]==1){
        setMode(4);
    }
}