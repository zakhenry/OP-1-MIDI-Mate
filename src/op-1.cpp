//
//  op-1.cpp
//  OP-1
//
//  Created by Zak Henry on 26/06/11.
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

int keyMap[] = {53, 55, 57, 59, 60, 62, 64, 65, 67, 69, 71, 72, 74, 76, 54, 56, 58, 61, 63, 66, 68, 70, 73, 75};

OP1::OP1(){ // constructor
    
    cout << "OP-1 created\n";
    
    keySpacing = 0.7;
    frameWidth = 4.5;
    
    // font name, size, anti-aliased, full character set
	verdana.loadFont("verdana.ttf",80, true, true);
    spyroclassic.loadFont("spyroclassic.ttf",80, true, true);
    ofSetRectMode(OF_RECTMODE_CENTER);
    
    midiIn.listPorts();
    midiIn.openPort(0);
    internalMidi.openVirtualPort("Virtual OP-1");
    midiIn.setVerbose(false);
    ofAddListener(midiIn.newMessageEvent, this, &OP1::newMessageEvent);
    ofAddListener(internalMidi.newMessageEvent, this, &OP1::newVirtualMessageEvent); //send data to same callback as the external midi in
    
    for (int i=0; i<34; i++){
        buttonStatus.push_back(false);
    }
    
    for (int i=0; i<24; i++){
        keyStatus.push_back(false);
    }
    
    midiOut.openPort(0);
    
    currentNotePlaying = -1;
    
    // 0 output channels, 
	// 2 input channels
	// 22050 samples per second
	// 256 samples per buffer
	// 4 num buffers (latency)
	
    	ofSoundStreamSetup(0,2,this, 44100, 256, 4);	
    	left = new float[256];
    	right = new float[256];
    
    
    //defining the buttons
    
    controlButton mic;
    mic.name = "Mic/Input";
    mic.midiId = 48;
    mic.graphicId = 0;
    mic.icon.loadImage("mic.png");
    controlButtons.push_back(mic);
    
    controlButton com;
    com.name = "Album/Computer Connection";
    com.midiId = 49;
    com.graphicId = 1;
    com.icon.loadImage("com.png");
    controlButtons.push_back(com);
    
    controlButton synth;
    synth.name = "Synthesizer";
    synth.midiId = 7;
    synth.graphicId = 2;
    synth.icon.loadImage("synth.png");
    controlButtons.push_back(synth);
    
    controlButton drum;
    drum.name = "Drum";
    drum.midiId = 8;
    drum.graphicId = 3;
    drum.icon.loadImage("drum.png");
    controlButtons.push_back(drum);
    
    controlButton tape;
    tape.name = "Tape";
    tape.midiId = 9;
    tape.graphicId = 4;
    tape.icon.loadImage("tape.png");
    controlButtons.push_back(tape);
    
    controlButton mixer;
    mixer.name = "Mixer";
    mixer.midiId = 10;
    mixer.graphicId = 5;
    mixer.icon.loadImage("mix.png");
    controlButtons.push_back(mixer);
    
    controlButton one;
    one.name = "One";
    one.midiId = -1;
    one.graphicId = 6;
    one.icon.loadImage("one.png");
    controlButtons.push_back(one);
    
    controlButton two;
    two.name = "Two";
    two.midiId = -1;
    two.graphicId = 7;
    two.icon.loadImage("two.png");
    controlButtons.push_back(two);
    
    controlButton three;
    three.name = "Three";
    three.midiId = -1;
    three.graphicId = 8;
    three.icon.loadImage("three.png");
    controlButtons.push_back(three);
    
    controlButton four;
    four.name = "Four";
    four.midiId = -1;
    four.graphicId = 9;
    four.icon.loadImage("four.png");
    controlButtons.push_back(four);
    
    controlButton voice_1;
    voice_1.name = "Voice 1/";
    voice_1.midiId = 50;
    voice_1.graphicId = 10;
    voice_1.icon.loadImage("voice_1.png");
    controlButtons.push_back(voice_1);
    
    controlButton voice_2;
    voice_2.name = "Voice 1/";
    voice_2.midiId = 51;
    voice_2.graphicId = 11;
    voice_2.icon.loadImage("voice_2.png");
    controlButtons.push_back(voice_2);
    
    controlButton voice_3;
    voice_3.name = "Voice 1/";
    voice_3.midiId = 52;
    voice_3.graphicId = 12;
    voice_3.icon.loadImage("voice_3.png");
    controlButtons.push_back(voice_3);
    
    controlButton voice_4;
    voice_4.name = "Voice 1/";
    voice_4.midiId = 21;
    voice_4.graphicId = 13;
    voice_4.icon.loadImage("voice_4.png");
    controlButtons.push_back(voice_4);
    
    controlButton voice_5;
    voice_5.name = "Voice 1/";
    voice_5.midiId = 22;
    voice_5.graphicId = 14;
    voice_5.icon.loadImage("voice_5.png");
    controlButtons.push_back(voice_5);
    
    controlButton voice_6;
    voice_6.name = "Voice 1/";
    voice_6.midiId = 23;
    voice_6.graphicId = 15;
    voice_6.icon.loadImage("voice_6.png");
    controlButtons.push_back(voice_6);
    
    controlButton voice_7;
    voice_7.name = "Voice 1/";
    voice_7.midiId = 24;
    voice_7.graphicId = 16;
    voice_7.icon.loadImage("voice_7.png");
    controlButtons.push_back(voice_7);
    
    controlButton voice_8;
    voice_8.name = "Voice 1/";
    voice_8.midiId = 25;
    voice_8.graphicId = 17;
    voice_8.icon.loadImage("voice_8.png");
    controlButtons.push_back(voice_8);
    
    controlButton sequencer;
    sequencer.name = "Sequencer";
    sequencer.midiId = 26;
    sequencer.graphicId = 18;
    sequencer.icon.loadImage("sequencer.png");
    controlButtons.push_back(sequencer);
    
    controlButton help;
    help.name = "Help";
    help.midiId = 5;
    help.graphicId = 19;
    help.icon.loadImage("help.png");
    controlButtons.push_back(help);
    
    controlButton metro;
    metro.name = "Metronome";
    metro.midiId = 6;
    metro.graphicId = 20;
    metro.icon.loadImage("metro.png");
    controlButtons.push_back(metro);
    
    controlButton lift;
    lift.name = "Lift";
    lift.midiId = 15;
    lift.graphicId = 21;
    lift.icon.loadImage("lift.png");
    controlButtons.push_back(lift);
    
    controlButton drop;
    drop.name = "Drop";
    drop.midiId = 16;
    drop.graphicId = 22;
    drop.icon.loadImage("drop.png");
    controlButtons.push_back(drop);
    
    controlButton join;
    join.name = "Join";
    join.midiId = 17;
    join.graphicId = 23;
    join.icon.loadImage("join.png");
    controlButtons.push_back(join);
    
    controlButton record;
    record.name = "Record";
    record.midiId = 38;
    record.graphicId = 24;
    record.icon.loadImage("record.png");
    controlButtons.push_back(record);
    
    controlButton play;
    play.name = "Play";
    play.midiId = 39;
    play.graphicId = 25;
    play.icon.loadImage("play.png");
    controlButtons.push_back(play);
    
    controlButton stop;
    stop.name = "Stop";
    stop.midiId = 40;
    stop.graphicId = 26;
    stop.icon.loadImage("stop.png");
    controlButtons.push_back(stop);
    
    controlButton arrow_left;
    arrow_left.name = "Octave Down/Rewind";
    arrow_left.midiId = 41;
    arrow_left.graphicId = 27;
    arrow_left.icon.loadImage("arrow_left.png");
    controlButtons.push_back(arrow_left);
    
    controlButton arrow_right;
    arrow_right.name = "Octave Up/Fast Forward";
    arrow_right.midiId = 42;
    arrow_right.graphicId = 28;
    arrow_right.icon.loadImage("arrow_right.png");
    controlButtons.push_back(arrow_right);
    
    controlButton shift;
    shift.name = "Shift";
    shift.midiId = -1;
    shift.graphicId = 29;
    shift.icon.loadImage("shift.png");
    controlButtons.push_back(shift);
    
    controlButton encoder_blue;
    encoder_blue.name = "Blue Encoder";
    encoder_blue.midiId = 64;
    encoder_blue.graphicId = -1;
    controlButtons.push_back(encoder_blue);
    
    controlButton encoder_green;
    encoder_green.name = "Green Encoder";
    encoder_green.midiId = 65;
    encoder_green.graphicId = -1;
    controlButtons.push_back(encoder_green);
    
    controlButton encoder_white;
    encoder_white.name = "White Encoder";
    encoder_white.midiId = 66;
    encoder_white.graphicId = -1;
    controlButtons.push_back(encoder_white);
    
    controlButton encoder_orange;
    encoder_orange.name = "Orange Encoder";
    encoder_orange.midiId = 67;
    encoder_orange.graphicId = -1;
    controlButtons.push_back(encoder_orange);
    
}

float OP1::keySpan(int span){
    return ((14.7*span)+keySpacing*(span-1));
}

void OP1::setDimensions(int _x, int _y, int _width){
    posX = _x;
    posY = _y;
    width = _width;
    
    scaleFactor = width/284;
}

void OP1::draw(){ //all is drawn as 1px = 1mm, then scaled up
    
    ofPushMatrix();
        
        
        ofTranslate(posX, posY);
        ofScale(scaleFactor, scaleFactor);
        ofTranslate(-(284/2), -(102/2)); //set coords to top left
        
        

        drawFrame();
        drawKeyboard();
        drawSpeakerGrille();
        drawVolumeKnob(1);
        drawKnobs();
        drawButtons();
        
        ofPushMatrix();
        ofPushStyle();
        ofTranslate(frameWidth+keySpan(4)+keySpacing*2, frameWidth+keySpacing);
        drawScreen();
        ofPopStyle();
        ofPopMatrix();
    
    ofSetColor(0x0000ff);
    ofCircle(cursorX, cursorY, 2);
    
    ofPopMatrix();
    
    ofTranslate(cursorX, cursorY);
    
}

float OP1::getScreenHeight(){
    return keySpan(2);
}

float OP1::getScreenWidth(){
    return keySpan(4);
}


void OP1::drawFrame(){
    
//    ofSetColor(0xff0000);
//    ofCircle(0, 0, 10);
    
    ofPushMatrix();
        ofSetColor(darkGrey);
        roundedRect(284, 102, 4);
        ofSetColor(black);
    ofTranslate(frameWidth, frameWidth);
        roundedRect(keySpan(17)+2*keySpacing, keySpan(6)+2*keySpacing, 2);
    ofPopMatrix();
    
    //mic grill
    
    ofPushMatrix();
    ofTranslate(274, 11.05);
        ofCircle(0, 0, 0.5);
        ofCircle(2.5, 0, 0.5);
        ofCircle(0, 2.5, 0.5);
        ofCircle(2.5, 2.5, 0.5);
    ofPopMatrix();
    
    //vu grill
    
    ofPushMatrix();
    ofTranslate(275.5, 37);
        ofCircle(0, 0, 0.5);
        ofCircle(0, 3, 0.5);
        ofCircle(0, 6, 0.5);
        ofCircle(0, 9, 0.5);
        ofCircle(0, 12, 0.5);
    ofPopMatrix();
    
    ofPushMatrix();
        ofTranslate(277.5, 87);
        ofRotateZ(-90);
        ofScale(0.07, 0.07);
        ofSetColor(0x555555);
        spyroclassic.drawString("OP-1", 0, 0);
    ofPopMatrix();
    
}

void OP1::drawKeyboard(){
    
    ofPushMatrix();
    ofTranslate(frameWidth+2*keySpacing+keySpan(3), frameWidth+2*keySpacing+keySpan(4));
    
    int keyNumber = 0;
        
    //white notes
    for (int i=0; i<14; i++){
        ofPushMatrix();
        
            ofSetColor(darkGrey);
            roundedRect(keySpan(1), keySpan(2), 0.5);
            ofTranslate(keySpan(1)/2, keySpan(2)/2);
            ofSetColor(lightGrey);
            roundedRect(10, 25, 5, true);
        
        
        
        if (keyStatus[keyNumber]){
            ofSetColor(0x000000);
            ofCircle(0, 0, 3);
        }
            
        ofPopMatrix();
        
        ofTranslate(keySpan(1)+keySpacing, 0);
        
        keyNumber++;
    }
    
    ofPopMatrix();
    //black notes
    float blackSpan = (keySpan(4)-(keySpan(1)+2*keySpacing))/2;
    ofPushMatrix();
    ofTranslate(frameWidth+2*keySpacing+keySpan(3), frameWidth+2*keySpacing+keySpan(3));
    for (int i=1; i<=10; i++){
        ofPushMatrix();
        ofSetColor(darkGrey);
        
        if (i==2||i==7){
            roundedRect(keySpan(1), keySpan(1), 0.5);
            ofTranslate(blackSpan/3, keySpan(1)/2);
        }else if (i==3||i==5||i==8||i==10){
            roundedRect(blackSpan, keySpan(1), 0.5);
            ofTranslate(blackSpan/3, keySpan(1)/2);
        }else{
            roundedRect(blackSpan, keySpan(1), 0.5);
            ofTranslate(2*blackSpan/3, keySpan(1)/2);
        }
        
        ofSetColor(lightGrey);
        ofCircle(0, 0, 5);
        ofSetColor(black);
        ofCircle(0, 0, 4.5);
        if (keyStatus[keyNumber]){
            ofSetColor(0xffffff);
            ofCircle(0, 0, 2.5);
        }
        
        ofPopMatrix();
        
        if (i==2||i==7){
            ofTranslate(keySpan(1)+keySpacing, 0);
        }else{
            ofTranslate(blackSpan+keySpacing, 0);
        }
     keyNumber++;   
    }
    ofPopMatrix();
        
    
    
    
}

void OP1::drawSpeakerGrille(){
    ofPushMatrix();
    ofTranslate(frameWidth+keySpacing, frameWidth+keySpacing);
        ofSetColor(darkGrey);
        roundedRect(keySpan(2), keySpan(2), 0.5);
    
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
    ofTranslate(frameWidth+2*keySpacing+keySpan(2), frameWidth+keySpacing);
        ofSetColor(darkGrey);
        roundedRect(keySpan(2), keySpan(1), 0.5);
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
    roundedRect(keySpan(1), keySpan(1), 0.5);
    ofPushMatrix();
        ofTranslate(keySpan(1)/2, keySpan(1)/2);
        ofSetColor(lightGrey);
        ofCircle(0, 0, 5);
        
        ofScale(0.1, 0.1);
        if (controlButtons[buttonNumber].graphicId>=0){ //only draw if it has a graphic id
            controlButtons[buttonNumber].icon.draw(0,0);
        }
    ofPopMatrix();
    
    if (buttonStatus[buttonNumber]){
        //highlight keydown
        ofPushMatrix();
        ofTranslate(14.5/2, 14.5/2);
        ofSetColor(0xff0000);
        ofCircle(0, 0, 3);
        ofPopMatrix();
    }
    
}

void OP1::drawButtons(){
    
    int buttonNumber = 0;
    
    ofPushMatrix();
    ofTranslate(frameWidth+2*keySpacing+keySpan(16), frameWidth+keySpacing);
    for (int i=1; i<=2; i++){
        drawButton(buttonNumber);
        ofTranslate(0, keySpan(1)+keySpacing);
        buttonNumber++;
    }
    ofPopMatrix();
    
    ofPushMatrix();
    ofTranslate(frameWidth+keySpacing, frameWidth+2*keySpacing+keySpan(2));
    for (int i=1; i<=17; i++){
        drawButton(buttonNumber);
        ofTranslate(keySpan(1)+keySpacing, 0);
        buttonNumber++;
    }
    ofPopMatrix();
    
    ofPushMatrix();
    ofTranslate(frameWidth+2*keySpacing+keySpan(2), frameWidth+2*keySpacing+keySpan(1));
    for (int i=1; i<=2; i++){
        drawButton(buttonNumber);
        ofTranslate(keySpan(1)+keySpacing, 0);
        buttonNumber++;
    }
    ofPopMatrix();
    
    ofPushMatrix();
    ofTranslate(frameWidth+keySpacing, frameWidth+2*keySpacing+keySpan(3));
    for (int i=0; i<=2; i++){
        for (int j=0; j<=2; j++){
            ofPushMatrix();
                ofTranslate((keySpacing+keySpan(1))*j, (keySpacing+keySpan(1))*i);
                drawButton(buttonNumber);
                buttonNumber++;
            ofPopMatrix();
        }
    }
    ofPopMatrix();
        
    
}

void OP1::drawKnob(int knobNumber){
    ofSetColor(darkGrey);
    roundedRect(keySpan(2), keySpan(2), 0.5);
    ofPushMatrix();
    ofTranslate(keySpan(2)/2, keySpan(2)/2);
    ofSetColor(0xaaaaaa);
    ofCircle(0, 0, 9);
    ofSetColor(lightGrey);
    ofCircle(0, 0, 8.5);
    
    int buttonNumber = -1;
    
    int color = 0x000000; 
    float angle;
    switch (knobNumber) {
        case 0:
            color = blue;
            angle = bEncoder;
            buttonNumber = 30;
            break;
        case 1:
            color = green;
            angle = gEncoder;
            buttonNumber = 31;
            break;
        case 2:
            color = white;
            angle = wEncoder;
            buttonNumber = 32;
            break;
        case 3:
            color = orange;
            angle = oEncoder;
            buttonNumber = 33;
            break;
            
        default:
            break;
    }
    
    if (buttonNumber>0){
        if (buttonStatus[buttonNumber]){
            ofSetColor(0x000000);
            ofCircle(0, 0, 7);
        }
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
    ofTranslate(frameWidth+2*keySpacing+keySpan(8), frameWidth+keySpacing);
    for (int i=0; i<4; i++){
        drawKnob(i);
        ofTranslate(keySpan(2)+keySpacing, 0);
    }
    ofPopMatrix();
}

void OP1::roundedRect(float w, float h, float r, bool rectModeCenter) {
    
    ofPushMatrix();
    if (rectModeCenter){
        ofTranslate(-(w/2), -(h/2));
    }
    
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
    
    ofPopMatrix();
}

void OP1::roundedRect(float w, float h, float r) { //function overloader
    roundedRect(w, h, r, false);
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

void OP1::changeButtonStatus(int buttonNum, bool buttonDown){
    if (buttonNum>=0){
        buttonStatus[buttonNum] = buttonDown;
        cout << "button ["<<buttonNum<<"] status changed to ["<<buttonDown<<"]\n";
    }else{
        cout <<"button not found\n";
    }
    
}

void OP1::buttonEvent(int button, bool buttonDown, string& buttonName){
    int buttonNum = -1; //changing midi id's to graphical ids
    
//    
//    switch (button) {
//        case 48:
//            buttonNum = 0;
//            buttonName = "input";
//            break;
//        case 49:
//            buttonNum = 1;
//            buttonName = "com";
//            break;
//        case 7:
//            buttonNum = 2;
//            buttonName = "synth";
//            break;
//        case 8:
//            buttonNum = 3;
//            buttonName = "drum";
//            break;
//        case 9:
//            buttonNum = 4;
//            buttonName = "tape";
//            break;
//        case 10:
//            buttonNum = 5;
//            buttonName = "mixer";
//            break;
//    /*    case :
//            buttonNum = 6;
//            break;
//        case :
//            buttonNum = 7;
//            break;
//        case :
//            buttonNum = 8;
//            break;
//        case :
//            buttonNum = 9;
//            break;
//     */
//        case 50:
//            buttonNum = 10;
//            buttonName = "tape_in";
//            break;
//        case 51:
//            buttonNum = 11;
//            buttonName = "tape_out";
//            break;
//        case 52:
//            buttonNum = 12;
//            buttonName = "tape_loop";
//            break;
//        case 21:
//            buttonNum = 13;
//            buttonName = "tape_pause";
//            break;
//        case 22:
//            buttonNum = 14;
//            buttonName = "tape_reverse";
//            break;
//        case 23:
//            buttonNum = 15;
//            buttonName = "tape_jitter";
//            break;
//        case 24:
//            buttonNum = 16;
//            buttonName = "m1";
//            break;
//        case 25:
//            buttonNum = 17;
//            buttonName = "m2";
//            break;
//        case 26:
//            buttonNum = 18;
//            buttonName = "sequencer";
//            break;
//        case 5:
//            buttonNum = 19;
//            buttonName = "help";
//            break;
//        case 6:
//            buttonNum = 20;
//            buttonName = "metronome";
//            break;
//        case 15:
//            buttonNum = 21;
//            buttonName = "tape_lift";
//            break;
//        case 16:
//            buttonNum = 22;
//            buttonName = "tape_drop";
//            break;
//        case 17:
//            buttonNum = 23;
//            buttonName = "tape_join";
//            break;
//        case 38:
//            buttonNum = 24;
//            buttonName = "record";
//            break;
//        case 39:
//            buttonNum = 25;
//            buttonName = "play";
//            break;
//        case 40:
//            buttonNum = 26;
//            buttonName = "stop";
//            break;
//        case 41:
//            buttonNum = 27;
//            buttonName = "octave_down";
//            break;
//        case 42:
//            buttonNum = 28;
//            buttonName = "octave_up";
//            break;
//        /*case :
//            buttonNum = 29;
//             buttonName = "shift";
//            break;*/
//        case 64: //encoder 1
//            buttonNum = 30;
//            buttonName = "encoder_blue";
//            break;
//            
//        case 65: //encoder 2
//            buttonNum = 31;
//            buttonName = "encoder_green";
//            break;
//            
//        case 66: //encoder 3
//            buttonNum = 32;
//            buttonName = "encoder_white";
//            break;
//            
//        case 67: //encoder 4
//            buttonNum = 33;
//            buttonName = "encoder_orange";
//            break;
//            
//        default:
//            cout <<"button not found\n";
//            break;
//    }
    
    for (int i=0; i<=controlButtons.size(); i++){
        if (controlButtons[button].midiId==button){
            buttonNum = i;
            break;
        }
    }
    
    if (buttonDown){
        changeButtonStatus(buttonNum, buttonDown);
    }else{
        changeButtonStatus(buttonNum, buttonDown);
    }
}

void OP1::keyEvent(int key, bool keyDown, string& keyName){
    int keyNum = -1; //changing midi id's to graphical ids
    
//    cout <<"key input is ["<<key<<"]\n";
    
    if (((key+3)%12)==0) {
        cout << "A pressed\n";
    }
    
    switch (key) {
            //white keys
        case 53:
            keyNum = 0;
            keyName = "F";
            break;
        case 55:
            keyNum = 1;
            keyName = "G";
            break;
        case 57:
            keyNum = 2;
            keyName = "A";
            break;
        case 59:
            keyNum = 3;
            keyName = "B";
            break;
        case 60:
            keyNum = 4;
            keyName = "C";
            break;
        case 62:
            keyNum = 5;
            keyName = "D";
            break;
        case 64:
            keyNum = 6;
            keyName = "E";
            break;
        case 65:
            keyNum = 7;
            keyName = "F";
            break;
        case 67:
            keyNum = 8;
            keyName = "G";
            break;
        case 69:
            keyNum = 9;
            keyName = "A";
            break;
        case 71:
            keyNum = 10;
            keyName = "B";
            break;
        case 72:
            keyNum = 11;
            keyName = "C";
            break;
        case 74:
            keyNum = 12;
            keyName = "D";
            break;
        case 76:
            keyNum = 13;
            keyName = "E";
            break;
            
            //black keys
            
        case 54:
            keyNum = 14;
            keyName = "F#";
            break;
        case 56:
            keyNum = 15;
            keyName = "G#";
            break;
        case 58:
            keyNum = 16;
            keyName = "A#";
            break;
        case 61:
            keyNum = 17;
            keyName = "C#";
            break;
        case 63:
            keyNum = 18;
            keyName = "D#";
            break;
        case 66:
            keyNum = 19;
            keyName = "F#";
            break;
        case 68:
            keyNum = 20;
            keyName = "G#";
            break;
        case 70:
            keyNum = 21;
            keyName = "A#";
            break;
        case 73:
            keyNum = 22;
            keyName = "C#";
            break;
        case 75:
            keyNum = 23;
            keyName = "D#";
            break;
           
        default:
            cout <<"key not found\n";
            break;
    }
    
    if (keyDown){
        changeKeyStatus(keyNum, keyDown);
    }else{
        changeKeyStatus(keyNum, keyDown);
    }
}

void OP1::changeKeyStatus(int keyNum, bool keyDown){
    if (keyNum>=0){
        keyStatus[keyNum] = keyDown;
//        cout << "key ["<<keyNum<<"] status changed to ["<<keyDown<<"]\n";
    }else{
        cout <<"key not found\n";
    }
    
}

void OP1::newMessageEvent (ofxMidiEventArgs & args){
    
    int port = args.port;
	int	channel = args.channel;
	int status = args.status;
	int byteOne = args.byteOne;
	int byteTwo = args.byteTwo;
	double 	timestamp = args.timestamp;
    
    string event;
    string elementName;
    
    if (status == 176){ //control input
        if (byteOne<=4){ //encoder
            incrementEncoder(byteOne, byteTwo==1);
            event = (byteTwo==1)?"encoder_cw":"encoder_ccw";
        }else{
            buttonEvent(byteOne, byteTwo==127, elementName); //buttonid buttondown
            event = (byteTwo==127)?"button_down":"button_up";
        }
    }else{ //keyboard input?
        while (byteOne>64) { //octave shifting
            byteOne-=24;
            
        }
        
        while (byteOne<53) { //octave shifting
            byteOne+=24;
        }
        
        keyEvent(byteOne, status==144, elementName); //keyid keydown
        event = (status==144)?"key_down":"key_up";
    }
    
    midiPacket newPacket;
    newPacket.channel = 0;
    newPacket.event = event;
    newPacket.elementId = byteOne;
    newPacket.elementName = elementName;
    newPacket.timestamp = timestamp;
    
    ofNotifyEvent(midiEvent, newPacket, this);
    
        cout << "midi packet: port ["<<port<<"], channel ["<<channel<<"], status ["<<status<<"], byteOne ["<<byteOne<<"], byte2 ["<<byteTwo<<"], timestamp ["<<timestamp<<"]\n";

}

void OP1::newVirtualMessageEvent (ofxMidiEventArgs & args){
    
    int port = args.port;
	int	channel = args.channel;
	int status = args.status;
	int byteOne = args.byteOne;
	int byteTwo = args.byteTwo;
	double 	timestamp = args.timestamp;
    
    string event;
    string elementName;
    
    int keyId = byteOne;

    while (keyId>64) { //octave shifting
        keyId-=24;
        
    }
    
    while (keyId<53) { //octave shifting
        keyId+=24;
    }
    
//    keyEvent(byteOne, status==144, elementName); //keyid keydown
    event = (status==144)?"key_down":"key_up";
    
    if (event=="key_down"){
        sendNoteOn(byteOne, keyId);
    }else{
        sendNoteOff(byteOne, keyId);
    }
    
    midiPacket newPacket;
    newPacket.channel = 0;
    newPacket.event = event;
    newPacket.elementId = byteOne;
    newPacket.elementName = elementName;
    newPacket.timestamp = timestamp;
    
//    ofNotifyEvent(midiEvent, newPacket, this);
    
    cout << "virtual midi packet: port ["<<port<<"], channel ["<<channel<<"], status ["<<status<<"], byteOne ["<<byteOne<<"], byte2 ["<<byteTwo<<"], timestamp ["<<timestamp<<"]\n";

}


void OP1::sendNoteOn(int noteId, int keyId){ //note is the absolute note id, key is remapped notes to fit the length of the keyboard
    midiOut.sendNoteOn(1, noteId, 144);
    string name;
    keyEvent(keyId, true, name);
}

void OP1::sendNoteOff(int noteId, int keyId){
    midiOut.sendNoteOff(1, noteId, 128);
    string name;
    keyEvent(keyId, false, name);
}

void OP1::mouseDown(int x, int y){
    
//    cout << "mouse down at ("<<cursorX<<","<<cursorY<<")\n";
    handleKeystrokes();
}

void OP1::mouseUp(){
    
    sendNoteOff(currentNotePlaying, currentNotePlaying);
    currentNotePlaying = -1;
}

void OP1::updateCursorPosition(int x, int y){ //global mouseX, mouseY is passed in
    
    cursorX = (x-posX)/scaleFactor+(284/2);
    cursorY = (y-posY)/scaleFactor+(102/2);
    
}

bool OP1::cursorInBoundingBox(float x, float y, float width, float height){
    
    if (cursorX>x && cursorX<x+width){
        if (cursorY>y && cursorY<y+height){
            ofSetColor(0x00ffff);
            return true;
        }
    }
    return false;
}

void OP1::handleKeystrokes(){
    
    int keyNumber = 0;
    
//white notes
    for (int i=0; i<14; i++){
        
            if (cursorInBoundingBox(50.5+i*15.5, 66, 14.5, 30)){
                currentNotePlaying = keyMap[keyNumber];
                sendNoteOn(currentNotePlaying, currentNotePlaying);
            }
        
        keyNumber++;
    }
//black notes
    float xOffset = 0;
    
    for (int i=1; i<=10; i++){
        
        int keyWidth = (i==2||i==7)? 15.3:23.3;
        
        if (cursorInBoundingBox(50.5+xOffset, 50.5, keyWidth, 15.5)){
            currentNotePlaying = keyMap[keyNumber];
            sendNoteOn(currentNotePlaying, currentNotePlaying);
        }
        
        if (i==2||i==7){
            xOffset += 15.3;
        }else{
            xOffset += 23.3;
        }
        
        keyNumber++;   
    }
}

void OP1::drawScreen(){
    ofSetRectMode(OF_RECTMODE_CORNER);
    
    ofPushStyle();
    ofNoFill();
    ofSetLineWidth(2);
    ofSetColor(0x333333);
    roundedRect(getScreenWidth(), getScreenHeight(), 0.5);
    ofPopStyle();
    
	// draw the left:
    ofNoFill();
    ofBeginShape();
	ofSetColor(blue);
	for (int i = 0; i < 256; i++){
        float val = left[i]*20.0f;
        if (val>5){
            val = 5;
            ofSetColor(orange);
        }else if (val<-5){
            val = -5;
            ofSetColor(orange);
        }
		ofVertex(5+(float)i/5,10+val);
	}
    ofEndShape();
    
    ofSetColor(blue);
    ofBeginShape();
	for (int i = 0; i < 256; i++){
        float val = right[i]*20.0f;
        if (val>5){
            val = 5;
            ofSetColor(orange);
        }else if (val<-5){
            val = -5;
            ofSetColor(orange);
        }
        ofVertex(5+(float)i/5,20+val);
	}
    ofEndShape();
    
}

void OP1::audioReceived (float * input, int bufferSize, int nChannels){	
	// samples are "interleaved"
	for (int i = 0; i < bufferSize; i++){
		left[i] = input[i*2];
		right[i] = input[i*2+1];
	}
    
//    cout <<"audio recieved ["<<left[128]<<"]\n";
	
}




