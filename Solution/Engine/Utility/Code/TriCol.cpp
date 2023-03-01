#include "..\..\Header\TriCol.h"

CTriCol::CTriCol(void)
{
}

CTriCol::CTriCol(LPDIRECT3DDEVICE9 pGraphicDev)
	:CVIBuffer(pGraphicDev)
{
}

CTriCol::CTriCol(const CTriCol & rhs)
	:CVIBuffer(rhs)
{
}

CTriCol::~CTriCol()
{
}

HRESULT CTriCol::Ready_Buffer(void)
{
	m_dwFVF = FVF_COL;
	m_dwVtxSize = sizeof(VTXCOL);
	m_dwVtxCnt = 3;
	m_dwTriCnt = 1;

	m_dwIdxSize = sizeof(INDEX32);
	m_IdxFmt = D3DFMT_INDEX32;

	FAILED_CHECK_RETURN(CVIBuffer::Ready_Buffer(), E_FAIL);

	VTXCOL*		pVertex = nullptr;

	m_pVB->Lock(0, 0, (void**)&pVertex, 0);
	// Lock : ���ؽ� ���� �޸� ������ ������ ����, ���ؽ� ���ۿ� ����Ǿ� �ִ� ù ��° ���ؽ��� �ּҸ� ����

	pVertex[0].vPos = {0.f, 1.f, 0.f};
	pVertex[0].dwColor = D3DXCOLOR(1.f, 0.f, 0.f, 1.f);

	pVertex[1].vPos = { 1.f, -1.f, 0.f };
	pVertex[1].dwColor = D3DXCOLOR(1.f, 0.f, 0.f, 1.f);

	pVertex[2].vPos = { -1.f, -1.f, 0.f };
	pVertex[2].dwColor = D3DXCOLOR(1.f, 0.f, 0.f, 1.f);

	m_pVB->Unlock();

	INDEX32*		pIndex = nullptr;

	m_pIB->Lock(0, 0, (void**)&pIndex, 0);

	pIndex[0]._0 = 0;
	pIndex[0]._1 = 1;
	pIndex[0]._2 = 2;

	m_pIB->Unlock();


	return S_OK;
}

void CTriCol::Render_Buffer(void)
{
	__super::Render_Buffer();
}


Engine::CComponent* CTriCol::Clone(void)
{	
	return new CTriCol(*this);
}

CTriCol * CTriCol::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CTriCol * pInstance = new CTriCol(pGraphicDev);

	if (FAILED(pInstance->Ready_Buffer()))
	{
		Safe_Release(pInstance);
		return nullptr;
	}

	return pInstance;
}

void Engine::CTriCol::Free(void)
{
	__super::Free();
}
