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
	verdana.loadFont("verdana.ttf",40, false, true);
}

void OP1::draw(int x, int y, int width){ //all is drawn as 1px = 1mm, then scaled up
    
    
    ofTranslate(x, y);
    ofScale(width/284, width/284);
    ofTranslate(-(284/2), -(102/2)); //set coords to top right

    drawFrame();
    drawKeyboard();
    drawSpeakerGrille();
    drawVolumeKnob(1);
    drawKnobs();
    drawButtons();
    
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
            ofSetColor(0x222222);
            ofTranslate(-3, 2);
            ofScale(0.05, 0.05);
            verdana.drawString("input", 0,0);
        }
        break;
            
        case 1:
        {
            ofSetColor(0x222222);
            ofTranslate(-3, 2);
            ofScale(0.05, 0.05);
            verdana.drawString("com", 0,0);
        }
        break;
            
        case 2:
        {
            ofSetColor(0x222222);
            ofTranslate(-3, 2);
            ofScale(0.05, 0.05);
            verdana.drawString("synth", 0,0);
        }
        break;
            
        case 3:
        {
            ofSetColor(0x222222);
            ofTranslate(-3, 2);
            ofScale(0.05, 0.05);
            verdana.drawString("drum", 0,0);
        }
        break;
            
        case 4:
        {
            ofSetColor(0x222222);
            ofTranslate(-3, 2);
            ofScale(0.05, 0.05);
            verdana.drawString("tape", 0,0);
        }
        break;
            
        case 5:
        {
            ofSetColor(0x222222);
            ofTranslate(-3, 2);
            ofScale(0.05, 0.05);
            verdana.drawString("mix", 0,0);
        }
        break;
            
        case 6:
        {
            ofSetColor(0x222222);
            ofTranslate(-3, 2);
            ofScale(0.05, 0.05);
            verdana.drawString("1", 0,0);
        }
        break;
            
        case 7:
        {
            ofSetColor(0x222222);
            ofTranslate(-3, 2);
            ofScale(0.05, 0.05);
            verdana.drawString("2", 0,0);
        }
        break;
            
        case 8:
        {
            ofSetColor(0x222222);
            ofTranslate(-3, 2);
            ofScale(0.05, 0.05);
            verdana.drawString("3", 0,0);
        }
        break;
            
        case 9:
        {
            ofSetColor(0x222222);
            ofTranslate(-3, 2);
            ofScale(0.05, 0.05);
            verdana.drawString("4", 0,0);
        }
        break;
            
        case 10:
        {
            ofSetColor(0x222222);
            ofTranslate(-3, 2);
            ofScale(0.05, 0.05);
            verdana.drawString("in", 0,0);
        }
        break;
            
        case 11:
        {
            ofSetColor(0x222222);
            ofTranslate(-3, 2);
            ofScale(0.05, 0.05);
            verdana.drawString("out", 0,0);
        }
        break;
            
        case 12:
        {
            ofSetColor(0x222222);
            ofTranslate(-3, 2);
            ofScale(0.05, 0.05);
            verdana.drawString("loop", 0,0);
        }
        break;
            
        case 13:
        {
            ofSetColor(0x222222);
            ofTranslate(-3, 2);
            ofScale(0.05, 0.05);
            verdana.drawString("mute", 0,0);
        }
        break;
            
        case 14:
        {
            ofSetColor(0x222222);
            ofTranslate(-3, 2);
            ofScale(0.05, 0.05);
            verdana.drawString("rev", 0,0);
        }
        break;
            
        case 15:
        {
            ofSetColor(0x222222);
            ofTranslate(-3, 2);
            ofScale(0.05, 0.05);
            verdana.drawString("stop", 0,0);
        }
        break;
            
        case 16:
        {
            ofSetColor(0x222222);
            ofTranslate(-3, 2);
            ofScale(0.05, 0.05);
            verdana.drawString("M1", 0,0);
        }
        break;
            
        case 17:
        {
            ofSetColor(0x222222);
            ofTranslate(-3, 2);
            ofScale(0.05, 0.05);
            verdana.drawString("M2", 0,0);
        }
        break;
            
        case 18:
        {
            ofSetColor(0x222222);
            ofTranslate(-3, 2);
            ofScale(0.05, 0.05);
            verdana.drawString("seq", 0,0);
        }
        break;
            
        case 19:
        {
            ofSetColor(0x222222);
            ofTranslate(-3, 2);
            ofScale(0.05, 0.05);
            verdana.drawString("help", 0,0);
        }
        break;
            
        case 20:
        {
            ofSetColor(0x222222);
            ofTranslate(-3, 2);
            ofScale(0.05, 0.05);
            verdana.drawString("metro", 0,0);
        }
        break;
            
        case 21:
        {
            ofSetColor(0x222222);
            ofTranslate(-3, 2);
            ofScale(0.05, 0.05);
            verdana.drawString("lift", 0,0);
        }
        break;
            
        case 22:
        {
            ofSetColor(0x222222);
            ofTranslate(-3, 2);
            ofScale(0.05, 0.05);
            verdana.drawString("drop", 0,0);
        }
        break;
            
        case 23:
        {
            ofSetColor(0x222222);
            ofTranslate(-3, 2);
            ofScale(0.05, 0.05);
            verdana.drawString("join", 0,0);
        }
        break;
            
        case 24:
        {
            ofSetColor(0x222222);
            ofTranslate(-3, 2);
            ofScale(0.05, 0.05);
            verdana.drawString("rec", 0,0);
        }
        break;
            
        case 25:
        {
            ofSetColor(0x222222);
            ofTranslate(-3, 2);
            ofScale(0.05, 0.05);
            verdana.drawString("play", 0,0);
        }
        break;
            
        case 26:
        {
            ofSetColor(0x222222);
            ofTranslate(-3, 2);
            ofScale(0.05, 0.05);
            verdana.drawString("stop", 0,0);
        }
        break;
            
        case 27:
        {
            ofSetColor(0x222222);
            ofTranslate(-3, 2);
            ofScale(0.05, 0.05);
            verdana.drawString("rw", 0,0);
        }
        break;
            
        case 28:
        {
            ofSetColor(0x222222);
            ofTranslate(-3, 2);
            ofScale(0.05, 0.05);
            verdana.drawString("ff", 0,0);
        }
        break;
            
        case 29:
        {
            ofSetColor(0x222222);
            ofTranslate(-3, 2);
            ofScale(0.05, 0.05);
            verdana.drawString("shift", 0,0);
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

void OP1::drawKnob(int knobNumber, float angle){
    ofSetColor(darkGrey);
    roundedRect(30, 30, 0.5);
    ofPushMatrix();
    ofTranslate(15, 15);
    ofSetColor(0xaaaaaa);
    ofCircle(0, 0, 9);
    ofSetColor(lightGrey);
    ofCircle(0, 0, 8.5);
    
    int color = 0x000000;
    switch (knobNumber) {
        case 0:
            color = blue;
            break;
        case 1:
            color = green;
            break;
        case 2:
            color = white;
            break;
        case 3:
            color = orange;
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
        drawKnob(i, 0.125);
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

  
