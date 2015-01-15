
// Time_detectorDlg.h : ͷ�ļ�
//

#pragma once

const double PI = 3.1415926;
typedef unsigned char byte;
#define CV_IMAGE_ELEM( image,elemtype,row,col) (((elemtype*)((image)->imageData + (image)->widthStep*(row)))[(col)])
const int eps = 3;
// CTime_detectorDlg �Ի���
class CTime_detectorDlg : public CDialogEx
{
	// ����
public:
	CTime_detectorDlg(CWnd* pParent = NULL);	// ��׼���캯��

	// �Ի�������
	enum { IDD = IDD_TIME_DETECTOR_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


	// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
	IplImage* src;
	IplImage* orgin;
	IplImage* gray_orgin;
	IplImage* gray_src;
	IplImage *t_bin;
	IplImage *t_thin;
	IplImage *t_canny;
	bool have_src;
public:
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedOk();
	void DrawPicToHDC(IplImage *img, UINT ID);
	afx_msg void OnBnClickedButton1();
	inline double dis(double i,double j,double x,double y) {	//��������ľ��롣
		return (i-x)*(i-x) + (j-y)*(j-y);
	}
	void clearbg(IplImage* src, double x,double y,double r);	//��ձ���

	int dcmp(double x) {
		if(fabs(x) < eps) return 0;
		else return x < 0? -1: 1;
	}

	double Dot(CvPoint A,CvPoint B) {	//�����������ĵ��
		return A.x * B.x + A.y * B.y;
	}
	double Length(CvPoint A) {		//��һ�������ĳ���
		return sqrt(Dot(A,A));
	}
	double Angle(CvPoint A,CvPoint B) {		//�����������ļн�
		return acos(Dot(A,B) / Length(A) / Length(B));
	}
	static bool cmp(double a,double b) {
		return a > b;
	}
	CvPoint Sub(CvPoint a,CvPoint b) {		//�������
		CvPoint c;
		c.x = a.x - b.x;
		c.y = a.y - b.y;
		return c;
	}
	double Cross(CvPoint a,CvPoint b) {		//���������
		return a.x * b.y - a.y * b.x;
	}
	double Distance(CvPoint p,CvPoint a,CvPoint b) {	//���p���߶�ab�ľ��롣ע��ab����ֱ�ߣ�����Ҫ�����������
		if(abs(a.x - b.x) + abs(a.y - b.y) <= eps) return Length(Sub(p,a));
		CvPoint v1 = Sub(b,a);
		CvPoint v2 = Sub(p,a);
		CvPoint v3 = Sub(p,b);
		if(dcmp(Dot(v1,v2)) < 0) return Length(v2);
		else if(dcmp(Dot(v1,v3)) > 0) return Length(v3);
		else return fabs(Cross(v1,v2)) / Length(v1);
	}

	static bool cmp2(pair<double,int> a, pair<double,int> b){
		return a.second > b.second;
	}
	void cvThin( IplImage* src, IplImage* dst, int iterations);		//ϸ������
	double angle( CvPoint* pt1, CvPoint* pt2, CvPoint* pt0 )	//���������ļн�
	{
		double dx1 = pt1->x - pt0->x;
		double dy1 = pt1->y - pt0->y;
		double dx2 = pt2->x - pt0->x;
		double dy2 = pt2->y - pt0->y;
		return (dx1*dx2 + dy1*dy2)/sqrt((dx1*dx1 + dy1*dy1)*(dx2*dx2 + dy2*dy2) + 1e-10);
	}
	// ����ͼ�����ҵ��������������У��������д洢���ڴ�洢����
	CvSeq* findSquares4( IplImage* img, CvMemStorage* storage );
	void clearbg2(IplImage* src, double x,double y,double r1,double r2);	//��ձ���
	CString Miao;
	CString Fen;
	CString Shi;
	double cenx;
	double ceny;
	bool flag1;
	bool flag2;
	char mShi[10];
	char mFen[10];
	char mMiao[10];
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnBnClickedOk2();
};
