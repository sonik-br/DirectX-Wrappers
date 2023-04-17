#pragma once

class m_IDirectInputDevice8A : public IDirectInputDevice8A, public AddressLookupTableObject
{
private:
	IDirectInputDevice8A *ProxyInterface;
	
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
	m_IDirectInputDevice8A(IDirectInputDevice8A *aOriginal) : ProxyInterface(aOriginal)
	{
		ProxyAddressLookupTable.SaveAddress(this, ProxyInterface);

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
	~m_IDirectInputDevice8A()
	{
		ProxyAddressLookupTable.DeleteAddress(this);
	}

	IDirectInputDevice8A *GetProxyInterface() { return ProxyInterface; }

	/*** IUnknown methods ***/
	STDMETHOD(QueryInterface)(THIS_ REFIID riid, LPVOID * ppvObj);
	STDMETHOD_(ULONG, AddRef)(THIS);
	STDMETHOD_(ULONG, Release)(THIS);

	/*** IDirectInputDevice8A methods ***/
	STDMETHOD(GetCapabilities)(THIS_ LPDIDEVCAPS);
	STDMETHOD(EnumObjects)(THIS_ LPDIENUMDEVICEOBJECTSCALLBACKA, LPVOID, DWORD);
	STDMETHOD(GetProperty)(THIS_ REFGUID, LPDIPROPHEADER);
	STDMETHOD(SetProperty)(THIS_ REFGUID, LPCDIPROPHEADER);
	STDMETHOD(Acquire)(THIS);
	STDMETHOD(Unacquire)(THIS);
	STDMETHOD(GetDeviceState)(THIS_ DWORD, LPVOID);
	STDMETHOD(GetDeviceData)(THIS_ DWORD, LPDIDEVICEOBJECTDATA, LPDWORD, DWORD);
	STDMETHOD(SetDataFormat)(THIS_ LPCDIDATAFORMAT);
	STDMETHOD(SetEventNotification)(THIS_ HANDLE);
	STDMETHOD(SetCooperativeLevel)(THIS_ HWND, DWORD);
	STDMETHOD(GetObjectInfo)(THIS_ LPDIDEVICEOBJECTINSTANCEA, DWORD, DWORD);
	STDMETHOD(GetDeviceInfo)(THIS_ LPDIDEVICEINSTANCEA);
	STDMETHOD(RunControlPanel)(THIS_ HWND, DWORD);
	STDMETHOD(Initialize)(THIS_ HINSTANCE, DWORD, REFGUID);
	STDMETHOD(CreateEffect)(THIS_ REFGUID, LPCDIEFFECT, LPDIRECTINPUTEFFECT *, LPUNKNOWN);
	STDMETHOD(EnumEffects)(THIS_ LPDIENUMEFFECTSCALLBACKA, LPVOID, DWORD);
	STDMETHOD(GetEffectInfo)(THIS_ LPDIEFFECTINFOA, REFGUID);
	STDMETHOD(GetForceFeedbackState)(THIS_ LPDWORD);
	STDMETHOD(SendForceFeedbackCommand)(THIS_ DWORD);
	STDMETHOD(EnumCreatedEffectObjects)(THIS_ LPDIENUMCREATEDEFFECTOBJECTSCALLBACK, LPVOID, DWORD);
	STDMETHOD(Escape)(THIS_ LPDIEFFESCAPE);
	STDMETHOD(Poll)(THIS);
	STDMETHOD(SendDeviceData)(THIS_ DWORD, LPCDIDEVICEOBJECTDATA, LPDWORD, DWORD);
	STDMETHOD(EnumEffectsInFile)(THIS_ LPCSTR, LPDIENUMEFFECTSINFILECALLBACK, LPVOID, DWORD);
	STDMETHOD(WriteEffectToFile)(THIS_ LPCSTR, DWORD, LPDIFILEEFFECT, DWORD);
	STDMETHOD(BuildActionMap)(THIS_ LPDIACTIONFORMATA, LPCSTR, DWORD);
	STDMETHOD(SetActionMap)(THIS_ LPDIACTIONFORMATA, LPCSTR, DWORD);
	STDMETHOD(GetImageInfo)(THIS_ LPDIDEVICEIMAGEINFOHEADERA);
};
