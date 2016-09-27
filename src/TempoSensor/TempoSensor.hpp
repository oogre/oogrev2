//
//  TempoSensor.hpp
//  oogrev2
//
//  Created by Vincent Evrard on 2016-07-28.
//
//

#ifndef TempoSensor_hpp
#define TempoSensor_hpp

#include "ofMain.h"
#include "ofxMidi.h"

enum class Action {
    BPM_TAPPING = 44,
    BPM_RESET = 45
};


class TempoSensor : public ofxMidiListener {
    ofxMidiIn midiIn;
    float deltaTime [2] = {0.0f, 0.0f} ;

    float totalTime = 0.0f;
    int tapCmpt = 0;
public:
    float tempo = 0.0f;
    TempoSensor(){
        midiIn.listPorts(); // via instance
        midiIn.openPort(2);
        midiIn.addListener(this);
        midiIn.setVerbose(false);
    };
    ~TempoSensor(){
        midiIn.closePort();
        midiIn.removeListener(this);
    };
    void reset();
    void beat(float time);
    float getTempo();
    void newMidiMessage(ofxMidiMessage& eventArgs);
};


#endif /* TempoSensor_hpp */
