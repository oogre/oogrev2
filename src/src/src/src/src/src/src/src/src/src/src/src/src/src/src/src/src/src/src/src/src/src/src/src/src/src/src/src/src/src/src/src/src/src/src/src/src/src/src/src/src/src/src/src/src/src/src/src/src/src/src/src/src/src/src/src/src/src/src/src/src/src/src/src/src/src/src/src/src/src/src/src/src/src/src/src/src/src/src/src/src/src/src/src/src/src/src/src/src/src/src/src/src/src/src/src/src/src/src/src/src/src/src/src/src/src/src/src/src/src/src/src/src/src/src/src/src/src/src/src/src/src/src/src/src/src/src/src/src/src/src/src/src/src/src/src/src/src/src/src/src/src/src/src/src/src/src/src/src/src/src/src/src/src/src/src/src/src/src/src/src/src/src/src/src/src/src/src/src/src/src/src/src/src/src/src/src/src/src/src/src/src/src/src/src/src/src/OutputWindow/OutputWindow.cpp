//
//  OutputWindow.cpp
//  oogrev2
//
//  Created by Vincent Evrard on 2016-07-24.
//
//

#include "OutputWindow.hpp"
int OutputWindow::id = 1;

void OutputWindow::init(
                       shared_ptr<ofAppBaseWindow> mainWindow,
                       ofFbo * fbo
                       )
{
    this->fbo = fbo;
    ofGLFWWindowSettings settings;
    settings.setGLVersion(3,2);
    settings.width = 800;
    settings.height = 600;
    settings.setPosition(ofVec2f(ofGetScreenWidth()-settings.width,ofGetScreenHeight()-settings.height));
    settings.title = title;
    settings.shareContextWith = mainWindow;
    window_ptr = ofCreateWindow(settings);
}

void OutputWindow::draw()
{
    fbo->draw(0, 0, window_ptr->getWidth(), window_ptr->getHeight());
}