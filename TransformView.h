// TransformView.h : CTransformView Ŭ������ �������̽�
//


#pragma once


class CTransformView : public CScrollView
{
protected: // serialization������ ��������ϴ�.
	CTransformView();
	DECLARE_DYNCREATE(CTransformView)

// Ư���Դϴ�.
public:
	CTransformDoc* GetDocument() const;

// �۾��Դϴ�.
public:

// �������Դϴ�.
public:
	virtual void OnDraw(CDC* pDC);  // �� �並 �׸��� ���� �����ǵǾ����ϴ�.
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual void OnInitialUpdate(); // ���� �� ó�� ȣ��Ǿ����ϴ�.
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// �����Դϴ�.
public:
	virtual ~CTransformView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ������ �޽��� �� �Լ�
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnGeometryPerspectiveTransform();
};

#ifndef _DEBUG  // TransformView.cpp�� ����� ����
inline CTransformDoc* CTransformView::GetDocument() const
   { return reinterpret_cast<CTransformDoc*>(m_pDocument); }
#endif

