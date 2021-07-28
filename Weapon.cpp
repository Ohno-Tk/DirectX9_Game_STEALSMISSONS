/*=============================================================================

����[ Weapon.cpp ]

-------------------------------------------------------------------------------

��  Create
2017/11/19
=============================================================================*/

/*-----------------------------------------------------------------------------
Include Files
-----------------------------------------------------------------------------*/
#include "FrameworkBase\RendererDirectX.h"
#include "FrameworkBase\Common.h"
#include "FrameworkBase\Game.h"
#include "FrameworkBase\ModelManagerDirectX.h"
#include "Object.h"
#include "Weapon.h"


Weapon::Weapon(int priolity):Object(priolity)
{
	m_Rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);

	D3DXMatrixIdentity(&m_OwnerMatrix);
}

void Weapon::Draw(void)
{
	D3DMATERIAL9 materialDefault;

	LPDIRECT3DDEVICE9 Device = RendererDirectX::GetDevice();

	ModelManagerDirectX* manager = Game::GetInstance()->GetModelManager();
	m_ModelParam = manager->GetModelParam(m_ModelFilePath);

	WorldTransform(Device);

	// ���݃f�o�C�X�ɐݒ肳��Ă���}�e���A�����̎擾
	Device->GetMaterial(&materialDefault);

	// �}�e���A���ւ̃|�C���^���擾
	m_ModelParam.Material = (D3DXMATERIAL*)m_ModelParam.BufferMaterial->GetBufferPointer();

	for (int CountMaterial = 0; CountMaterial < (int)m_ModelParam.NumMaterial; CountMaterial++)
	{
		//	�A���r�G���g���̐ݒ�
		m_ModelParam.Material[CountMaterial].MatD3D.Ambient = m_ModelParam.Material[CountMaterial].MatD3D.Diffuse;

		// �f�o�C�X�Ƀ}�e���A���̐ݒ�
		Device->SetMaterial(&m_ModelParam.Material[CountMaterial].MatD3D);

		// �e�N�X�`���̐ݒ�
		Device->SetTexture(0, m_ModelParam.Texture[CountMaterial]);

		// �`��
		m_ModelParam.Mesh->DrawSubset(CountMaterial);
	}

	// �}�e���A�������ɖ߂�
	Device->SetMaterial(&materialDefault);
}

void Weapon::WorldTransform(LPDIRECT3DDEVICE9 Device)
{
	D3DXVECTOR3 position = Object::GetPosition();

	D3DXMATRIX matrixScale, matrixRotation, matrixPosition;

	D3DXMatrixIdentity(&m_MatrixWorld);

	D3DXMatrixScaling(&matrixScale,
		m_Scale.x,	//	X���g��
		m_Scale.y,	//	Y���g��
		m_Scale.z);	//	Z���g��

	D3DXMatrixRotationYawPitchRoll(&matrixRotation,
		D3DXToRadian(m_Rotation.y), //	Y����]
		D3DXToRadian(m_Rotation.x), //	X����]
		D3DXToRadian(m_Rotation.z)); //	Z����]

	D3DXMatrixTranslation(&matrixPosition,
		position.x,	//	X���ړ�
		position.y,	//	Y���ړ�
		position.z);	//	Z���ړ�

	D3DXMatrixMultiply(&m_MatrixWorld, &m_MatrixWorld, &matrixScale);
	D3DXMatrixMultiply(&m_MatrixWorld, &m_MatrixWorld, &matrixRotation);
	D3DXMatrixMultiply(&m_MatrixWorld, &m_MatrixWorld, &matrixPosition);

	D3DXMatrixMultiply(&m_MatrixWorld, &m_MatrixWorld, &m_OwnerMatrix); // �e�̃}�g���N�X�̂�����

	//	�f�o�C�X�Ƀ��[���h�ϊ��s���ݒ�
	Device->SetTransform(D3DTS_WORLD, &m_MatrixWorld);
}