#pragma once

class m_IDirectInputDeviceX
{
private:
	IDirectInputDevice7W *ProxyInterface;
	m_IDirectInputDevice7W *WrapperInterface;
	DWORD DirectXVersion;
	REFIID WrapperID;

	bool userDefined_DeviceGain_Enabled;
	DIPROPDWORD dip_gain_set;

	bool userDefined_ConstantGain_Enabled;
	DWORD constant_gain_set;

	bool userDefined_RampGain_Enabled;
	DWORD ramp_gain_set;

	bool userDefined_SquareGain_Enabled;
	DWORD square_gain_set;

	bool userDefined_SineGain_Enabled;
	DWORD sine_gain_set;

	bool userDefined_TriangleGain_Enabled;
	DWORD triangle_gain_set;

public:
	m_IDirectInputDeviceX(IDirectInputDevice7W *aOriginal, DWORD Version, REFIID riid, m_IDirectInputDevice7W *Interface) : ProxyInterface(aOriginal), DirectXVersion(Version), WrapperID(riid), WrapperInterface(Interface)
	{
		//Custom device gain
		{
			std::ifstream ifs("dinput_device_gain.ini", std::ios_base::in);
			userDefined_DeviceGain_Enabled = !ifs.bad();
			if (userDefined_DeviceGain_Enabled)
			{
				unsigned int gain;
				ifs >> gain;
				ifs.close();

				dip_gain_set.diph.dwSize = sizeof(DIPROPDWORD);
				dip_gain_set.diph.dwHeaderSize = sizeof(DIPROPHEADER);
				dip_gain_set.diph.dwObj = 0;
				dip_gain_set.diph.dwHow = DIPH_DEVICE;
				dip_gain_set.dwData = gain;
			}
		}

		//Custom constant gain
		{
			std::ifstream ifs("dinput_constant_gain.ini", std::ios_base::in);
			userDefined_ConstantGain_Enabled = !ifs.bad();
			if (userDefined_ConstantGain_Enabled)
			{
				ifs >> constant_gain_set;
				ifs.close();
			}
		}

		//Custom ramp gain
		{
			std::ifstream ifs("dinput_ramp_gain.ini", std::ios_base::in);
			userDefined_RampGain_Enabled = !ifs.bad();
			if (userDefined_RampGain_Enabled)
			{
				ifs >> ramp_gain_set;
				ifs.close();
			}
		}

		//Custom square gain
		{
			std::ifstream ifs("dinput_square_gain.ini", std::ios_base::in);
			userDefined_SquareGain_Enabled = !ifs.bad();
			if (userDefined_SquareGain_Enabled)
			{
				ifs >> square_gain_set;
				ifs.close();
			}
		}

		//Custom sine gain
		{
			std::ifstream ifs("dinput_sine_gain.ini", std::ios_base::in);
			userDefined_SineGain_Enabled = !ifs.bad();
			if (userDefined_SineGain_Enabled)
			{
				ifs >> sine_gain_set;
				ifs.close();
			}
		}

		//Custom triangle gain
		{
			std::ifstream ifs("dinput_triangle_gain.ini", std::ios_base::in);
			userDefined_TriangleGain_Enabled = !ifs.bad();
			if (userDefined_TriangleGain_Enabled)
			{
				ifs >> triangle_gain_set;
				ifs.close();
			}
		}
	}
	~m_IDirectInputDeviceX() {}

	DWORD GetDirectXVersion() { return DDWRAPPER_TYPEX; }
	REFIID GetWrapperType() { return WrapperID; }
	IDirectInputDevice7W *GetProxyInterface() { return ProxyInterface; }
	m_IDirectInputDevice7W *GetWrapperInterface() { return WrapperInterface; }

	/*** IUnknown methods ***/
	STDMETHOD(QueryInterface)(THIS_ REFIID riid, LPVOID * ppvObj);
	STDMETHOD_(ULONG, AddRef)(THIS);
	STDMETHOD_(ULONG, Release)(THIS);

	/*** IDirectInputDevice methods ***/
	STDMETHOD(GetCapabilities)(THIS_ LPDIDEVCAPS);
	STDMETHOD(EnumObjectsA)(THIS_ LPDIENUMDEVICEOBJECTSCALLBACKA, LPVOID, DWORD);
	STDMETHOD(EnumObjectsW)(THIS_ LPDIENUMDEVICEOBJECTSCALLBACKW, LPVOID, DWORD);
	STDMETHOD(GetProperty)(THIS_ REFGUID, LPDIPROPHEADER);
	STDMETHOD(SetProperty)(THIS_ REFGUID, LPCDIPROPHEADER);
	STDMETHOD(Acquire)(THIS);
	STDMETHOD(Unacquire)(THIS);
	STDMETHOD(GetDeviceState)(THIS_ DWORD, LPVOID);
	STDMETHOD(GetDeviceData)(THIS_ DWORD, LPDIDEVICEOBJECTDATA, LPDWORD, DWORD);
	STDMETHOD(SetDataFormat)(THIS_ LPCDIDATAFORMAT);
	STDMETHOD(SetEventNotification)(THIS_ HANDLE);
	STDMETHOD(SetCooperativeLevel)(THIS_ HWND, DWORD);
	STDMETHOD(GetObjectInfoA)(THIS_ LPDIDEVICEOBJECTINSTANCEA, DWORD, DWORD);
	STDMETHOD(GetObjectInfoW)(THIS_ LPDIDEVICEOBJECTINSTANCEW, DWORD, DWORD);
	STDMETHOD(GetDeviceInfoA)(THIS_ LPDIDEVICEINSTANCEA);
	STDMETHOD(GetDeviceInfoW)(THIS_ LPDIDEVICEINSTANCEW);
	STDMETHOD(RunControlPanel)(THIS_ HWND, DWORD);
	STDMETHOD(Initialize)(THIS_ HINSTANCE, DWORD, REFGUID);

	/*** IDirectInputDevice2 methods ***/
	STDMETHOD(CreateEffect)(THIS_ REFGUID, LPCDIEFFECT, LPDIRECTINPUTEFFECT *, LPUNKNOWN);
	STDMETHOD(EnumEffectsA)(THIS_ LPDIENUMEFFECTSCALLBACKA, LPVOID, DWORD);
	STDMETHOD(EnumEffectsW)(THIS_ LPDIENUMEFFECTSCALLBACKW, LPVOID, DWORD);
	STDMETHOD(GetEffectInfoA)(THIS_ LPDIEFFECTINFOA, REFGUID);
	STDMETHOD(GetEffectInfoW)(THIS_ LPDIEFFECTINFOW, REFGUID);
	STDMETHOD(GetForceFeedbackState)(THIS_ LPDWORD);
	STDMETHOD(SendForceFeedbackCommand)(THIS_ DWORD);
	STDMETHOD(EnumCreatedEffectObjects)(THIS_ LPDIENUMCREATEDEFFECTOBJECTSCALLBACK, LPVOID, DWORD);
	STDMETHOD(Escape)(THIS_ LPDIEFFESCAPE);
	STDMETHOD(Poll)(THIS);
	STDMETHOD(SendDeviceData)(THIS_ DWORD, LPCDIDEVICEOBJECTDATA, LPDWORD, DWORD);

	/*** IDirectInputDevice7 methods ***/
	STDMETHOD(EnumEffectsInFileA)(THIS_ LPCSTR, LPDIENUMEFFECTSINFILECALLBACK, LPVOID, DWORD);
	STDMETHOD(EnumEffectsInFileW)(THIS_ LPCWSTR, LPDIENUMEFFECTSINFILECALLBACK, LPVOID, DWORD);
	STDMETHOD(WriteEffectToFileA)(THIS_ LPCSTR, DWORD, LPDIFILEEFFECT, DWORD);
	STDMETHOD(WriteEffectToFileW)(THIS_ LPCWSTR, DWORD, LPDIFILEEFFECT, DWORD);

	// Helper functions
	IDirectInputDevice7A *GetProxyInterfaceA() { return (IDirectInputDevice7A*)ProxyInterface; }
	IDirectInputDevice7W *GetProxyInterfaceW() { return ProxyInterface; }
};
