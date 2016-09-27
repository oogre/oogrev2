//
//  MixerGui.cpp
//  oogrev2
//
//  Created by Vincent Evrard on 2016-07-29.
//
//

#include "MixerGui.hpp"


void MixerGui::setup(ofxGuiGroup * _mixerGroup, int oscillatorLen, ofxMasterSlaveControl * msc, ofTexture * output){

    this->msc = msc;
    
    
    ofxGuiGroup* wrapper = _mixerGroup->addGroup("", ofJson({
        {"show-header", false},
        {"background-color" , "transparent"}
    }));
    group = wrapper->addGroup("", ofJson({
        {"show-header", false},
        {"flex-direction", "column"},
        {"flex-wrap", "wrap"},
        {"background-color" , "transparent"}
    }));
    
    
    ofxGuiGroup* mixerGroup = group->addGroup("Channel All", ofJson({
        {"show-header", false},
        {"background-color" , "transparent"},
        {"width", 100}
    }));
    graphics.push_back(mixerGroup->add<ofxGuiGraphics>("All", output, ofJson({
        {"width", 100}
    })));
    graphics.back()->setAutoHeight();
    
    
    ofParameter<float> * lvl = new ofParameter<float>();
    lvl->set("lvl output", 1, 0,  1);
    lvls.push_back(lvl);
    msc->addSlave(mixerGroup->add(*lvl, ofJson({
        {"precision", 2}
    })));
    
    ofParameter<bool> * nega = new ofParameter<bool>();
    nega->set("nega", false), ofJson({{"width", 30}, {"height", 30}});
    negas.push_back(nega);
    msc->addSlave(mixerGroup->add(*nega));

    
    ofParameter<float> * circ = new ofParameter<float>();
    circ->set("circ output", 1, 0,  1);
    circs.push_back(circ);
    msc->addSlave(mixerGroup->add(*circ, ofJson({
        {"precision", 2}
    })));
    
    
    for(int i = 0 ; i < oscillatorLen ; i ++){
        addChannel();
    }
}


void MixerGui::addChannel(){
    ofxGuiGroup* mixerGroup = group->addGroup("Channel "+ofToString(graphics.size()), ofJson({
        {"show-header", false},
        {"background-color" , "transparent"},
        {"width", 100}
    }));
    
    graphics.insert(graphics.end()-1, mixerGroup->add<ofxGuiGraphics>("Oscillator "+ofToString(graphics.size()), ofJson({
        {"width", 100}
    })));

    ofParameter<float> * lvl = new ofParameter<float>();
    lvl->set("lvl "+ofToString(lvls.size()), 0, 0,  1);
    lvls.insert(lvls.end()-1, lvl);
    msc->addSlave(mixerGroup->add(*lvl, ofJson({
        {"precision", 2}
    })));
    
    ofParameter<bool> * nega = new ofParameter<bool>();
    nega->set("nega"+ofToString(negas.size()), false), ofJson({{"width", 30}, {"height", 30}});
    negas.insert(negas.end()-1, nega);
    msc->addSlave(mixerGroup->add(*nega));
    
    ofParameter<float> * circ = new ofParameter<float>();
    circ->set("circ "+ofToString(circs.size()), 0, 0,  1);
    circs.insert(circs.end()-1, circ);
    msc->addSlave(mixerGroup->add(*circ, ofJson({
        {"precision", 2}
    })));
}