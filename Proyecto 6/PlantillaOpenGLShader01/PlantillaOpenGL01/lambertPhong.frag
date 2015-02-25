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
   cos_theta_1 = dot(Ln.xyz,Nn);
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
   vec3 H;
   w = 0.18 * (1.0-sharpness);
   H = normalize(normalize(L.xyz)+camDirection);
   c = smoothstep(0.72-w, 0.72+w, pow(max(dot(N, H), 0.0), 1.0/roughness));
   return c;
}

void main (void)  
{   
   vec4 cFinal = vec4(0.0,0.0,0.0,1.0);
   float iDiff, iSpec;
   vec3 vRef;

   // para el bias
   float c = 0.0;

   // para el fresnel
   float col = 0.0;

   // para el glossy
   float g = 0.0;

   //Componente Specular Phong
   vRef = -normalize(reflect(L.xyz,N));
   iSpec = pow(max(dot(vRef, normalize(camDirection)), 0.0),10.0);
   iDiff = max(dot(normalize(N),normalize(L.xyz)), 0.0);

   if (cook == false){
      g = glossySharp(N, camDirection, L, sharpness, roughness);
      iSpec += g;
   }

   //intensidad Especular
   if (intSpec>0.0){
      iSpec = iSpec * intSpec;
   }

   //intensidad Difusa
   if (intDiff>0.0){
      iDiff = iDiff * intDiff;
   }

   if (fresnel == false){
      c = biasFinal(L,N,bias);
      //Componente difuso.
      iDiff += c;
      cFinal = vec4(10.0,0.0,0.0,1.0)*cLightAmb*cMatAmb + iDiff*(cLightDiff*cMatDiff) + iSpec*(cLightSpec*cMatSpec);
   }
   else {
      col = fresnelFunc(camDirection,N,bias,eta,Kfr);
      cFinal = vec4(1.0*col,2.0*col,1.0*col,1.0);
   }
  
   cFinal.w = 1.0;
   gl_FragColor = cFinal;

}