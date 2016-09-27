//
//  Oscillator.hpp
//  oogrev2
//
//  Created by Vincent Evrard on 2016-07-24.
//
//

#ifndef Oscillator_hpp
#define Oscillator_hpp

#include "ofMain.h"
#include "OscilatorGui.hpp"


class ofxGui;
class ofxMasterSlaveControl;
class Oscillator {
    static int id;
    int _id;
    ofShader shader, shaderEffect;
    ofFbo fbo, fbo2;
    OscilatorGui gui;
    public:
        friend class ofApp;
        ofTexture * draw(ofFbo * modifier);
        void setWidth(int value){
            fbo.allocate(value, fbo.getHeight());
            fbo.begin();
            ofClear(0, 0, 0, 255);
            fbo.end();
            fbo2.allocate(value, fbo.getHeight());
            fbo2.begin();
            ofClear(0, 0, 0, 255);
            fbo2.end();
        };
        void setHeight(int value){
            fbo.allocate(fbo.getWidth(), value);
            fbo.begin();
            ofClear(0, 0, 0, 255);
            fbo.end();
            fbo2.allocate(fbo.getWidth(), value);
            fbo2.begin();
            ofClear(0, 0, 0, 255);
            fbo2.end();
        };
        ofFbo * getModifier (){
            return &fbo2;
        };
        Oscillator(ofxGuiGroup * _oscillatorGroup, ofPoint size, ofxMasterSlaveControl * msc)
        {
            _id = id++;
            if(ofIsGLProgrammableRenderer()){
                shader.load("shadersGL3/oscillator");
                shaderEffect.load("shadersGL3/effects");
            }
            fbo.allocate(size.x, size.y);
            fbo.begin();
            ofClear(0, 0, 0, 255);
            fbo.end();
            fbo2.allocate(size.x, size.y);
            fbo2.begin();
            ofClear(0, 0, 0, 255);
            fbo2.end();
            
            gui.setup(_oscillatorGroup, &fbo2.getTexture(), msc);
           
        }
};


#endif /* Oscillator_hpp */
