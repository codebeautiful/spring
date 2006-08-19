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
namespace terrain 
{
	struct Blendmap;
	struct TiledTexture;
	class BufferTexture;

	struct NodeGLSLShader : public IShaderSetup
	{
		NodeGLSLShader ();
		~NodeGLSLShader ();
		
		std::string GetDebugDesc ();
		uint GetVertexDataRequirements ();
		void GetTextureUnits(BaseTexture* tex, int &imageUnit, int& coordUnit);

		void BindTSM(Vector3* buf, uint vertexSize);
		void UnbindTSM();

		std::vector<BaseTexture*> texUnits; // texture image units
		std::vector<BaseTexture*> texCoordGen; // textures that are used for texture coordinate generation

		GLhandleARB vertexShader;
		GLhandleARB fragmentShader;
		GLhandleARB program;

		GLint tsmAttrib; // attribute ID of tangent space matrix
		GLint wsLightDirLocation, wsEyePosLocation; // location for wsLightDir
		uint vertBufReq;
		std::string debugstr;

		BufferTexture* renderBuffer; // 0 for normal display

		void Setup(NodeSetupParams& params);
		void Cleanup();

		enum RenderMethod
		{
			RM_Direct, // direct diffuse + bumpmap + lighting in a single pass
			RM_SingleBuffer, // bumpmap rendered to buffer, then diffuse + lighting (possibly multipass) rendered to screen
			RM_MultiBuffer, // multipass bumpmap rendering, then diffuse (possibly multipass) rendered to screen
		};

		RenderMethod renderMethod;
	};

	class GLSLShaderHandler : public ITexShaderHandler
	{
	public:
		GLSLShaderHandler ();
		~GLSLShaderHandler ();

		// ITexShaderHandler interface
		void BeginPass (const std::vector<Blendmap*>& blendmaps, const std::vector<TiledTexture*>& textures);
		void EndPass () {}

		void BeginTexturing();
		void EndTexturing();

		void BuildNodeSetup (ShaderDef *shaderDef, RenderSetup *renderSetup);
		bool SetupShader (IShaderSetup *shadercfg, NodeSetupParams& params);

		int MaxTextureUnits ();
		int MaxTextureCoords ();
	protected:
		NodeGLSLShader* curShader;

		std::vector<BufferTexture*> buffers;
	};
};

