/*=============================================================================

入力デバイス(DirectX)[ InputDirectX.h ]

-------------------------------------------------------------------------------
■  Author
	Ohno Takuya

■  Create
	2017/10/15
=============================================================================*/

#ifndef _INPUTDIRECTX_H_
#define _INPUTDIRECTX_H_

/*-----------------------------------------------------------------------------
Macro
-----------------------------------------------------------------------------*/
#define NUM_KEY_MAX ( 256 )	//	キーの最大数
#define XBOX_KEY_MAX (16)

/*-----------------------------------------------------------------------------
Class
-----------------------------------------------------------------------------*/
class InputDirectX
{
public:
	InputDirectX():m_DIDevice(NULL){}

	virtual void Initialize(HINSTANCE instance);
	virtual void Uninitialize(void);
	virtual void Update(void) = 0;

protected:
	static LPDIRECTINPUT8 m_DInput;	// DirectInputオブジェクトへのポインタ
	LPDIRECTINPUTDEVICE8 m_DIDevice;	// 入力デバイス(キーボード)へのポインタ
};

class DirectXKeyboard :public InputDirectX
{
public:
	DirectXKeyboard();

	HRESULT Initialize(HINSTANCE instance, HWND wnd);
	void Uninitialize(void);
	void Update(void)override;

	BOOL AnyKey(void); // 全キー判定( プレス )
	BOOL AnyKeyDown(void); // 全キー判定( トリガー )

	//	引数:DIK_WなどDIK_～
	//	キーボードデータ取得
	BOOL GetKeyPress(int nKey) { return (m_KeyState[nKey] & 0x80) ? TRUE : FALSE; } // プレス
	BOOL GetKeyTrigger(int nKey) { return (m_KeyStateTrigger[nKey] & 0x80) ? TRUE : FALSE; } // トリガー
	BOOL GetKeyRepeat(int nKey) { return (m_KeyStateRepeat[nKey] & 0x80) ? TRUE : FALSE; }// リピート
	BOOL GetKeyRelease(int nKey) { return (m_KeyStateRelease[nKey] & 0x80) ? TRUE : FALSE; } // リリース
	void FlushKeyTrigger(int nKey) { m_KeyStateTrigger[nKey] = 0; } // キーボードデータ削除( トリガー )

private:
	BYTE m_KeyState[NUM_KEY_MAX]; // キーボードの入力情報ワーク
	BYTE m_KeyStateTrigger[NUM_KEY_MAX]; // キーボードのトリガー情報ワーク
	BYTE m_KeyStateRelease[NUM_KEY_MAX]; // キーボードのリリース情報ワーク
	BYTE m_KeyStateRepeat[NUM_KEY_MAX];	// キーボードのリピート情報ワーク
	int	 m_KeyStateRepeatCnt[NUM_KEY_MAX]; // キーボードのリピートカウンタ
};

class DirectXMouse :public InputDirectX
{
public:
	enum MOUSE_BUTTOM
	{
		MOUSE_LEFT = 0,	//	左クリック
		MOUSE_RIGHT,	//	右クリック
		MOUSE_WHEEL,	//	ホイール
	};

	void Initialize(HINSTANCE instance, HWND wnd);
	void Uninitialize(void);
	void Update(void)override;

	BOOL AnyKey(void); // 全キー判定( プレス )
	BOOL AnyKeyDown(void); // 全キー判定( トリガー )

	//	引数 : MOUSEBUTTOM構造体を使う
	//	マウスデータ取得
	BOOL GetKeyPress(int Key) { return (m_MouseState.rgbButtons[Key] & 0x80) ? TRUE : FALSE; }//	プレス
	BOOL GetKeyTrigger(int Key) { return (m_MouseStateTrigger.rgbButtons[Key] & 0x80) ? TRUE : FALSE; }//	トリガー
	BOOL GetKeyRepeat(int Key) { return (m_MouseStateRepeat.rgbButtons[Key] & 0x80) ? TRUE : FALSE; }//	リピート
	BOOL GetKeyRelease(int nKey) { return (m_MouseStateRelease.rgbButtons[nKey] & 0x80) ? TRUE : FALSE; }	//	リリース

	// 前フレームからの差分座標
	LONG GetAxisX(void) { return m_MouseState.lX; }
	LONG GetAxisY(void) { return m_MouseState.lY; }
	LONG GetAxisZ(void) { return m_MouseState.lZ; }

	const POINT& GetPosWorld(void) { return m_PosMouseWorld; }// マウスのスクリーン座標取得

private:
	DIMOUSESTATE2 m_MouseState; // マウスの状態を受けるワーク
	DIMOUSESTATE2 m_MouseStateTrigger; // トリガーのワーク
	DIMOUSESTATE2 m_MouseStateRelease; // リリースのワーク
	DIMOUSESTATE2 m_MouseStateRepeat; // リピートのワーク
	POINT		  m_PosMouseWorld; // マウスのスクリーン座標
};

class XInput
{
public:
	enum CONTROLLER_NUM
	{
		CONTROLLER_1 = 0,
		CONTROLLER_2,
		CONTROLLER_3,
		CONTROLLER_4,
		CONTROLLER_MAX
	};
	enum VALUE_TYPE
	{
		LEFT = 0,
		RIGHT,
		TYPE_MAX
	};

	XInput();
	void Update(void);

	BOOL AnyKey(CONTROLLER_NUM Idx); // 全キー判定( プレス )
	BOOL AnyKeyDown(CONTROLLER_NUM Idx); // 全キー判定( トリガー )

	bool GetKeyPress(CONTROLLER_NUM index, WORD Key); // XBOXコントローラーの入力
	bool GetKeyTrigger(CONTROLLER_NUM index, WORD Key); // XBOXコントローラーのトリガー
	bool GetKeyRepeat(CONTROLLER_NUM index, WORD Key); // XBOXコントローラーのリピート
	bool GetKeyRelease(CONTROLLER_NUM index, WORD Key); // XBOXコントローラーのリリース
	void FlushKeyTrigger(CONTROLLER_NUM index, WORD Key);
	D3DXVECTOR2 GetAnalogValue(CONTROLLER_NUM index, XInput::VALUE_TYPE type); // アナログの値を返す(-1～1)
	int GetTriggerValue(CONTROLLER_NUM index, XInput::VALUE_TYPE type); // LTの値を返す(0～255)

	bool GetActive(CONTROLLER_NUM index){return m_Active[index];}

private:
	WORD		m_KeyState[CONTROLLER_MAX][XBOX_KEY_MAX]; // XBOXコントローラーの入力情報ワーク
	WORD		m_KeyStateTrigger[CONTROLLER_MAX][XBOX_KEY_MAX]; // XBOXコントローラーのトリガー情報ワーク
	WORD		m_KeyStateRelease[CONTROLLER_MAX][XBOX_KEY_MAX]; // XBOXコントローラーのリリース情報ワーク
	WORD		m_KeyStateRepeat[CONTROLLER_MAX][XBOX_KEY_MAX];	// XBOXコントローラーのリピート情報ワーク
	WORD		m_KeyStateRepeatCnt[CONTROLLER_MAX][XBOX_KEY_MAX]; // XBOXコントローラーのリピートカウンタ
	D3DXVECTOR2 m_Analog[CONTROLLER_MAX][TYPE_MAX];
	int			m_Trigger[CONTROLLER_MAX][TYPE_MAX];

	bool		m_Active[CONTROLLER_MAX];
};

#endif
