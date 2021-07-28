/*=============================================================================

�X�e���V���V���h�E[ StencilShadow.h ]
( Maybe-Later:std::string�̃�����������o���Ă��Ȃ� )
-------------------------------------------------------------------------------
��  Create
	2017/11/09
=============================================================================*/

#ifndef _STENCILSHADOW_H_
#define _STENCILSHADOW_H_

/*-----------------------------------------------------------------------------
Class
-----------------------------------------------------------------------------*/
class StencilShadow:public Object
{
public:
	StencilShadow(int Priolity = 1):Object(Priolity),m_VertexBuffer(NULL){}

	static StencilShadow* Create(char* modelFileName);

private:
	void Initialize(void)override;
	void Uninitialize(void)override;
	void Update(void)override{}
	void Draw(void)override;

	void Polygon2DDraw(LPDIRECT3DDEVICE9 Device); // �S���2D�|���S���`��
	void ModelDraw(LPDIRECT3DDEVICE9 Device); // ���f���`��
	void MakeVerTex(void); // ���_�̍쐬
	void WorldTransform(LPDIRECT3DDEVICE9 Device);	//	���[���h���W�ϊ�

private:
	LPDIRECT3DVERTEXBUFFER9 m_VertexBuffer;	//	���_�o�b�t�@

	D3DXMATRIX m_MatrixWorld;

	char* m_ModelFilePath;	//	���f���̃p�X

	MODEL_PARAM m_ModelParam;	//	���f���\����
};

#endif
