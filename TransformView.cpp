// TransformView.cpp : CTransformView 클래스의 구현
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
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CScrollView::OnFilePrintPreview)
	ON_COMMAND(ID_GEOMETRY_PERSPECTIVE_TRANSFORM, &CTransformView::OnGeometryPerspectiveTransform)
END_MESSAGE_MAP()

// CTransformView 생성/소멸

CTransformView::CTransformView()
{
	// TODO: 여기에 생성 코드를 추가합니다.

}

CTransformView::~CTransformView()
{
}

BOOL CTransformView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CScrollView::PreCreateWindow(cs);
}

// CTransformView 그리기

void CTransformView::OnDraw(CDC* pDC)
{
	CTransformDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 여기에 원시 데이터에 대한 그리기 코드를 추가합니다.
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
	// TODO: 이 뷰의 전체 크기를 계산합니다.
	sizeTotal.cx = 2048;
	sizeTotal.cy = 1024;
	SetScrollSizes(MM_TEXT, sizeTotal);
}


// CTransformView 인쇄

BOOL CTransformView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비
	return DoPreparePrinting(pInfo);
}

void CTransformView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}

void CTransformView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
}


// CTransformView 진단

#ifdef _DEBUG
void CTransformView::AssertValid() const
{
	CScrollView::AssertValid();
}

void CTransformView::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}

CTransformDoc* CTransformView::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CTransformDoc)));
	return (CTransformDoc*)m_pDocument;
}
#endif //_DEBUG


// CTransformView 메시지 처리기

void CTransformView::OnGeometryPerspectiveTransform()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CTransformDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	if(pDoc->inputImg == NULL) return;
	pDoc->GeomertyPerspectiveTransform();
	Invalidate(FALSE);
}
