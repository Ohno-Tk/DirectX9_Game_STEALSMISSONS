/*=============================================================================

�X�N���[���I�u�W�F�N�g(2D)[ Scroll2DObject.h ]

-------------------------------------------------------------------------------

��  Create
2017/11/17
=============================================================================*/

#ifndef _SCROLL2DOBJECT_H_
#define _SCROLL2DOBJECT_H_

/*-----------------------------------------------------------------------------
Class
-----------------------------------------------------------------------------*/
class Scroll2DObject:public Sprite2D
{
public:
	Scroll2DObject(int Priolity):Sprite2D(Priolity), m_ScrollSpeed(D3DXVECTOR2(0.0f,0.0f)), m_TexCoord(D3DXVECTOR2(0.0f,0.0f)){}

	static Scroll2DObject* Create(D3DXVECTOR3 position, D3DXVECTOR2 size, char* textureFilePath, D3DXVECTOR2 scrollSpeed, int priolity = 3);

	void Initialize(void)override;
	void Uninitialize(void)override;
	void Update(void)override;
	void Draw(void)override;

	// Setter
	void SetScrollSpeed(const D3DXVECTOR2 scrollSpeed){ m_ScrollSpeed = scrollSpeed; }

private:
	void SetVertex(void); // ���_�̕ύX

private:
	D3DXVECTOR2 m_TexCoord;
	D3DXVECTOR2 m_ScrollSpeed;
};

#endif
