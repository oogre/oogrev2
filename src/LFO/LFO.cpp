//
//  LFO.cpp
//  lfo
//
//  Created by Vincent Evrard on 2016-08-02.
//
//

#include "LFO.hpp"
int LFO::id = 1;


void LFO::update()
{
    //float multiplier = (float)gui.multi / (float)gui.divider;
    float value;
        
    if(gui->active)
    {
        // delay + SEC * (BEAT/MIN) * 1 / 60
        value = (gui->delay/10.0f) + (ofGetElapsedTimef() * (*gui->BPM)  * 0.0166667f);
        value *= gui->clockRate;
        value = value - (long) value;
        
        float exp = 1.0f;
        if(gui->exp >= 5){
            exp = 1.0f / (gui->exp - 4.0f);
        }else{
            exp = abs(6.0f - gui->exp);
        }
        value = pow(value, exp);
        gui->value = MIN(MAX(gui->reverse ? 1.0f - value : value, gui->min.get()/10.0f), gui->max.get()/10.0f) ;
        gui->sineValue = (gui->reverse ? - 1 : 1) * cos(gui->value * TWO_PI);

        
        
        gui->squareValue = (gui->step/10.0f) < gui->value ? gui->max.get()/10.0f : gui->min.get()/10.0f;
    }
}