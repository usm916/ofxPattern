//
//  ofxColorSelector.cpp
//  LS_PatternGeenerate
//
//  Created by usm on 12/17/12.
//
//

#include "ofxColorSelector.h"

//---------------------------------------------Setup of color selector
void ofxColorSelector::HSV2RGB( double *rr, double *gg, double *bb, double H, double S, double V ){
    int in;
    double fl;
    double m, n;
    in = (int)floor( H / 60 );
    fl = ( H / 60 ) - in;
    if( !(in & 1)) fl = 1 - fl; // if i is even
    
    m = V * ( 1 - S );
    n = V * ( 1 - S * fl );
    switch( in ){
        case 0: *rr = V; *gg = n; *bb = m; break;
        case 1: *rr = n; *gg = V; *bb = m; break;
        case 2: *rr = m; *gg = V; *bb = n; break;
        case 3: *rr = m; *gg = n; *bb = V; break;
        case 4: *rr = n; *gg = m; *bb = V; break;
        case 5: *rr = V; *gg = m; *bb = n; break;
    }
}

void ofxColorSelector::setColors(){
    setHsvElementColor();
    setHsvBgColor();
}
//
void ofxColorSelector::setConvertColor(){
    //-----------------------------------------convert HSV
//    double h = oscValue->msY[3]*360;
//    double s = oscValue->tFader[0][1];
//    double v = oscValue->msX[3];
//    HSV2RGB( &r, &g, &b, h, s, v );
//    elementColor->r = 255*r;
//    elementColor->g = 255*g;
//    elementColor->b = 255*b;
}

//
void ofxColorSelector::setBgColor(){
    //-----------------------------------------convert HSV
//    double h = oscValue->tFader[0][3] *360;
//    double s = 1.0;//oscValue->tFader[0][1];
//    double v = oscValue->tFader[0][4];
//    HSV2RGB( &r, &g, &b, h, s, v );
//    elementColor->r = 255*r;
//    elementColor->g = 255*g;
//    elementColor->b = 255*b;
}

void ofxColorSelector::setHsvElementColor(){
    //-----------------------------------------convert HSV
    pack.update();
    checkPushColor();
    double h = hsvValue->x * 360;
    double s = oscValue->tFader[0][1];
    double v = oscValue->tFader[0][4];
    HSV2RGB( &eleR, &eleG, &eleB, h, s, v );
    elementColor->r = 255*eleR;
    elementColor->g = 255*eleG;
    elementColor->b = 255*eleB;
}

void ofxColorSelector::setHsvBgColor(){
    //-----------------------------------------convert HSV
    pack.update();
    checkPushColor();
    double h = hsvBgValue->x * 360;
    double s = oscValue->tFader[0][1];
    double v = oscValue->tFader[0][5];
    HSV2RGB( &bgR, &bgG, &bgB, h, s, v );
    bgColor->r = 255*bgR;
    bgColor->g = 255*bgG;
    bgColor->b = 255*bgB;
}

//--------------------------------------------
void ofxColorSelector::checkPushColor(){
    // flash images
    // check frame

    for(int j=0;j<3;j++){
        for(int i=0;i<8;i++){
            if(oscValue->mPush[8][i][j]==1){
                if(j==0){
                    switch (i) {
                        case 0: pack.addValue(hsvValue, ofPoint(0.96,1.0,1.0), 150*oscValue->tFader[0][3], 0, VT_POINT_AS_COLOR); break;//RED
                        case 1: pack.addValue(hsvValue, ofPoint(0.06,1.0,1.0), 150*oscValue->tFader[0][3], 0, VT_POINT_AS_COLOR); break;//ORANGE
                        case 2: pack.addValue(hsvValue, ofPoint(0.11,1.0,1.0), 150*oscValue->tFader[0][3], 0, VT_POINT_AS_COLOR); break;//YELLOW
                        case 3: pack.addValue(hsvValue, ofPoint(0.33,1.0,1.0), 150*oscValue->tFader[0][3], 0, VT_POINT_AS_COLOR); break;//GREEN
                        case 4: pack.addValue(hsvValue, ofPoint(0.62,1.0,1.0), 150*oscValue->tFader[0][3], 0, VT_POINT_AS_COLOR); break;//BLUE
                        case 5: pack.addValue(hsvValue, ofPoint(0.76,1.0,1.0), 150*oscValue->tFader[0][3], 0, VT_POINT_AS_COLOR); break;//PURPLE
                        case 6: pack.addValue(hsvValue, ofPoint(0.88,1.0,1.0), 150*oscValue->tFader[0][3], 0, VT_POINT_AS_COLOR); break;//PINK
                        case 7: pack.addValue(hsvValue, ofPoint(0.0,0.0,0.0), 150*oscValue->tFader[0][3], 0, VT_POINT_AS_COLOR); break;//BLACK
                        default: break;
                    }
                }else if(j==1){
                    switch (i) {
                        case 0: pack.addValue(hsvBgValue, ofPoint(0.0,1.0,1.0), 150*oscValue->tFader[0][3], 0, VT_POINT_AS_COLOR); break;//Bg WHITE
                        case 1: pack.addValue(hsvValue, ofPoint(0.09,1.0,1.0), 150*oscValue->tFader[0][3], 0, VT_POINT_AS_COLOR); break;//ORANGE
                        case 2: pack.addValue(hsvValue, ofPoint(0.2,1.0,1.0), 150*oscValue->tFader[0][3], 0, VT_POINT_AS_COLOR); break;//YELLOW
                        case 3: pack.addValue(hsvValue, ofPoint(0.4,1.0,1.0), 150*oscValue->tFader[0][3], 0, VT_POINT_AS_COLOR); break;//GREEN
                        case 4: pack.addValue(hsvValue, ofPoint(0.5,1.0,1.0), 150*oscValue->tFader[0][3], 0, VT_POINT_AS_COLOR); break;//BLUE
                        case 5: pack.addValue(hsvValue, ofPoint(0.68,1.0,1.0), 150*oscValue->tFader[0][3], 0, VT_POINT_AS_COLOR); break;//PURPLE
                        case 6: pack.addValue(hsvValue, ofPoint(0.82,1.0,1.0), 150*oscValue->tFader[0][3], 0, VT_POINT_AS_COLOR); break;//PINK
                        case 7: pack.addValue(hsvValue, ofPoint(0.0,0.0,1.0), 150*oscValue->tFader[0][3], 0, VT_POINT_AS_COLOR); break;//Ele WHITE
                        default: break;
                    }
                }else if(j==2){
                    switch (i) {
                        case 0: pack.addValue(hsvBgValue, ofPoint(0.0,1.0,1.0), 150*oscValue->tFader[0][3], 0, VT_POINT_AS_COLOR); break;//RED
                        case 1: pack.addValue(hsvBgValue, ofPoint(0.07,1.0,1.0), 150*oscValue->tFader[0][3], 0, VT_POINT_AS_COLOR); break;//ORANGE
                        case 2: pack.addValue(hsvBgValue, ofPoint(0.12,1.0,1.0), 150*oscValue->tFader[0][3], 0, VT_POINT_AS_COLOR); break;//YELLOW
                        case 3: pack.addValue(hsvBgValue, ofPoint(0.34,1.0,1.0), 150*oscValue->tFader[0][3], 0, VT_POINT_AS_COLOR); break;//GREEN
                        case 4: pack.addValue(hsvBgValue, ofPoint(0.63,1.0,1.0), 150*oscValue->tFader[0][3], 0, VT_POINT_AS_COLOR); break;//BLUE
                        case 5: pack.addValue(hsvBgValue, ofPoint(0.77,1.0,1.0), 150*oscValue->tFader[0][3], 0, VT_POINT_AS_COLOR); break;//PURPLE
                        case 6: pack.addValue(hsvBgValue, ofPoint(0.89,1.0,1.0), 150*oscValue->tFader[0][3], 0, VT_POINT_AS_COLOR); break;//PINK
                        case 7: pack.addValue(hsvBgValue, ofPoint(0.0,0.0,0.0), 150*oscValue->tFader[0][3], 0, VT_POINT_AS_COLOR); break;//BLACK
                        default: break;
                    }
                }
            }
        }
    }
}

void ofxColorSelector::testColor(){
    pack.addValue(hsvValue, ofPoint(ofRandom(0,1.0),1.0,1.0), 150*oscValue->tFader[0][3], 0, VT_POINT_AS_COLOR);
//    pack.addValue(hsvBgValue, ofPoint(ofRandom(0,1.0),1.0,1.0), 150*oscValue->tFader[0][3], 0, VT_POINT_AS_COLOR);
}
