/*=============================================================================

���_�V�F�[�_�[[ VertexShader.h ]

-------------------------------------------------------------------------------

��  Create
2017/11/16
=============================================================================*/

#ifndef _VERTEXSHADER_H_
#define _VERTEXSHADER_H_

/*-----------------------------------------------------------------------------
Class
-----------------------------------------------------------------------------*/
class VertexShader
{
public:
	VertexShader();

	HRESULT Initialize(std::string filePath, std::string entryFunction = "main");
	void Uninitialize(void);

	// Getter
	LPDIRECT3DVERTEXSHADER9 GetVertexShader(void){ return m_VertexShader; }
	LPD3DXCONSTANTTABLE GetVertexShaderConstantTable(void){ return m_VertexShaderConstantTable; }

private:
	LPDIRECT3DVERTEXSHADER9 m_VertexShader;
	LPD3DXCONSTANTTABLE m_VertexShaderConstantTable;
};

#endif
