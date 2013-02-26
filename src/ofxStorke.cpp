//
#include "ofxStorke.h"
#include "billboard.h"
//#include <iostream>
//#include <vector>
//#include <math.h>

//-----------------------------
void Storke::setup(){
    imgTemp.loadImage("images/emitter_.png");
    pLight.push_back(imgTemp);
    imgTemp.loadImage("images/1.png");
    pLight.push_back(imgTemp);
    imgTemp.loadImage("images/4.png");
    pLight.push_back(imgTemp);
    imgTemp.loadImage("images/2.png");
    
    w240 = ofColor(240,240,240);
    w255 = ofColor(255,255,255);
    
    setPos(0.0, 0.0, 0.0);
}

void Storke::move(float mX, float mY, float macX, float macY){
    float scale = 1000 * pow(oscValue->tFader[0][6] * 2.0, 2.0);
    float fric = 0.7;
    float acScale = 0.05;
    //orx = mX;
    //ory = mY;
    //orz = mX-mY;
    mX = mX/5;
    mY = mY/5;
    for(int i=0;i<stPos.size();i++){
        stPos[i].pvx = stPos[i].pvx * fric;
        stPos[i].pvy = stPos[i].pvy * fric;
        stPos[i].pvz = stPos[i].pvz * fric;
        stPos[i].speedX = sqrt(abs( float(mX - pmX) ));
        stPos[i].speedY = sqrt(abs( float(mY - pmY) ));
        rndXX += 0.01;
        stPos[i].trgtX = orx + ofRandom(-stPos[i].speedX*8, stPos[i].speedX*8) + ofRandom(- *scaledVol * scale, *scaledVol * scale);
        stPos[i].trgtY = ory + ofRandom(-stPos[i].speedY*8, stPos[i].speedY*8) + ofRandom(- *scaledVol * scale, *scaledVol * scale);
        stPos[i].trgtZ = orz + ofRandom(-stPos[i].speedY*8, stPos[i].speedY*8) + ofRandom(- *scaledVol * scale, *scaledVol * scale);
        stPos[i].distX = stPos[i].x - stPos[i].trgtX;
        stPos[i].distY = stPos[i].y - stPos[i].trgtY;
        stPos[i].distZ = stPos[i].z - stPos[i].trgtZ;
        stPos[i].pvx += stPos[i].distX*-1* pow( 1.0-oscValue->tFader[0][6],2.0);
        stPos[i].pvy += stPos[i].distY*-1* pow( 1.0-oscValue->tFader[0][6],2.0);
        stPos[i].pvz += stPos[i].distZ*-1* pow( 1.0-oscValue->tFader[0][6],2.0);
        
        stPos[i].x = stPos[i].x + stPos[i].pvx * (mY-2)/550 * macX * pow( 1.0-oscValue->tFader[0][6],2.0) + ofRandom(-0.5,0.5);
        stPos[i].y = stPos[i].y + stPos[i].pvy * (mY-2)/550 * macY * pow( 1.0-oscValue->tFader[0][6],2.0) + ofRandom(-0.5,0.5);
        stPos[i].z = stPos[i].z + stPos[i].pvz * (mY-2)/550 + macX * pow( 1.0-oscValue->tFader[0][6],2.0) + ofRandom(-0.5,0.5);
        stPos[i].vx[0] = stPos[i].x;
        stPos[i].vy[0] = stPos[i].y;
        stPos[i].vz[0] = stPos[i].z;
        for(int k=_TAILLEN-1;k>0;k--){
            stPos[i].vx[k] = stPos[i].vx[k-1];
            stPos[i].vy[k] = stPos[i].vy[k-1];
            stPos[i].vz[k] = stPos[i].vz[k-1];
            //cout << k << ",";
        }
        
    }
    pmX = mX;
    pmY = mY;
}

//------------------------------------------------
void Storke::drawOwn(int imgMode){
    float drawSize;
    int numi = 72;
    float value = pow(oscValue->tFader[1][2] * 2.0, 2.0);
    drawSize = magSqrt[numi] * (*scaledVol+0.5) * 450 * value;
    if(drawSize > 800)drawSize = 800;
    ofEnableBlendMode(OF_BLENDMODE_ADD);
    ofSetRectMode(OF_RECTMODE_CENTER);
    ofSetLineWidth(1);
    
    float checkLength = 100 * value * 20;
    for(int i=0;i<stPos.size();i++){
        ofNoFill();
        
        ofSetColor(w240,82 * oscValue->tFader[1][0]);
        if(!oscValue->mToggle[1][0][0]){
            glBegin(GL_LINE_STRIP);
            for(int k=0;k<_TAILLEN;k++){
                glVertex3d(stPos[i].vx[k], stPos[i].vy[k], stPos[i].vz[k] * oscValue->tFader[4][0]);
            }
            glEnd();
        } else {
            ofSetColor(*baseColor,96 * oscValue->tFader[1][0]);//w240
            for(int k=0;k<stPos.size();k++){
                if( !(i==k) ){
                        float deltaX, deltaY, deltaZ, pwX, pwY, pwZ;
                        deltaX = stPos[i].x-stPos[k].x;
                        deltaY = stPos[i].y-stPos[k].y;
                        deltaY = stPos[i].z-stPos[k].z;
                        pwX = deltaX * deltaX;
                        pwX = deltaY * deltaY;
                        pwX = deltaZ * deltaZ;
                        if( sqrt( pwX + pwY ) < checkLength ){
                            ofLine(stPos[i].x, stPos[i].y, stPos[i].z * oscValue->tFader[4][0], stPos[k].x, stPos[k].y, stPos[k].z * oscValue->tFader[4][0]);
                    }
                }
            }
        }
        ofFill();
        ofSetColor(*baseColor, 255 * ofMap( oscValue->tFader[1][2],0.0,1.0,0.4,0.7)); //w255
        if(imgMode!=0){
            ofPushMatrix();
            ofTranslate(stPos[i].x, stPos[i].y, stPos[i].z * oscValue->tFader[4][0]);
            pLight[imgMode].draw(0,0, drawSize, drawSize);
            ofPopMatrix();
        }else{
            ofPushMatrix();
            ofTranslate(stPos[i].x, stPos[i].y, stPos[i].z * oscValue->tFader[4][0]);
            pLight[imgMode].draw(0,0, drawSize, drawSize);
            ofPopMatrix();
        }
    }
    ofSetRectMode(OF_RECTMODE_CORNER);
//    cout << stPos[5].x << "," << stPos[5].y << "," << stPos[5].z << "-" << orx << "- " << *scaledVol << " drawSize: " << (float)drawSize << endl;
}

//------------------------------------------------
void Storke::drawOwnBillboard(int imgMode){
    float drawSize;
    int numi = 72;
    float value = pow(oscValue->tFader[1][2] * 2.0, 2.0);
    drawSize = magSqrt[numi] * (*scaledVol+0.5) * 450 * value;
    if(drawSize > 800)drawSize = 800;
    ofEnableBlendMode(OF_BLENDMODE_ADD);
    ofSetRectMode(OF_RECTMODE_CENTER);
    ofSetLineWidth(1);
    for(int i=0;i<stPos.size();i++){
        ofNoFill();
        
        ofSetColor(w240,240 * oscValue->tFader[1][0]);
        if(!oscValue->mToggle[1][0][0]){
            glBegin(GL_LINE_STRIP);
            for(int k=0;k<_TAILLEN;k++){
                glVertex3d(stPos[i].vx[k], stPos[i].vy[k], stPos[i].vz[k]);
            }
            glEnd();
        } else {
            ofSetColor(w240,240 * oscValue->tFader[1][0]);
            for(int k=0;k<stPos.size();k++){
                if( !(i==k) ){
                    float deltaX, deltaY, deltaZ, pwX, pwY, pwZ;
                    deltaX = stPos[i].x-stPos[k].x;
                    deltaY = stPos[i].y-stPos[k].y;
                    deltaY = stPos[i].z-stPos[k].z;
                    pwX = deltaX * deltaX;
                    pwX = deltaY * deltaY;
                    pwX = deltaZ * deltaZ;
                    if( sqrt( pwX + pwY ) < 60 ){
                        ofLine(stPos[i].x, stPos[i].y, stPos[i].z, stPos[k].x, stPos[k].y, stPos[k].z);
                    }
                }
            }
        }
//        ofFill();
        ofSetColor(w255, 255);
        if(imgMode!=0){
            ofPushMatrix();
            ofTranslate(stPos[i].x, stPos[i].y, stPos[i].z);
            pLight[imgMode].draw(0,0,0, drawSize, drawSize);
            ofPopMatrix();
        }else{
            ofPushMatrix();
            ofTranslate(stPos[i].x, stPos[i].y, stPos[i].z);
            billboard();
            pLight[imgMode].draw(0,0,0, drawSize, drawSize);
            ofPopMatrix();
        }
    }
    ofSetRectMode(OF_RECTMODE_CORNER);
    //    cout << stPos[5].x << "," << stPos[5].y << "," << stPos[5].z << "-" << orx << "- " << *scaledVol << " drawSize: " << (float)drawSize << endl;
}

//------------------------------------------------
void Storke::setPos(float tvx, float tvy, float tvz){
    orx = tvx;
    ory = tvy;
    orz = tvz;
}

//setup date
void ofxStorkerSystem::targetUpdate(){
    //[i][0-3] = [i][XYZ] position
    if( oscValue->mPush[1][0][0] == 1 ){
        for(int i=0;i<numOfStkr;i++){
            oscValue->stsTch[i][0] = 0;
            oscValue->stsTch[i][1] = 0;
            oscValue->stsTch[i][2] = 0;
        }
    }
    if( oscValue->mPush[1][1][0] == 1 ){
        for(int i=0;i<numOfStkr;i++){
            float scale = 0.67;
            oscValue->stsTch[i][0] += ofRandom(-fboSize.y*scale, fboSize.y*scale);
            oscValue->stsTch[i][1] += ofRandom(-fboSize.y*scale, fboSize.y*scale);
            oscValue->stsTch[i][2] += ofRandom(-fboSize.y*scale, fboSize.y*scale);
        }
    }
    if( oscValue->mPush[1][2][0] == 1 ){
        for(int i=0;i<numOfStkr;i++){
            oscValue->stsTch[i][0] = (i-numOfStkr/2.0)*fboSize.x/numOfStkr;
            oscValue->stsTch[i][1] = 0;
            oscValue->stsTch[i][2] = 0;
//                            num[i].setPos((i-1)*fboSize.x*0.2, 0, 0);
        }
    }
    if( oscValue->mPush[1][3][0] == 1 ){
        for(int i=0;i<numOfStkr;i++){
            float scale = 0.5;
            oscValue->stsTch[i][0] = ofRandom(-fboSize.x*scale, fboSize.x*scale);
            oscValue->stsTch[i][1] = ofRandom(-fboSize.y*scale, fboSize.y*scale);
            oscValue->stsTch[i][2] = ofRandom(-fboSize.x*scale, fboSize.x*scale);
        }
//        for(int i=0;i<numOfStkr;i++){
//            float degree = 360.0/(float)numOfStkr;
//            float scale = 0.27;
//            oscValue->stsTch[i][0] = sin(degree*(float)i)*(float)fboSize.x*scale;
//            oscValue->stsTch[i][1] = 0;
//            oscValue->stsTch[i][2] = cos(degree*(float)i)*(float)fboSize.x*scale;
//        }
    }
    if( oscValue->mPush[1][4][0] == 1 ){
        for(int i=0;i<numOfStkr;i++){
            float degree = ofRandom(0,360);
            float scale = 0.27;
            oscValue->stsTch[i][0] = sin(degree)*(float)fboSize.x*scale;
            oscValue->stsTch[i][1] = 0;
            oscValue->stsTch[i][2] = cos(degree)*(float)fboSize.x*scale;
        }
    }
}

//------------------------------------------------
void ofxStorkerSystem::draw(){
    targetUpdate();
    int macX,macY;
    macX = macY = 1.0;
    
    for(int i=0;i<stkr.size();i++){
        stkr[i]->setPos(oscValue->stsTch[i][0], oscValue->stsTch[i][1], oscValue->stsTch[i][2]);
    }
    float _num = oscValue->tFader[1][1]*2.9;
    if(_num>3) _num=3;
    int imgNumS = int(_num);
    for(int i=0;i<stkr.size();i++){
        switch (stkrSpeed) {
            case 0:
                stkr[i]->move(oscValue->msY[0]*fboSize.x+((i-1)*100* pow( 1.0-oscValue->tFader[0][6],2.0)), oscValue->msX[0]*fboSize.y, macX, macY);
                break;
            case 1:
                stkr[i]->move(oscValue->msY[0]*fboSize.x+((i-1)*100* pow( 1.0-oscValue->tFader[0][6],2.0)), 10, macX, macY);
                break;
            case 2:
                stkr[i]->move(oscValue->msY[0]*fboSize.x+((i-1)*100* pow( 1.0-oscValue->tFader[0][6],2.0)), 90, macX, macY);
                break;
            case 3:
                stkr[i]->move(oscValue->msY[0]*fboSize.x+((i-1)*100* pow( 1.0-oscValue->tFader[0][6],2.0)), 200, macX, macY);
                break;
            case 4:
                stkr[i]->move(oscValue->msY[0]*fboSize.x+((i-1)*100* pow( 1.0-oscValue->tFader[0][6],2.0)), 1000, macX, macY);
                break;
            default:
                cout << "stkr def" << endl;
                break;
        }
        stkr[i]->drawOwn(imgNumS); //BCONNECTION
    }// if play with add 10
}
