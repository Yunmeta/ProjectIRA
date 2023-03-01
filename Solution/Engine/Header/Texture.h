#pragma once
#include "Component.h"

BEGIN(Engine)

class ENGINE_DLL CTexture : public CComponent
{
private:
	explicit CTexture(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit CTexture(const CTexture&  rhs);
	virtual ~CTexture();

public:
	HRESULT			Ready_Texture(TEXTYPE eType, const _tchar* pPath, const _uint& iCnt);
	void			Set_Texture(const _uint& iIndex = 0);

private:
	vector<IDirect3DBaseTexture9*>		m_vecTexture;
					
public:
	virtual CComponent*		Clone(void);
	static CTexture*		Create(LPDIRECT3DDEVICE9 pGraphicDev, TEXTYPE eType, const _tchar* pPath, const _uint& iCnt = 1);

private:
	virtual void	Free(void);
};

END