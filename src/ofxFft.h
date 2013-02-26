
#ifndef _OFXFFT
#define _OFXFFT

#ifndef M_PI
#define	M_PI 3.14159265358979323846  /* pi */
#endif

#include "ofMain.h"
#include "fft.h"

#define BUFFER_SIZE 512
#define NUM_WINDOWS 80
#define FFT_AVG 10


class ofxFft : ofBaseApp {
    public :
        void update();
        void draw();
        void setup();
    
        void audioReceived 	(float * input, int bufferSize, int nChannels);
        void audioIn(float * input, int bufferSize, int nChannels);
        void getSpectrum();
        void drawSpectrum();
        void drawPram();
        void settingMenu();
        float* getMagnitude();
        float* getMagSqrt();
        float* getLeftStream();
        float* getRightStream();
        float* getScaledVol();
        int getBufferSize();

    private:
        float * left;
        float * right;
        int 	bufferCounter;
        fft		myfft, myfftR;
    
        bool* bDisplayMenu;
    
        vector <float> leftS;
        vector <float> rightS;
        vector <float> volHistory;
    
        float smoothedVol;
        float scaledVol;
    
        ofSoundStream soundStream;
        float * magSqrt;
    
        float * magnitude;
        float * pMagnitudeFF;
        float * magnitudeFF;
        
        float mag[5], magFilterFacter;
        float * phase;
        float * power;
        
        float freq[NUM_WINDOWS][BUFFER_SIZE/2];
        float freq_phase[NUM_WINDOWS][BUFFER_SIZE/2];
        
        float magnitudeR[BUFFER_SIZE];
        float phaseR[BUFFER_SIZE];
        float powerR[BUFFER_SIZE];
        
        float freqR[NUM_WINDOWS][BUFFER_SIZE/2];
        float freq_phaseR[NUM_WINDOWS][BUFFER_SIZE/2];
};

#endif
