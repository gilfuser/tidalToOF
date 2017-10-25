#pragma once
#include "ofMain.h"
#include "ofxOsc.h"
#define PORT 3333

class ofApp : public ofBaseApp{
    public:
        void setup();
        void update();
        void draw();
//        void mousePressed(int x, int y, int button);
        ofVideoPlayer vidPlayer;
        string movieFile;
        float playFrom;
        int totalDuration;
        float totalFrames;
        int segments;
        ofxOscReceiver receiver;
        ofxOscMessage msg;
        float delta;
        float begin;
        float end;
        float speed;
        float fadeTime;
        float gain;
        int n;
        float w;
        float h;
        float segmentTime;

        float startTime;
        float endTime;
        bool  bTimerReached;
};

