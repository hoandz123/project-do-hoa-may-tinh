varying vec3 normal; // vector phap tuyen nhan tu vertex shader

void main() 
{
 //Anh xa huong phap tuyen vao khong gian RGB
 gl_FragColor = vec4(normal, 1.0);
}