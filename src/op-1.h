//
//  op-1.h
//  OP-1
//
//  Created by Zak Henry on 26/06/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#ifndef _OP_1 // if this class hasn't been defined, the program can define it
#define _OP_1 // by using this if statement you prevent the class to be called more 
// than once which would confuse the compiler

#include "ofMain.h"
#include "ofEvents.h"
#include "ofxMidi.h"

class OP1 {
	
	//private
    
    void drawFrame();
    void drawKeyboard();
    void drawSpeakerGrille();
    void drawVolumeKnob(float volume);
    void drawButtons();
    void drawButton(int buttonNumber);
    void drawKnobs();
    void drawKnob(int knobNumber);
    
    void drawScreen();
    float getScreenHeight();
    float getScreenWidth();
    
    void quadraticBezierVertex(float cpx, float cpy, float x, float y, float prevX, float prevY);
    void roundedRect(float w, float h, float r);
    
    ofTrueTypeFont	verdana, spyroclassic;
    
    float scaleFactor;
    float volume, bEncoder, gEncoder, wEncoder, oEncoder; //angles
    
    ofxMidiIn midiIn;
    void newMessageEvent (ofxMidiEventArgs & args);
    
public:
    
    OP1(); //constructor
    
    void draw(int x, int y, int width);
    void setEncoder(int encoder, float angle);
    void incrementEncoder(int encoder, bool cw);
    
};









#endif