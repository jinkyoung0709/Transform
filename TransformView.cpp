// TransformView.cpp : CTransformView Ŭ������ ����
//

#include "stdafx.h"
#include "Transform.h"

#include "TransformDoc.h"
#include "TransformView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CTransformView

IMPLEMENT_DYNCREATE(CTransformView, CScrollView)

BEGIN_MESSAGE_MAP(CTransformView, CScrollView)
	// ǥ�� �μ� ����Դϴ�.
	ON_COMMAND(ID_FILE_PRINT, &CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CScrollView::OnFilePrintPreview)
	ON_COMMAND(ID_GEOMETRY_PERSPECTIVE_TRANSFORM, &CTransformView::OnGeometryPerspectiveTransform)
END_MESSAGE_MAP()

// CTransformView ����/�Ҹ�

CTransformView::CTransformView()
{
	// TODO: ���⿡ ���� �ڵ带 �߰��մϴ�.

}

CTransformView::~CTransformView()
{
}

BOOL CTransformView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs�� �����Ͽ� ���⿡��
	//  Window Ŭ���� �Ǵ� ��Ÿ���� �����մϴ�.

	return CScrollView::PreCreateWindow(cs);
}

// CTransformView �׸���

void CTransformView::OnDraw(CDC* pDC)
{
	CTransformDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: ���⿡ ���� �����Ϳ� ���� �׸��� �ڵ带 �߰��մϴ�.
	if(pDoc->inputImg == NULL) return;

	if(pDoc->depth == 1) {
		for(int y=0; y < pDoc->imageHeight; y++)
			for(int x=0; x < pDoc->imageWidth; x++)
				pDC->SetPixel(x, y, RGB(pDoc->inputImg[y][x], pDoc->inputImg[y][x], pDoc->inputImg[y][x]));

		for(int y=0; y < pDoc->gImageHeight; y++)
			for(int x=0; x < pDoc->gImageWidth; x++)
				pDC->SetPixel(x+pDoc->imageWidth+30, y, RGB(pDoc->resultImg[y][x], pDoc->resultImg[y][x], pDoc->resultImg[y][x]));
	}
	else if(pDoc->depth == 3) {
		for(int y=0; y < pDoc->imageHeight; y++)
			for(int x=0; x < pDoc->imageWidth; x++)
				pDC->SetPixel(x, y, RGB(pDoc->inputImg[y][3*x], pDoc->inputImg[y][3*x+1], pDoc->inputImg[y][3*x+2]));

		for(int y=0; y < pDoc->gImageHeight; y++)
			for(int x=0; x < pDoc->gImageWidth; x++)
				pDC->SetPixel(x+pDoc->imageWidth+30, y, RGB(pDoc->resultImg[y][3*x], pDoc->resultImg[y][3*x+1], pDoc->resultImg[y][3*x+2]));
	}
}

void CTransformView::OnInitialUpdate()
{
	CScrollView::OnInitialUpdate();

	CSize sizeTotal;
	// TODO: �� ���� ��ü ũ�⸦ ����մϴ�.
	sizeTotal.cx = 2048;
	sizeTotal.cy = 1024;
	SetScrollSizes(MM_TEXT, sizeTotal);
}


// CTransformView �μ�

BOOL CTransformView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// �⺻���� �غ�
	return DoPreparePrinting(pInfo);
}

void CTransformView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: �μ��ϱ� ���� �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
}

void CTransformView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: �μ� �� ���� �۾��� �߰��մϴ�.
}


// CTransformView ����

#ifdef _DEBUG
void CTransformView::AssertValid() const
{
	CScrollView::AssertValid();
}

void CTransformView::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}

CTransformDoc* CTransformView::GetDocument() const // ����׵��� ���� ������ �ζ������� �����˴ϴ�.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CTransformDoc)));
	return (CTransformDoc*)m_pDocument;
}
#endif //_DEBUG


// CTransformView �޽��� ó����

void CTransformView::OnGeometryPerspectiveTransform()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	CTransformDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	if(pDoc->inputImg == NULL) return;
	pDoc->GeomertyPerspectiveTransform();
	Invalidate(FALSE);
}
