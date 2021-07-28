/*=============================================================================

���̓f�o�C�X(DirectX)[ InputDirectX.cpp ]

-------------------------------------------------------------------------------

��  Create
	2017/10/15
=============================================================================*/

/*-----------------------------------------------------------------------------
Include Files
-----------------------------------------------------------------------------*/
#include "RendererDirectX.h"
#include "InputDirectX.h"

/*-----------------------------------------------------------------------------
Macro
-----------------------------------------------------------------------------*/
#define	COUNT_WAIT_REPEAT	( 20 )	// ���s�[�g�҂�����
#define MOUSE_KEY_MAX ( 8 )	//	�}�E�X�L�[�̍ő吔
#define ANALOG_METER_MAX (32767.0f)

/*-----------------------------------------------------------------------------
Static
-----------------------------------------------------------------------------*/
LPDIRECTINPUT8	InputDirectX::m_DInput = NULL;

void InputDirectX::Initialize(HINSTANCE hInstance)
{
	// DirectInput�I�u�W�F�N�g�̍쐬
	if (!m_DInput)
	{	//	�f�o�C�X������������
		DirectInput8Create(hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&m_DInput, NULL);
	}
}

void InputDirectX::Uninitialize(void)
{
	if (m_DIDevice)
	{	// �f�o�C�X�I�u�W�F�N�g�̊J��
		m_DIDevice->Unacquire(); // �f�o�C�X�ւ̃A�N�Z�X�������
		m_DIDevice->Release();
		m_DIDevice = NULL;
	}

	if (m_DInput)
	{	// DirectInput�I�u�W�F�N�g�̊J��
		m_DInput->Release();
		m_DInput = NULL;
	}
}


DirectXKeyboard::DirectXKeyboard()
{
	// �e���[�N�̃N���A
	ZeroMemory(m_KeyState, sizeof m_KeyState);
	ZeroMemory(m_KeyStateTrigger, sizeof m_KeyStateTrigger);
	ZeroMemory(m_KeyStateRelease, sizeof m_KeyStateRelease);
	ZeroMemory(m_KeyStateRepeat, sizeof m_KeyStateRepeat);
	ZeroMemory(m_KeyStateRepeatCnt, sizeof m_KeyStateRepeatCnt);
}

HRESULT DirectXKeyboard::Initialize(HINSTANCE instance, HWND wnd)
{
	HRESULT hr;

	InputDirectX::Initialize(instance);

	// �f�o�C�X�I�u�W�F�N�g���쐬
	hr = m_DInput->CreateDevice(GUID_SysKeyboard, &m_DIDevice, NULL);
	if (FAILED(hr) || !m_DIDevice )
	{
		MessageBox(wnd, "�L�[�{�[�h������܂���", "InputDirectX.cpp", MB_ICONWARNING);
		return E_FAIL;
	}

	// �f�[�^�t�H�[�}�b�g��ݒ�
	hr = m_DIDevice->SetDataFormat(&c_dfDIKeyboard);
	if (FAILED(hr))
	{
		MessageBox(wnd, "�L�[�{�[�h�̃f�[�^�t�H�[�}�b�g��ݒ�ł��܂���ł����B", "InputDirectX.cpp", MB_ICONWARNING);
		return E_FAIL;
	}

	// �������[�h��ݒ�i�t�H�A�O���E���h����r�����[�h�j
	hr = m_DIDevice->SetCooperativeLevel(wnd, (DISCL_FOREGROUND | DISCL_NONEXCLUSIVE));
	if (FAILED(hr))
	{
		MessageBox(wnd, "�L�[�{�[�h�̋������[�h��ݒ�ł��܂���ł����B", "InputDirectX.cpp", MB_ICONWARNING);
		return E_FAIL;
	}

	// m_pDIDevice�A�N�Z�X�����l��( ���͐���J�n )
	m_DIDevice->Acquire();

	return S_OK;
}

void DirectXKeyboard::Uninitialize(void)
{
	InputDirectX::Uninitialize();
}

void DirectXKeyboard::Update(void)
{
	HRESULT hr;
	BYTE KeyState[NUM_KEY_MAX];

	if (!m_DIDevice){ return; }

	// �f�o�C�X����f�[�^���擾
	hr = m_DIDevice->GetDeviceState(sizeof(KeyState), KeyState);
	if (SUCCEEDED(hr))
	{
		for (int nCntKey = 0; nCntKey < NUM_KEY_MAX; nCntKey++)
		{
			// �L�[�g���K�[ �����[�X���̍쐬
			// 1�t���[���O�̃L�[�󋵂ƍ��̃L�[�󋵂�XOR�������̂����̃L�[�󋵂�AND���Ƃ�
			m_KeyStateTrigger[nCntKey] = (m_KeyState[nCntKey] ^ KeyState[nCntKey]) & KeyState[nCntKey];
			m_KeyStateRelease[nCntKey] = (m_KeyState[nCntKey] ^ KeyState[nCntKey]) & ~KeyState[nCntKey];
			m_KeyStateRepeat[nCntKey] = m_KeyStateTrigger[nCntKey];

			// �L�[���s�[�g���̐���
			if (KeyState[nCntKey])
			{
				m_KeyStateRepeatCnt[nCntKey]++;

				if (m_KeyStateRepeatCnt[nCntKey] >= COUNT_WAIT_REPEAT)
				{
					m_KeyStateRepeat[nCntKey] = KeyState[nCntKey];
				}
			}
			else
			{
				m_KeyStateRepeatCnt[nCntKey] = 0;
				m_KeyStateRepeat[nCntKey] = 0;
			}
			// �L�[����ۑ�
			m_KeyState[nCntKey] = KeyState[nCntKey];
		}
	}
	else
	{
		m_DIDevice->Acquire(); // m_pDIDevice�A�N�Z�X�����l��( ���͐���J�n )
	}
}

BOOL DirectXKeyboard::AnyKey(void)
{
	if (GetKeyPress(DIK_Q)) { return TRUE; }
	else if (GetKeyPress(DIK_W)) { return TRUE; }
	else if (GetKeyPress(DIK_E)) { return TRUE; }
	else if (GetKeyPress(DIK_R)) { return TRUE; }
	else if (GetKeyPress(DIK_T)) { return TRUE; }
	else if (GetKeyPress(DIK_Y)) { return TRUE; }
	else if (GetKeyPress(DIK_U)) { return TRUE; }
	else if (GetKeyPress(DIK_I)) { return TRUE; }
	else if (GetKeyPress(DIK_O)) { return TRUE; }
	else if (GetKeyPress(DIK_P)) { return TRUE; }
	else if (GetKeyPress(DIK_A)) { return TRUE; }
	else if (GetKeyPress(DIK_S)) { return TRUE; }
	else if (GetKeyPress(DIK_D)) { return TRUE; }
	else if (GetKeyPress(DIK_F)) { return TRUE; }
	else if (GetKeyPress(DIK_G)) { return TRUE; }
	else if (GetKeyPress(DIK_H)) { return TRUE; }
	else if (GetKeyPress(DIK_J)) { return TRUE; }
	else if (GetKeyPress(DIK_K)) { return TRUE; }
	else if (GetKeyPress(DIK_L)) { return TRUE; }
	else if (GetKeyPress(DIK_Z)) { return TRUE; }
	else if (GetKeyPress(DIK_X)) { return TRUE; }
	else if (GetKeyPress(DIK_C)) { return TRUE; }
	else if (GetKeyPress(DIK_V)) { return TRUE; }
	else if (GetKeyPress(DIK_B)) { return TRUE; }
	else if (GetKeyPress(DIK_N)) { return TRUE; }
	else if (GetKeyPress(DIK_M)) { return TRUE; }
	else if (GetKeyPress(DIK_0)) { return TRUE; }
	else if (GetKeyPress(DIK_1)) { return TRUE; }
	else if (GetKeyPress(DIK_2)) { return TRUE; }
	else if (GetKeyPress(DIK_3)) { return TRUE; }
	else if (GetKeyPress(DIK_4)) { return TRUE; }
	else if (GetKeyPress(DIK_5)) { return TRUE; }
	else if (GetKeyPress(DIK_6)) { return TRUE; }
	else if (GetKeyPress(DIK_7)) { return TRUE; }
	else if (GetKeyPress(DIK_8)) { return TRUE; }
	else if (GetKeyPress(DIK_9)) { return TRUE; }
	else if (GetKeyPress(DIK_F1)) { return TRUE; }
	else if (GetKeyPress(DIK_F2)) { return TRUE; }
	else if (GetKeyPress(DIK_F3)) { return TRUE; }
	else if (GetKeyPress(DIK_F4)) { return TRUE; }
	else if (GetKeyPress(DIK_F5)) { return TRUE; }
	else if (GetKeyPress(DIK_F6)) { return TRUE; }
	else if (GetKeyPress(DIK_F7)) { return TRUE; }
	else if (GetKeyPress(DIK_F8)) { return TRUE; }
	else if (GetKeyPress(DIK_F9)) { return TRUE; }
	else if (GetKeyPress(DIK_F10)) { return TRUE; }
	else if (GetKeyPress(DIK_F11)) { return TRUE; }
	else if (GetKeyPress(DIK_F12)) { return TRUE; }
	else if (GetKeyPress(DIK_SPACE)) { return TRUE; }
	else if (GetKeyPress(DIK_RETURN)) { return TRUE; }
	else if (GetKeyPress(DIK_UPARROW)) { return TRUE; }
	else if (GetKeyPress(DIK_DOWNARROW)) { return TRUE; }
	else if (GetKeyPress(DIK_LEFTARROW)) { return TRUE; }
	else if (GetKeyPress(DIK_RIGHTARROW)) { return TRUE; }
	else if (GetKeyPress(DIK_TAB)) { return TRUE; }
	else if (GetKeyPress(DIK_LSHIFT)) { return TRUE; }
	else if (GetKeyPress(DIK_RSHIFT)) { return TRUE; }
	else if (GetKeyPress(DIK_LCONTROL)) { return TRUE; }
	else if (GetKeyPress(DIK_RCONTROL)) { return TRUE; }
	else if (GetKeyPress(DIK_LALT)) { return TRUE; }
	else if (GetKeyPress(DIK_RALT)) { return TRUE; }

	return FALSE;
}

BOOL DirectXKeyboard::AnyKeyDown(void)
{
	if (GetKeyTrigger(DIK_Q)) { return TRUE; }
	else if (GetKeyTrigger(DIK_W)) { return TRUE; }
	else if (GetKeyTrigger(DIK_E)) { return TRUE; }
	else if (GetKeyTrigger(DIK_R)) { return TRUE; }
	else if (GetKeyTrigger(DIK_T)) { return TRUE; }
	else if (GetKeyTrigger(DIK_Y)) { return TRUE; }
	else if (GetKeyTrigger(DIK_U)) { return TRUE; }
	else if (GetKeyTrigger(DIK_I)) { return TRUE; }
	else if (GetKeyTrigger(DIK_O)) { return TRUE; }
	else if (GetKeyTrigger(DIK_P)) { return TRUE; }
	else if (GetKeyTrigger(DIK_A)) { return TRUE; }
	else if (GetKeyTrigger(DIK_S)) { return TRUE; }
	else if (GetKeyTrigger(DIK_D)) { return TRUE; }
	else if (GetKeyTrigger(DIK_F)) { return TRUE; }
	else if (GetKeyTrigger(DIK_G)) { return TRUE; }
	else if (GetKeyTrigger(DIK_H)) { return TRUE; }
	else if (GetKeyTrigger(DIK_J)) { return TRUE; }
	else if (GetKeyTrigger(DIK_K)) { return TRUE; }
	else if (GetKeyTrigger(DIK_L)) { return TRUE; }
	else if (GetKeyTrigger(DIK_Z)) { return TRUE; }
	else if (GetKeyTrigger(DIK_X)) { return TRUE; }
	else if (GetKeyTrigger(DIK_C)) { return TRUE; }
	else if (GetKeyTrigger(DIK_V)) { return TRUE; }
	else if (GetKeyTrigger(DIK_B)) { return TRUE; }
	else if (GetKeyTrigger(DIK_N)) { return TRUE; }
	else if (GetKeyTrigger(DIK_M)) { return TRUE; }
	else if (GetKeyTrigger(DIK_0)) { return TRUE; }
	else if (GetKeyTrigger(DIK_1)) { return TRUE; }
	else if (GetKeyTrigger(DIK_2)) { return TRUE; }
	else if (GetKeyTrigger(DIK_3)) { return TRUE; }
	else if (GetKeyTrigger(DIK_4)) { return TRUE; }
	else if (GetKeyTrigger(DIK_5)) { return TRUE; }
	else if (GetKeyTrigger(DIK_6)) { return TRUE; }
	else if (GetKeyTrigger(DIK_7)) { return TRUE; }
	else if (GetKeyTrigger(DIK_8)) { return TRUE; }
	else if (GetKeyTrigger(DIK_9)) { return TRUE; }
	else if (GetKeyTrigger(DIK_F1)) { return TRUE; }
	else if (GetKeyTrigger(DIK_F2)) { return TRUE; }
	else if (GetKeyTrigger(DIK_F3)) { return TRUE; }
	else if (GetKeyTrigger(DIK_F4)) { return TRUE; }
	else if (GetKeyTrigger(DIK_F5)) { return TRUE; }
	else if (GetKeyTrigger(DIK_F6)) { return TRUE; }
	else if (GetKeyTrigger(DIK_F7)) { return TRUE; }
	else if (GetKeyTrigger(DIK_F8)) { return TRUE; }
	else if (GetKeyTrigger(DIK_F9)) { return TRUE; }
	else if (GetKeyTrigger(DIK_F10)) { return TRUE; }
	else if (GetKeyTrigger(DIK_F11)) { return TRUE; }
	else if (GetKeyTrigger(DIK_F12)) { return TRUE; }
	else if (GetKeyTrigger(DIK_SPACE)) { return TRUE; }
	else if (GetKeyTrigger(DIK_RETURN)) { return TRUE; }
	else if (GetKeyTrigger(DIK_UPARROW)) { return TRUE; }
	else if (GetKeyTrigger(DIK_DOWNARROW)) { return TRUE; }
	else if (GetKeyTrigger(DIK_LEFTARROW)) { return TRUE; }
	else if (GetKeyTrigger(DIK_RIGHTARROW)) { return TRUE; }
	else if (GetKeyTrigger(DIK_TAB)) { return TRUE; }
	else if (GetKeyTrigger(DIK_LSHIFT)) { return TRUE; }
	else if (GetKeyTrigger(DIK_RSHIFT)) { return TRUE; }
	else if (GetKeyTrigger(DIK_LCONTROL)) { return TRUE; }
	else if (GetKeyTrigger(DIK_RCONTROL)) { return TRUE; }
	else if (GetKeyTrigger(DIK_LALT)) { return TRUE; }
	else if (GetKeyTrigger(DIK_RALT)) { return TRUE; }

	return FALSE;
}


void DirectXMouse::Initialize(HINSTANCE instance, HWND wnd)
{
	HRESULT hr;

	// ���͏����̏�����
	InputDirectX::Initialize(instance);

	// �f�o�C�X�I�u�W�F�N�g�𐶐�
	hr = m_DInput->CreateDevice(GUID_SysMouse, &m_DIDevice, NULL);
	if (FAILED(hr) || !m_DIDevice)
	{
		MessageBox(wnd, "�}�E�X������܂���", "InputDirectX.cpp", MB_OK);
	}

	// �f�[�^�t�H�[�}�b�g���w��
	hr = m_DIDevice->SetDataFormat(&c_dfDIMouse2);
	if (FAILED(hr))
	{
		MessageBox(wnd, "�}�E�X�̃f�[�^�t�H�[�}�b�g", "InputDirectX.cpp", MB_OK);
	}

	// �������[�h��ݒ�(�t�H�A�O�����h����r��
	hr = m_DIDevice->SetCooperativeLevel(wnd, (DISCL_FOREGROUND | DISCL_NONEXCLUSIVE));
	if (FAILED(hr))
	{
		MessageBox(wnd, "�}�E�X�̋������[�h��ݒ�", "InputDirectX.cpp", MB_OK);
	}

	// �f�o�C�X�̐ݒ�
	DIPROPDWORD dipdw;

	dipdw.diph.dwSize = sizeof(dipdw);
	dipdw.diph.dwHeaderSize = sizeof(dipdw.diph);
	dipdw.diph.dwObj = 0;
	dipdw.diph.dwHow = DIPH_DEVICE;
	dipdw.dwData = DIPROPAXISMODE_REL;

	hr = m_DIDevice->SetProperty(DIPROP_AXISMODE, &dipdw.diph);

	if (FAILED(hr))
	{
		MessageBox(wnd, "�}�E�X�̃f�o�C�X�ݒ�Ɏ��s", "InputDirectX.cpp", MB_OK);
	}

	// �L�[�{�[�h�փA�N�Z�X�����l��(���͐���J�n)
	m_DIDevice->Acquire();

	//	�}�E�X�̎��̏�����
	m_MouseState.lX = (LONG)0.0f;
	m_MouseState.lY = (LONG)0.0f;
	m_MouseState.lZ = (LONG)0.0f;
}

void DirectXMouse::Uninitialize(void)
{
	InputDirectX::Uninitialize();
}

void DirectXMouse::Update(void)
{
	HRESULT hr;
	DIMOUSESTATE2 mouseState;

	if (!m_DIDevice) return;

	// �f�o�C�X����f�[�^���擾
	hr = m_DIDevice->GetDeviceState(sizeof(mouseState), &mouseState);

	if (SUCCEEDED(hr))
	{
		m_MouseStateTrigger.lX = ((m_MouseState.lX ^ mouseState.lX) & mouseState.lX);
		m_MouseStateTrigger.lY = ((m_MouseState.lY ^ mouseState.lY) & mouseState.lY);
		m_MouseStateTrigger.lZ = ((m_MouseState.lZ ^ mouseState.lZ) & mouseState.lZ);

		for (int nCntKey = 0; nCntKey < MOUSE_KEY_MAX; nCntKey++)
		{
			m_MouseStateTrigger.rgbButtons[nCntKey] = ((m_MouseState.rgbButtons[nCntKey] ^ mouseState.rgbButtons[nCntKey]) & mouseState.rgbButtons[nCntKey]);
		}

		m_MouseState = mouseState;

		// �X�N���[�����W���擾
		GetCursorPos(&m_PosMouseWorld);
	}
	else
	{
		m_DIDevice->Acquire();	// m_pDIDevice�A�N�Z�X�����l��( ���͐���J�n )
	}
}

BOOL DirectXMouse::AnyKey(void)
{
	if (GetKeyPress(MOUSE_LEFT)) { return TRUE; }
	else if (GetKeyPress(MOUSE_RIGHT)) { return TRUE; }
	else if (GetKeyPress(MOUSE_WHEEL)) { return TRUE; }

	return FALSE;
}

BOOL DirectXMouse::AnyKeyDown(void)
{
	if (GetKeyTrigger(MOUSE_LEFT)) { return TRUE; }
	else if (GetKeyTrigger(MOUSE_RIGHT)) { return TRUE; }
	else if (GetKeyTrigger(MOUSE_WHEEL)) { return TRUE; }

	return FALSE;
}


XInput::XInput()
{
	for(unsigned int i=0; i<(int)CONTROLLER_MAX; i++)
	{
		m_Active[i] = false;
	}

	ZeroMemory(m_KeyState, sizeof m_KeyState);
	ZeroMemory(m_KeyStateTrigger, sizeof m_KeyStateTrigger);
	ZeroMemory(m_KeyStateRelease, sizeof m_KeyStateRelease);
	ZeroMemory(m_KeyStateRepeat, sizeof m_KeyStateRepeat);
	ZeroMemory(m_KeyStateRepeatCnt, sizeof m_KeyStateRepeatCnt);
}

void XInput::Update(void)
{
	XINPUT_STATE State;

	WORD counter;
	DWORD result;

	for (int nCount = 0; nCount < (int)CONTROLLER_MAX; nCount++)
	{
		counter = 1;

		ZeroMemory(&State, sizeof(State));
		result = XInputGetState(nCount, &State);

		if(result == ERROR_SUCCESS)
		{// �R���g���[�����ڑ�����Ă��邩
			m_Active[nCount] = true;
		}
		else
		{
			m_Active[nCount] = false;
		}

		m_Analog[nCount][LEFT] = D3DXVECTOR2(State.Gamepad.sThumbLX / ANALOG_METER_MAX, State.Gamepad.sThumbLY / ANALOG_METER_MAX);
		m_Analog[nCount][RIGHT] = D3DXVECTOR2(State.Gamepad.sThumbRX / ANALOG_METER_MAX, State.Gamepad.sThumbRY / ANALOG_METER_MAX);

		m_Trigger[nCount][LEFT] = State.Gamepad.bLeftTrigger;
		m_Trigger[nCount][RIGHT] = State.Gamepad.bRightTrigger;

		for (WORD nCntKey = 0; nCntKey < XBOX_KEY_MAX; nCntKey++)
		{
			m_KeyStateTrigger[nCount][nCntKey] = (m_KeyState[nCount][nCntKey] ^ (State.Gamepad.wButtons & counter)) & (State.Gamepad.wButtons & counter);
			m_KeyStateRelease[nCount][nCntKey] = (m_KeyState[nCount][nCntKey] ^ (State.Gamepad.wButtons & counter)) & ~(State.Gamepad.wButtons & counter);
			m_KeyStateRepeat[nCount][nCntKey] = m_KeyStateTrigger[nCount][nCntKey];

			if ((State.Gamepad.wButtons & counter))
			{
				m_KeyStateRepeatCnt[nCount][nCntKey]++;
				if (m_KeyStateRepeatCnt[nCount][nCntKey] >= COUNT_WAIT_REPEAT)
				{
					m_KeyStateRepeat[nCount][nCntKey] = (State.Gamepad.wButtons & counter);
				}
			}
			else
			{
				m_KeyStateRepeatCnt[nCount][nCntKey] = 0;
				m_KeyStateRepeat[nCount][nCntKey] = 0;
			}
			m_KeyState[nCount][nCntKey] = (State.Gamepad.wButtons & counter);
			counter *= 2;
		}
	}
}

BOOL XInput::AnyKey(CONTROLLER_NUM index)
{
	if (GetKeyPress(index, XINPUT_GAMEPAD_DPAD_UP)) { return TRUE; }
	else if (GetKeyPress(index, XINPUT_GAMEPAD_DPAD_DOWN)) { return TRUE; }
	else if (GetKeyPress(index, XINPUT_GAMEPAD_DPAD_LEFT)) { return TRUE; }
	else if (GetKeyPress(index, XINPUT_GAMEPAD_DPAD_RIGHT)) { return TRUE; }
	else if (GetKeyPress(index, XINPUT_GAMEPAD_START)) { return TRUE; }
	else if (GetKeyPress(index, XINPUT_GAMEPAD_BACK)) { return TRUE; }
	else if (GetKeyPress(index, XINPUT_GAMEPAD_LEFT_THUMB)) { return TRUE; }
	else if (GetKeyPress(index, XINPUT_GAMEPAD_RIGHT_THUMB)) { return TRUE; }
	else if (GetKeyPress(index, XINPUT_GAMEPAD_LEFT_SHOULDER)) { return TRUE; }
	else if (GetKeyPress(index, XINPUT_GAMEPAD_RIGHT_SHOULDER)) { return TRUE; }
	else if (GetKeyPress(index, XINPUT_GAMEPAD_A)) { return TRUE; }
	else if (GetKeyPress(index, XINPUT_GAMEPAD_B)) { return TRUE; }
	else if (GetKeyPress(index, XINPUT_GAMEPAD_X)) { return TRUE; }
	else if (GetKeyPress(index, XINPUT_GAMEPAD_Y)) { return TRUE; }

	return FALSE;
}

BOOL XInput::AnyKeyDown(CONTROLLER_NUM index)
{
	if (GetKeyTrigger(index, XINPUT_GAMEPAD_DPAD_UP)) { return TRUE; }
	else if (GetKeyTrigger(index, XINPUT_GAMEPAD_DPAD_DOWN)) { return TRUE; }
	else if (GetKeyTrigger(index, XINPUT_GAMEPAD_DPAD_LEFT)) { return TRUE; }
	else if (GetKeyTrigger(index, XINPUT_GAMEPAD_DPAD_RIGHT)) { return TRUE; }
	else if (GetKeyTrigger(index, XINPUT_GAMEPAD_START)) { return TRUE; }
	else if (GetKeyTrigger(index, XINPUT_GAMEPAD_BACK)) { return TRUE; }
	else if (GetKeyTrigger(index, XINPUT_GAMEPAD_LEFT_THUMB)) { return TRUE; }
	else if (GetKeyTrigger(index, XINPUT_GAMEPAD_RIGHT_THUMB)) { return TRUE; }
	else if (GetKeyTrigger(index, XINPUT_GAMEPAD_LEFT_SHOULDER)) { return TRUE; }
	else if (GetKeyTrigger(index, XINPUT_GAMEPAD_RIGHT_SHOULDER)) { return TRUE; }
	else if (GetKeyTrigger(index, XINPUT_GAMEPAD_A)) { return TRUE; }
	else if (GetKeyTrigger(index, XINPUT_GAMEPAD_B)) { return TRUE; }
	else if (GetKeyTrigger(index, XINPUT_GAMEPAD_X)) { return TRUE; }
	else if (GetKeyTrigger(index, XINPUT_GAMEPAD_Y)) { return TRUE; }

	return FALSE;
}

//=============================================================================
// XBOX�R���g���[���[�f�[�^�擾(�v���X)
//=============================================================================
bool XInput::GetKeyPress(CONTROLLER_NUM index, WORD Key)
{
	WORD nkey = 0;

	while (Key > 1)
	{
		Key /= 2;
		nkey++;
	}

	return (m_KeyState[index][nkey]) ? TRUE : FALSE;
}
//=============================================================================
// XBOX�R���g���[���[�f�[�^�擾(�g���K�[)
//=============================================================================
bool XInput::GetKeyTrigger(CONTROLLER_NUM index, WORD Key)
{
	WORD nkey = 0;

	while (Key > 1)
	{
		Key /= 2;
		nkey++;
	}
	return (m_KeyStateTrigger[index][nkey]) ? TRUE : FALSE;
}

//=============================================================================
// XBOX�R���g���[���[�f�[�^�擾(�����[�X)
//=============================================================================
bool XInput::GetKeyRelease(CONTROLLER_NUM index, WORD Key)
{
	WORD nkey = 0;

	while (Key > 1)
	{
		Key /= 2;
		nkey++;
	}
	return (m_KeyStateRelease[index][nkey] != 0) ? TRUE : FALSE;
}

//=============================================================================
// XBOX�R���g���[���[�f�[�^�擾(���s�[�g)
//=============================================================================
bool XInput::GetKeyRepeat(CONTROLLER_NUM index, WORD Key)
{
	WORD nkey = 0;

	while (Key > 1)
	{
		Key /= 2;
		nkey++;
	}

	return (m_KeyStateRepeat[index][nkey] != 0) ? TRUE : FALSE;
}

//=============================================================================
// XBOX�R���g���[���[�f�[�^�폜(�g���K�[)
//=============================================================================
void XInput::FlushKeyTrigger(CONTROLLER_NUM index, WORD Key)
{
	WORD nkey = 0;

	while (Key > 1)
	{
		Key /= 2;
		nkey++;
	}

	m_KeyStateTrigger[index][nkey] = 0;
}
//=============================================================================
// �A�i���O�l
//=============================================================================
D3DXVECTOR2 XInput::GetAnalogValue(CONTROLLER_NUM index, XInput::VALUE_TYPE type)
{
	return m_Analog[index][type];
}
//=============================================================================
// �g���K�[�l
//=============================================================================
int XInput::GetTriggerValue(CONTROLLER_NUM index, XInput::VALUE_TYPE type)
{
	return m_Trigger[index][type];
}