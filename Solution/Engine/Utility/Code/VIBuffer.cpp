#include "..\..\Header\VIBuffer.h"

CVIBuffer::CVIBuffer(void)
{
}

CVIBuffer::CVIBuffer(LPDIRECT3DDEVICE9 pGraphicDev)
	: CComponent(pGraphicDev)
	, m_pVB(nullptr)
	, m_pIB(nullptr)
	, m_dwFVF(0)
	, m_dwVtxSize(0)
	, m_dwVtxCnt(0)
	, m_dwTriCnt(0)
	, m_dwIdxSize(0)
	, m_IdxFmt(D3DFMT_UNKNOWN)
{
}

CVIBuffer::CVIBuffer(const CVIBuffer & rhs)
	: CComponent(rhs)
	, m_pVB(rhs.m_pVB)
	, m_pIB(rhs.m_pIB)
	, m_dwFVF(rhs.m_dwFVF)
	, m_dwVtxSize(rhs.m_dwVtxSize)
	, m_dwVtxCnt(rhs.m_dwVtxCnt)
	, m_dwTriCnt(rhs.m_dwTriCnt)
	, m_dwIdxSize(rhs.m_dwIdxSize)
	, m_IdxFmt(rhs.m_IdxFmt)
{
	m_pVB->AddRef();
	m_pIB->AddRef();
}

CVIBuffer::~CVIBuffer()
{
}

HRESULT CVIBuffer::Ready_Buffer(void)
{
	if (FAILED(m_pGraphicDev->CreateVertexBuffer(m_dwVtxCnt * m_dwVtxSize,	// ���� ������ ������
												0,			// ���۸� ����� ���(0�� ��� ���� ����, D3DUSAGE_DYNAMIC�� �����ϸ� ���� ����)
												m_dwFVF,	// ������ �ɼ�
												D3DPOOL_MANAGED,
												&m_pVB,
												nullptr)))
	{
		MSG_BOX("Createvertexbuffer Failed");
		return E_FAIL;
	}

	if (FAILED(m_pGraphicDev->CreateIndexBuffer(m_dwIdxSize * m_dwTriCnt,	// �ε��� ������ ������
													0,			// ���۸� ����� ���(0�� ��� ���� ����, D3DUSAGE_DYNAMIC�� �����ϸ� ���� ����)
													m_IdxFmt,	// �ε����� �ɼ�
													D3DPOOL_MANAGED,
													&m_pIB,
													nullptr)))
	{
		MSG_BOX("CreateIndexbuffer Failed");
		return E_FAIL;
	}
	

	return S_OK;
}

void CVIBuffer::Render_Buffer(void)
{
	// �׸��� ��ġ�� ���� �׸����� �ϴ� ���ؽ� ������ �����ϴ� �Լ�
	m_pGraphicDev->SetStreamSource(0, m_pVB, 0, m_dwVtxSize);

	// 1. �� ��° ���Կ� ������ ���ΰ�
	// 2. � ������ ������ ���ΰ�
	// 3. ��𼭺��� �׸��� ������ ������ ���ΰ�
	// 4. � ������ �׸��� ������ ������ ���ΰ�

	m_pGraphicDev->SetFVF(m_dwFVF);

	m_pGraphicDev->SetIndices(m_pIB);

	m_pGraphicDev->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, m_dwVtxCnt, 0, m_dwTriCnt);


	/*m_pGraphicDev->DrawPrimitive(D3DPT_TRIANGLELIST, 0, m_dwTriCnt);

	// �׸��� �Լ�
	// 1. �÷��� ���� ���� �ﰢ���� �׸��� ����� ����
	// 2. �� ��° ���ؽ����� �׸� ���ΰ�
	// 3. �׸� �ﰢ���� ����*/
}

void Engine::CVIBuffer::Free(void)
{
	Safe_Release(m_pVB);
	Safe_Release(m_pIB);
}

