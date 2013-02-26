//
//  particleFlow.cpp
//  emptyExample
//
//  Created by usm on 1/16/13.
//
//

#include "particleFlow.h"

using namespace ofxCv;
using namespace cv;

//-----------------------------------------------------------------------------
void TextMove::setup(){
    ofRegisterMouseEvents(this);
//    ofRegisterKeyEvents(this);
    movFrameNum = 0;
    timeT = 0.0;
    pTimeT = &timeT;
    deltaTime = 0.0013;
    pDeltaTime = &deltaTime;
    timeT += deltaTime;
    noiseContrast = 1.0;
    pNoiseContrast = &noiseContrast;
    cout << "timeT " << timeT << endl;
    cout << "& pTimeT " << pTimeT << endl;
    /// to Get featurePoint /////////////////////////////////////////////////////
    maxFeatures = 4000;
    featureQuality = 0.01;
	minDistance = 9;
    farClip = 6000;
    /////////////////////////////////////////////////////////////////////////////
    msX = msY = pmsX = pmsY = .0;
    timeCnt = 0;
    k=0.0001;
    damp=0.99;
    pk = &k;
    pdamp = &damp;
    noiseContrast = 1.0;
    load();

    cout << "pk " << pk << endl;
}

void TextMove::load(){
//    setRectStr();
//    setSphereStr();
//    movie.loadMovie("pn.mp4");
//	movie.play();
    img0.loadImage("images/0_bl.png");
    img1.loadImage("images/0_bl2.png");
    loadAllParam();
    
//    milkyWay.loadImage("images/milkyWay.jpg");

    saveIniParam();
    if(!bEnableLimit){
        loadFileVertex(objName+ofToString(modeNum)+".obj", objScale);
        wireWall60 = loadVertex("wireWall60.obj");
        wireWall61 = loadVertex("wireWall61.obj");
        wireWall70 = loadVertex("wireWall70.obj");
        wireWall71 = loadVertex("wireWall71.obj");
        wireWall80 = loadVertex("wireWall80.obj");
        wireWall81 = loadVertex("wireWall81.obj");
        wireWall90 = loadVertex("wireWall90.obj");
        wireWall91 = loadVertex("wireWall91.obj");
    }
    cout << wireWall90.size() << endl;
}

void TextMove::iniRandom(int num){
    charactors.clear();
    for(int i=0;i<num;i++){
        charactors.push_back(new Character(true, ofVec3f( ofGetWidth()*ofRandom(-1,1), ofGetWidth()*ofRandom(-1,1), ofGetWidth()*ofRandom(-1,1)),
                                                    screenSize, attRadius, armLength, nodeSize, &noiseScaleL, &noiseScaleS, &timeScale));
        charactors[i]->setValue(pTimeT, pDeltaTime, pNoiseContrast, pk, pdamp);
    }
}

//-----------------------------------------------------------------------------
void TextMove::loadFileVertex(string objFileName, float scale){
    ifstream fin; //declare a file stream
    fin.open( ofToDataPath(objFileName).c_str() ); //open your text file
    if(!fin.is_open()){
        cout << "Faled to import objfile" << endl;
    }
    
    vector<string> data; //declare a vector of strings to store data
    vector<ofVec3f> vtx;
    vtx.clear();
    int numLine = 0;
    charactors.clear();
    
    while(fin!=NULL) //as long as theres still text to be read
    {
        string str; //declare a string for storage
        stringstream sstr;
        sstr.str("");
        getline(fin, str); //get a line from the file, put it in the string
        sstr << str;
        string typ;
        float x,y,z;
        float objScale = scale;
        char c;
        sstr >> typ >> x >> y >> z;
        if(typ=="v"){
//            ofPoint temp = ofPoint( ofRandom(1920)*objScale,ofRandom(1080)*objScale,0);//test for random
//            ofPoint temp = ofPoint( (x+ofRandom(1))*objScale,y*objScale,z*objScale);
//            triangle.addPoint( temp );
            charactors.push_back(new Character(false, ofVec3f(x, y, z)*objScale,screenSize, attRadius+ofRandom(100,150), armLength+ofRandom(0,25), nodeSize, &noiseScaleL, &noiseScaleS, &timeScale));
//            ch.push_back( 1.0 * ofVec3f(x,y,z) ); //push the string onto a vector of strings
            cout << "OBJ VTX add Vertex: " << x << ", " << y << ", " << z << endl;
        }
//        else if(typ=="g"){
//            //            vtxLine.assign(numLine, vtx);
//            vtxLine.push_back(vtx);
//            vtx.clear();
//            cout << "add Line: " << numLine << " size() " << vtxLine.size() << endl;
//            numLine++;
//        }
    }
    for(int i=0;i<charactors.size();i++) {
        charactors[i]->setValue(&timeT, &deltaTime, &noiseContrast, pk, pdamp);
    }
    cout << "setup: .obj was Loaded, added " << charactors.size() << " vertexes" << endl;
}

//-----------------------------------------------------------------------------
vector<ofVec3f* > TextMove::loadVertex(string objFileName) {
    ifstream fin; //declare a file stream
    fin.open( ofToDataPath(objFileName).c_str() ); //open your text file
    if(!fin.is_open()){
        cout << "Faled to import objfile" << endl;
    }
    
    vector<string> data; //declare a vector of strings to store data
    vector<ofVec3f* > vtx;
    vtx.clear();
    int numLine = 0;
    
    while(fin!=NULL) //as long as theres still text to be read
    {
        string str; //declare a string for storage
        stringstream sstr;
        sstr.str("");
        getline(fin, str); //get a line from the file, put it in the string
        sstr << str;
        string typ;
        float x,y,z;
        char c;
        sstr >> typ >> x >> y >> z;
        if(typ=="v"){
            vtx.push_back(new ofVec3f(x, y, z));
            cout << "add Vertex: " << x << ", " << y << ", " << z << endl;
        }
    }
    cout << "setup: .obj was Loaded, added " << vtx.size() << " vertexes" << endl;
    return vtx;
}

//-----------------------------------------------------------------------------
void TextMove::rebirth(int num){
    for(int i=0;i<num;i++){
        charactors.pop_front();
        charactors.push_back(new Character(true, ofPoint( ofRandom(-ofGetWidth(),ofGetWidth()),
                                                        ofRandom(-ofGetWidth(),ofGetWidth()),
                                                        ofRandom(-ofGetWidth(),ofGetWidth())),
                                           screenSize, attRadius, armLength, nodeSize, &noiseScaleL, &noiseScaleS, &timeScale));
        charactors[charactors.size()-1]->setValue(&timeT, &deltaTime, &noiseContrast, pk, pdamp);
    }
}

///---
void TextMove::attrMove(){
    if(!attr.empty()){
        for(int i=0;i<attr.size();i++){
//            attr[i].pos += attr[i].vec;
        }
    }
}

void TextMove::setK(float _k){
    k = _k;
    noiseContrast = 1 + (1-k);
//    cout << "NC " << noiseContrast << endl;
//        cout << "k " << _k << endl;
}

void TextMove::resetAttr(){
    attr.clear();
}

void TextMove::setAttr(int _pid, ofVec3f _pos){
//    ofVec3f _vec = ofVec3f(0,0,0);
    attr.push_back(Attractor(_pid, _pos));
//    cout << "add pid" << _pid << ": " << _pos << endl;
}

void TextMove::updateAttr(int _pid, ofVec3f _pos){
//    ofVec3f pos = _pos;
//    for(int i=0;i<pid.size();i++){
//        if(pid[i]==_pid)attrPos[i]=_pos;
//    }
//    int iPid;
//    list<Attractor* >::iterator it;
//    for(it=attr.begin();it!=attr.end();it++){
//        iPid = (*it)->pid;
//        if( _pid==iPid){
//            cout << "ipdat ipid" << iPid << endl;
//            cout << "update pid" << _pid << endl;
//            cout << "update Pos " << _pos << endl;
////            (*it)->pos = _pos;
//        }
//		++it;
//	}
}

void TextMove::deleteAttr(int _pid){
//    int iPid;
//    list<Attractor* >::iterator it = attr.begin();
//	while( it != attr.end() ){  //to end of the list
//        iPid = (*it)->pid;
//        if( _pid==iPid){
//            cout << "____delete pid" << _pid << endl;
//            it = attr.erase(it);
//        }
//        ++it;
//    }
}

//-----------------------------------------------------------------------------
void TextMove::update(){
    
    timeCnt ++;
    timeT += deltaTime;
    //////////update k
//    k = 0.00001;
    /*
    if(attr.empty()){
        k=0.6;
//        k = 0.13 * pow(double(ofNoise(ofGetElapsedTimef()/7.0*(ofNoise(ofGetElapsedTimef()/3.0)*0.5+0.5) )),4.0);
    }else{
        k =0.14+0.22*(ofNoise(ofGetElapsedTimef(),0.78)-0.3);
    }
     */
    if(!bModeAttr){
        if(charactors.size()>0){
            for(int i=0;i<charactors.size();i++){
                charactors[i]->update();
            }
        }
    } else {
        if(charactors.size()>0){
            for(int i=0;i<charactors.size();i++){
                if(!attr.empty()){
                    for(int j=0;j<attr.size();j++){
                        charactors[i]->update( attr[j].pos);
                    }
                }else{
                    charactors[i]->update();
                }
            }
        }
        if(bMove)attrMove();
    }
//    k = (float)mouseX/(float)ofGetWidth();
//    *pk = k;
//    cout << k << endl;
//    cout << *pk << endl;
//    getFeaturePoint();
//    if(featurePoints.size()!=0)buildTriangleMesh();
}

//-----------------------------------------------------------------------------
void TextMove::updateAll(){
    if(bEnableLimit)rebirth(10);
    if(charactors.size()>0){
        for(int i=0;i<charactors.size();i++){
            charactors[i]->update();//k,1.0,timeT);
        }
    }    
}

//-----------------------------------------------------------------------------
void TextMove::draw(ofColor color){
    ofEnableBlendMode(OF_BLENDMODE_ADD);
    ofSetRectMode(OF_RECTMODE_CENTER);
    //draw for universe
//    ofPushMatrix();
//    ofTranslate(-500, 0);
//    ofRotateZ(ofGetElapsedTimef());
//    milkyWay.draw(0,0);
//    ofPopMatrix();
//    
//    ofPushMatrix();
//    ofTranslate(ofGetWidth(), 0);
//    ofRotateZ(-ofGetElapsedTimef()*0.6);
//    milkyWay.draw(0,0);
//    ofRotateZ(ofGetElapsedTimef());
//    ofPopMatrix();

    ofSetColor(255, 128);
    if(featurePoints.size()!=0){
        triangle.triangleMesh.drawWireframe();
    }
    ofFill();
    ofSetColor(color,235+ofRandom(20));
    for(int i=0;i<charactors.size();i++){
        if(0.1<ofRandom(2)){
            charactors[i]->draw(&img0);
        }else{
            charactors[i]->draw(&img1);
        }        
    }
    ofSetRectMode(OF_RECTMODE_CORNER);
    
    if(bSphere){
        ofNoFill();
        ofSetColor(255, 128);
        for(int i=0;i<attr.size();i++){
            ofSphere( attr[i].pos, charactors[0]->attRadius);
        }
//        list<Attractor* >::iterator it;
//        for(it=attr.begin();it!=attr.end();it++){
//            ofSphere( (*it)->pos, charactors[0]->attRadius);
//        }
    }
    
//    pos+=vec;
}

//---------------------------------------------------------------------------
void TextMove::drawConnection(int times, ofColor color){
    Character *curi, *curj;
    ofSetColor(color,255);
    for(int j=0;j<charactors.size();j+=times){
        curj = charactors[j];
        for(int i=j+1;i<charactors.size();i+=times){
            curi = charactors[i];
            float distance = curi->pos.distance(curj->pos);
            if(i!=j && curi->maxLimit>distance && curi->minLimit<distance){
                ofLine(charactors[i]->pos, charactors[j]->pos);
            }
        }
    }
}

//---------------------------------------------------------------------------
void TextMove::addParticle(float x, float y){
//    setRect(x,y);
//    setVertex();
}

//---------------------------------------------------------------------------
void TextMove::setVertex(float x, float y){
    float jitter = 8;
    float dim = 20;
//    charactors.push_back(new Character( ofVec3f(x+ofRandom(-jitter,jitter),
//                                                y+ofRandom(-jitter,jitter),
//                                                ofRandom(-jitter,jitter)),
//                                       screenSize, timeScale ));
}

//--------------------------------------------------------------------------
void TextMove::setRect(float x, float y){
    float jitter = 8;
    float dim = 20;
//    charactors.push_back(new Character( ofVec3f(-dim + x + ofRandom(-jitter,jitter),
//                                                y + ofRandom(-jitter,jitter),
//                                                -dim + ofRandom(-jitter,jitter)),
//                                       screenSize, timeScale ));
//    charactors.push_back(new Character( ofVec3f(dim + x + ofRandom(-jitter,jitter),
//                                                y + ofRandom(-jitter,jitter),
//                                                -dim + ofRandom(-jitter,jitter)),
//                                       screenSize, timeScale ));
//    charactors.push_back(new Character( ofVec3f(dim + x + ofRandom(-jitter,jitter),
//                                                y + ofRandom(-jitter,jitter),
//                                                dim + ofRandom(-jitter,jitter)),
//                                       screenSize, timeScale ));
//    charactors.push_back(new Character( ofVec3f(-dim + x + ofRandom(-jitter,jitter),
//                                                y + ofRandom(-jitter,jitter),
//                                                dim + ofRandom(-jitter,jitter)),
//                                       screenSize, timeScale ));
}

//--------------------------------------------------------------------------
void TextMove::setRectStr(){
//    float strGrid = 45;
//    si = 20;
//    sj = 20;
//    sk = 10;
    for(int k=-sk;k<sk;k++){
        for(int j=-sj;j<sj;j++){
            for(int i=-si;i<si;i++){
//                charactors.push_back(new Character(ofVec3f(strGrid*i, strGrid*j, strGrid*k),screenSize, timeScale) );
            }
        }
    }
}

//--------------------------------------------------------------------------
void TextMove::setSphereStr(){
    float strGrid = 40;
    int si, sj, sk;
    si = 100;
    sj = 10;
    for(int j=1;j<sj;j++){
        for(int i=-si;i<si;i++){
            float s = ofRandom(360.0);
            float t = ofRandom(360.0);
//            charactors.push_back(new Character( ofVec3f( strGrid*j*cos(s)*sin(t), strGrid*j*sin(s)*sin(t), strGrid*j*cos(t)),screenSize, timeScale) );
        }
    }
}

//-------------------------------------------------------
void TextMove::setAttrPos(ofVec3f _pos){
//    *attrPos[0] = _pos;
}

void TextMove::mouseMoved(ofMouseEventArgs& args){
    msX = args.x;
    msY = args.y;
    if(checkMove()) addParticle(args.x-ofGetWidth()/2, args.y-ofGetHeight()/2);
//    cout << "pk " << *pk << ", " << *pdamp << endl;
}

//

bool TextMove::checkMove(){
    if( 20 < ofVec2f(msX,msY).distance( ofVec2f(pmsX,pmsY) )){
        pmsX = msX;
        pmsY = msY;
        return true;
    }else{
        pmsX = msX;
        pmsY = msY;
        return false;
    }
}

void TextMove::saveAllParam(){
    saveGridParam();
}

//
void TextMove::clear(){
    charactors.clear();
}

//-------------------------------------------------------
void TextMove::birth(){
    float legth = 400;
    charactors.push_back(new Character(false, ofVec3f( legth*ofRandom(-1,1), legth*ofRandom(-1,1), legth*ofRandom(-1,1)),
                                       screenSize, attRadius, armLength, nodeSize, &noiseScaleL, &noiseScaleS, &timeScale));
    charactors[charactors.size()-1]->setValue(pTimeT, pDeltaTime, pNoiseContrast, pk, pdamp);
}

//-------------------------------------------------------
void TextMove::setTargetPos(int swh){
    if(modeNum==0){
        switch (swh) {
            case 0: setTargetPos(wireWall60); break;
            case 1: setTargetPos(wireWall70); break;
            case 2: setTargetPos(wireWall80); break;
            case 3: setTargetPos(wireWall90); break;
            default: break;
        }
    }else{
        switch (swh) {
            case 0: setTargetPos(wireWall61); break;
            case 1: setTargetPos(wireWall71); break;
            case 2: setTargetPos(wireWall81); break;
            case 3: setTargetPos(wireWall91); break;
            default: break;
        }
    }
}

//-------------------------------------------------------
void TextMove::setTargetPos(vector<ofVec3f *> _trgPos){
    if(charactors.size()>_trgPos.size()){
        for(int i=0;i<_trgPos.size();i++){
            charactors[i]->setTrgPos(_trgPos[i]);
        }
    }else if(charactors.size()<_trgPos.size()){
        for(int i=0;i<charactors.size();i++){
            charactors[i]->setTrgPos(_trgPos[i]);
        }
    }else{
        for(int i=0;i<charactors.size();i++){
            charactors[i]->setTrgPos(_trgPos[i]);
        }
    }
}
//-------------------------------------------------------
void TextMove::saveGridParam(){
    
	ofxXmlSettings saveValue;
	saveValue.addTag("grid");
	saveValue.pushTag("grid");
    
	saveValue.addTag("number");
	saveValue.pushTag("number");
    
	saveValue.addValue("si", si);
	saveValue.addValue("sj", sj);
	saveValue.addValue("sk", sk);
	saveValue.addValue("strGrid", strGrid);
    
	saveValue.popTag(); //number
	saveValue.popTag(); //pop grid
    
	saveValue.saveFile(paramFile);
    
}

void TextMove::loadAllParam(){
    loadFileName();
    paramFile = "_paramFile.xml";
    iniValueFile = "_iniValueFile.xml";
//
//    loadGridParam();
    loadIniParam();
}
//--------------------------------------------
void TextMove::loadFileName(){
    ofxXmlSettings loadValue;
	if(loadValue.loadFile("_fileName.xml")){
        loadValue.pushTag("fileName");
        paramFile = loadValue.getValue("param", "faled");
        iniValueFile = loadValue.getValue("ini", "faled");
        loadValue.popTag();
    }
}


//-------------------------------------------------------
void TextMove::loadGridParam(){
	ofxXmlSettings loadValue;
	if(loadValue.loadFile(paramFile)){
        
		loadValue.pushTag("grid");
		loadValue.pushTag("number");
		// tig: defaulting with floats so as to get floats back.
		si = loadValue.getValue("si", 0.);
		sj = loadValue.getValue("sj", 0.);
		sk = loadValue.getValue("sk", 0.);
		strGrid = loadValue.getValue("strGrid", 10.);
        		
		loadValue.popTag(); //pop number;
        loadValue.popTag(); //pop grid;

	}
	else{
		ofLog(OF_LOG_ERROR, "loadParam: couldn't load parametor!");
	}

}

//-------------------------------------------------------
void TextMove::saveIniParam(){
    
	ofxXmlSettings saveValue;
    
	saveValue.addTag("attractor");
	saveValue.pushTag("attractor");
    
	saveValue.addTag("num");
	saveValue.pushTag("num");
    
    int numSize;
    if(!attr.empty()){
        numSize = attr.size();
    }else{
        numSize = 0;
    }
    saveValue.addValue("size", numSize);
    saveValue.popTag();
    
    if(attr.empty()!=0){
        int i=0;
        for(int i=0;i<attr.size();i++){
            saveValue.addTag("attPos");
            saveValue.pushTag("attPos");
            saveValue.addValue("X"+ofToString(i), attr[i].pos.x);
            saveValue.addValue("Y"+ofToString(i), attr[i].pos.y);
            saveValue.addValue("Z"+ofToString(i), attr[i].pos.z);
            saveValue.addValue("VX"+ofToString(i), attr[i].vec.x);
            saveValue.addValue("VY"+ofToString(i), attr[i].vec.y);
            saveValue.addValue("VZ"+ofToString(i), attr[i].vec.z);
            saveValue.popTag();
        }
    }
    
    saveValue.addTag("fileName");
	saveValue.pushTag("fileName");
    saveValue.addValue("name", objName);
    saveValue.addValue("scale", objScale);
    saveValue.addValue("videoScale", videoScale);
    saveValue.addValue("timeScale", timeScale);
    saveValue.addValue("noiseScaleL", noiseScaleL);
    saveValue.addValue("noiseScaleS", noiseScaleS);
    saveValue.addValue("attRadius", attRadius);
    saveValue.addValue("armLength", armLength);
    saveValue.addValue("nodeSize", nodeSize);
    saveValue.popTag();//fileName
    
    saveValue.addTag("CamMvParam");
    saveValue.pushTag("CamMvParam");
    saveValue.addValue("posX", pos.x);
	saveValue.addValue("posY", pos.y);
	saveValue.addValue("posZ", pos.z);
    saveValue.addValue("vecX", vec.x);
	saveValue.addValue("vecY", vec.y);
	saveValue.addValue("vecZ", vec.z);
    saveValue.addValue("rotX", rot.x);
	saveValue.addValue("rotY", rot.y);
	saveValue.addValue("rotZ", rot.z);
    saveValue.popTag();//fileName
    
    saveValue.saveFile(iniValueFile);
    
}
//--------------------
void TextMove::loadIniParam(){
    ofxXmlSettings loadValue;
	if(loadValue.loadFile(iniValueFile)){
        
        loadValue.pushTag("attractor");
        loadValue.pushTag("num");
        int numAtt = loadValue.getValue("size", 0.);
        loadValue.popTag();//num
        for(int i=0;i<numAtt;i++) {
            loadValue.pushTag("attPos");
            ofVec3f pos = ofVec3f(loadValue.getValue("X"+ofToString(i), 0.),loadValue.getValue("Y"+ofToString(i), 0.),loadValue.getValue("Z"+ofToString(i), 0.) );
            ofVec3f vec = ofVec3f(loadValue.getValue("VX"+ofToString(i), 0.),loadValue.getValue("VY"+ofToString(i), 0.),loadValue.getValue("VZ"+ofToString(i), 0.));
            attr.push_back(Attractor(999,pos,vec) );
            loadValue.popTag();//attPos
        }
//        loadValue.popTag();//att
        
        loadValue.pushTag("fileName");
        objName = loadValue.getValue("name", "null");
        objScale = loadValue.getValue("scale", 1.0);
        videoScale = loadValue.getValue("videoScale", 2.0);
        timeScale = loadValue.getValue("timeScale", 0.03);
        noiseScaleL = loadValue.getValue("noiseScaleL", 0.007);
        noiseScaleS = loadValue.getValue("noiseScaleS", 0.028);
        attRadius = loadValue.getValue("attRadius", 100);
        armLength = loadValue.getValue("armLength", 40);
        nodeSize = loadValue.getValue("nodeSize", 30);
        loadValue.popTag();
        
        loadValue.pushTag("CamMvParam");
        pos.x = loadValue.getValue("posX", 0.);
        pos.y = loadValue.getValue("posY", 0.);
        pos.z = loadValue.getValue("posZ", 0.);
        vec.x = loadValue.getValue("vecX", 0.);
        vec.y = loadValue.getValue("vecY", 0.);
        vec.z = loadValue.getValue("vecZ", 0.);
        rot.x = loadValue.getValue("rotX", 0.);
        rot.y = loadValue.getValue("rotY", 0.);
        rot.z = loadValue.getValue("rotZ", 0.);
        loadValue.popTag();
        
        cout << "obj name : " << objName << endl;
        cout << "numAtt :" << numAtt << endl;
        cout << "attRadius :" << attRadius << endl;
	}
    
	else{
		ofLog(OF_LOG_ERROR, "loadIniParam: couldn't load parametor!");
	}
}

//--------------------------------------------------------------
void TextMove::buildTriangleMesh(){
/*
    triangle.reset();
//    charactors.clear();
//    cout << "fPoint :" << featurePoints.size() << endl;
    for(int i=0;i<featurePoints.size();i++){
        charactors.push_back(new Character(false, ofVec3f(featurePoints[i].x,featurePoints[i].y,0)*videoScale,screenSize, timeScale, attRadius+ofRandom(100,150), armLength+ofRandom(0,25), nodeSize, &timeT, &noiseScaleL, &noiseScaleS));
        triangle.addPoint(featurePoints[i].x*videoScale,featurePoints[i].y*videoScale,0);
//        cout << "fPoint x: " << featurePoints[i].x << ", y: " << featurePoints[i].y << endl;
    }
    triangle.triangulate();
*/
}

//--------------------------------------------------------------
void TextMove::getFeaturePoint(){
    //1 find features on the color image
    if(bVideo)movFrameNum ++;
    if(movie.isFrameNew()) {
        if(movie.getTotalNumFrames()>movFrameNum){
            movie.setFrame(movFrameNum);
        }else{
            movFrameNum = 0;
        }
//        cout << "fNum: " << movFrameNum << endl;
        featurePoints.clear();
        ofImage tmp;
        tmp = movie.getPixelsRef();
    //    tmp.loadImage("triTest.png");
        
        ofImage imgFCV;
        imgFCV.clear();
        imgFCV.setUseTexture(false);
        imgFCV.setFromPixels(tmp);
    //    imgFCV.setFromPixels(player.getVideoPlayer()->getPixelsRef());
        imgFCV.setImageType(OF_IMAGE_GRAYSCALE);
        goodFeaturesToTrack(toCv(imgFCV),
                            featurePoints,
                            maxFeatures,
                            featureQuality,
                            minDistance);
    }
    /*
    ofImage depth;
    depth.setFromPixels(player.getDepthSequence()->getPixels());
    ofColor dclr;
    //2 triangulated the features
    triangulate.reset();
    for(int i = 0; i < featurePoints.size(); i++){
        //        dclr = depth.getColor(featurePoints[i].x, featurePoints[i].y);
        triangulate.addPoint( meshBuilder.getDepthPoint(featurePoints[i].x-1,featurePoints[i].y-1) );
    }
    triangulate.triangulate();
    
    //    cout << "d color :" << ofToString(dclr) << endl;
    //    cout << "featurePoint :" << featurePoints[ofRandom(0,50)].x << ": " << featurePoints[ofRandom(0,50)].y << endl;
    //    cout << "vertex :" << meshBuilder.getMesh().getVertex(ofRandom(640)) << endl;
    //    renderer.bindRenderer(renderer.meshShader);
    //    triangulate.triangleMesh.draw();
    //    renderer.unbindRenderer();
    
    //3 copy them into a 3d mesh
    triangulatedMesh.clear();
    
    vector<ofVec3f>& trianglePoints = triangulate.triangleMesh.getVertices();
//    vector<ofVec2f>& textureCoords = meshBuilder.getMesh().getTexCoords();
    vector<ofVec2f> tempTextureCoords;
    for (int i=0;i<featurePoints.size();i++){
        tempTextureCoords.push_back( ofVec2f(featurePoints[i].x,featurePoints[i].y) );
    }
    vector<ofVec2f>& textureCoords = tempTextureCoords;

         
    vector<bool> validVertIndeces;
    
    int cnt = 0;
    for(int i = 0; i < trianglePoints.size(); i++){
        int closestTexCoordIndex  = 0;
        float closestTexCoordDistance = 1000000;
        for(int j = 0; j < textureCoords.size(); j++){
            ofVec2f tri2d(trianglePoints[i].x,trianglePoints[i].y);
            float texCoordDist = tri2d.distanceSquared(textureCoords[j]);
            
            if(texCoordDist < closestTexCoordDistance){
                closestTexCoordDistance = texCoordDist;
                closestTexCoordIndex = j;
            }
        }
        ofVec3f vert = ofVec3f(---);
        triangulatedMesh.addVertex(vert);
        triangulatedMesh.addTexCoord(meshBuilder.getMesh().getTexCoord(closestTexCoordIndex));
        validVertIndeces.push_back(vert.z < farClip && vert.z > 10);
    }
    
    //copy indices across
    faceNormals.clear();
    faceCenters.clear();
    
	map<ofIndexType, vector<int> > vertexIndexToFaceIndex;
    for(int i = 0 ; i < triangulate.triangleMesh.getNumIndices(); i+=3){
        ofIndexType a,b,c;
        a = triangulate.triangleMesh.getIndex(i);
        if(!validVertIndeces[a]) continue;
        
        b = triangulate.triangleMesh.getIndex(i+1);
        if(!validVertIndeces[b]) continue;
        
        c = triangulate.triangleMesh.getIndex(i+2);
        if(!validVertIndeces[c]) continue;
        
        triangulatedMesh.addIndex(triangulate.triangleMesh.getIndex(i  ));
        triangulatedMesh.addIndex(triangulate.triangleMesh.getIndex(i+1));
        triangulatedMesh.addIndex(triangulate.triangleMesh.getIndex(i+2));
        
        //keep track of which faces belong to which vertices
    	vertexIndexToFaceIndex[a].push_back(faceNormals.size());
        vertexIndexToFaceIndex[b].push_back(faceNormals.size());
        vertexIndexToFaceIndex[c].push_back(faceNormals.size());
        
        //calculate the face normal
        ofVec3f& va = triangulatedMesh.getVertices()[a];
        ofVec3f& vb = triangulatedMesh.getVertices()[b];
        ofVec3f& vc = triangulatedMesh.getVertices()[c];
        ofVec3f faceNormal = (vb-va).getCrossed(vc-va).normalized();
        faceNormals.push_back( faceNormal );
        faceCenters.push_back( (va + vb + vc) / 3.);
        
    }
    
    //now go through and average the normals into the vertices
    triangulatedMesh.getNormals().resize(triangulatedMesh.getNumVertices());
    map<ofIndexType, vector<int> >::iterator it;
    for(it = vertexIndexToFaceIndex.begin(); it != vertexIndexToFaceIndex.end(); it++) {
        ofVec3f average(0,0,0);
		vector<int>& faceNormalIndices = it->second;
        for(int i = 0 ; i < faceNormalIndices.size(); i++){
            average += faceNormals[ faceNormalIndices[i] ];
        }
        average.normalize();
        triangulatedMesh.setNormal(it->first, average);
    }
    
    //Create a lattice structure
    latticeMesh.clear();
    
    //copy the main vertices into the lattice mesh
    for(int i = 0; i < triangulatedMesh.getNumVertices(); i++){
        latticeMesh.addVertex(triangulatedMesh.getVertex(i));
        latticeMesh.addNormal(triangulatedMesh.getNormal(i));
    }
    
    innerPoints.clear();
    backInnerPoints.clear();
    backPoints.clear();
    
    //for each triangle, find the centroid and create 3 new vertices that move a fixed distane towards the center
    //then stitch them
    
    for(int i = 0 ; i < triangulatedMesh.getNumIndices(); i+=3){
        
        ofIndexType o1 = triangulatedMesh.getIndex(i);
        ofIndexType o2 = triangulatedMesh.getIndex(i+1);
        ofIndexType o3 = triangulatedMesh.getIndex(i+2);
        
        ofVec3f& va = triangulatedMesh.getVertices()[o1];
        ofVec3f& vb = triangulatedMesh.getVertices()[o2];
        ofVec3f& vc = triangulatedMesh.getVertices()[o3];
        
        ofVec3f& center = faceCenters[i/3];
        ofVec3f& normal = faceNormals[i/3];
        
        ofVec3f innerA = va + (center - va).normalized() * 2;
        ofVec3f innerB = vb + (center - vb).normalized() * 2;
        ofVec3f innerC = vc + (center - vc).normalized() * 2;
        
        innerPoints.push_back(innerA);
        innerPoints.push_back(innerB);
        innerPoints.push_back(innerC);
        
        
        backPoints.push_back(va - triangulatedMesh.getNormal(o1) * 2);
        backPoints.push_back(vb - triangulatedMesh.getNormal(o2) * 2);
        backPoints.push_back(vc - triangulatedMesh.getNormal(o3) * 2);
        
        backInnerPoints.push_back(innerA - normal*2);
        backInnerPoints.push_back(innerB - normal*2);
        backInnerPoints.push_back(innerC - normal*2);
        
        //get the indices of the inner points
        ofIndexType i1 = latticeMesh.getNumVertices();
        ofIndexType i2 = i1+1;
        ofIndexType i3 = i1+2;
        
        //add the inner points to the mesh
        latticeMesh.addVertex(innerA);
        latticeMesh.addVertex(innerB);
        latticeMesh.addVertex(innerC);
        
        latticeMesh.addNormal(normal);
        latticeMesh.addNormal(normal);
        latticeMesh.addNormal(normal);
        
        //stitch the 3 quads around the inner mesh
        latticeMesh.addIndex(o1);latticeMesh.addIndex(o2);latticeMesh.addIndex(i2);
        latticeMesh.addIndex(i2);latticeMesh.addIndex(i1);latticeMesh.addIndex(o1);
        
        latticeMesh.addIndex(o2);latticeMesh.addIndex(o3);latticeMesh.addIndex(i3);
        latticeMesh.addIndex(i3);latticeMesh.addIndex(i2);latticeMesh.addIndex(o2);
        
        latticeMesh.addIndex(o3);latticeMesh.addIndex(o1);latticeMesh.addIndex(i1);
        latticeMesh.addIndex(i1);latticeMesh.addIndex(i3);latticeMesh.addIndex(o3);
        
        //add back vertices
        ofIndexType bo1 = latticeMesh.getNumVertices();
        ofIndexType bo2 = bo1+1;
        ofIndexType bo3 = bo1+2;
        
        latticeMesh.addVertex(innerA);
        latticeMesh.addVertex(innerB);
        latticeMesh.addVertex(innerC);
        
    }
     */
}

//-------------------------------------------------------
void TextMove::exit(){
    saveAllParam();
}
