#version 150
#define DEBUG 0
#ifdef GL_ES
    precision mediump float;
#endif

#define PI 3.14159265359
#define TWO_PI 6.283185306

#define WAVE_SINE_SQUARE 0
#define WAVE_SAW 1
#define ANTIALIAZING 0.02

uniform vec2 u_resolution;

out vec4 outputColor;


uniform sampler2DRect modifier;
uniform float sync, frequency, delta, modIntensity, exp, shape;
uniform vec4 color;
uniform int wave, reverse;

vec2 n_fragCoord;

float map(in float x, in float in_min, in float in_max, in float out_min, in float out_max)
{
    return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

float phaseProcess(in float modifierV){
    float phase =  modifierV + (n_fragCoord.y * (1.0 - sync) + n_fragCoord.x * sync) / frequency;
    return fract(phase);
}

void main()
{
    n_fragCoord = gl_FragCoord.xy / u_resolution;
    
    vec4 modifierValue = texture(modifier, gl_FragCoord.xy);
    //vec4 automodifierValue = texture(automodifier, gl_FragCoord.xy);    
    
    float phase = phaseProcess(1.0 - delta 
                    + (modIntensity * (modifierValue[0] + modifierValue[1] + modifierValue[2]) ));
                    //+ (automodIntensity * (automodifierValue[0] + automodifierValue[1] + automodifierValue[2]) ) );
    float value = 0.0;

    if(WAVE_SINE_SQUARE == wave)
    {
        value = (1.0 + sin( 1.5 * PI + phase * TWO_PI))/2.0;
        value = map(value, 0.0, 1.0, map(shape, 0.0, 1.0, -1.0, 1.0), map(shape, 0.0, 1.0, 0.0, 2.0));
    }
    else if( WAVE_SAW == wave)
    {
        value = phase + 2.0 * shape - 1.0;
        
        /* ANTIALIASING */
        if(phase <= ANTIALIAZING){
            value += map(abs(phase), 0.0, ANTIALIAZING, 1.0, 0.0);
        }
    }
    
    value = min(max(value, 0.0), 1.0);
    if(reverse == 0){
        value = 1.0 - pow(value, exp);    
    }else{
        value = pow(value, exp);
    }
    
 

    float r = color[3] * color[0] * value;
    float g = color[3] * color[1] * value;
    float b = color[3] * color[2] * value;
    float a = 1.0;
    
 //   #if DEBUG
     //   gl_FragColor = vec4(vec3(r, g, b), a);
   // #else
        outputColor = vec4(r, g, b, a);
    //#endif
}