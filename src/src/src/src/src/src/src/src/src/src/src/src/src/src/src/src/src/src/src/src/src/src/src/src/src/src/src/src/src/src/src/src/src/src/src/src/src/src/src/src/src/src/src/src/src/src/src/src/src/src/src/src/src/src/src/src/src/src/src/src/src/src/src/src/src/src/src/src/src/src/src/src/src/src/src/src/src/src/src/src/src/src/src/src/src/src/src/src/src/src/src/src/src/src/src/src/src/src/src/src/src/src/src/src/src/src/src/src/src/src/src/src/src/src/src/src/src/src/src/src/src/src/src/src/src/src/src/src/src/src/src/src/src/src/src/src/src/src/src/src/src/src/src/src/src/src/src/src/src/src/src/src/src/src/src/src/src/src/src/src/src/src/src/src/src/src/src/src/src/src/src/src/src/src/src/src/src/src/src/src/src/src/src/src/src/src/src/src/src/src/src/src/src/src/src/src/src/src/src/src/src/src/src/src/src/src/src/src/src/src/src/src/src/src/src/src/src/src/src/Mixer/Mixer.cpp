//
//  Mixer.cpp
//  oogrev2
//
//  Created by Vincent Evrard on 2016-07-26.
//
//

#include "Mixer.hpp"

void Mixer::update()
{
    fbo.begin();
    ofClear(0, 0, 0, 255);
    shader.begin();
    shader.setUniform2f("u_resolution", fbo.getWidth(), fbo.getHeight());
    shader.setUniform1i("channelLen", gui.textures.size());
    for(unsigned i = 0 ; i < gui.textures.size() ; i ++){
        shader.setUniform1f("circleSize"+ofToString(i), 4.0f);
        shader.setUniform1f("lvl"+ofToString(i), 1.0f);
        shader.setUniformTexture("channel"+ofToString(i), *gui.textures.at(i), i);
    }
    ofDrawRectangle(0, 0, ofGetWidth(), ofGetHeight());
    shader.end();
    fbo.end();
    gui.textures.push_back(&fbo.getTexture());
    
    mainOut.begin();
    ofClear(0, 0, 0, 255);
    shader.begin();
    shader.setUniform2f("u_resolution", fbo.getWidth(), fbo.getHeight());
    shader.setUniform1i("channelLen", gui.textures.size());
    for(unsigned i = 0 ; i < gui.textures.size() ; i ++){
        shader.setUniform1f("circleSize"+ofToString(i), 4.0f * pow(*gui.circs.at(i), 3));
        shader.setUniform1f("lvl"+ofToString(i), ((*gui.negas.at(i))?-1 : 1) * (*gui.lvls.at(i)));
        shader.setUniformTexture("channel"+ofToString(i), *gui.textures.at(i), i);
    }
    ofDrawRectangle(0, 0, ofGetWidth(), ofGetHeight());
    shader.end();
    mainOut.end();
    
    
}

