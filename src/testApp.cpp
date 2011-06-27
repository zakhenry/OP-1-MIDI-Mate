#include "testApp.h"


//--------------------------------------------------------------
void testApp::setup(){
	ofSetCircleResolution(50);
	ofBackground(0, 0, 0);
	ofSetWindowTitle("graphics example");

	ofSetFrameRate(60); // if vertical sync is off, we can go a bit fast... this caps the framerate at 60fps.
    
    ofHideCursor();
    op1.setDimensions(ofGetWidth()/2, ofGetHeight()/2, ofGetWidth()-200);
}

//--------------------------------------------------------------
void testApp::update(){
//    op1.update();
//    CGPoint point;
//    point.x = 100*sin(ofGetElapsedTimef()*5)+500;
//    point.y = 100*cos(ofGetElapsedTimef()*5)+500;
//    CGWarpMouseCursorPosition(point);
    

}

//--------------------------------------------------------------
void testApp::draw(){
    op1.draw();
}

void OP1::drawScreen(){
    ofSetRectMode(OF_RECTMODE_CORNER);
    ofSetColor(0xff0000);
    ofRect(0, 0, this->getScreenWidth(), this->getScreenHeight());
    
}


//--------------------------------------------------------------
void testApp::keyPressed  (int key){
    cout << "key pressed ("<<key<<")\n";
    switch (key) {
        case 'f':
            ofToggleFullscreen();
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
