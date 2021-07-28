/*=============================================================================

�A�C�e��[ Item.h ]

-------------------------------------------------------------------------------

��  Create
2018/01/22
=============================================================================*/

#ifndef _ITEM_H_
#define _ITEM_H_

class ItemGetUI;

/*-----------------------------------------------------------------------------
Class
-----------------------------------------------------------------------------*/
class Item:public Object
{
public:
	Item(int priolity):Object(priolity), m_Active(true){}

	void Uninitialize(void)override;// �I��
	void Update(void)override;// �X�V

	//Setter
	void SetActive(bool flag){ m_Active = flag; }

private:
	virtual bool Collision(void) = 0;// �����蔻��

private:
	bool m_Active;// ����

	ItemGetUI* m_ItemGetUI;

protected:
	bool GetActive(void){ return m_Active;}
	void SetItemGetUI(ItemGetUI* object){ m_ItemGetUI = object; }
	ItemGetUI* GetItemGetUI(void){ return m_ItemGetUI; }
};

#endif
