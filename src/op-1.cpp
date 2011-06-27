//
//  op-1.cpp
//  OP-1
//
//  Created by Zak Henry on 26/06/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#include "op-1.h"

//colours grabbed from the pantone chart on the main site
int blue = 0x0098D4;
int green = 0x01BB00;
int lightGrey = 0xDEE8E9;
int orange = 0xFE4F00;
int darkGrey = 0xC3C9C9;
int black = 0x000000;
int white = 0xFFFFFF;


OP1::OP1(){ // constructor
    
    cout << "OP-1 created\n";
    
    // font name, size, anti-aliased, full character set
	verdana.loadFont("verdana.ttf",80, true, true);
    spyroclassic.loadFont("spyroclassic.ttf",80, true, true);
    ofSetRectMode(OF_RECTMODE_CENTER);
    
    midiIn.listPorts();
    midiIn.openPort(0);
    ofAddListener(midiIn.newMessageEvent, this, &OP1::newMessageEvent);
}

void OP1::draw(int x, int y, int width){ //all is drawn as 1px = 1mm, then scaled up
    
    scaleFactor = (float)width/284;
    ofTranslate(x, y);
    ofScale(scaleFactor, scaleFactor);
    ofTranslate(-(284/2), -(102/2)); //set coords to top right

    drawFrame();
    drawKeyboard();
    drawSpeakerGrille();
    drawVolumeKnob(1);
    drawKnobs();
    drawButtons();
    
    ofPushMatrix();
    ofPushStyle();
    ofTranslate(66, 4.5);
    drawScreen();
    ofPopStyle();
    ofPopMatrix();
    
}

float OP1::getScreenHeight(){
    return 30;
}

float OP1::getScreenWidth(){
    return 61;
}


void OP1::drawFrame(){
    
//    ofSetColor(0xff0000);
//    ofCircle(0, 0, 10);
    
    ofPushMatrix();
        ofSetColor(darkGrey);
        roundedRect(284, 102, 4);
        ofSetColor(black);
    ofTranslate(4, 4);
        roundedRect(264, 93, 2);
    ofPopMatrix();
    
    //mic grill
    
    ofPushMatrix();
    ofTranslate(275, 10.05);
        ofCircle(0, 0, 0.5);
        ofCircle(2.5, 0, 0.5);
        ofCircle(0, 2.5, 0.5);
        ofCircle(2.5, 2.5, 0.5);
    ofPopMatrix();
    
    //vu grill
    
    ofPushMatrix();
    ofTranslate(276.5, 37);
        ofCircle(0, 0, 0.5);
        ofCircle(0, 3, 0.5);
        ofCircle(0, 6, 0.5);
        ofCircle(0, 9, 0.5);
        ofCircle(0, 12, 0.5);
    ofPopMatrix();
    
}

void OP1::drawKeyboard(){
    
    ofPushMatrix();
    ofTranslate(50.5, 66);
        
    //white notes
    for (int i=0; i<14; i++){
        ofPushMatrix();
            ofSetColor(darkGrey);
            roundedRect(14.5, 30, 0.5);
            ofTranslate(2, 2);
            ofSetColor(lightGrey);
            roundedRect(10, 25, 5);
        ofPopMatrix();
        
        ofTranslate(15.5, 0);
    }
    
    ofPopMatrix();
    //black notes
    ofPushMatrix();
    ofTranslate(50.5, 50.5);
    for (int i=1; i<=10; i++){
        ofPushMatrix();
        ofSetColor(darkGrey);
        
        if (i==2||i==7){
            roundedRect(14.5, 14.5, 0.5);
            ofTranslate(7, 7);
        }else if (i==3||i==5||i==8||i==10){
            roundedRect(22.5, 14.5, 0.5);
            ofTranslate(7, 7);
        }else{
            roundedRect(22.5, 14.5, 0.5);
            ofTranslate(15, 7);
        }
        
        ofSetColor(lightGrey);
        ofCircle(0, 0, 5);
        ofSetColor(black);
        ofCircle(0, 0, 4.5);
        ofPopMatrix();
        
        if (i==2||i==7){
            ofTranslate(15.3, 0);
        }else{
            ofTranslate(23.3, 0);
        }
        
    }
    ofPopMatrix();
        
    
    
    
}

void OP1::drawSpeakerGrille(){
    ofPushMatrix();
    ofTranslate(4.5, 4.5);
        ofSetColor(darkGrey);
        roundedRect(30, 30, 0.5);
    
    ofTranslate(1.2, 1.2);
    ofSetColor(black);
    for (int x=1; x<=13; x++){
        for (int y=1; y<=13; y++){
            //this is truly a horrific implementation. needs fixing
            if (!(x==1&&y==1)&&!(x==2&&y==1)&&!(x==3&&y==1)&&!(x==1&&y==2)&&!(x==1&&y==3)){
                if(!(x==11&&y==1)&&!(x==12&&y==1)&&!(x==13&&y==1)&&!(x==13&&y==2)&&!(x==13&&y==3)){
                    if(!(x==1&&y==11)&&!(x==1&&y==12)&&!(x==1&&y==13)&&!(x==2&&y==13)&&!(x==3&&y==13)){
                        if(!(x==13&&y==11)&&!(x==13&&y==12)&&!(x==13&&y==13)&&!(x==12&&y==13)&&!(x==11&&y==13)){
                            ofCircle(x*2, y*2, 0.6);
                        }
                    }
                }
            }
        }
    }
    
    ofPopMatrix();
}

void OP1::drawVolumeKnob(float volume){
    ofPushMatrix();
    ofTranslate(35, 4.5);
        ofSetColor(darkGrey);
        roundedRect(30, 14.5, 0.5);
        ofTranslate(7, 7);
        ofSetColor(white);
        ofCircle(0, 0, 5);
        ofRotateZ(volume*360*0.8+135);
        ofTranslate(3, 0);
        ofSetColor(lightGrey);
        ofCircle(0, 0, 1.4);
        ofSetColor(white);
        ofCircle(0, 0, 1);
    
    ofPopMatrix();
}

void OP1::drawButton(int buttonNumber){
    ofSetColor(darkGrey);
    roundedRect(14.5, 14.5, 0.5);
    ofPushMatrix();
    ofTranslate(14.5/2, 14.5/2);
    ofSetColor(lightGrey);
    ofCircle(0, 0, 5);
    
    switch (buttonNumber) {
        case 0:
        {
            ofSetColor(orange);
            ofRotateZ(45);
            ofTranslate(0, -1.5);
            ofCircle(0, 0, 0.8);
            ofRect(0, 2, 0.6, 2.5);
        }
        break;
            
        case 1:
        {
            ofSetColor(black);
            ofTranslate(0, -1.5);
            ofCircle(0, 0, 2);
            ofSetColor(lightGrey);
            ofCircle(0, 0, 1.7);
            ofSetColor(black);
            ofCircle(0, 0, 0.6);
            ofScale(0.025, 0.025);
            ofSetColor(black);
            spyroclassic.drawString("COM", -100,180);
        }
        break;
            
        case 2:
        {
            ofSetColor(blue);
            ofTranslate(-3, 2);
            ofScale(0.05, 0.05);
            spyroclassic.drawString("synth", 0,0);
        }
        break;
            
        case 3:
        {
            ofSetColor(green);
            ofCircle(0, 0, 1.7);
            ofSetColor(lightGrey);
            ofCircle(0, 0, 1.4);
            ofSetColor(green);
            ofCircle(0, 0, 0.5);
            ofTranslate(0, 1.4);
            ofRect(0, 0, 0.3, 1.8);
        }
        break;
            
        case 4:
        {
            ofTranslate(-1.5, 0);
            ofSetColor(orange);
            ofCircle(0, 0, 1.3);
            ofSetColor(lightGrey);
            ofCircle(0, 0, 1);
            ofTranslate(3, 0);
            ofSetColor(orange);
            ofCircle(0, 0, 1.3);
            ofSetColor(lightGrey);
            ofCircle(0, 0, 1);
            ofTranslate(-1.5, 1.1);
            ofSetColor(orange);
            ofRect(0, 0, 3, 0.3);
        }
        break;
            
        case 5:
        {
            ofSetColor(black);
            ofTranslate(-1.5, 0.4);
            ofRect(0, 0, 0.3, 2);
            ofRect(1, -0.5, 0.3, 3);
            ofRect(2, 0.15, 0.3, 1.7);
            ofRect(3, 0, 0.3, 2);
        }
        break;
            
        case 6:
        {
            ofSetColor(black);
            ofRect(0, 0, 0.55, 5);
        }
        break;
            
        case 7:
        {
            ofSetColor(black);
            ofTranslate(-2, 2.5);
            ofScale(0.1, 0.08);
            spyroclassic.drawString("2", 0,0);
        }
        break;
            
        case 8:
        {
            ofSetColor(black);
            ofTranslate(-2.5, 2.5);
            ofScale(0.1, 0.08);
            spyroclassic.drawString("3", 0,0);
        }
        break;
            
        case 9:
        {
            ofSetColor(black);
            ofTranslate(-2.5, 2.5);
            ofScale(0.1, 0.08);
            spyroclassic.drawString("4", 0,0);
        }
        break;
            
        case 10:
        {
            ofScale(0.04, 0.04);
            ofSetColor(black);
            spyroclassic.drawString("1", -20,0);
            ofScale(0.5, 0.7);
            ofSetColor(green);
            spyroclassic.drawString("IN", -50,100);
        }
        break;
            
        case 11:
        {
            ofScale(0.04, 0.04);
            ofSetColor(black);
            spyroclassic.drawString("2", -20,0);
            ofScale(0.5, 0.7);
            ofSetColor(green);
            spyroclassic.drawString("OUT", -100,100);
        }
        break;
            
        case 12:
        {
            ofScale(0.04, 0.04);
            ofSetColor(black);
            spyroclassic.drawString("3", -20,0);
            ofSetColor(green);
        }
        break;
            
        case 13:
        {
            ofPushMatrix();
            ofScale(0.04, 0.04);
            ofSetColor(black);
            spyroclassic.drawString("4", -20,0);
            ofPopMatrix();
            
            ofTranslate(-1.5, 2);
            ofScale(0.8, 0.8);
            //            ofScale(8, 8);
            //            ofTranslate(-10, 0);
            ofSetColor(orange);
            ofCircle(0, 0, 1.3);
            ofSetColor(lightGrey);
            ofCircle(0, 0, 1);
            ofTranslate(3, 0);
            ofSetColor(orange);
            ofCircle(0, 0, 1.3);
            ofSetColor(lightGrey);
            ofCircle(0, 0, 1);
            ofTranslate(-1.5, 1.1);
            ofSetColor(orange);
            ofRect(0, 0, 3, 0.3);
            
            ofBeginShape();
            //            ofCurve(-0.3, -0.3, <#float x1#>, <#float y1#>, <#float x2#>, <#float y2#>, <#float x3#>, <#float y3#>);
            ofEndShape();
        }
        break;
            
        case 14:
        {
            ofScale(0.04, 0.04);
            ofSetColor(black);
            spyroclassic.drawString("5", -20,0);
            ofSetColor(orange);
        }
        break;
            
        case 15:
        {
            ofPushMatrix();
            ofScale(0.04, 0.04);
            ofSetColor(black);
            spyroclassic.drawString("6", -20,0);
            ofPopMatrix();
        }
        break;
            
        case 16:
        {
            ofScale(0.04, 0.04);
            ofSetColor(black);
            spyroclassic.drawString("7", -20,0);
            ofScale(0.5, 0.7);
            spyroclassic.drawString("M1", -50,100);
        }
        break;
            
        case 17:
        {
            ofScale(0.04, 0.04);
            ofSetColor(black);
            spyroclassic.drawString("8", -20,0);
            ofScale(0.5, 0.7);
            spyroclassic.drawString("M2", -50,100);
        }
        break;
            
        case 18:
        {
            ofSetColor(blue);
            ofTranslate(-2, 0.8);
            ofCircle(0, 0, 0.5);
            ofCircle(1.5, -1.5, 0.5);
            ofCircle(3, 0, 0.5);
            ofCircle(4.5, 0, 0.5);
        }
        break;
            
        case 19:
        {
            ofSetColor(black);
            ofTranslate(-3, 2);
            ofScale(0.05, 0.05);
            spyroclassic.drawString("help", 0,0);
        }
        break;
            
        case 20:
        {
            ofSetColor(black);
            ofTranslate(-3, 2);
            ofScale(0.05, 0.05);
            spyroclassic.drawString("metro", 0,0);
        }
        break;
            
        case 21:
        {
            ofSetColor(orange);
            
            ofScale(0.04, 0.03);
            ofSetColor(black);
            spyroclassic.drawString("1-4", -50,100);
        }
        break;
            
        case 22:
        {
            ofSetColor(orange);
            ofSetColor(black);
            ofTranslate(0, 2.5);
            ofCircle(0, 0, 0.5);
        }
        break;
            
        case 23:
        {
            ofSetColor(orange);
            ofScale(0.03, 0.03);
            ofSetColor(black);
            spyroclassic.drawString("JOIN", -70,100);
        }
        break;
            
        case 24:
        {
            ofSetColor(orange);
            ofCircle(0, 0, 4);
            ofSetColor(lightGrey);
            ofCircle(0, 0, 1);
        }
        break;
            
        case 25:
        {
            ofSetColor(black);
            ofTranslate(-3, 2);
            ofScale(0.05, 0.05);
            spyroclassic.drawString("play", 0,0);
        }
        break;
            
        case 26:
        {
            ofSetColor(black);
            ofRect(0, 0, 2.5, 2.5);
        }
        break;
            
        case 27:
        {
            ofSetColor(black);
            ofTranslate(-2, 2);
            ofScale(0.06, 0.06);
            spyroclassic.drawString("<", 0,0);
        }
        break;
            
        case 28:
        {
            ofSetColor(black);
            ofTranslate(-1, 2);
            ofScale(0.06, 0.06);
            spyroclassic.drawString(">", 0,0);
        }
        break;
            
        case 29:
        {
            ofSetColor(black);
            ofTranslate(-2, 1);
            ofScale(0.03, 0.04);
            spyroclassic.drawString("Shift", 0,0);
        }
        break;
            
        default:
            break;
    }
    
    
    
    ofPopMatrix();
}

void OP1::drawButtons(){
    
    int buttonNumber = 0;
    
    ofPushMatrix();
    ofTranslate(252.5, 4.5);
    for (int i=1; i<=2; i++){
        drawButton(buttonNumber);
        ofTranslate(0, 15.45);
        buttonNumber++;
    }
    ofPopMatrix();
    
    ofPushMatrix();
    ofTranslate(4.5, 35);
    for (int i=1; i<=17; i++){
        drawButton(buttonNumber);
        ofTranslate(15.45, 0);
        buttonNumber++;
    }
    ofPopMatrix();
    
    ofPushMatrix();
    ofTranslate(35, 20);
    for (int i=1; i<=2; i++){
        drawButton(buttonNumber);
        ofTranslate(15.45, 0);
        buttonNumber++;
    }
    ofPopMatrix();
    
    ofPushMatrix();
    ofTranslate(4.5, 35+15.45);
    for (int i=0; i<=2; i++){
        for (int j=0; j<=2; j++){
            ofPushMatrix();
                ofTranslate(15.45*j, 15.45*i);
                drawButton(buttonNumber);
                buttonNumber++;
            ofPopMatrix();
        }
    }
    ofPopMatrix();
        
    
}

void OP1::drawKnob(int knobNumber){
    ofSetColor(darkGrey);
    roundedRect(30, 30, 0.5);
    ofPushMatrix();
    ofTranslate(15, 15);
    ofSetColor(0xaaaaaa);
    ofCircle(0, 0, 9);
    ofSetColor(lightGrey);
    ofCircle(0, 0, 8.5);
    
    int color = 0x000000; 
    float angle;
    switch (knobNumber) {
        case 0:
            color = blue;
            angle = bEncoder;
            break;
        case 1:
            color = green;
            angle = gEncoder;
            break;
        case 2:
            color = white;
            angle = wEncoder;
            break;
        case 3:
            color = orange;
            angle = oEncoder;
            break;
            
        default:
            break;
    }
    ofSetColor(color);
    ofCircle(0, 0, 5);
    
    ofRotateZ(angle*360);
    
    ofTranslate(-3, -1);
    ofSetColor(0x888888);
    roundedRect(6, 2, 1);
    ofSetColor(color);
    ofTranslate(0.2, 0.1);
    ofScale(0.9, 0.9);
    roundedRect(6, 2, 1);
    
    ofPopMatrix();
}

void OP1::drawKnobs(){
    ofPushMatrix();
    ofTranslate(128.5, 4.5);
    for (int i=0; i<4; i++){
        drawKnob(i);
        ofTranslate(31, 0);
    }
    ofPopMatrix();
}

void OP1::roundedRect(float w, float h, float r) {
    ofBeginShape();
    ofVertex(r, 0);
    ofVertex(w-r, 0);
    quadraticBezierVertex(w, 0, w, r, w-r, 0);
    ofVertex(w, h-r);
    quadraticBezierVertex(w, h, w-r, h, w, h-r);
    ofVertex(r, h);
    quadraticBezierVertex(0, h, 0, h-r, r, h);
    ofVertex(0, r);
    quadraticBezierVertex(0, 0, r, 0, 0, r);
    ofEndShape();
}

void OP1::quadraticBezierVertex(float cpx, float cpy, float x, float y, float prevX, float prevY) {
    float cp1x = prevX + 2.0/3.0*(cpx - prevX);
    float cp1y = prevY + 2.0/3.0*(cpy - prevY);
    float cp2x = cp1x + (x - prevX)/3.0;
    float cp2y = cp1y + (y - prevY)/3.0;
    
    // finally call cubic Bezier curve function
    ofBezierVertex(cp1x, cp1y, cp2x, cp2y, x, y);
}



/*Setting values*/

void OP1::setEncoder(int encoder, float angle){
    
    
    switch (encoder) {
        case 'b':
            bEncoder = angle;
            break;
            
        case 'g':
            gEncoder = angle;
            break;
            
        case 'w':
            wEncoder = angle;
            break;
            
        case 'o':
            oEncoder = angle;
            break;
            
        default:
            cout <<"bad encoder id\n";
            break;
    }
    
}

void OP1::incrementEncoder(int encoder, bool cw){
    
    
    switch (encoder) {
        case 1:
            bEncoder = cw ? bEncoder+((float)1/32):bEncoder-((float)1/32);
            break;
            
        case 2:
            gEncoder = cw ? gEncoder+((float)1/32):gEncoder-((float)1/32);
            break;
            
        case 3:
            wEncoder = cw ? wEncoder+((float)1/32):wEncoder-((float)1/32);
            break;
            
        case 4:
            oEncoder = cw ? oEncoder+((float)1/32):oEncoder-((float)1/32);
            break;
            
        default:
            cout <<"bad encoder id\n";
            break;
    }
    
}

void OP1::newMessageEvent (ofxMidiEventArgs & args){
    
    int port = args.port;
	int	channel = args.channel;
	int status = args.status;
	int byteOne = args.byteOne;
	int byteTwo = args.byteTwo;
	double 	timestamp = args.timestamp;
    
    if (byteOne<=4){ //encoder
        incrementEncoder(byteOne, byteTwo==1);
    }else{
        
    }
    
    cout << "midi packet: port ["<<port<<"], channel ["<<channel<<"], status ["<<status<<"], byteOne ["<<byteOne<<"], byte2 ["<<byteTwo<<"], timestamp ["<<timestamp<<"]\n";
}
