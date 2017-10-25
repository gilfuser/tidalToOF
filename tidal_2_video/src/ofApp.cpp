#include "ofApp.h"

void ofApp::setup() {
    ofBackground(0);
    ofSetHexColor(0xFFFFFF);
    ofSetFrameRate(60);
    ofSetVerticalSync(true);
    movieFile = ofToString("videos/c0716_moby2.avi");
    vidPlayer.load(movieFile);
    segments = 200;
    if (vidPlayer.isLoaded()){
        vidPlayer.play();
        totalFrames = vidPlayer.getTotalNumFrames();
        totalDuration = vidPlayer.getDuration();
    }
    vidPlayer.setLoopState(OF_LOOP_NORMAL);

    receiver.setup(PORT);
    begin=0;
    end=1;
    speed=1;
    n = 0;
    playFrom = 0;
    delta = 1;
    fadeTime = 0;
    segmentTime = 1;

    bTimerReached = false;
    startTime = ofGetElapsedTimeMillis();  // get the start time
    endTime = (int)ofRandom(1000, 5000); // in milliseconds

}
////--------------------------------------------------------------
void ofApp::update() {

    segmentTime = segments / totalDuration;

    vidPlayer.update();
}

////--------------------------------------------------------------
void ofApp::draw(){

    while(receiver.hasWaitingMessages()){
        receiver.getNextMessage(msg);
        if (msg.getAddress() == "/delta"){
            delta = msg.getArgAsFloat(0);
        }
        if (msg.getAddress() == "/begin"){
            begin = msg.getArgAsFloat(0);
        }
        if (msg.getAddress() == "/end"){
            end = msg.getArgAsFloat(0);
        }
        if (msg.getAddress() == "/fadetime"){
            fadeTime = msg.getArgAsFloat(0);
        }
        if (msg.getAddress() == "/gain"){
            gain = msg.getArgAsFloat(0);
        }
        if (msg.getAddress() == "/n"){
            n = msg.getArgAsInt(0);
            playFrom = (n + begin) / segments;
            vidPlayer.setPosition(playFrom);
            vidPlayer.setPaused(false);
            bTimerReached = false;
            if(end < 1) {
                startTime = ofGetElapsedTimeMillis();
                endTime = segmentTime * end * 1000;
            }
        }
        if (msg.getAddress() == "/speed"){
            speed = msg.getArgAsFloat(0);
            vidPlayer.setSpeed(speed);
        }
    }

    ofSetColor(255);
    string msgstring;
    msgstring="delta: " + ofToString(delta) + "\n"
            + "begin: " + ofToString(begin) + "\n"
            + "end:   " + ofToString(end) + "\n"
            + "fdTim: " + ofToString(fadeTime) + "\n"
            + "gain:  " + ofToString(gain) + "\n"
            + "n:     " + ofToString(n) + "\n"
            + "speed: " + ofToString(speed) + "\n \n"
            + "segmentTime: " + ofToString(segmentTime) + "\n"
            + "totalDur: " + ofToString(totalDuration) + "\n"
            + "totalFrames: " + ofToString(totalFrames) + "\n"
            + "endTime: " + ofToString(endTime);
    ofDrawBitmapString(msgstring, 400, 640);;
    ofDrawBitmapString(msgstring, 400, 640);

    // update the timer this frame
    float timer = ofGetElapsedTimeMillis() - startTime;

    if( (timer >= endTime) && !bTimerReached ){
        bTimerReached = true;
    }
    else if ( (end < 1) && bTimerReached){
        vidPlayer.setPaused(true);
    }

    vidPlayer.draw((ofGetWidth() / 2) - 400, 0, 800, 600);
}
