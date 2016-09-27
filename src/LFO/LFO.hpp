//
//  LFO.hpp
//  lfo
//
//  Created by Vincent Evrard on 2016-08-02.
//
//

#ifndef LFO_hpp
#define LFO_hpp

#include "ofMain.h"
#include "LFOGui.hpp"

class ofxGui;
class ofxMasterSlaveControl;
class LFO {
    static int id;
    int _id;
    LFOGui * gui;
    
    public :
    LFO(ofxGuiGroup * group, ofxMasterSlaveControl * msc, ofParameter<int> * BPM){
        _id = id++;
        gui = new LFOGui(_id, group, msc, BPM);
    };
    void update();
    void exit()
    {
        gui->exit();
    }
};

#endif /* LFO_hpp */
