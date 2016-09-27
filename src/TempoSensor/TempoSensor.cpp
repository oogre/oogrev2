//
//  TempoSensor.cpp
//  oogrev2
//
//  Created by Vincent Evrard on 2016-07-28.
//
//

#include "TempoSensor.hpp"


void TempoSensor::newMidiMessage(ofxMidiMessage& msg)
{
    if(msg.status == MidiStatus::MIDI_NOTE_ON){
        switch(msg.pitch){
            case (int)Action::BPM_RESET:
                reset();
                break;
            case (int)Action::BPM_TAPPING :
                beat(ofGetElapsedTimef());
                /*
                 cout << "time : "     << ofGetElapsedTimef() <<
                 endl << "velocity : " << msg.velocity <<
                 endl;
                /**/
                break;
        }
    }
    /*
     cout << "time : "     << ofGetElapsedTimef() <<
     endl << "pitch : "    << msg.pitch <<
     endl << "velocity : " << msg.velocity <<
     endl << "status : "   << msg.getStatusString(msg.status) <<
     endl;
     /**/
}


void TempoSensor::beat(float time){
    deltaTime[1] = time;
    if(deltaTime[0] != 0.0f){
        totalTime += deltaTime[1] - deltaTime[0];
        tapCmpt ++;
        deltaTime[0] = deltaTime[1];
    }
    else
    {
        deltaTime[0] = deltaTime[1];
        return;
    }
    tempo = 60.0 / (totalTime/tapCmpt);
    cout << tempo << endl;
}
float TempoSensor::getTempo(){
    return tempo;
}

void TempoSensor::reset(){
    deltaTime[0] = deltaTime[1] = 0.0f;
    totalTime = 0;
    tapCmpt = 0 ;
    cout << "reset" << endl;
}
