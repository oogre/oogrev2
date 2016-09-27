//
//  OscilatorGui.hpp
//  oogrev2
//
//  Created by Vincent Evrard on 2016-07-25.
//
//

#ifndef OscilatorGui_hpp
#define OscilatorGui_hpp


#include "ofMain.h"
#include "ofxGuiExtended.h"
#include "ofxMasterSlaveControl.h"
//class Oscillator;


class OscilatorGui {
    static int id;
    ofColor defaultBgColor;
    ofxGuiGroup * group;
    ofxGuiGraphics* graphics;
    
    ofParameter<ofColor> color = ofColor(0, 0, 0, 0);
    
    vector <ofxGuiElement * > colors;
    
    ofParameter<int> red;
    ofParameter<int> green;
    ofParameter<int> blue;
    ofParameter<int> alpha;
    
    ofParameter<float> frequency;
    ofParameter<float> sync;
    
    ofParameter<float> delta;
    ofParameter<float> mod;
    
    ofParameter<float> exp;
    ofParameter<float> shape;
    ofParameter<bool> reverse;
    ofxGuiContainer* waveToggles;
    ofParameter<bool> sinwaveSquare;
    ofParameter<bool> sawSawn;
    
    ofParameter<float> tile;
    ofParameter<float> Xtile;
    ofParameter<float> Ytile;
    ofParameter<float> rotation;
    ofParameter<float> tileXcenter;
    ofParameter<float> tileYcenter;
    
    
    ofParameter<float> mainRotation;
    ofParameter<float> postRotation;
    ofParameter<float> rotXcenter;
    ofParameter<float> rotYcenter;


    int _id;
public:
    friend class Oscillator;
    friend class ofApp;
    
    void tileChanged(float &value)
    {
        Xtile = Ytile = value;
    }
   
    void updateRed(int & value){
        updateColor(ofColor(value, green, blue, alpha));
    };
    void updateGreen(int & value){
        updateColor(ofColor(red, value, blue, alpha));
    };
    void updateBlue(int & value){
        updateColor(ofColor(red, green, value, alpha));
    };
    void updateAlpha(int & value){
        updateColor(ofColor(red, green, blue, value));
    };
    void updateColor(ofColor color){
        for(unsigned i = 0 ; i < colors.size() ; i ++){
            colors.at(i)->setFillColor(color);
        }
        this->color = color;
    };

    void setup(ofxGuiGroup * oscillatorGroup, ofTexture * tex, ofxMasterSlaveControl * msc);
};


#endif /* OscilatorGui_hpp */
