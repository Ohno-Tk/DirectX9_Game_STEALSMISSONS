/*=============================================================================

カメラ(DirectX)[ CameraDirectX.h ]

-------------------------------------------------------------------------------
■  Author
	Ohno Takuya

■  Create
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
	const D3DXMATRIX GetInversedView(void)const;//	逆行列
	D3DXVECTOR3 GetPositionEye(void){ return m_PositionEye; }
	D3DXVECTOR3 GetPositionAt(void){ return m_PositionAt; }
	D3DXMATRIX GetViewMatrix(void){ return m_MtxView; }
	D3DXMATRIX GetProjectionMatrix(void){ return m_mtxProj; }
	D3DXMATRIX GetViewProjectionMatrix(void);

private:
	void SetProjection(void); // プロジェクション
	void NormalizeCamera(void);

#ifdef _DEBUG
	void DebugCamera(void);
#endif

private:
#ifdef _DEBUG
	static bool m_DebugCameraFlag;
#endif

	D3DXVECTOR3 m_PositionEye;	// カメラ座標
	D3DXVECTOR3 m_PositionAt;	// 注視点
	D3DXVECTOR3 m_VecUp;		// 上の視点
	D3DXVECTOR3 m_FrontVector;	// 前方向ベクトル
	D3DXVECTOR3 m_RightVector;	// 右方向ベクトル

	D3DXMATRIX m_MtxView;		// ビュー行列マトリクス
	D3DXMATRIX m_mtxProj;		// プロジェクション行列マトリクス

	CameraState* m_State;
};

#endif
