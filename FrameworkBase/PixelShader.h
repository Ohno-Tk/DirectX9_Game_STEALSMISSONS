/*=============================================================================

�s�N�Z���V�F�[�_�[[ PixelShader.h ]

-------------------------------------------------------------------------------

��  Create
2017/11/16
=============================================================================*/

#ifndef _PIXELSHADER_H_
#define _PIXELSHADER_H_

/*-----------------------------------------------------------------------------
Class
-----------------------------------------------------------------------------*/
class PixelShader
{
public:
	PixelShader();

	void Initialize(std::string filePath, std::string entryFunction = "main");
	void Uninitialize(void);
	
	// Getter
	LPDIRECT3DPIXELSHADER9 GetPixelShader(void){ return m_PixelShader; }
	LPD3DXCONSTANTTABLE GetPixelShaderConstantTable(void){ return m_PixelShaderConstantTable; }

private:
	LPDIRECT3DPIXELSHADER9 m_PixelShader;
	LPD3DXCONSTANTTABLE m_PixelShaderConstantTable;
};

#endif
