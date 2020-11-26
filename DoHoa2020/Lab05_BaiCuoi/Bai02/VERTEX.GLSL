varying vec3 normal; // vector phap tuyen noi suy duoc su dung cho fragment shader

void main() 
{
 normal = normalize(gl_NormalMatrix * gl_Normal + 10);
 gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;
}