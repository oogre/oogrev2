//
//  LFOGui.hpp
//  lfo
//
//  Created by Vincent Evrard on 2016-08-02.
//
//

#ifndef LFOGui_hpp
#define LFOGui_hpp

#include "ofMain.h"
#include "ofxGuiExtended.h"
#include "ofxMasterSlaveControl.h"



class LFOGui {
    friend class LFO;
    ofColor colors [42] =
    {
            ofColor::navy,
            ofColor::mediumBlue,
            ofColor::blue,
            ofColor::royalBlue,
            ofColor::dodgerBlue,
            ofColor::deepSkyBlue,
            
            ofColor::indigo,
            ofColor::darkSlateBlue,
            ofColor::mediumPurple,
            ofColor::purple,
            ofColor::darkViolet,
            ofColor::mediumOrchid,
            
            ofColor::darkRed,
            ofColor::fireBrick,
            ofColor::red,
            ofColor::crimson,
            ofColor::indianRed,
            ofColor::lightCoral,
            
            ofColor::orangeRed,
            ofColor::tomato,
            ofColor::coral,
            ofColor::darkorange,
            ofColor::orange,
            ofColor::gold,
            
            ofColor::teal,
            ofColor::lightSeaGreen,
            ofColor::mediumAquaMarine,
            ofColor::darkSeaGreen,
            ofColor::darkOliveGreen,
            ofColor::oliveDrab,
            
            ofColor::springGreen,
            ofColor::lightGreen,
            ofColor::paleGreen,
            ofColor::limeGreen,
            ofColor::lime,
            ofColor::greenYellow,
            
            ofColor::mediumVioletRed,
            ofColor::paleVioletRed,
            ofColor::deepPink,
            ofColor::hotPink,
            ofColor::lightPink,
            ofColor::pink
    };
    string _id;
    ofxGuiGroup * lfoGroup;
    float clockRate = 1.0f;
    
    ofParameter<int> *BPM;
    
    ofParameter<bool> active;
    ofParameter<bool> reverse;
    ofParameter<int> delay;
    
    ofParameter<string> clock_rate;
    ofParameter<int> clck_multi = 1;
    ofParameter<int> clck_divid = 1;
    ofParameter<int> exp;
    ofParameter<int> min, max;
    ofParameter<float> value;
    ofParameter<float> sineValue;
    ofParameter<int> step;
    ofParameter<float> squareValue;
    
    void activeEvent(bool &value)
    {
        active.setName(value?"On":"Off");
    };
    void reverseEvent(bool &value)
    {
        reverse.setName(value?"<-":"->");
    };
    void clockChangeEvent(int & value){
        clockRate = (float)clck_multi / (float)clck_divid;
        clock_rate = ofToString(clck_multi)+"/"+ofToString(clck_divid);
    }
    void resetEvent(){
    
        cout << "CLICK" << endl;
    }
    public :

    LFOGui(int id, ofxGuiGroup * group, ofxMasterSlaveControl * msc, ofParameter<int> * BPM);;
    
        void exit(){
            active.removeListener(this, &LFOGui::activeEvent);
            reverse.removeListener(this, &LFOGui::reverseEvent);   
        }
};


#endif /* LFOGui_hpp */

/*

ofParameter<int> *BPM;

ofParameter<bool> active;
ofParameter<float> delta;
ofParameter<bool> reverse;
ofParameter<float> valueMin, valueMax;
ofParameter<float> value;
ofParameter<float> minMap, maxMap;
ofParameter<float> mapedValue;
ofParameter<int> multi;
ofParameter<int> divider;
ofParameter<float> dividedValue;
ofParameter<float> min, max, step;
ofParameter<float> shapedValue;
ofParameter<float> sinedValue;
ofParameter<float> squaredValue;
*/