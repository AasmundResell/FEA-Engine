#include "feepch.h"
#include "Shader.h"

#include "Renderer.h"
#include "Platform/OpenGL/OpenGLShader.h"


namespace FEE {

	Ref<Shader>  Shader::Create(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:
		{
			FEE_CORE_ASSERT(false, "RendererAPI::None is not supported!")
				return nullptr;
		}
		case RendererAPI::API::OpenGL: return std::make_shared<OpenGLShader>(name, vertexSrc, fragmentSrc);
		}

		FEE_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;

	}

	Ref<Shader> Shader::Create(const std::string& filePath)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:
		{
			FEE_CORE_ASSERT(false, "RendererAPI::None is not supported!")
				return nullptr;
		}
		case RendererAPI::API::OpenGL: return std::make_shared<OpenGLShader>(filePath);
		}

		FEE_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
 
	}

	void ShaderLibrary::Add(const Ref<Shader>& shader)
	{
		auto& name = shader->GetName();
		Add(name, shader);  
	}

	void ShaderLibrary::Add(const std::string& name, const Ref<Shader>& shader)
	{	 
		FEE_CORE_ASSERT(!Exists(name), "Shader already exists!");
		m_shaders[name] = shader;

	}

	FEE::Ref<FEE::Shader> ShaderLibrary::Load(const std::string& filePath)
	{
		auto shader = Shader::Create(filePath);
		Add(shader);
		return shader;
	}

	FEE::Ref<FEE::Shader> ShaderLibrary::Load(const std::string& name, const std::string& filePath)
	{ 
		auto shader = Shader::Create(filePath);
		Add(name, shader);
		return shader;
	}

	FEE::Ref<FEE::Shader> ShaderLibrary::Get(const std::string& name)
	{
		FEE_CORE_ASSERT(Exists(name), "Shader not found!");
		return m_shaders[name];
	}

	bool ShaderLibrary::Exists(const std::string& name) const
	{
		return m_shaders.find(name) != m_shaders.end();
	}

}