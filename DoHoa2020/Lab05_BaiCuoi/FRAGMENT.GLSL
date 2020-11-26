// POSITION TO RGB MAPPING: FRAGMENT SHADER

varying vec4 color; // Gia tri mau da tinh tu vertex shader
void main() 
{
 // Gan gia tri mau cho pixel
 gl_FragColor = color;
}