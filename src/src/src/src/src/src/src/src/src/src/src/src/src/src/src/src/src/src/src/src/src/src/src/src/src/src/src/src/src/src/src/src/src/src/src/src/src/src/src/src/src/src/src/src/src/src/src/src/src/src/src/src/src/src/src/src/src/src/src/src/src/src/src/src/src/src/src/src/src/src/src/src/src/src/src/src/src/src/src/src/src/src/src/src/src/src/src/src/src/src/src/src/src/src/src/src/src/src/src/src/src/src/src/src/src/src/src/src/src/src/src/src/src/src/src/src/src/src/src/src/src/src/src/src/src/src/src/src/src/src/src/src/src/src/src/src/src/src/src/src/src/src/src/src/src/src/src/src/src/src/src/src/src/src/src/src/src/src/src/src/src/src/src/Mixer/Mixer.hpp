//
//  Mixer.hpp
//  oogrev2
//
//  Created by Vincent Evrard on 2016-07-26.
//
//

#ifndef Mixer_hpp
#define Mixer_hpp

#include "ofMain.h"
#include "MixerGui.hpp"

class ofxGui;
class ofxMasterSlaveControl;

class Mixer {
    ofShader shader;
    MixerGui gui;
     ofFbo fbo, mainOut;
    public :
    friend class ofApp;
    
    Mixer(ofxGuiGroup * _mixerGroup, int oscillatorLen, ofxMasterSlaveControl * msc, ofPoint size){
        if(ofIsGLProgrammableRenderer()){
            shader.load("shadersGL3/mixer");
        }
        
        fbo.allocate(size.x, size.y);
        fbo.begin();
        ofClear(0, 0, 0, 255);
        fbo.end();
        mainOut.allocate(size.x, size.y);
        mainOut.begin();
        ofClear(0, 0, 0, 255);
        mainOut.end();

        gui.setup(_mixerGroup, oscillatorLen, msc, &fbo.getTexture());
    }
    void setWidth(int value){
        fbo.allocate(value, fbo.getHeight());
        fbo.begin();
        ofClear(0, 0, 0, 255);
        fbo.end();
        mainOut.allocate(value, fbo.getHeight());
        mainOut.begin();
        ofClear(0, 0, 0, 255);
        mainOut.end();
    };
    void setHeight(int value){
        fbo.allocate(value, fbo.getHeight());
        fbo.begin();
        ofClear(0, 0, 0, 255);
        fbo.end();
        mainOut.allocate(value, fbo.getHeight());
        mainOut.begin();
        ofClear(0, 0, 0, 255);
        mainOut.end();
    };

    void update();
    
    void setPreview(vector <ofTexture * >oscOut){
        gui.setPreview(oscOut);
    };
    
    void addChannel(){
        gui.addChannel();
    }
};

#endif /* Mixer_hpp */
