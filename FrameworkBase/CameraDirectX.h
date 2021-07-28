/*=============================================================================

�J����(DirectX)[ CameraDirectX.h ]

-------------------------------------------------------------------------------

��  Create
	2017/10/16
=============================================================================*/

#ifndef _CAMERADIRECTX_H_
#define _CAMERADIRECTX_H_

/*-----------------------------------------------------------------------------

-----------------------------------------------------------------------------*/
class CameraState;

/*-----------------------------------------------------------------------------
Class
-----------------------------------------------------------------------------*/
class CameraDirectX
{
public:
	CameraDirectX();

	void Uninitialize(void);
	void Update(void);

	void SetState(CameraState* state);

	// Setter
	void SetPositionEye(const D3DXVECTOR3 position){ m_PositionEye = position; }
	void SetPositionAt(const D3DXVECTOR3 position){ m_PositionAt = position; }

	//	Getter
	const D3DXMATRIX GetInversedView(void)const;//	�t�s��
	D3DXVECTOR3 GetPositionEye(void){ return m_PositionEye; }
	D3DXVECTOR3 GetPositionAt(void){ return m_PositionAt; }
	D3DXMATRIX GetViewMatrix(void){ return m_MtxView; }
	D3DXMATRIX GetProjectionMatrix(void){ return m_mtxProj; }
	D3DXMATRIX GetViewProjectionMatrix(void);

private:
	void SetProjection(void); // �v���W�F�N�V����
	void NormalizeCamera(void);

#ifdef _DEBUG
	void DebugCamera(void);
#endif

private:
#ifdef _DEBUG
	static bool m_DebugCameraFlag;
#endif

	D3DXVECTOR3 m_PositionEye;	// �J�������W
	D3DXVECTOR3 m_PositionAt;	// �����_
	D3DXVECTOR3 m_VecUp;		// ��̎��_
	D3DXVECTOR3 m_FrontVector;	// �O�����x�N�g��
	D3DXVECTOR3 m_RightVector;	// �E�����x�N�g��

	D3DXMATRIX m_MtxView;		// �r���[�s��}�g���N�X
	D3DXMATRIX m_mtxProj;		// �v���W�F�N�V�����s��}�g���N�X

	CameraState* m_State;
};

#endif
