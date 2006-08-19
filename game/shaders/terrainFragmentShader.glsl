/*
---------------------------------------------------------------------
   Terrain Renderer using texture splatting and geomipmapping
   Copyright (c) 2006 Jelmer Cnossen

   This software is provided 'as-is', without any express or implied
   warranty. In no event will the authors be held liable for any
   damages arising from the use of this software.

   Permission is granted to anyone to use this software for any
   purpose, including commercial applications, and to alter it and
   redistribute it freely, subject to the following restrictions:

   1. The origin of this software must not be misrepresented; you
      must not claim that you wrote the original software. If you use
      this software in a product, an acknowledgment in the product
      documentation would be appreciated but is not required.

   2. Altered source versions must be plainly marked as such, and
      must not be misrepresented as being the original software.

   3. This notice may not be removed or altered from any source
      distribution.

   Jelmer Cnossen
   j.cnossen at gmail dot com
---------------------------------------------------------------------
*/

// Optimized function generated by the GLSL handler
// This function uses the utility functions below to do things like texture reading and lighting
vec4 CalculateColor();

#ifdef DiffuseFromBuffer

	vec4 ReadDiffuseColor()
	{
		return texture2DRect(_buffer, gl_FragCoord.xy);
	}

#endif

#ifdef UseBumpmapping
	vec3 reflect(vec3 N, vec3 L)
	{
		return 2.0*N*dot(N, L) - L;
	}

	vec4 CalcFinal(vec4 diffuse, vec4 texValue)
	{
		vec3 normal = normalize(texValue.xyz * vec3(2.0) - vec3(1.0));
		float diffuseFactor = max(0.0, -dot(tsLightDir, normal));
		
		vec3 R = reflect(normal, tsLightDir);
		float specularFactor = clamp(pow(dot(R, tsEyeDir), specularExponent), 0.0, 1.0);
		
		vec4 r = diffuse * (gl_LightSource[0].diffuse * diffuseFactor + gl_LightSource[0].ambient);
		r += gl_LightSource[0].specular * specularFactor * texValue.a;

		return r;
	}
#endif


// Shader entry point
void main()
{
	gl_FragColor=CalculateColor();
}
