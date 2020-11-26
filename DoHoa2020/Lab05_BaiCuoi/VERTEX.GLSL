// POSITION TO RGB MAPPING: VERTEX SHADER

varying vec4 color; // Gia tri mau fragment shader

void main() 
{
 //Chuan hoa toa do dinh va anh xa vao khong gian RGB
 color = (normalize(gl_Vertex.zyxw) + vec4(0.2, 1.0, 1.0, 1.0));

 // Tinh toa do cho moi dinh
 gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;
}