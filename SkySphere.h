/*=============================================================================

�X�J�C�X�t�B�A[ SkySphere.h ]

-------------------------------------------------------------------------------

��  Create
2017/11/15
=============================================================================*/

#ifndef _SKYSPHERE_H_
#define _SKYSPHERE_H_

/*-----------------------------------------------------------------------------
Class
-----------------------------------------------------------------------------*/
class SkySphere:public MeshSphere
{
public:
	SkySphere(int Priolity = 1):MeshSphere(Priolity){}

	static SkySphere* Create(void);

	void Initialize(void)override;
	void Uninitialize(void)override;
	void Update(void)override;
	void Draw(void)override;
};

#endif
