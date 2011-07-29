//
//  op-1.h
//  OP-1
//
//  Created by Zak Henry on 26/06/11.
//

#ifndef _OP_1 // if this class hasn't been defined, the program can define it
#define _OP_1 // by using this if statement you prevent the class to be called more 
// than once which would confuse the compiler

#include "ofMain.h"
#include "ofEvents.h"
#include "ofxMidi.h"

typedef struct midiPacket {
    string event;
    int elementId;
    string elementName;
    int channel;
    double timestamp;
} midiPacket;

typedef struct controlButton{
    string name;
    int midiId;
    int graphicId;
    ofImage icon;
    bool keyPressed;
    
} controlButton;

//struct findButtonByGraphicalId{
//    bool operator()(const int graphicalId , const controlButton& button) const{
//        return graphicalId == button.graphicId;
//    }
//};

class OP1 : public ofBaseApp{
	
	//private
    public:
    
    float posX, posY, width;
    
    float cursorX, cursorY;
    
    float keySpacing, frameWidth;
    
    
    
    ofEvent<midiPacket> midiEvent;
    
    float keySpan(int span); //returns value in mm of a key spanning int grids
    
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
    void roundedRect(float w, float h, float r, bool rectModeCenter);
    
    ofImage op1Logo;
    
    vector<controlButton>controlButtons;
    
    float scaleFactor;
    float volume, bEncoder, gEncoder, wEncoder, oEncoder; //angles
    
    //MIDI IN (FROM OP-1)
    
    ofxMidiIn midiIn;
    void newMessageEvent (ofxMidiEventArgs & args);
    ofxMidiIn internalMidi;
    void newVirtualMessageEvent (ofxMidiEventArgs & args);
    
    bool op1Connected;
    bool connectToExternalOP1();
    int nextConnectionAttempt;
    
    
    vector<bool>buttonStatus;
    vector<bool>keyStatus;
    
    void changeButtonStatus(int keyNum, bool keyDown);
    void changeKeyStatus(int keyNum, bool keyDown);
    
    //MIDI OUT (TO OP-1)
    
    ofxMidiOut midiOut;
    void sendNoteOn(int noteId, int keyId);
    void sendNoteOff(int noteId, int keyId);

    
    OP1(); //constructor
    
    void setDimensions(int x, int y, int width);
    void draw();
    void setEncoder(int encoder, float angle);
    void incrementEncoder(int encoder, bool cw);
    
    void buttonEvent (int key, bool keydown, string &keyName);
    void keyEvent (int key, bool keydown, string &keyName);
    
    void update(){};
    
    void updateCursorPosition(int x, int y);
    void mouseDown(int x, int y);
    void mouseUp();
    
    bool mouseClicked;
    bool cursorInBoundingBox(float x, float y, float width, float height);
    int currentNotePlaying;
    
    void handleKeystrokes();
    
    //audio in (optional)
    void audioReceived 	(float * input, int bufferSize, int nChannels); 
    
    float * left;
    float * right;
    
};









#endif