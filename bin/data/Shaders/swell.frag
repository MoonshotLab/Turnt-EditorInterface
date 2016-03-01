uniform sampler2DRect image;
uniform int imgWidth,imgHeight;
uniform float fixedIntensity, intensity;
uniform float timer;
float pix_w,pix_h;
varying vec3 pos;

void main (void)
{
    if(fixedIntensity > 10.0){
        pix_w = 1.0;
        pix_h = 1.0;
        
        vec2 texCoord = vec2(pos.x,pos.y);
        vec4 col = texture2DRect(image,texCoord);
        vec4 col_s = texture2DRect(image,texCoord + vec2(sin(pos.y*0.03+timer*20.0)*(6.0+12.0*(intensity*.1)),0));
        
        col = col_s;
        
        gl_FragColor.rgba = col.rgba;
    } else{
        vec2 texCoord = vec2(pos.x, pos.y);
        vec4 col = texture2DRect(image, texCoord);
        
        gl_FragColor = col;
    }
}
