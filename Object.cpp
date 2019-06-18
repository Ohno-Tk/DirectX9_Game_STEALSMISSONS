/*=============================================================================

オブジェクト生成[ Object.cpp ]

-------------------------------------------------------------------------------
■  Author
Ohno Takuya

■  Create
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
Object *Object::m_Top[] = { NULL };	// 先頭のポインタ

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
			//	m_Nextの指し示す先のポインタを入れている
			object = object->m_Next;
		}
		object->m_Next = this;
	}

	this->m_Next = NULL;
}

/*-----------------------------------------------------------------------------
Function:   void Object::UpdateAll(void)
Overview:   全オブジェクトの更新
-----------------------------------------------------------------------------*/
void Object::UpdateAll(void)
{
	for (int CntPriolity = 0; CntPriolity < PRIOLITY_MAX; CntPriolity++)
	{

		Object *object = m_Top[CntPriolity];
		Object *objectPrev = m_Top[CntPriolity]; //	前のシーンポインタ
		Object *objectNext; // 次のシーンポインタ

		while (object != NULL)
		{
			object->Update();	//	更新

			object = object->m_Next;
		}
		while (object != NULL)
		{	//	リスト構造を1つずつ調べていく

			objectNext = object->m_Next;

			if (object->m_DeleteFlag == true)
			{	//	削除フラグがtrueだったら

				if (object == m_Top[CntPriolity])
				{
					m_Top[CntPriolity] = object->m_Next;
				}
				else
				{					
					objectPrev->m_Next = object->m_Next;	//	リスト構造のつなぎ変え
				}

				object->Uninitialize();	//	終了
				delete object;		//	削除
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
Overview:   全オブジェクトの描画
-----------------------------------------------------------------------------*/
void Object::DrawAll(void)
{
	for (unsigned int CntPriolity = 0; CntPriolity < PRIOLITY_MAX; CntPriolity++)
	{
		Object *object = m_Top[CntPriolity];

		while (object != NULL)
		{			
			object->Draw();	//	描画
		
			object = object->m_Next;	//	次を指し示すポインタを格納
		}
	}
}

/*-----------------------------------------------------------------------------
Function:   void Object::ReleaseAll(void)
Overview:   全オブジェクトの解放
-----------------------------------------------------------------------------*/
void Object::ReleaseAll(void)
{
	for (unsigned int CntPriolity = 0; CntPriolity < PRIOLITY_MAX; CntPriolity++)
	{

		Object *object = m_Top[CntPriolity];
		Object *objectNext;

		while (object != NULL)
		{
	
			objectNext = object->m_Next; //	次のポインタを保存
			
			object->Uninitialize();	//	終了

			delete object;	//	シーンのデリート

			object = objectNext; //	シーンに次のシーンを入れる

		}	
		m_Top[ CntPriolity ] = NULL; //	トップにNULLをいれる
	}
}