// TransformDoc.cpp : CTransformDoc Ŭ������ ����
//

#include "stdafx.h"
#include "Transform.h"

#include "TransformDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CTransformDoc

IMPLEMENT_DYNCREATE(CTransformDoc, CDocument)

BEGIN_MESSAGE_MAP(CTransformDoc, CDocument)
END_MESSAGE_MAP()


// CTransformDoc ����/�Ҹ�

CTransformDoc::CTransformDoc()
{
	// TODO: ���⿡ ��ȸ�� ���� �ڵ带 �߰��մϴ�.
	inputImg = NULL;
	resultImg = NULL;

}

CTransformDoc::~CTransformDoc()
{
}

BOOL CTransformDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: ���⿡ ���ʱ�ȭ �ڵ带 �߰��մϴ�.
	// SDI ������ �� ������ �ٽ� ����մϴ�.

	return TRUE;
}




// CTransformDoc serialization

void CTransformDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: ���⿡ ���� �ڵ带 �߰��մϴ�.
	}
	else
	{
		// TODO: ���⿡ �ε� �ڵ带 �߰��մϴ�.
		LoadImageFile(ar);
	}
}


// CTransformDoc ����

#ifdef _DEBUG
void CTransformDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CTransformDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CTransformDoc ���
#include "math.h"
void CTransformDoc::LoadImageFile(CArchive& ar)
{
	int i, maxValue;
	char type[16], buf[256];
	CFile *fp = ar.GetFile();
	CString fname = fp->GetFilePath();

	if(strcmp(strrchr(fname, '.'), ".ppm") == 0 || strcmp(strrchr(fname, '.'), ".PPM") == 0 ||
		strcmp(strrchr(fname, '.'), ".pgm") == 0 || strcmp(strrchr(fname, '.'), ".PGM") == 0) {
		ar.ReadString(type, 15);

		do {
			ar.ReadString(buf, 255);
		} while(buf[0] == '#');
		sscanf_s(buf, "%d %d", &imageWidth, &imageHeight);

		do {
			ar.ReadString(buf, 255);
		} while(buf[0] == '#');
		sscanf_s(buf, "%d", &maxValue);

		if(strcmp(type, "P5") == 0) depth = 1;
		else depth = 3;

		//���ϴ� ��ü�� �� ���� ���̸� ���ϰ� �� �� ���� ���� �� ���̸� ��ȯ�� ������ ũ��� �մϴ�.
		CPoint TopLeft(54, 22), TopRight(221, 10), BottomLeft(21, 264), BottomRight(226, 272); //ex1
		//CPoint TopLeft(82, 102), TopRight(314, 99), BottomLeft(135, 459), BottomRight(427, 412); //ex2
		int w1, w2, h1, h2;
		w1 = sqrt(pow((double)TopLeft.x - TopRight.x, 2) + pow((double)TopLeft.y - TopRight.y, 2));
		w2 = sqrt(pow((double)BottomLeft.x - BottomRight.x, 2) + pow((double)BottomLeft.y - BottomRight.y, 2));
		gImageWidth = (w1 > w2) ? (w1 - 1) : (w2 - 1);
		h1 = sqrt(pow((double)TopLeft.y - BottomLeft.y, 2) + pow((double)TopLeft.x - BottomLeft.x, 2));
		h2 = sqrt(pow((double)TopRight.y - BottomRight.y, 2) + pow((double)TopRight.x - BottomRight.x, 2));
		gImageHeight = (h1 > h2) ? (h1 - 1) : (h2 - 1);
		
	} else if(strcmp(strchr(fname, '.'), ".raw") == 0 || strcmp(strchr(fname, '.'), ".RAW") == 0) {
		if(fp->GetLength() != 256*256) {
			AfxMessageBox("256x256 ũ���� ���ϸ� ��밡���մϴ�.");
			return;
		}

		imageWidth = 256;
		imageHeight = 256;
		gImageWidth = 256;
		gImageHeight = 256;
		depth = 1;
	}

	inputImg = (unsigned char **) malloc(imageHeight * sizeof(unsigned char *));
	resultImg = (unsigned char **) malloc(gImageHeight * sizeof(unsigned char *));

	for(i = 0; i < imageHeight; i++) inputImg[i] = (unsigned char *) malloc(imageWidth * depth);
	for(i = 0; i < gImageHeight; i++) resultImg[i] = (unsigned char *) malloc(gImageWidth * depth);

	for(i = 0; i < imageHeight; i++) ar.Read(inputImg[i], imageWidth*depth);
}

void CTransformDoc::GeomertyPerspectiveTransform(void)
{
	int x, y, ix, iy;
	double rx, ry, E, F;

	for(y = 0; y < gImageHeight; y++)
		for(x = 0; x < gImageWidth; x++) {
			//����ȯ ���
			//ex1
			rx = (0.704*x - 0.1341*y + 51.2714) / (-0.0003*x - 0.0007*y + 0.9495);
			ry = (-0.0591*x + 0.7039*y + 20.8883) / (-0.0003*x - 0.0007*y + 0.9495);
			//ex2
			//rx = (0.8376*x + 0.0515*y + 76.5237) / (0.0003*x - 0.0006*y + 0.9332);
			//ry = (0.0230*x + 0.6334*y + 95.188) / (0.0003*x - 0.0006*y + 0.9332);
			
			//�缱�� ������
			ix = floor(rx);
			iy = floor(ry);
			rx = rx - ix;
			ry = ry - iy;
			for(int i=0; i < depth; i++) {
				E = (1 - rx)*inputImg[iy][depth*ix+i] + rx*inputImg[iy][depth*(ix+1)+i];
				F = (1 - rx)*inputImg[iy+1][depth*ix+i] + rx*inputImg[iy+1][depth*(ix+1)+i];
				resultImg[y][depth*x+i] = (unsigned char) ((1 - ry)*E + ry*F);
			}
		}
}