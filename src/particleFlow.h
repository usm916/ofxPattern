//
//  particleFlow.h
//  emptyExample
//
//  Created by usm on 1/16/13.
//
//

#ifndef __emptyExample__particleFlow__
#define __emptyExample__particleFlow__

#include <iostream>
#include "ofMain.h"
#include "billboard.h"
#include "ofxXmlSettings.h"
#include "ofxDelaunay.h"
#include "ofxCv.h"


#define CHARANUM 724

class Character : public ofBaseApp {
public:
    ofPoint* screenSize;
    ofVec3f pos, vecNoise, vecSprg, vecScale, pPos, trgPos;
    float *k, *damp, *noiseContrast, *timeScale, *delta;
    float minLimit, maxLimit;
    float life, preLife, ts;
    float randomSeed, gs;
    float marginH;
    float scaleZ, *forceDenstL, *forceDenstS;
    float attRadius;
    float attSize;
    float nodeSize;
    float* tt;
    
    bool bEnableLimit;
    
    Character(){}
    Character(bool _limit, ofVec3f _pos, ofPoint* _screenSize, float _attRadius, float _armLength, float _nodeSize, float* _noiseScaleL, float* _noiseScaleS, float* _timeScale){
        timeScale = _timeScale;
        pos = _pos;
        trgPos = pos;
        screenSize = _screenSize;
        life = 6000 + ofRandom(2000);
        preLife = life;
        life = life - ofRandom(0,life);
        vecNoise = vecSprg = ofVec3f(0.0,0.0,0.0);
        minLimit = 10;
        maxLimit = _armLength;
        marginH = 1.0;
        randomSeed = ofRandom(255);
        scaleZ = 40.0;//40.0
        forceDenstL = _noiseScaleL;//0.007;//0.0009
        forceDenstS = _noiseScaleS;//0.021;//0.0009
        nodeSize = _nodeSize;
//        attRadius = ofRandom(270,350);
//        attRadius = ofRandom(500,650);
        attRadius = _attRadius;
        bEnableLimit = _limit;
    }
    
    void setValue(float *_tt, float * _m, float * _noiseContrast, float * _k, float * _damp){
        noiseContrast = _noiseContrast;
        delta = _m;
        tt = _tt;
        k = _k;
        damp = _damp;
    }
    
    //--------------------------------------------------------------
    void checkPos(ofVec3f _pos){
//        cout << "dist: " << pos.distance(_ppos) << endl;
        float dist = pos.distance(_pos);
        if(390 > dist ){
            ofSetColor(255, 30+255*ts*(1-dist/390));
            ofLine(pos.x,pos.y,pos.z/scaleZ,_pos.x,_pos.y,_pos.z/scaleZ);
        }
    }
    
    //--------------------------------------------------------------
    ofVec3f& getPos(){
        return pos;
    }
    //--------------------------------------------------------------
    float& getSize(){
        return gs;
    }
    
    //--------------------------------------------------------------
    int setPos(ofVec3f _pos){
        pos = _pos;
        return 0;
    }
    
    void setInful(){
        attRadius += 10;
    }
    //-----------------------------------------------------------------------------
    void setup(){
        
    }
    
    void updateValue(){
//        cout << "tS " << *timeScale << endl;
//        cout << "tT " << _tt << endl;
    }

    //-----------------------------------------------------------------------------
    void updateZero(){
        ofVec3f scaleNoiseL = *forceDenstL * pos;
        ofVec3f scaleNoiseS = *forceDenstS * pos;
        
//        float t = ofGetElapsedTimef() / 6.0;
        vecNoise = *timeScale * ofVec3f( 0.5-ofNoise((float)scaleNoiseL.x, (float)scaleNoiseL.y, *tt),
                              0.5-ofNoise((float)scaleNoiseL.y, *tt, (float)scaleNoiseL.x),
                              0) +
        *timeScale * ofVec3f( 0.5-ofNoise((float)scaleNoiseS.x, (float)scaleNoiseS.y, *tt),
                        0.5-ofNoise((float)scaleNoiseS.y, *tt, (float)scaleNoiseS.x),
                        0) + vecNoise * 0.97;
        vecSprg = (trgPos-pos)* *k + vecSprg * *damp;
        pos = pos + vecNoise + vecSprg;
        pPos = pos;
        life --;
        ts = pow(sin((float)life/(float)preLife*180.0), 2.75);
        gs = nodeSize*ts + 7;
        if(bEnableLimit){
            if(pos.x < -ofGetWidth() ){
                pos.x = pos.x + ofGetWidth();
            }else if( pos.x > ofGetWidth() ){
                pos.x = pos.x - ofGetWidth();
            }
            if(pos.y < -ofGetHeight()*marginH ){
                pos.y = pos.y + ofGetHeight()*marginH;
            }else if( pos.y > ofGetHeight()*marginH ){
                pos.y = pos.y - ofGetHeight()*marginH;
            }
        }
    }
    
    //-----------------------------------------------------------------------------
    void update(){//float _k, float _noiseContrast, float _tt){
        ofVec3f scaleNoiseL = *forceDenstL * pos;
        ofVec3f scaleNoiseS = *forceDenstS * pos;
        
//        float t = ofGetElapsedTimef() / 6.0;
//        _noiseContrast = 1.0;
//        *timeScale = 1.0;
        vecNoise = *noiseContrast * *timeScale * ofVec3f( 0.5-ofNoise((float)scaleNoiseL.x, (float)scaleNoiseL.y, *tt),
                              0.5-ofNoise((float)scaleNoiseL.y, *tt, (float)scaleNoiseL.z),
                              0.5-ofNoise(*tt, (float)scaleNoiseL.z, (float)scaleNoiseL.x)) +
               *timeScale * ofVec3f( 0.5-ofNoise(*tt, (float)scaleNoiseS.x, (float)scaleNoiseS.y),
                              0.5-ofNoise((float)scaleNoiseS.y, (float)scaleNoiseS.z, *tt),
                              0.5-ofNoise((float)scaleNoiseS.z, *tt, (float)scaleNoiseS.x)) + vecNoise * 0.98 + vecSprg * 0.98;
        pos = pos + vecNoise;
        vecSprg = (trgPos-pos) * *k;
        pos = pos + vecSprg;
        pPos = pos;
        life --;
        ts = pow(sin((float)life/preLife*180.0), 2.75);
        gs = nodeSize*ts + 7;
        if(bEnableLimit){
            if(pos.x < -ofGetWidth() ){
                pos.x = pos.x + ofGetWidth()*2;
            }else if( pos.x > ofGetWidth() ){
                pos.x = pos.x - ofGetWidth()*2;
            }
            if(pos.y < -ofGetHeight()*marginH ){
                pos.y = pos.y + ofGetHeight()*marginH*2;
            }else if( pos.y > ofGetHeight()*marginH ){
                pos.y = pos.y - ofGetHeight()*marginH*2;
            }
        }
//        cout << "vecN " << vecNoise << endl;
//        cout << "nc " << _noiseContrast << endl;
//        cout << "k " << *k << endl;
//        cout << "tS " << *timeScale << endl;
//        cout << "tT " << *tt << endl;

    }
    
    //-----------------------------------------------------------------------------
    void update(ofVec3f attractor) {
        ofVec3f scaleNoiseL = *forceDenstL * pos;
        ofVec3f scaleNoiseS = *forceDenstS * pos;
        
//        attRadius = 900 * abs(pow((double)sin(ofGetElapsedTimef()/2),0.1));
        
//        float t = ofGetElapsedTimef() / 6.0;
//        cout << ofGetElapsedTimef() << endl;
        float attDist = pos.distance(attractor);
        ofVec3f rplForce;
        if(attDist < attRadius){
            rplForce = (pos-attractor)*0.00004;//0.00001;
            attDist = 1 - attDist/attRadius;
        }else{
            attDist = 0.0;
            rplForce = ofVec3f(0.0, 0.0, 0.0);
        }
        vecNoise = ofMap(attDist,0,1,0.2,1.1) * *noiseContrast * *timeScale * ofVec3f( 0.5-ofNoise((float)scaleNoiseL.x, (float)scaleNoiseL.y, *tt),
                                          0.5-ofNoise((float)scaleNoiseL.y, *tt, (float)scaleNoiseL.z),
                                        0.5-ofNoise(*tt, (float)scaleNoiseL.z, (float)scaleNoiseL.x)) +
                ofMap(attDist,0,1,0.8,1.1) * *noiseContrast/3 * *timeScale * ofVec3f( 0.5-ofNoise((float)scaleNoiseS.x, (float)scaleNoiseS.y, *tt),
                                  0.5-ofNoise((float)scaleNoiseS.y, *tt, (float)scaleNoiseS.z),
                                          0.5-ofNoise(*tt, (float)scaleNoiseS.z, (float)scaleNoiseS.x)) + vecNoise * 0.983 + rplForce + vecSprg * 0.98;
        pos = pos + vecNoise;
//        cout << scale << endl;
        vecSprg = (trgPos-pos) * ofMap(pow(1.0-(double)attDist,10.0),0.0,1.0,0.0,0.9)* *k;
        pos = pos + vecSprg;
        pPos = pos;
        life --;
        ts = pow(sin((float)life/preLife*180.0), 2.75);
        gs = nodeSize*ts + 7;
        if(bEnableLimit){
            if(pos.x < -ofGetWidth() ){
                pos.x = pos.x + ofGetWidth()*2;
            }else if( pos.x > ofGetWidth() ){
                pos.x = pos.x - ofGetWidth()*2;
            }
            if(pos.y < -ofGetHeight()*marginH ){
                pos.y = pos.y + ofGetHeight()*marginH*2;
            }else if( pos.y > ofGetHeight()*marginH ){
                pos.y = pos.y - ofGetHeight()*marginH*2;
            }
        }
    }
    
    void setTrgPos(ofVec3f* _newTrg){
        trgPos = *_newTrg;
    }
    
    //-----------------------------------------------------------------------------
    void draw(ofImage* img){
        ofPushMatrix();
//        ofSetColor(255,235+ofRandom(20));
        ofTranslate(pos.x, pos.y, pos.z);// /scaleZ);
        billboard();
        img->draw(0,0,0,gs,gs);
        ofPopMatrix();
    }
};

class Attractor : public ofBaseApp {
public:
    Attractor(){}
    Attractor(int _pid, ofVec3f _pos){
        pid = _pid;
        pos = _pos;
        vec = ofVec3f(0,0,0);
    }
    Attractor(int _pid, ofVec3f _pos, ofVec3f _vec){
        pid = _pid;
        pos = _pos;
        vec = _vec;
    }
    ofVec3f pos;
    ofVec3f vec;
    int pid;
};

class TextMove : public ofBaseApp {
public:
    void setup();
    
    TextMove(){}
    TextMove(int _num, ofPoint* _screenSize){
        modeNum = _num;
        screenSize = _screenSize;
        bMove = false;
        bEffectAtt = false;
        bVideo = true;
        bSphere = false;
        bModeAttr = false;
        bEnableLimit = false;
    }
    
    TextMove(ofPoint* _screenSize, int _numOfParticle){
        screenSize = _screenSize;
        bMove = false;
        bEffectAtt = false;
        bVideo = true;
        bSphere = false;
        bEnableLimit = true;
        bModeAttr = false;
        numPtcl = _numOfParticle;
    }
    
    void mouseMoved(ofMouseEventArgs& args);
    void mouseDragged(ofMouseEventArgs& args){}
    void mousePressed(ofMouseEventArgs& args){}
    void mouseReleased(ofMouseEventArgs& args){}

    void update();
    void updateAll();
    
    void attrMove();
    void draw(ofColor);
    void load();
    void exit();
    
    void clear();
    
    //// set attr
    vector<Attractor> attr;
    void resetAttr();
    void setAttr(int,ofVec3f);
    void updateAttr(int,ofVec3f);
    void deleteAttr(int);
    
    void iniRandom(int);
    void loadFileVertex(string,float);
    
    void drawConnection(int,ofColor);
    void rebirth(int killNum);
    void addParticle(float, float );
    bool checkMove();
    void setRect(float, float);
    void setRectStr();
    void setSphereStr();
    void setVertex(float, float);
    void setK(float _k);
    
    bool bMove;
    bool bEffectAtt;
    bool bVideo;
    bool bSphere;
    bool bEnableLimit;
    bool bModeAttr;
    
    ofVec3f getChPos(int index)
    {
        return charactors[index]->getPos();
    }
    void setChPos(int index, ofVec3f pos)
    {
        charactors[index]->setPos(pos);
    }
    
    float getChSize(int index)
    {
        return charactors[index]->getSize();
    }
    
    void setAttrPos(ofVec3f);
    void birth();
    
    void saveAllParam();
    void saveGridParam();
    void saveIniParam();
    void loadAllParam();
    void loadFileName();
    void loadGridParam();
    void loadIniParam();
    ofxDelaunay triangle;
    void getFeaturePoint();
    void buildTriangleMesh();
    ofVec3f pos, vec, rot;
    string paramFile, iniValueFile, objName;
    vector<ofVec3f* > loadVertex(string _filename);
    void setTargetPos(int swh);
    void setTargetPos(vector<ofVec3f* >);
//    void birth();
    
//    deque<Character* > charactors;

private:
    ofImage base;
    ofVideoPlayer movie;
    int movFrameNum, modeNum;
    
    float k, damp, noiseContrast, timeT, deltaTime;
    float * pk, * pdamp, * pNoiseContrast, * pTimeT, * pDeltaTime;

    
    float objScale, timeScale, videoScale;
    float attRadius, armLength, nodeSize;
    float noiseScaleL, noiseScaleS;
    int numPtcl;
    
    float strGrid;
    int si,sj,sk;
    bool bSwCenter, bSwMove;
    
    vector<ofVec3f* > wireWall60;
    vector<ofVec3f* > wireWall61;
    vector<ofVec3f* > wireWall70;
    vector<ofVec3f* > wireWall71;
    vector<ofVec3f* > wireWall80;
    vector<ofVec3f* > wireWall81;
    vector<ofVec3f* > wireWall90;
    vector<ofVec3f* > wireWall91;
    
    int timeCnt;
    float pmsX, pmsY;
    float msX, msY;
    float moveDencity;
    ofPoint* screenSize;
    ofImage img0, img1, milkyWay;
    deque<Character* > charactors;
//    ofVec3f pos, vec, rot;
    
    ///////////////////////////////////
    float farClip;
    int maxFeatures;
    float featureQuality;
	float minDistance;
        
    vector<cv::Point2f> featurePoints;
    vector<ofVec3f> faceNormals;
    vector<ofVec3f> faceCenters;
	vector<ofVec3f> innerPoints;
	vector<ofVec3f> backPoints;
    vector<ofVec3f> backInnerPoints;
    
    ofxDelaunay triangulate;
    ofVboMesh triangulatedMesh;
    ofVboMesh latticeMesh;
    
    bool bRotateAxis;
    ////////////////////////////////////
};

#endif /* defined(__emptyExample__particleFlow__) */
