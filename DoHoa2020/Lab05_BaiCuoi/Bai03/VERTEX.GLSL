varying vec3 N; // Vector phao tuyen noi suy, chuyen cho fragment shader
varying vec3 v; // Vi tri cua dinh khong gian trong goc nhin
void main(void) 
{
 v = vec3(gl_ModelViewMatrix * gl_Vertex); //Tinh toa do dinh trong khong gian goc nhin

 N = normalize(gl_NormalMatrix * gl_Normal); //Noi suy phap tuyen

 gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex; //Tinh toa do chieu cua dinh
}