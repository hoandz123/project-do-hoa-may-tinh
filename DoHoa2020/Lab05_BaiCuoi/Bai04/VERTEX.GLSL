varying vec3 position; // Toa do dinh dung cho fragment shader
void main() 
{
 position = gl_Vertex.xyz;
 gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;
}
