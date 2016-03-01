uniform sampler2DRect image;
uniform int imgWidth,imgHeight;
uniform int trueWidth,trueHeight;
uniform float intensity;
uniform float val2,val3;
uniform float timer;
float pix_w,pix_h;
varying vec3 pos;

void main (void)
{
    float rand = intensity*2.1;
    pix_w = 1.0 / float(imgWidth);
    pix_h = 1.0 / float(imgHeight);
	
    vec2 texCoord = vec2(max(3.0,min(float(trueWidth)  ,pos.x+sin(pos.y/(153.25*rand*rand)*rand+rand+timer*3.0)*intensity)),
						  max(3.0,min(float(trueHeight),pos.y+cos(pos.x/(251.57*rand*rand)*rand+rand+timer*2.4)*intensity)-3.));


    vec4 col = texture2DRect(image,texCoord);

    gl_FragColor.rgba = col.rgba;
}
