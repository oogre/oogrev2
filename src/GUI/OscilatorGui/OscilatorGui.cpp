//
//  OscilatorGui.cpp
//  oogrev2
//
//  Created by Vincent Evrard on 2016-07-25.
//
//

#include "OscilatorGui.hpp"

int OscilatorGui::id = 1;



void OscilatorGui::setup(ofxGuiGroup * oscillatorGroup, ofTexture * tex, ofxMasterSlaveControl * msc){
    _id = id++;
    ofxGuiGroup* wrapper = oscillatorGroup->addGroup("", ofJson({
        {"show-header", false},
    }));
    group = wrapper->addGroup(ofToString(_id));
    defaultBgColor = ofColor(group->getBackgroundColor());    if(id>=2){
        group->setShape((oscillatorGroup->children().back()->getShape().getTopRight() + ofPoint(20, 0)).x,
                        (oscillatorGroup->children().back()->getShape().getTopRight() + ofPoint(20, 0)).y,
                        200, 200);
    }
    
    ofxGuiGroup* groupColor = group->addGroup("Color"+ofToString(_id), ofJson({
        {"show-header", false},
    }));
    colors.push_back(groupColor->add(red.set("r"+ofToString(_id), 0, 0, 255)));
    msc->addSlave(colors.back());
    red.addListener(this, &OscilatorGui::updateRed);
    colors.push_back(groupColor->add(green.set("g"+ofToString(_id), 0, 0, 255)));
    msc->addSlave(colors.back());
    green.addListener(this, &OscilatorGui::updateGreen);
    colors.push_back(groupColor->add(blue.set("b"+ofToString(_id), 0, 0, 255)));
    msc->addSlave(colors.back());
    blue.addListener(this, &OscilatorGui::updateBlue);
    colors.push_back(groupColor->add(alpha.set("a"+ofToString(_id), 0, 0, 255)));
    msc->addSlave(colors.back());
    alpha.addListener(this, &OscilatorGui::updateAlpha);
    
    
    ofxGuiGroup* groupOsc = group->addGroup("Oscillator_"+ofToString(_id), ofJson({
        {"show-header", false},
    }));
    groupOsc->add<ofxGuiLabel>("Oscillator", ofToString(_id));
    msc->addSlave(groupOsc->add(frequency.set("Hz"+ofToString(_id), 60.0f, 0.125f, 600.0f)));
    msc->addSlave(groupOsc->add(sync.set("Sync"+ofToString(_id), 0.0f,0.0f, 1.0f)));
    
    ofxGuiGroup* groupShape = group->addGroup("Shape"+ofToString(_id), ofJson({
        {"show-header", false},
    }));
    groupShape->add<ofxGuiLabel>("Shape", ofToString(_id));
    msc->addSlave(groupShape->add(exp.set("exp"+ofToString(_id), 1.0f,0.064f, 1.0f)));
    msc->addSlave(groupShape->add(shape.set("shape"+ofToString(_id), 0.0f,-1.0f, 1.0f)));
    waveToggles = groupShape->addContainer();
    waveToggles->setShowName(false);
    msc->addSlave(waveToggles->add(sinwaveSquare.set("sine/square"+ofToString(_id), true)));
    msc->addSlave(waveToggles->add(sawSawn.set("saw/sawn"+ofToString(_id), false)));
    waveToggles->setExclusiveToggles(true);
    waveToggles->setConfig(ofJson({{"type", "radio"}}));
    waveToggles->setActiveToggle(0);
    msc->addSlave(groupShape->add(reverse.set("reverse"+ofToString(_id), false), ofJson({{"width", 30}, {"height", 30}})));
    
    
    ofxGuiGroup* groupModer  = group->addGroup("Moders"+ofToString(_id), ofJson({
        {"show-header", false},
    }));
    groupModer->add<ofxGuiLabel>("Moders", ofToString(_id));
    msc->addSlave(groupModer->add(delta.set("delta"+ofToString(_id), 0.0f,0.0f, 1.0f)));
    msc->addSlave(groupModer->add(mod.set("mod"+ofToString(_id), 0.0f,-1.0f, 1.0f)));
    
    ofxGuiGroup* groupTile = group->addGroup("Tiles"+ofToString(_id), ofJson({
        
    }));
    groupTile->add<ofxGuiLabel>("Tiles", ofToString(_id));
    msc->addSlave(groupTile->add(tile.set("tile"+ofToString(_id), 0.0f, 0.0f, 1.0f)));
    tile.addListener(this, &OscilatorGui::tileChanged);
    msc->addSlave(groupTile->add(Xtile.set("X-Tile"+ofToString(_id), 0.0f, 0.0f, 1.0f)));
    msc->addSlave(groupTile->add(Ytile.set("Y-Tile"+ofToString(_id), 0.0f, 0.0f, 1.0f)));
    msc->addSlave(groupTile->add(rotation.set("tile-Rotation"+ofToString(_id), 0.0f, 0.0f, 1.0f)));
    msc->addSlave(groupTile->add(tileXcenter.set("tileXcenter"+ofToString(_id), 0.5f, 0.0f, 1.0f)));
    msc->addSlave(groupTile->add(tileYcenter.set("tileYcenter"+ofToString(_id), 0.5f, 0.0f, 1.0f)));
    
    ofxGuiGroup* groupRotation = group->addGroup("Rotations"+ofToString(_id), ofJson({
        {"show-header", false},
    }));
    groupRotation->add<ofxGuiLabel>("Rotations", ofToString(_id));
    msc->addSlave(groupRotation->add(mainRotation.set("pre-Rotation"+ofToString(_id), 0.0f, 0.0f, 1.0f)));
    msc->addSlave(groupRotation->add(postRotation.set("post-Rotation"+ofToString(_id), 0.0f, 0.0f, 1.0f)));
    msc->addSlave(groupRotation->add(rotXcenter.set("rotXcenter"+ofToString(_id), 0.5f, 0.0f, 1.0f)));
    msc->addSlave(groupRotation->add(rotYcenter.set("rotYcenter"+ofToString(_id), 0.5f, 0.0f, 1.0f)));
    
    
    
    ofxGuiGraphics* graphics = wrapper->add<ofxGuiGraphics>("some texture"+ofToString(_id), tex);
    graphics->setAutoHeight();
}
