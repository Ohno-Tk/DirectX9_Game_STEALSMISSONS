/*=============================================================================

アイテム表示UI[ ItemUI.h ]

-------------------------------------------------------------------------------
■  Author
Ohno Takuya

■  Create
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
		ITEM_ID_RATION = 0,// レーション
	};

	ItemUI(int priolity):Object(priolity), m_Active(true){}

	void Uninitialize(void)override;// 終了

	virtual void PlusNowPossession(const unsigned int plusValue) = 0;// 現在所持数追加
	virtual void SubNowPossession(const unsigned int subValue) = 0;  // 現在所持数減算

	virtual void Use(void) = 0;// 使用

	//Setter
	void SetActive(const bool flag){ m_Active = flag; }

	// Getter
	ITEM_ID GetItemID(void){ return m_ItemID; }

private:
	bool m_Active;// 可視化
	ITEM_ID m_ItemID;

protected:
	bool GetActive(void){ return m_Active;}
	void SetItemID(const ITEM_ID id){ m_ItemID = id; }
};

#endif
