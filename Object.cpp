/*=============================================================================

�I�u�W�F�N�g����[ Object.cpp ]

-------------------------------------------------------------------------------

��  Create
2017/11/11
=============================================================================*/

/*-----------------------------------------------------------------------------
Include Files
-----------------------------------------------------------------------------*/
#include "FrameworkBase\Common.h"
#include "FrameworkBase\RendererDirectX.h"
#include "Object.h"

/*-----------------------------------------------------------------------------
Static
-----------------------------------------------------------------------------*/
Object *Object::m_Top[] = { NULL };	// �擪�̃|�C���^

Object::Object(int Priolity)
{
	m_Position = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	m_ObjectType = OBJECT_TYPE_NONE;

	m_DeleteFlag = false;

	if (m_Top[Priolity] == NULL)
	{
		m_Top[Priolity] = this;
	}
	else
	{
		Object *object = m_Top[Priolity];

		while (object->m_Next != NULL)
		{
			//	m_Next�̎w��������̃|�C���^�����Ă���
			object = object->m_Next;
		}
		object->m_Next = this;
	}

	this->m_Next = NULL;
}

/*-----------------------------------------------------------------------------
Function:   void Object::UpdateAll(void)
Overview:   �S�I�u�W�F�N�g�̍X�V
-----------------------------------------------------------------------------*/
void Object::UpdateAll(void)
{
	for (int CntPriolity = 0; CntPriolity < PRIOLITY_MAX; CntPriolity++)
	{

		Object *object = m_Top[CntPriolity];
		Object *objectPrev = m_Top[CntPriolity]; //	�O�̃V�[���|�C���^
		Object *objectNext; // ���̃V�[���|�C���^

		while (object != NULL)
		{
			object->Update();	//	�X�V

			object = object->m_Next;
		}
		while (object != NULL)
		{	//	���X�g�\����1�����ׂĂ���

			objectNext = object->m_Next;

			if (object->m_DeleteFlag == true)
			{	//	�폜�t���O��true��������

				if (object == m_Top[CntPriolity])
				{
					m_Top[CntPriolity] = object->m_Next;
				}
				else
				{					
					objectPrev->m_Next = object->m_Next;	//	���X�g�\���̂Ȃ��ς�
				}

				object->Uninitialize();	//	�I��
				delete object;		//	�폜
			}
			else
			{
				objectPrev = object;
			}
			object = objectNext;
		}
	}
}

/*-----------------------------------------------------------------------------
Function:   void Object::DrawAll(void)
Overview:   �S�I�u�W�F�N�g�̕`��
-----------------------------------------------------------------------------*/
void Object::DrawAll(void)
{
	for (unsigned int CntPriolity = 0; CntPriolity < PRIOLITY_MAX; CntPriolity++)
	{
		Object *object = m_Top[CntPriolity];

		while (object != NULL)
		{			
			object->Draw();	//	�`��
		
			object = object->m_Next;	//	�����w�������|�C���^���i�[
		}
	}
}

/*-----------------------------------------------------------------------------
Function:   void Object::ReleaseAll(void)
Overview:   �S�I�u�W�F�N�g�̉��
-----------------------------------------------------------------------------*/
void Object::ReleaseAll(void)
{
	for (unsigned int CntPriolity = 0; CntPriolity < PRIOLITY_MAX; CntPriolity++)
	{

		Object *object = m_Top[CntPriolity];
		Object *objectNext;

		while (object != NULL)
		{
	
			objectNext = object->m_Next; //	���̃|�C���^��ۑ�
			
			object->Uninitialize();	//	�I��

			delete object;	//	�V�[���̃f���[�g

			object = objectNext; //	�V�[���Ɏ��̃V�[��������

		}	
		m_Top[ CntPriolity ] = NULL; //	�g�b�v��NULL�������
	}
}