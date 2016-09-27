//
//  LFOGui.cpp
//  lfo
//
//  Created by Vincent Evrard on 2016-08-02.
//
//

#include "LFOGui.hpp"

string ofColorToRGBA(ofColor * color){
    return "rgba("+
                ofToString((int)color->r) + ", "+
                ofToString((int)color->g) + ", "+
                ofToString((int)color->b) + ", "+
                ofToString(((float)color->a)/255.0f) +
            ")";
}

LFOGui::LFOGui(int id, ofxGuiGroup * group, ofxMasterSlaveControl * msc, ofParameter<int> * BPM)
{
    this->_id = ofToString(id);
    this->BPM = BPM;
    lfoGroup = group->addGroup("LFO_"+_id, ofJson({
        {"show-header", false},
        {"flex-wrap", "wrap"},
        {"flex-direction", "row"}
    }));
    
    lfoGroup->add<ofxGuiLabel>("LFO", _id);
    
    //  START BTN GROUP
    ofxGuiGroup * btnGroup = lfoGroup->addGroup("buttons "+_id, ofJson({
        {"show-header", false},
        {"flex-wrap", "wrap"},
        {"flex-direction", "column"},
        {"background-color" , "transparent"},
        {"width", 130},
    }));
    active.addListener(this, &LFOGui::activeEvent);
    msc->addSlave(btnGroup->add(active.set("On", true), ofJson({
        {"width", 30},
        {"height", 30}
    })));
    reverse.addListener(this, &LFOGui::reverseEvent);
    msc->addSlave(btnGroup->add(reverse.set("->", false), ofJson({
        {"width", 30},
        {"height", 30}
    })));
    //  END BTN GROUP
    
    msc->addSlave(lfoGroup->add<ofxGuiSlider<int>>(delay.set("delay", 0, 0, 10), ofJson({
        {"precision", 2},
        {"width", 130},
    })));

    lfoGroup->add(clock_rate.set("clock", ofToString(clck_multi)+"/"+ofToString(clck_divid)));
    msc->addSlave(lfoGroup->add<ofxGuiSlider<int>>(clck_multi.set("multor", 1, 1, 20), ofJson({
        {"precision", 2},
        {"width", 130},
    })));
    msc->addSlave(lfoGroup->add<ofxGuiSlider<int>>(clck_divid.set("dividor", 1, 1, 20), ofJson({
        {"precision", 2},
        {"width", 130},
    })));
    clck_multi.addListener(this, &LFOGui::clockChangeEvent);
    clck_divid.addListener(this, &LFOGui::clockChangeEvent);
    
    
    
    msc->addSlave(lfoGroup->add<ofxGuiSlider<int>>(exp.set("exp", 5, 1, 9), ofJson({
        {"precision", 2},
        {"width", 130},
    })));
    
    msc->addSlave(lfoGroup->add<ofxGuiSlider<int>>(min.set("min", 0, 0, 10), ofJson({
        {"precision", 2},
        {"width", 130},
    })));
    msc->addSlave(lfoGroup->add<ofxGuiSlider<int>>(max.set("max", 10, 0, 10), ofJson({
        {"precision", 2},
        {"width", 130},
    })));
    ofxGuiElement* control;
    
    msc->addMaster(lfoGroup->add<ofxGuiSlider<float>>(value.set("value", 0, 0, 1), ofJson({
        {"precision", 2},
        {"width", 130},
        {"fill-color", ofColorToRGBA(&colors[6 * id])}
    })));
    
    //cout << Config::colors[0][0] << endl;
    
    msc->addMaster(lfoGroup->add<ofxGuiSlider<float>>(sineValue.set("sine", 0, -1, 1), ofJson({
        {"precision", 2},
        {"width", 130},
        {"fill-color", ofColorToRGBA(&colors[6 * id+1])}
    })));
    
    msc->addSlave(lfoGroup->add<ofxGuiSlider<int>>(step.set("step", 5, 0, 10), ofJson({
        {"precision", 2},
        {"width", 130}
    })));
    
    msc->addMaster(lfoGroup->add<ofxGuiSlider<float>>(squareValue.set("square", 0, 0, 1), ofJson({
        {"precision", 2},
        {"width", 130},
        {"fill-color", ofColorToRGBA(&colors[6 * id+2])}
    })));
};
