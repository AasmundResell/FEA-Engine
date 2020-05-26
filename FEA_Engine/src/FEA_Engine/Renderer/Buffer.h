#pragma once

//this file will contain both the Vertex and the Index buffer as Pure virtual classes


namespace FEE {

	class VertexBuffer
	{
	public:
		virtual ~VertexBuffer() {}

		
		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		//static:does not belong to the class, need this pointer to pass in the actual vertices
		//Use this instead of creating a constructor because we want to be able to choose the API
		//instead of having to use this specific class.
		static VertexBuffer* Create(float* vertices, uint32_t size);
	};

	class IndexBuffer
	{
	public:
		virtual ~IndexBuffer() {}
		virtual void Bind() const = 0; 
		virtual void Unbind() const  = 0;

		virtual uint32_t GetCount() const = 0;

		static IndexBuffer* Create(uint32_t* indices, uint32_t count);


	};



}