#version 150
#define AUTO 0

#ifdef GL_ES
    precision mediump float;
#endif
#define PI 3.14159265359
#define TWO_PI 6.283185306

uniform vec2 u_resolution;

out vec4 outputColor;

uniform sampler2DRect source;
uniform vec2 tile, rotCenter, tileCenter;
uniform float rotation, mainRotation, postRotation;


vec2 n_fragCoord;

float map(in float x, in float in_min, in float in_max, in float out_min, in float out_max)
{
    return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

vec2 rotate2D(vec2 _st, float _angle){
    _st -= rotCenter;
    _st =  mat2(cos(_angle), -sin(_angle),
                sin(_angle),  cos(_angle) ) * _st;
    _st += rotCenter;
    return _st;
}


vec2 mirrorTilePattern(vec2 _st){

    //  Scale the coordinate system by tile 
    _st -= tileCenter;
    _st *= tile;
    _st += tileCenter;

    //  Give each cell an index number
    //  according to its position
    float index = 0.0;    
    index += step(1., mod(_st.x,2.0));
    index += step(1., mod(_st.y,2.0))*2.0;
    
    //      |
    //  0   |   1
    //      |
    //--------------
    //      |
    //  2   |   3
    //      |

    _st = fract(_st);
    
    if(index == 1.0)
    {
        _st = rotate2D(_st, rotation * PI/2);
        //_st = vec2(map(_st.x, 0.5, 1.0, 0.0, 1.0), map(_st.y, 0.5, 1.0, 0.0, 1.0));
    } else if(index == 2.0)
    {
        _st = rotate2D(_st, rotation * -PI/2.0);
        //_st = vec2(map(_st.x, 0.0, 1.0/tile.x, 1.0, 0.0), map(_st.y, 0.0, 1.0/tile.y, 1.0, 0.0));
    } else if(index == 3.0)
    {
        _st = rotate2D(_st, rotation * PI);
        //_st = vec2(map(_st.x, 0.5, 1.0, 0.0, 1.0), map(_st.y, 0.0, 0.5, 1.0, 0.0));
    } else if(index == 0.0)
    {
       // _st = vec2(map(_st.x, 0.0, 0.5, 1.0, 0.0), map(_st.y, 0.5, 1.0, 0.0, 1.0));
    }
    
    return _st;
}


void main()
{
    n_fragCoord = gl_FragCoord.xy / u_resolution;
    n_fragCoord = rotate2D(n_fragCoord, postRotation * TWO_PI);
    n_fragCoord = mirrorTilePattern(n_fragCoord);
    n_fragCoord = rotate2D(n_fragCoord, mainRotation * TWO_PI);
    outputColor = texture(source, n_fragCoord * u_resolution);
}








