//
//  Oscillator.cpp
//  oogrev2
//
//  Created by Vincent Evrard on 2016-07-24.
//
//

#include "Oscillator.hpp"

int Oscillator::id = 1;

ofTexture * Oscillator::draw(ofFbo * modifier){
    ofColor color = gui.color.get();
    fbo.begin();
    ofClear(0, 0, 0, 255);
    shader.begin();
    shader.setUniform2f("u_resolution", fbo.getWidth(), fbo.getHeight());
    shader.setUniformTexture("modifier", modifier->getTexture(), 0);
    shader.setUniform4f("color", color.r / 255.0f,color.g / 255.0f, color.b / 255.0f, color.a / 255.0f);
    shader.setUniform1f("frequency",  100.0f / gui.frequency);
    shader.setUniform1f("sync", gui.sync);
    shader.setUniform1f("modIntensity", pow(gui.mod, 3));
    shader.setUniform1f("delta", gui.delta);
    shader.setUniform1f("exp", gui.exp);
    shader.setUniform1f("shape", ofMap(pow(gui.shape, 3), -1.0, 1.0, 0.0, 1.0 ));
    shader.setUniform1i("wave", gui.waveToggles->getActiveToggleIndex());
    shader.setUniform1i("reverse", gui.reverse);
    ofDrawRectangle(0, 0, fbo.getWidth(), fbo.getHeight());
    shader.end();
    fbo.end();

    fbo2.begin();
    ofClear(0, 0, 0, 255);
    shaderEffect.begin();
    shader.setUniform2f("u_resolution", fbo.getWidth(), fbo.getHeight());
    shaderEffect.setUniformTexture("source", fbo.getTexture(), 0);
    shaderEffect.setUniform2f("tile", 1 + 10 * pow(gui.Xtile, 3), 1 + 10 * pow(gui.Ytile, 3));
    shaderEffect.setUniform1f("rotation", gui.rotation);
    shaderEffect.setUniform2f("tileCenter", gui.tileXcenter, gui.tileYcenter);
    shaderEffect.setUniform1f("mainRotation", gui.mainRotation);
    shaderEffect.setUniform1f("postRotation", gui.postRotation);
    shaderEffect.setUniform2f("rotCenter", gui.rotXcenter, gui.rotYcenter);
    ofDrawRectangle(0, 0, fbo.getWidth(), fbo.getHeight());
    shaderEffect.end();
    fbo2.end();
    
    return &fbo2.getTexture();
}