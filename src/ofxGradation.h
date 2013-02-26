//
//  ofxGradation.h
//  LS_PatternGeenerate
//
//  Created by usm on 12/9/12.
//
//

#ifndef __ofxGradation_H_
#define __ofxGradation_H_

#include <iostream>
#include "ofMain.h"
#include "ofxMeshGrid.h"

class ofxGradationGenerator {
    public :
        ofxGradationGenerator(){}
        ~ofxGradationGenerator(){}
        void draw(float);
        void setup(int, int);
        void buildMesh(int, int);
    
    private :
        float freqR,freqG,freqB;
        float pFreqR,pfreqG,pFreqB;
        unsigned char 	* colorPixels;
    
        ofxMeshGrid mesh;
        ofTexture gradation;
};

class ofxGradation {
    public:
        ofxGradation(){}
        ~ofxGradation(){}
        void draw();
        void setup(int, int);
    private:
        ofxGradationGenerator gg;
};

#endif /* defined(__LS_PatternGeenerate__ofxGradation__) */
