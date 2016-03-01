uniform sampler2DRect image;
uniform int imgWidth,imgHeight;
uniform float intensity;
float pix_w,pix_h;
varying vec3 pos;

void main (void)
{
    pix_w = 1.0 / float(imgWidth);
    pix_h = 1.0 / float(imgHeight);
    
	float slit_h = intensity;
	
    vec2 texCoord = vec2(3.0+floor(pos.x/slit_h)*slit_h ,pos.y);
    vec4 col = texture2DRect(image,texCoord);
	
    gl_FragColor.rgba = col.rgba;
}
