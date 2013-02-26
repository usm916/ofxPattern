//
//  OSCvalue.h
//  VJ
//
//  Created by usm on 11/30/12.
//
//

#ifndef VJ_OSCvalue_h
#define VJ_OSCvalue_h

#include "ofMain.h"
//#include "testApp.h"

#define AvgCnt 12
#define StkrNum 11

struct OSCVALUE {
    int     mouseX, mouseY;
    float   tFader[8][8];
    int     tToggle[10][10];
    int     tPush[9][7];
    float   mmx[6], mmy[6];
    float   msX[5], msY[5];
    float   pmsX[5], pmsY[5];
    float   degree[6][641];
    float   degCvtSin[6][AvgCnt];
    bool    mToggle[9][12][10];
    bool    mPush[9][10][10];
    int     stsTch[StkrNum][3];
    float   sound[3];
};



#endif
