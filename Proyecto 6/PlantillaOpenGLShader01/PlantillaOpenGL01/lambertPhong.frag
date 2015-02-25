varying vec4 cLightDiff, cLightAmb, cLightSpec;
varying vec4 cMatDiff, cMatAmb, cMatSpec;
varying vec3 camDirection;
varying vec3 N;
varying vec4 L;

uniform float bias;
uniform bool fresnel;
uniform float eta;
uniform float Kfr;

// funcion bias
float biasFun(float t, float a){
   return pow(t, (sign(-1.0)*(log(a)/log(2.0))));
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
   Vn = (sign(-1.0)) * normalize(camDirection);
   dotnv = abs(dot(Nn, Vn));
   Kr = eta + (1-eta)*pow(1-dotnv,5);
   Kr = Kfr * biasFun(Kr,bias);
   //col = dot(Kr, dot(Kr,Kr));
   return Kr;
}

void main (void)  
{     
   
   vec4 cFinal = vec4(0.0,0.0,0.0,1.0);
   float iDiff, iSpec;
   vec3 vRef;

   // para el bias
/*   vec4 Ln = vec4(0.0,0.0,0.0,1.0);
   vec3 Nn;
   float cos_theta_1, c;*/
   float c = 0;

   // para el fresnel
/*   vec3 Vn;
   float dotnv, Kr, col;*/
   float col = 0;

   //Componente Specular Phong
   vRef = -normalize(reflect(L.xyz,N));
   iSpec = pow(max(dot(vRef, normalize(camDirection)), 0.0),10.0);

   if (fresnel == false){
      // bias
      /*   Ln = normalize(L);
      Nn = normalize(N);
      cos_theta_1 = dot(Ln.xyz,Nn);
      c = biasFun(cos_theta_1, bias);*/
      c = biasFinal(L,N,bias);
      //Componente difuso.
      iDiff = max(dot(normalize(N),normalize(L.xyz)), 0.0) + c;

      cFinal = vec4(10.0,0.0,0.0,1.0)*cLightAmb*cMatAmb + iDiff*(cLightDiff*cMatDiff) + iSpec*(cLightSpec*cMatSpec);
   }
   else {
      // fresnel
   /*   Vn = (sign(-1.0)) * normalize(camDirection);
      dotnv = abs(dot(Nn, Vn));
      Kr = eta + (1-eta)*pow(1-dotnv,5);
      Kr = Kfr * biasFun(Kr,bias);
      col = dot(Kr, dot(Kr,Kr));*/
      col = fresnelFunc(camDirection,N,bias,eta,Kfr);
      cFinal = vec4(1.0*col,2.0*col,1.0*col,1.0);
   }
  
   cFinal.w = 1.0;
   gl_FragColor = cFinal;

}