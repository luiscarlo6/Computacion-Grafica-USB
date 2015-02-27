varying vec4 cLightDiff, cLightAmb, cLightSpec;
varying vec4 cMatDiff, cMatAmb, cMatSpec;
varying vec3 camDirection;
varying vec3 N;
varying vec4 L;

uniform float bias;

uniform bool fresnel;
uniform float eta;
uniform float Kfr;

uniform bool cook;
uniform float refraccion;
uniform float m;

uniform bool glossy;
uniform float sharpness;
uniform float roughness;

uniform float intSpec;
uniform float intDiff;

// funcion bias
float biasFun(float t, float a){
   return pow(t, -(log(a)/log(2.0)));
}

// para el calculo del bias
float biasFinal(vec4 L, vec3 N, float bias){
   vec4 Ln = vec4(0.0,0.0,0.0,1.0);
   vec3 Nn = vec3(0.0,0.0,0.0);
   float cos_theta_1, c;
   Ln = normalize(L);
   Nn = normalize(N);
   cos_theta_1 = max(0.0,dot(Ln.xyz,Nn));
   c = biasFun(cos_theta_1, bias);   
   return c;
}

// fresnel
float fresnelFunc(vec3 camDirection, vec3 N, float bias, float eta, float Kfr){
   vec3 Vn, Nn;
   float dotnv, Kr, col;
   Nn = normalize(N);
   Vn = -normalize(camDirection);
   dotnv = abs(dot(Nn, Vn));
   Kr = eta + ((1.0-eta)*pow((1.0-dotnv),5.0));
   Kr = Kfr * biasFun(Kr,bias);
   return Kr;
}

// glossy sharp
float glossySharp(vec3 N, vec3 camDirection, vec4 L, float sharpness, float roughness){
   float w, c;
   vec3 H, Vn;
   Vn = normalize(camDirection);
   w = 0.18 * (1.0-sharpness);
   H = normalize(normalize(L.xyz)+Vn);
   c = smoothstep(0.72-w, 0.72+w, pow(max(dot(N, H), 0.0), 1.0/roughness));
   return c;
}

// cook-torrence
float distro(vec3 N, vec3 H, float m){
   float ndoth = max(0.0,dot(N,H));
   float beta = acos(ndoth);
   float tanbeta = tan(beta);
   float tanbeta_over_m = tanbeta/m;
   float D = exp(-(tanbeta_over_m*tanbeta_over_m));
   D /= 4 *m*m * pow(ndoth,4);
   return D;
}

float geom(vec3 N, vec3 H, vec3 L, vec3 V){
   float G;
   float ndoth = max(0.0,dot(N,H));
   float ndotv = max(0.0,dot(N,V));
   float ndotl = max(0.0,dot(N,L));
   float vdoth = max(0.0,dot(V,H));

   float masking = (2 * ndoth * ndotv) / vdoth;
   float shadowing = (2 * ndoth * ndotl) / vdoth;
   G = min(1,min(masking,shadowing));
   return G;
}

float fresnelCook(vec3 normal, vec3 light, float indexR)
{
   float F;
   float R0 = pow((1.0-indexR),2)/pow((1.0+indexR),2);
   F = R0 + ((1.0-R0)*pow((1.0-dot(light,normal)),5));
   return F;
}

float cookTorrence(vec3 N, vec3 camDirection, float m, float refraccion){
   vec3 Nn = normalize(N);
   //vec3 Nf = faceforward(Nn,normalize(L.xyz),Nn);
   //Nf = normalize(Nf);
   float ct = 0.0;
   vec3 Ln = normalize(L.xyz);
   vec3 V = normalize(camDirection);
   vec3 H = normalize(Ln+V);
   float D = distro(Nn,H,m);
   float G = geom(Nn,H,Ln,V);
   float F = fresnelCook(Nn,V,refraccion);
   ct = D*G*F;
   float vdotn = max(0.0,dot(V,Nn));
   ct = vdotn;
   ct /= 3.14159265359;
   return ct;
}

void main (void)  
{   
   vec4 cFinal = vec4(0.0,0.0,0.0,1.0);
   float iDiff = 0.0, iSpec = 0.0;

   // para el bias
   float c = 0.0;

   // para el fresnel
   float col = 0.0;

   // para el glossy o el cook
   float g = 0.0;

   if (cook == false){
      if (glossy == true){
         g = glossySharp(N, camDirection, L, sharpness, roughness);
         iSpec = g;
      }
   }
   else{
      g = cookTorrence(N,camDirection,m,refraccion);
      iSpec = g;
   }

   if (fresnel == false){

      c = biasFinal(L,N,bias);
      //intensidad Especular
      if (intSpec>0.0){
         iSpec = iSpec * intSpec;
      }

      //intensidad Difusa
      if (intDiff>0.0){
         iDiff = c;
         iDiff = iDiff * intDiff;
      }

      cFinal = vec4(0.0,0.0,0.0,1.0)*cLightAmb*cMatAmb + iDiff*(cLightDiff*cMatDiff) + iSpec*(cLightSpec*cMatSpec);
   }
   else {
      col = fresnelFunc(camDirection,N,bias,eta,Kfr);
      cFinal = vec4(1.0*col,2.0*col,1.0*col,1.0);
   }
  
   cFinal.w = 1.0;
   gl_FragColor = cFinal;

}