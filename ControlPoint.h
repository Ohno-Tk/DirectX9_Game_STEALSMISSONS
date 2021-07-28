/*=============================================================================

����_( �f�o�b�O�p )[ ControlPoint.h ]

-------------------------------------------------------------------------------

��  Create
2017/11/29
=============================================================================*/

#ifndef _CONTROLPOINT_H_
#define _CONTROLPOINT_H_

/*-----------------------------------------------------------------------------
Class
-----------------------------------------------------------------------------*/
class ControlPoint:public MeshSphere
{
public:
	ControlPoint(int Priolity = 5):MeshSphere(Priolity), m_Actice(false){}

	static ControlPoint* Create(D3DXVECTOR3 position);

	void Initialize(void)override;
	void Uninitialize(void)override;
	void Update(void)override {}
	void Draw(void)override;

	// Setter
	void SetActive(const bool flag){ m_Actice = flag; }

private:
	bool m_Actice;
};

#endif
