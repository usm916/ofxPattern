//
//  ofxImagesystem.cpp
//  LS_PatternGeenerate
//
//  Created by usm on 12/17/12.
//
//

#include "ofxImageSystem.h"

//--------------------------------------------------------------
void ofxImageSystem::draw(){
    checkPush();
    if(oscValue->mToggle[6][7][0]){
//        cout << "tgl" << endl;
        checkLoopSlide();
    }
    ofEnableBlendMode(OF_BLENDMODE_ADD);
    ofSetRectMode(OF_RECTMODE_CENTER);
    ImgDrawImage(slideImg);
    ImgDrawImageRipple();
    ofSetRectMode(OF_RECTMODE_CORNER);
}

//--------------------------------------------------------------
void ofxImageSystem::checkLoopSlide(){
    if(timeCount==0){
        int imgNum = ofRandom(2,3-0.05);
        ImgHitKeySlide(imgNum);
        timeCount = ofRandom(120,260) * oscValue->tFader[2][1];
    }
    timeCount --;
}

//--------------------------------------------------------------
void ofxImageSystem::checkPush(){
    // flash images
    // check frame
    for(int i=0;i<9;i++){
        for(int r=2;r>0;r--){
            Imgkey[i][r] = Imgkey[i][r-1];
        }
        if(oscValue->mPush[3][i][0]==1){
            int fd = 0;
            for(int k=0;k<3;k++){
                fd = fd + Imgkey[i][k];
            }
            if(fd==0)if(allImage.size()>i)ImgHitKeySlide(i);
            Imgkey[i][0] = 1;
        }else if(oscValue->mPush[3][i][0]==1){
            int fd = 0;
            for(int k=0;k<3;k++){
                fd = fd + Imgkey[i][k];
            }
            if(fd==0)if(allImage.size()>i)ImgHitKey(i);
            Imgkey[i][0] = 1;
        }else{
            Imgkey[i][0] = 0;
        }
    }
    // check frame
    for(int i=0;i<9;i++){
        for(int r=2;r>0;r--){
            ImgkeyR[i][r] = ImgkeyR[i][r-1];
        }
        if(oscValue->mPush[4][i][0]==1){
            int fx = 0;
            for(int k=0;k<3;k++){
                fx = fx + ImgkeyR[i][k];
            }
            if(fx==0)if(allImage.size()>i)ImgHitKeySlow(i);
            ImgkeyR[i][0] = 1;
        }else{
            ImgkeyR[i][0] = 0;
        }
    }
}


//--------------------------------------------------------------
void ofxImageSystem::ImgLoadImage()
{
    bKawakami = true;
    // open from dir
    dropTime = 40;
    string path = "images/bgimages";
    ofDirectory dir(path);
    dir.listDir();
    
    addColor.loadImage("images/slowColor.png");
    
    //go through and print out all the paths
    for(int i = 0; i < dir.numFiles(); i++){
        ofLogNotice(dir.getPath(i));
        cout << dir.getPath(i) << endl;
        if(ofFilePath::getFileExt( dir.getPath(i) ) == ""){
            string dirPath = dir.getPath(i);
            cout << dirPath << " finded a folder..." << endl;
            dirFolderPath.push_back( dirPath );
            
            std::string iFile;
            std::stringstream tmp;
            iFile = ofFilePath::addTrailingSlash(dirPath);
            ofDirectory dir( iFile );
            cout << iFile << endl;
            dir.allowExt("png");
            dir.listDir();
            
            vector < ofImage > eachFolder;
            //go through and print out all the paths
            for(int i = 0; i < dir.numFiles(); i++){
                ofLogNotice(dir.getPath(i));
                cout << i << " : Loaded:" << dir.getPath(i) << endl;
                ofImage imgTmp;
                imgTmp.loadImage(dir.getPath(i));
                eachFolder.push_back( imgTmp );
            }
            photoNumber.push_back(eachFolder.size());
            cout << "photoCount : " << eachFolder.size() << endl;
            allImage.push_back(eachFolder);
            noteNum.push_back(50);
        }
    }
    dsplImages.clear();
    rippleImages.clear();
    cout << "floaderNum : " << allImage.size() << endl;
    for(int i=0;i<allImage.size();i++){
        cout << "photoNumber : " << photoNumber[i] << endl;
    }
}

//--------------------------------------------------------------
void ofxImageSystem::ImgDrawImage(bool slideImg)
{
    if(!dsplImages.empty()){
        int fi =0;
        int del = 0;
        deque<ofxBgImage*>::iterator it = dsplImages.begin();
        while( it != dsplImages.end() )
        {
            //            cout << "draw BG image : kbg" << dsplImages[fi]->kbg << endl;
            
            if( dsplImages[fi]->kbg>0 ){
                if(!slideImg){
                    dsplImages[fi]->drawBg();
                }else{
                    dsplImages[fi]->drawBgSlide();
                }
            }else{
                del++;
            }
            fi++;
            it++;
        }
        for(int i=0;i<del;i++){
            if(!dsplImages.empty() )dsplImages.pop_front();
        }
    }
    if(!dsplImagesSlow.empty()){
        // for Kawakami iterator
        int fi =0;
        int del = 0;
        deque<ofxBgImage*>::iterator it = dsplImagesSlow.begin();
        while( it != dsplImagesSlow.end() )
        {
            if( dsplImagesSlow[fi]->kbg>0 && dsplImagesSlow.size()>=2 ){
                if(fi==0){
                    dsplImagesSlow[fi]->drawBgStaticDisappear();
                }else{
                    dsplImagesSlow[fi]->drawBgStaticAppear();
                }
            }else if( dsplImagesSlow[fi]->kbg>0 && dsplImagesSlow.size()<2){
                dsplImagesSlow[fi]->drawBgStaticAppear();
            }else{
                del++;
            }
            fi++;
            it++;
        }
        for(int i=0;i<del;i++){
            if(!dsplImagesSlow.empty() )dsplImagesSlow.pop_front();
        }
    }
}

//--------------------------------------------------------------
void ofxImageSystem::ImgDrawImageRipple()
{
    if(!rippleImages.empty()){
        float ripSize = -oscValue->tFader[4][4];
        int fi =0;
        int del = 0;
        deque<ofxBgImage*>::iterator it = rippleImages.begin();
        if(bKawakami){
            // for Kawakami iterator
            while( it != rippleImages.end() )
            {
                if( rippleImages[fi]->kbg>0){
                    if(!rippleImages[fi]->bDisappear){
                        rippleImages[fi]->drawBgAppear(ripSize);
                    }else{
                        rippleImages[fi]->drawBg(ripSize);
                    }
                }else{
                    del++;
                }
                fi++;
                it++;
            }
            for(int i=0;i<del;i++){
                if(!rippleImages.empty() )rippleImages.pop_front();
            }
        }
    }
    if( abs(oscValue->msX[0]-pmsX)>0.024 || abs(oscValue->msY[0]-pmsY)>0.020 ){
        ImgHitKeyRipple(1);
    }
    pmsX = oscValue->msX[0];
    pmsY = oscValue->msY[0];
}

//--------------------------------------------------------------
void ofxImageSystem::ImgHitKey(int _num)
{
    dropTime = 45;
    int numA = _num;
    int numB = (int)ofRandom( 0, photoNumber[numA]-0.05 );
    dsplImages.push_back( new ofxBgImage( &allImage[ numA ][ numB ], dropTime, 50, screenSize, baseColor) );
    BDI = true;
    //    cout << "num : " << ofPoint(numA,numB) << endl;
}

//--------------------------------------------------------------
void ofxImageSystem::ImgHitKeySlide(int _num)
{
    dropTime = (float)screenSize->x * ofMap(oscValue->tFader[2][0]*4,0,1.0,0.01,0.3) / 5.0;
    int numA = _num;
    int numB = (int)ofRandom( 0, photoNumber[numA]-0.05 );  //SELECT PHOTO NUMBER
    dsplImages.push_back( new ofxBgImage( &allImage[ numA ][ numB ], dropTime, 50, screenSize, baseColor) );
    BDI = true;
}

//--------------------------------------------------------------
void ofxImageSystem::ImgHitKeySlow(int _num)
{
    dropTime = 180;
    int numA = _num;
    int numB = (int)ofRandom( 0, photoNumber[numA]-0.05 );
    dsplImagesSlow.push_back( new ofxBgImage( &allImage[ numA ][ numB ], dropTime, 50, screenSize, baseColor) );
    BDI = true;
    //    cout << "num : " << ofPoint(numA,numB) << endl;
}

//--------------------------------------------------------------
void ofxImageSystem::ImgHitKeyRipple(int _num)
{
    dropTime = 60;
    rippleImages.push_back( new ofxBgImage( &addColor, dropTime, 50, (oscValue->msY[0] * screenSize->x), (oscValue->msX[0] * screenSize->y), screenSize, baseColor) );
    BDI = true;
}

