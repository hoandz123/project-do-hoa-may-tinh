
uniform vec3 lightPosition; 
uniform vec3 ambientColor;  
uniform vec3 diffuseColor;  // Mau diffuse, tu chuong trinh chinh
uniform vec3 specularColor; // Mau specular, tu chuong trinh chinh
uniform float Ka;           // He so ambient, tu chuong trinh chinh
uniform float Kd;            // He so diffuse, tu chuong trinh chinh
uniform float Ks;            // He so specular, tu chuong trinh chinh
uniform float shininess;    // He so bong be mat, tu chuong trinh chinh
varying vec3 N;              // Phap tuyen nhan tu vertex shader
varying vec3 v;             // Toa do dinh tu vertex shader
 
void main (void) {   
    vec3 L = normalize(lightPosition.xyz - v);    // Xac dinh vector huong sang
    vec3 E = normalize(-v);                      //Xac dinh vector huong nhin
    vec3 R = normalize(-reflect(L,N));           //Xac dinh vector phan chieu
    
    vec4 Iamb = vec4(ambientColor, 1.0);		//Tinh thanh phan ambient
    
    vec4 Idiff = vec4(diffuseColor * max(dot(N, L), 0.0), 1.0);			//Tinh thanh phan diffuse
     
    vec4 Ispec = vec4(specularColor * max(dot(R, E),0.0), shininess);	//Tinh thanh phan specular
     
    gl_FragColor = Ka * Iamb + Kd * Idiff + Ks * Ispec;      //Cap nhat gia tri pixel dua tren chuong trinh
} 