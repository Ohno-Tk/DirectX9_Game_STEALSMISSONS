/*=============================================================================

�I�u�W�F�N�g����[ Object.h ]

-------------------------------------------------------------------------------

��  Create
2017/11/11
=============================================================================*/

#ifndef _OBJECT_H_
#define _OBJECT_H_

/*-----------------------------------------------------------------------------
	Macro
-----------------------------------------------------------------------------*/
#define PRIOLITY_MAX (6) //	�D�揇��

/*-----------------------------------------------------------------------------
Class
-----------------------------------------------------------------------------*/
class Object
{
public:
	enum OBJECT_TYPE
	{
		OBJECT_TYPE_NONE = 0,	//	�Ȃ�
		OBJECT_TYPE_PLAYER,     // �v���C���[
		OBJECT_TYPE_ENEMY,		//	�G
		OBJECT_TYPEMESHSPHERE,	//	���b�V����
		OBJECT_TYPE_CONTROLPOINT, // ����_
		OBJECT_TYPE_VISION, // ���E
		OBJECT_TYPE_OBSTACLE, // ��Q��
		OBJECT_TYPE_MAX			//	�ő吔
	};

	Object(int Priolity);

	virtual void Initialize(void) = 0;
	virtual void Uninitialize(void) = 0;
	virtual void Update(void) = 0;
	virtual void Draw(void) = 0;

	static void UpdateAll(void); //	�S�I�u�W�F�N�g�̍X�V
	static void DrawAll(void); // �S�I�u�W�F�N�g�̕`��
	static void ReleaseAll(void); // �S�I�u�W�F�N�g�̉��

	// Setter
	void SetPosition(const D3DXVECTOR3 position) { m_Position = position; }

	//	Getter
	D3DXVECTOR3 GetPosition(void) { return m_Position; }
	D3DXVECTOR3* GetPositionPointer(void) { return &m_Position; }

	const OBJECT_TYPE GetObjeType(void)const{ return m_ObjectType; }

	static Object *GetList(int Priority) { return m_Top[Priority]; }
	Object *GetNext(void) { return m_Next; }

private:
	D3DXVECTOR3 m_Position;	//	���W
	bool m_DeleteFlag;	//	�폜�t���O

	OBJECT_TYPE m_ObjectType; // �I�u�W�F�N�g�̎��

	static Object* m_Top[PRIOLITY_MAX];	//	�擪�̃|�C���^
	Object* m_Next;	//	���̃|�C���^

protected:
	// Setter
	void SetObjeType(const OBJECT_TYPE objectType) { m_ObjectType = objectType; }

	void Release(void) { m_DeleteFlag = true; }	//	�����[�X
};

#endif
