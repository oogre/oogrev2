//
//  MixerGui.hpp
//  oogrev2
//
//  Created by Vincent Evrard on 2016-07-29.
//
//

#ifndef MixerGui_hpp
#define MixerGui_hpp

#include "ofMain.h"
#include "ofxGuiExtended.h"
#include "ofxMasterSlaveControl.h"
//class Oscillator;


class MixerGui {
    vector <ofParameter<float> *> lvls;
    vector <ofParameter<bool> *> negas;
    vector <ofParameter<float> *> circs;


    vector <ofxGuiGraphics*> graphics;
    vector <ofTexture*> textures;
    ofxGuiGroup * group;
    ofxMasterSlaveControl * msc;
    
public:
    friend class Mixer;
    friend class ofApp;
    void addChannel();
    void setup(ofxGuiGroup * _mixerGroup, int oscillatorLen, ofxMasterSlaveControl * msc, ofTexture * output);
    
    void setPreview(vector <ofTexture * >oscOut){
        textures = oscOut;
        for(int i = 0 ; i < graphics.size()-1; i ++)
        {
            if(i < textures.size())
            {
                graphics.at(i)->setBload(true);
                graphics.at(i)->setGraphics(textures.at(i));
                graphics.at(i)->setAutoHeight();
            }
            else
            {
                graphics.at(i)->setBload(false);
            }
        }
        
    };
};


#endif /* MixerGui_hpp */
