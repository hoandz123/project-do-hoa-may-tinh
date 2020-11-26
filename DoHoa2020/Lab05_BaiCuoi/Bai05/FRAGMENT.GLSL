// DISPLACEMENT SHADER: FRAGMENT SHADER

uniform vec3 shade; // Mau cua van nhieu, tu chuong trinh chinh
varying float noise; // Gia tri mau cua pixel nhieu, tu vertex shader
void main() 
{
 gl_FragColor = vec4(shade * clamp(noise, 0.0, 1.0 ), 1.0 );
}