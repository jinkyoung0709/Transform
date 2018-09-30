// TransformDoc.h : CTransformDoc Ŭ������ �������̽�
//


#pragma once


class CTransformDoc : public CDocument
{
protected: // serialization������ ��������ϴ�.
	CTransformDoc();
	DECLARE_DYNCREATE(CTransformDoc)

// Ư���Դϴ�.
public:
	unsigned char **inputImg;
	unsigned char **resultImg;
	int imageWidth;
	int imageHeight;
	int depth;
	int gImageWidth;
	int gImageHeight;

// �۾��Դϴ�.
public:

// �������Դϴ�.
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);

// �����Դϴ�.
public:
	virtual ~CTransformDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ������ �޽��� �� �Լ�
protected:
	DECLARE_MESSAGE_MAP()
public:
	void LoadImageFile(CArchive& ar);
	void GeomertyPerspectiveTransform(void);
};


