#include "testApp.h"
#include "stdio.h"

//--------------------------------------------------------------
void testApp::setup(){
    ofSetDataPathRoot("./");
	ofSetCircleResolution(50);
	ofBackground(0, 0, 0);
	ofSetWindowTitle("ofxOP1 example");

	ofSetFrameRate(60); // if vertical sync is off, we can go a bit fast... this caps the framerate at 60fps.
    
//    ofHideCursor();
    op1.setDimensions(ofGetWidth()/2, ofGetHeight()/2, ofGetWidth()-200);
    
    
//    cout << "cwd is "<<getcwd()<<"\n";
    
//    verdana.loadFont("verdana.ttf",80, true, true);
    ofAddListener(op1.midiEvent, this, &testApp::op1Event);
    
}

//--------------------------------------------------------------
void testApp::update(){

}

void testApp::op1Event(midiPacket &packet){
    cout << "midi packet: channel ["<<packet.channel<<"], event ["<<packet.event<<"], keyId ["<<packet.elementId<<"], keyName ["<<packet.elementName<<"], timestamp ["<<packet.timestamp<<"]\n";
}

//--------------------------------------------------------------
void testApp::draw(){
    
    
//    ofPushMatrix();
//    ofScale(0.5, 0.5);
//    ofSetColor(0x555555);
//    verdana.drawString("fps: "+ofToString(ofGetFrameRate()), 10, 100);
//    ofPopMatrix();
    
    
    op1.draw();
}

static float adder = 0;

//--------------------------------------------------------------
void testApp::keyPressed  (int key){
//    cout << "key pressed ("<<key<<")\n";
    switch (key) {
        case 'f':
            {
                if (ofGetWindowMode()==OF_FULLSCREEN){
                    ofSetWindowShape(1024,768);
                    ofSetFullscreen(false);
                    op1.setDimensions(1024/2, 768/2, 1024-200);
                }else{
                    ofSetWindowShape(ofGetScreenWidth(),ofGetScreenHeight());
                    ofSetFullscreen(true);
                    op1.setDimensions(ofGetScreenWidth()/2, ofGetScreenHeight()/2, ofGetScreenWidth()-200);
                }
            }
            break;
            
        default:
            break;
    }
}

//--------------------------------------------------------------
void testApp::keyReleased  (int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){
    op1.updateCursorPosition(x, y);
}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){
}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){
    op1.mouseDown(x, y);
}


//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){
    op1.mouseUp();
}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}
