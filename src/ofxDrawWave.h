//
//  drawWave.h
//  VJ
//
//  Created by usm on 11/26/12.
//
//

#ifndef _OFXdrawWave_h
#define _OFXdrawWave_h

#include "ofMain.h"
#include "OSCvalue.h"

class ofxWave {
    
    private :
        int BuSIZE;
        float space;
        float* soundStream;
        float ssff[512], pssff[512];
        float filterFacter;
        ofImage imgTemp;
        vector <ofImage> pLight;
        vector <ofVec3f> par;
        ofColor* waveColor;
        bool bFiltering;
        
        OSCVALUE* oscValue;
        float patMax = 2.5;
        float scaleSize;
        float scalepl = 5;

    
    public :
        ofxWave() {};
        ofxWave(int _BUFFERSIZE, float * _soundStream, OSCVALUE * _oscValue, bool billboard) {
            BuSIZE = _BUFFERSIZE;
            bFiltering = false;
            //        space = (float)ofGetWidth()/(float)BuSIZE;
            space = 20;
            soundStream = _soundStream;
            oscValue = _oscValue;
            for(int i=0;i<512;i++){
                par.push_back( ofVec3f( ofRandom(0,ofGetWidth())*sin(ofRandom(0,360)),
                                       ofRandom(0,ofGetWidth())*cos(ofRandom(0,360)),
                                       0 ));
            }
            cout << "Will not using Filter facter" << endl;
            setup();
        };
        
        ofxWave(int _BUFFERSIZE, float * _soundStream, float _filterFacter, float _scaleSize, ofColor* _baseColor, OSCVALUE * _oscValue) {
            BuSIZE = _BUFFERSIZE;
            filterFacter = _filterFacter;
            waveColor = _baseColor;
            bFiltering = true;
            //        space = (float)ofGetWidth()/(float)BuSIZE;
            space = 20;
            soundStream = _soundStream;
            oscValue = _oscValue;
            scaleSize = _scaleSize;
            for(int i=0;i<512;i++){
                par.push_back( ofVec3f( ofRandom(0,ofGetWidth())*sin(ofRandom(0,360)),
                                       ofRandom(0,ofGetWidth())*cos(ofRandom(0,360)),
                                       0 ));
            }
            cout << "using Filter facter" << endl;
            setup();
        };
        
        void setup();
        void update();
        
        void drawWaveLine(float _x, float _y, float _z, float _space);
        void drawWaveLineParticleBill(float _x, float _y, float _z, float _space, int _step);
        void drawWaveLineParticle(float _x, float _y, float _z, float _space, int _step);
        void drawWaveLineCircleBill(float _x, float _y, float _z, float _space);
        void drawWaveLineCircle(float _x, float _y, float _z, float _space);
        
        void drawWaveLineY(float _x, float _y, float _z, float _space);
        void drawWaveLineParticleY(float _x, float _y, float _z, float _space);
        void drawWaveLineCircleY(float _x, float _y, float _z, float _space);
        
        void drawWaveSphere(float _x, float _y, float _z, float _baseRad, ofColor _flowerColor);
        
        void drawWavePlaneParticle(float, float,float,float,float,float,int,int, float);
        
        void drawWaveCircle();
        void drawWaveFields();
        void drawWaveLissa();
        float checkNum(float);
    
};

#endif /* defined(__VJ__drawWave__) */
