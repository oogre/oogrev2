//
//  OutputWindow.hpp
//  oogrev2
//
//  Created by Vincent Evrard on 2016-07-24.
//
//

#ifndef OutputWindow_hpp
#define OutputWindow_hpp

#include "ofMain.h"

class OutputWindow : public ofBaseApp
{
    static int id;
    ofFbo * fbo;
    string title;
    public :
        shared_ptr<ofAppBaseWindow> window_ptr;

        void init(
                  shared_ptr<ofAppBaseWindow> mainWindow,
                  ofFbo * fbo
                  );
        void draw();

        OutputWindow(){
            title = "Output : " + ofToString(id);
            cout << "START : " << title << endl;
            id++;
        };
        ~OutputWindow()
        {
            cout << "STOP : " << title << endl;
            window_ptr = NULL;
        };
};

#endif /* OutputWindow_hpp */
