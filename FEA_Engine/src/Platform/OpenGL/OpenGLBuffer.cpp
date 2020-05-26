#include "feepch.h"

#include "OpenGLBuffer.h"

#include <glad/glad.h>

namespace FEE {

	//-------------------------------------------------------------------------------------
	//--------------VERTEX BUFFER-----------------------------------------------------------
	//-------------------------------------------------------------------------------------

	OpenGLVertexBuffer::OpenGLVertexBuffer(float* vertices, uint32_t size)
	{
		//Generates the  Vertex buffer
		glCreateBuffers(1, &m_RendererID);

		//Binds
		glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
		
		//upload to GPU, draw the triangle statically 
		glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);

	}

	OpenGLVertexBuffer::~OpenGLVertexBuffer()
	{
		glDeleteBuffers(1, &m_RendererID);
	}

	void OpenGLVertexBuffer::Bind() const
	{
		glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
	}

	void OpenGLVertexBuffer::Unbind() const
	{
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	//-------------------------------------------------------------------------------------
	//--------------INDEX BUFFER-----------------------------------------------------------
	//-------------------------------------------------------------------------------------

	OpenGLIndexBuffer::OpenGLIndexBuffer(uint32_t* indices, uint32_t count)
		: m_Count(count)
	{
		//Generates the Index buffer
		glCreateBuffers(1, &m_RendererID);

		//Binds
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID);

		//upload to GPU, draw the triangle statically 
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(uint32_t), indices, GL_STATIC_DRAW);

	}

	OpenGLIndexBuffer::~OpenGLIndexBuffer()
	{
		glDeleteBuffers(1, &m_RendererID);
	}

	void OpenGLIndexBuffer::Bind() const
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID);
	}

	void OpenGLIndexBuffer::Unbind() const
	{
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}
	
}