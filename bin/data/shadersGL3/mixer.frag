#version 150

#ifdef GL_ES
    precision mediump float;
#endif

out vec4 outputColor;

uniform sampler2DRect channel0, channel1, channel2, channel3, channel4, channel5, channel6, channel7;
uniform float lvl0, lvl1, lvl2, lvl3, lvl4, lvl5, lvl6, lvl7;
uniform int channelLen;
uniform float circleSize0, circleSize1, circleSize2, circleSize3, circleSize4, circleSize5, circleSize6, circleSize7;
uniform vec2 u_resolution;
vec2 n_fragCoord;
float prop;
float circle(in vec2 _st, in float _radius){
    float dist = distance(_st,vec2(0.5 * prop, 0.5));
    return 1.-smoothstep(_radius-(_radius*0.005),
                         _radius+(_radius*0.005),
                         dist);
}

vec4 level(in vec2 coord, in sampler2DRect chan, in float lvl){
    vec4 localColor = texture(chan, coord);
    if(lvl < 0.0){
        localColor = vec4(1.0, 1.0, 1.0, 1.0) - localColor;
    }
    return lvl * localColor;
}

void main()
{
    prop = u_resolution.x/u_resolution.y;
    n_fragCoord = gl_FragCoord.xy / u_resolution;
    n_fragCoord = vec2(n_fragCoord.x * prop, n_fragCoord.y);
    outputColor   = vec4 (0.0);
    if(channelLen >= 1)
        outputColor  += level(gl_FragCoord.xy, channel0, lvl0) * circle(n_fragCoord, circleSize0);
    if(channelLen >= 2)
        outputColor  += level(gl_FragCoord.xy, channel1, lvl1) * circle(n_fragCoord, circleSize1);
    if(channelLen >= 3)
        outputColor  += level(gl_FragCoord.xy, channel2, lvl2) * circle(n_fragCoord, circleSize2);
    if(channelLen >= 4)
        outputColor  += level(gl_FragCoord.xy, channel3, lvl3) * circle(n_fragCoord, circleSize3);
    if(channelLen >= 5)
        outputColor  += level(gl_FragCoord.xy, channel4, lvl4) * circle(n_fragCoord, circleSize4);
    if(channelLen >= 6)
        outputColor  += level(gl_FragCoord.xy, channel5, lvl5) * circle(n_fragCoord, circleSize5);
    if(channelLen >= 7)
        outputColor  += level(gl_FragCoord.xy, channel6, lvl6) * circle(n_fragCoord, circleSize6);
    if(channelLen >= 8)
        outputColor  += level(gl_FragCoord.xy, channel7, lvl7) * circle(n_fragCoord, circleSize7);

    outputColor[0] = abs(outputColor[0]);
    outputColor[1] = abs(outputColor[1]);
    outputColor[2] = abs(outputColor[2]);
    outputColor[3] = 1.0;
}