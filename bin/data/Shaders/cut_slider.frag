uniform sampler2DRect image;
uniform int imgWidth,imgHeight;
uniform float intensity;
float pix_w,pix_h;
varying vec3 pos;

void main (void)
{
    float rand = intensity*.1;

    pix_w = 1.0;
    pix_h = 1.0;
    
    vec2 texCoord = vec2(pos.x, pos.y);
    vec4 col = texture2DRect(image,texCoord);
    vec4 col_s = texture2DRect(image,texCoord + vec2(floor(sin(pos.y/30.0*rand+rand*rand))*30.0*rand,0));
    
    col = col_s;
    
	gl_FragColor.rgba = col.rgba;
}
