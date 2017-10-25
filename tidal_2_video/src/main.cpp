#include "ofMain.h"
#include "ofApp.h"

//========================================================================
int main( ){
    ofSetupOpenGL(1920,1080,OF_WINDOW);			// <-------- setup the GL context
//OF_WINDOW
    // this kicks off the running of my app
    // can be OF_FULLSCREEN or OF_GAME_MODE
    // pass in width and height too:
    // OF_GAME_MODE
    ofRunApp(new ofApp());

}
