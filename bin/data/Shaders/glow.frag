uniform sampler2DRect image;
uniform float rand, fixedIntensity,intensity;
uniform int range;


varying vec3 pos;


void main (void)
{
    float e = 2.718281828459045235360287471352;
    vec2 texCoord = vec2(pos.x , pos.y);
    vec4 col = texture2DRect(image,texCoord);
    
    int blur_w = int(fixedIntensity*.1);
    float pi = 3.1415926535;
    vec4 gws = vec4(0.0,0.0,0.0,1.0);
    float weight;
    float k = 1.0;
    
    weight = 1.0/(float(blur_w)*2.0+1.0)/(float(blur_w)*2.0+1.0);

    for (int i = 0;i < blur_w*blur_w;i++){
        gws = gws + texture2DRect(image,vec2(pos.x+float(mod(float(i),float(blur_w))),pos.y+float(i/blur_w)))*weight*1.3;
        gws = gws + texture2DRect(image,vec2(pos.x-float(mod(float(i),float(blur_w))),pos.y+float(i/blur_w)))*weight*1.3;
        gws = gws + texture2DRect(image,vec2(pos.x+float(mod(float(i),float(blur_w))),pos.y-float(i/blur_w)))*weight*1.3;
        gws = gws + texture2DRect(image,vec2(pos.x-float(mod(float(i),float(blur_w))),pos.y-float(i/blur_w)))*weight*1.3;
    }


    gl_FragColor.rgba = col+gws;
}