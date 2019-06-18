/*=============================================================================

ì™è„É}Å[ÉN[ HeadMark.h ]

-------------------------------------------------------------------------------
Å°  Author
Ohno Takuya

Å°  Create
2017/11/24
=============================================================================*/

#ifndef _HEADMARK_H_
#define _HEADMARK_H_

/*-----------------------------------------------------------------------------
Class
-----------------------------------------------------------------------------*/
class HeadMark:public Object
{
public:
	HeadMark(int priolity = 3);

	static HeadMark* Create(D3DXVECTOR3 position);

	// Setter
	void SetActive(bool flag){ m_Active = flag; }
	void SetTexturePath(char* texturePath){ m_TexturePath = texturePath; }

private:
	void Initialize(void)override;
	void Uninitialize(void)override;
	void Update(void)override{}
	void Draw(void)override;
	void MakeVertex(LPDIRECT3DDEVICE9 Device);
	void WorldTransform(LPDIRECT3DDEVICE9 Device);

private:
	LPDIRECT3DVERTEXBUFFER9 m_VertexBuffer;

	D3DXVECTOR3 m_Scale;

	D3DXVECTOR2 m_Size;

	char* m_TexturePath;

	bool m_Active;
};

#endif
