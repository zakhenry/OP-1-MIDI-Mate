#include "testApp.h"


//--------------------------------------------------------------
void testApp::setup(){
	ofSetCircleResolution(50);
	ofBackground(0, 0, 0);
	ofSetWindowTitle("graphics example");

	ofSetFrameRate(60); // if vertical sync is off, we can go a bit fast... this caps the framerate at 60fps.
}

//--------------------------------------------------------------
void testApp::update(){
//    op1.setEncoder('b', (float)mouseX/1000);
//    op1.setEncoder('g', (float)mouseY/1000);
//    op1.setEncoder('w', (float)mouseX/1000+(float)mouseY/1000);
//    op1.setEncoder('o', (float)mouseX/1000*(float)mouseY/1000);
}

//--------------------------------------------------------------
void testApp::draw(){
    op1.draw(ofGetWidth()/2, ofGetHeight()/2, ofGetWidth()-200);
}

void OP1::drawScreen(){
    ofSetRectMode(OF_RECTMODE_CORNER);
    ofSetColor(0xff0000);
    ofRect(0, 0, this->getScreenWidth(), this->getScreenHeight());
    
}


//--------------------------------------------------------------
void testApp::keyPressed  (int key){
    cout << "key pressed ("<<key<<")\n";
}

//--------------------------------------------------------------
void testApp::keyReleased  (int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){
}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){
}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){
}


//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}
