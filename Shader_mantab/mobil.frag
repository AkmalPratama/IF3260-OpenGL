#ifdef GL_ES
precision mediump float;
#endif

#define PI 3.14159265359

uniform vec2 u_resolution;
uniform float u_time;

mat2 rotate2d(float _angle){
    return mat2(cos(_angle),-sin(_angle),
                sin(_angle),cos(_angle));
}

float box(in vec2 _st, in vec2 _size){
    _size = vec2(0.5) - _size*0.5;
    vec2 uv = smoothstep(_size,
                        _size+vec2(0.001),
                        _st);
    uv *= smoothstep(_size,
                    _size+vec2(0.001),
                    vec2(1.0)-_st);
    return uv.x*uv.y;
}

float cross(in vec2 _st, float _size){
    return  box(_st, vec2(_size,_size/4.)) +
            box(_st, vec2(_size/4.,_size));
}

float onecross(in vec2 _st, float _size) {
    return  box(_st, vec2(_size,_size/2.328));
}

mat2 scale(vec2 _scale){
    return mat2(_scale.x,0.0,
                0.0,_scale.y);
}

float circle(in vec2 _st, in float _radius){
    vec2 dist = _st-vec2(0.5);
	return 1.-smoothstep(_radius-(_radius*0.01),
                         _radius+(_radius*0.01),
                         dot(dist,dist)*4.0);
}

void main(){
    vec2 st = gl_FragCoord.xy/u_resolution.xy;
    vec2 st2 = gl_FragCoord.xy/u_resolution.xy;
    vec2 st3 = gl_FragCoord.xy/u_resolution.xy;
    vec2 st4 = gl_FragCoord.xy/u_resolution.xy;
    vec2 st5 = gl_FragCoord.xy/u_resolution.xy;
    vec3 color = vec3(0.059,0.025,0.125);
    vec3 color2 = vec3(0.000,0.034,0.195);
    vec3 color3 = vec3(0.000,0.018,0.055);
    vec3 color4 = vec3(0.004,0.018,0.110);
    vec3 color5 = vec3(0.004,0.018,0.110);
    // move space from the center to the vec2(0.0)
    st -= vec2(0.180,0.430);
    st2 -= vec2(0.600,0.500);
    st3 -= vec2(0.100,0.000);
    st4 -= vec2(-0.320,-0.070);
    st5 -= vec2(-0.110,0.090);
    // rotate the space
    st = rotate2d((u_time)*PI ) * st;
    st = scale( vec2(+2.336) ) * st;
    st2 = rotate2d((u_time*PI)) * st2;
    st2 = scale(vec2(+2.220)) * st2;
    // move it back to the original place
    st += vec2(0.5);
    st2 += vec2(0.5);

    // Show the coordinates of the space on the background
    //color = vec3(st.x,st.y,0.0);

    // Add the shape on the foreground
    color += vec3(cross(st,0.232));
    color2 += vec3(cross(st2,0.668));
	color3 += vec3(circle(st3,0.068));
    color4 += vec3(circle(st4,0.004));
    color5 += vec3(onecross(st5,0.544));
    gl_FragColor = vec4(color,1.0) + vec4(color2,1.0) + vec4(color3,1.0) + vec4(color4,-0.488) + vec4(color5,0.000);
}