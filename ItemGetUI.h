/*=============================================================================

アイテム取得UI[ ItemGetUI.h ]

-------------------------------------------------------------------------------
■  Author
Ohno Takuya

■  Create
2018/01/22
=============================================================================*/

#ifndef _ITEMGETUI_H_
#define _ITEMGETUI_H_

/*-----------------------------------------------------------------------------
Class
-----------------------------------------------------------------------------*/
class ItemGetUI:public Object
{
public:
	ItemGetUI(int priolity):Object(priolity),m_Color(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f)) ,m_Active(false){}

	void Uninitialize(void)override;// 終了

	//Setter
	void SetColor(const D3DXCOLOR color){ m_Color = color; }
	void SetActive(const bool flag){ m_Active = flag; }

private:
	D3DXCOLOR m_Color;
	bool m_Active;// 可視化

protected:
	D3DXCOLOR GetColor(void){ return m_Color; }
	bool GetActive(void){ return m_Active;}
};

#endif
