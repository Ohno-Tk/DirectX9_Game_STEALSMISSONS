/*=============================================================================

�t�F�[�h[ Fade.h ]

-------------------------------------------------------------------------------


��  Created Date
	2017/08/25
=============================================================================*/

#ifndef _FADE_H_
#define _FADE_H_

/*-----------------------------------------------------------------------------

-----------------------------------------------------------------------------*/
class Scene;

/*-----------------------------------------------------------------------------
Class
-----------------------------------------------------------------------------*/
class Fade
{
public:
	enum FADE_STATE
	{	//	�t�F�[�h�̏��
		FADE_NONE = 0,
		FADE_IN,	//	�t�F�[�h�C��
		FADE_OUT,	//	�t�F�[�h�A�E�g
	};

	Fade():m_VtxBuff(NULL),m_Color(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f)){}

	//	�t�F�[�h�̃Z�b�g
	static void SetFade(const FADE_STATE Fade, Scene *Mode) { m_Fade = Fade, m_Scene = Mode; }

	void Initialize(void);
	void Uninitialize(void);
	void Update(void);
	void Draw(void);

private:
	void MakeVerTex(void);		//	���_�̍쐬
	void SetVerTex(void);	//	���_�̕ύX
	void AlphaFade(void);		//	���l�̃t�F�[�h

private:
	LPDIRECT3DVERTEXBUFFER9 m_VtxBuff;	// ���_�o�b�t�@

	D3DXCOLOR m_Color;	//	�F

	static FADE_STATE m_Fade;		//	�t�F�[�h���
	static Scene* m_Scene;	//	�V�[���̃|�C���^
};

#endif