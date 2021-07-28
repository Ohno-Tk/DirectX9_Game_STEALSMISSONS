/*=============================================================================

���̓f�o�C�X(DirectX)[ InputDirectX.h ]

-------------------------------------------------------------------------------

��  Create
	2017/10/15
=============================================================================*/

#ifndef _INPUTDIRECTX_H_
#define _INPUTDIRECTX_H_

/*-----------------------------------------------------------------------------
Macro
-----------------------------------------------------------------------------*/
#define NUM_KEY_MAX ( 256 )	//	�L�[�̍ő吔
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
	static LPDIRECTINPUT8 m_DInput;	// DirectInput�I�u�W�F�N�g�ւ̃|�C���^
	LPDIRECTINPUTDEVICE8 m_DIDevice;	// ���̓f�o�C�X(�L�[�{�[�h)�ւ̃|�C���^
};

class DirectXKeyboard :public InputDirectX
{
public:
	DirectXKeyboard();

	HRESULT Initialize(HINSTANCE instance, HWND wnd);
	void Uninitialize(void);
	void Update(void)override;

	BOOL AnyKey(void); // �S�L�[����( �v���X )
	BOOL AnyKeyDown(void); // �S�L�[����( �g���K�[ )

	//	����:DIK_W�Ȃ�DIK_�`
	//	�L�[�{�[�h�f�[�^�擾
	BOOL GetKeyPress(int nKey) { return (m_KeyState[nKey] & 0x80) ? TRUE : FALSE; } // �v���X
	BOOL GetKeyTrigger(int nKey) { return (m_KeyStateTrigger[nKey] & 0x80) ? TRUE : FALSE; } // �g���K�[
	BOOL GetKeyRepeat(int nKey) { return (m_KeyStateRepeat[nKey] & 0x80) ? TRUE : FALSE; }// ���s�[�g
	BOOL GetKeyRelease(int nKey) { return (m_KeyStateRelease[nKey] & 0x80) ? TRUE : FALSE; } // �����[�X
	void FlushKeyTrigger(int nKey) { m_KeyStateTrigger[nKey] = 0; } // �L�[�{�[�h�f�[�^�폜( �g���K�[ )

private:
	BYTE m_KeyState[NUM_KEY_MAX]; // �L�[�{�[�h�̓��͏�񃏁[�N
	BYTE m_KeyStateTrigger[NUM_KEY_MAX]; // �L�[�{�[�h�̃g���K�[��񃏁[�N
	BYTE m_KeyStateRelease[NUM_KEY_MAX]; // �L�[�{�[�h�̃����[�X��񃏁[�N
	BYTE m_KeyStateRepeat[NUM_KEY_MAX];	// �L�[�{�[�h�̃��s�[�g��񃏁[�N
	int	 m_KeyStateRepeatCnt[NUM_KEY_MAX]; // �L�[�{�[�h�̃��s�[�g�J�E���^
};

class DirectXMouse :public InputDirectX
{
public:
	enum MOUSE_BUTTOM
	{
		MOUSE_LEFT = 0,	//	���N���b�N
		MOUSE_RIGHT,	//	�E�N���b�N
		MOUSE_WHEEL,	//	�z�C�[��
	};

	void Initialize(HINSTANCE instance, HWND wnd);
	void Uninitialize(void);
	void Update(void)override;

	BOOL AnyKey(void); // �S�L�[����( �v���X )
	BOOL AnyKeyDown(void); // �S�L�[����( �g���K�[ )

	//	���� : MOUSEBUTTOM�\���̂��g��
	//	�}�E�X�f�[�^�擾
	BOOL GetKeyPress(int Key) { return (m_MouseState.rgbButtons[Key] & 0x80) ? TRUE : FALSE; }//	�v���X
	BOOL GetKeyTrigger(int Key) { return (m_MouseStateTrigger.rgbButtons[Key] & 0x80) ? TRUE : FALSE; }//	�g���K�[
	BOOL GetKeyRepeat(int Key) { return (m_MouseStateRepeat.rgbButtons[Key] & 0x80) ? TRUE : FALSE; }//	���s�[�g
	BOOL GetKeyRelease(int nKey) { return (m_MouseStateRelease.rgbButtons[nKey] & 0x80) ? TRUE : FALSE; }	//	�����[�X

	// �O�t���[������̍������W
	LONG GetAxisX(void) { return m_MouseState.lX; }
	LONG GetAxisY(void) { return m_MouseState.lY; }
	LONG GetAxisZ(void) { return m_MouseState.lZ; }

	const POINT& GetPosWorld(void) { return m_PosMouseWorld; }// �}�E�X�̃X�N���[�����W�擾

private:
	DIMOUSESTATE2 m_MouseState; // �}�E�X�̏�Ԃ��󂯂郏�[�N
	DIMOUSESTATE2 m_MouseStateTrigger; // �g���K�[�̃��[�N
	DIMOUSESTATE2 m_MouseStateRelease; // �����[�X�̃��[�N
	DIMOUSESTATE2 m_MouseStateRepeat; // ���s�[�g�̃��[�N
	POINT		  m_PosMouseWorld; // �}�E�X�̃X�N���[�����W
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

	BOOL AnyKey(CONTROLLER_NUM Idx); // �S�L�[����( �v���X )
	BOOL AnyKeyDown(CONTROLLER_NUM Idx); // �S�L�[����( �g���K�[ )

	bool GetKeyPress(CONTROLLER_NUM index, WORD Key); // XBOX�R���g���[���[�̓���
	bool GetKeyTrigger(CONTROLLER_NUM index, WORD Key); // XBOX�R���g���[���[�̃g���K�[
	bool GetKeyRepeat(CONTROLLER_NUM index, WORD Key); // XBOX�R���g���[���[�̃��s�[�g
	bool GetKeyRelease(CONTROLLER_NUM index, WORD Key); // XBOX�R���g���[���[�̃����[�X
	void FlushKeyTrigger(CONTROLLER_NUM index, WORD Key);
	D3DXVECTOR2 GetAnalogValue(CONTROLLER_NUM index, XInput::VALUE_TYPE type); // �A�i���O�̒l��Ԃ�(-1�`1)
	int GetTriggerValue(CONTROLLER_NUM index, XInput::VALUE_TYPE type); // LT�̒l��Ԃ�(0�`255)

	bool GetActive(CONTROLLER_NUM index){return m_Active[index];}

private:
	WORD		m_KeyState[CONTROLLER_MAX][XBOX_KEY_MAX]; // XBOX�R���g���[���[�̓��͏�񃏁[�N
	WORD		m_KeyStateTrigger[CONTROLLER_MAX][XBOX_KEY_MAX]; // XBOX�R���g���[���[�̃g���K�[��񃏁[�N
	WORD		m_KeyStateRelease[CONTROLLER_MAX][XBOX_KEY_MAX]; // XBOX�R���g���[���[�̃����[�X��񃏁[�N
	WORD		m_KeyStateRepeat[CONTROLLER_MAX][XBOX_KEY_MAX];	// XBOX�R���g���[���[�̃��s�[�g��񃏁[�N
	WORD		m_KeyStateRepeatCnt[CONTROLLER_MAX][XBOX_KEY_MAX]; // XBOX�R���g���[���[�̃��s�[�g�J�E���^
	D3DXVECTOR2 m_Analog[CONTROLLER_MAX][TYPE_MAX];
	int			m_Trigger[CONTROLLER_MAX][TYPE_MAX];

	bool		m_Active[CONTROLLER_MAX];
};

#endif
