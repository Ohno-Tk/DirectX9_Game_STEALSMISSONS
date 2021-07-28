/*=============================================================================

�A�C�e���\��UI[ ItemUI.h ]

-------------------------------------------------------------------------------

��  Create
2018/01/24
=============================================================================*/

#ifndef _ITEMUI_H_
#define _ITEMUI_H_

/*-----------------------------------------------------------------------------
Class
-----------------------------------------------------------------------------*/
class ItemUI:public Object
{
public:
	enum ITEM_ID
	{
		ITEM_ID_RATION = 0,// ���[�V����
	};

	ItemUI(int priolity):Object(priolity), m_Active(true){}

	void Uninitialize(void)override;// �I��

	virtual void PlusNowPossession(const unsigned int plusValue) = 0;// ���ݏ������ǉ�
	virtual void SubNowPossession(const unsigned int subValue) = 0;  // ���ݏ��������Z

	virtual void Use(void) = 0;// �g�p

	//Setter
	void SetActive(const bool flag){ m_Active = flag; }

	// Getter
	ITEM_ID GetItemID(void){ return m_ItemID; }

private:
	bool m_Active;// ����
	ITEM_ID m_ItemID;

protected:
	bool GetActive(void){ return m_Active;}
	void SetItemID(const ITEM_ID id){ m_ItemID = id; }
};

#endif
