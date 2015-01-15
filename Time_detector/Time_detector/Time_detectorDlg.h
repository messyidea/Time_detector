
// Time_detectorDlg.h : 头文件
//

#pragma once

const double PI = 3.1415926;
typedef unsigned char byte;
#define CV_IMAGE_ELEM( image,elemtype,row,col) (((elemtype*)((image)->imageData + (image)->widthStep*(row)))[(col)])
const int eps = 3;
// CTime_detectorDlg 对话框
class CTime_detectorDlg : public CDialogEx
{
	// 构造
public:
	CTime_detectorDlg(CWnd* pParent = NULL);	// 标准构造函数

	// 对话框数据
	enum { IDD = IDD_TIME_DETECTOR_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


	// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
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
	inline double dis(double i,double j,double x,double y) {	//求两个点的距离。
		return (i-x)*(i-x) + (j-y)*(j-y);
	}
	void clearbg(IplImage* src, double x,double y,double r);	//清空背景

	int dcmp(double x) {
		if(fabs(x) < eps) return 0;
		else return x < 0? -1: 1;
	}

	double Dot(CvPoint A,CvPoint B) {	//求两个向量的点积
		return A.x * B.x + A.y * B.y;
	}
	double Length(CvPoint A) {		//求一个向量的长度
		return sqrt(Dot(A,A));
	}
	double Angle(CvPoint A,CvPoint B) {		//求两个向量的夹角
		return acos(Dot(A,B) / Length(A) / Length(B));
	}
	static bool cmp(double a,double b) {
		return a > b;
	}
	CvPoint Sub(CvPoint a,CvPoint b) {		//向量想减
		CvPoint c;
		c.x = a.x - b.x;
		c.y = a.y - b.y;
		return c;
	}
	double Cross(CvPoint a,CvPoint b) {		//求向量叉积
		return a.x * b.y - a.y * b.x;
	}
	double Distance(CvPoint p,CvPoint a,CvPoint b) {	//求点p到线段ab的距离。注意ab不是直线，所以要考虑三种情况
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
	void cvThin( IplImage* src, IplImage* dst, int iterations);		//细化函数
	double angle( CvPoint* pt1, CvPoint* pt2, CvPoint* pt0 )	//两个向量的夹角
	{
		double dx1 = pt1->x - pt0->x;
		double dy1 = pt1->y - pt0->y;
		double dx2 = pt2->x - pt0->x;
		double dy2 = pt2->y - pt0->y;
		return (dx1*dx2 + dy1*dy2)/sqrt((dx1*dx1 + dy1*dy1)*(dx2*dx2 + dy2*dy2) + 1e-10);
	}
	// 返回图像中找到的所有轮廓序列，并且序列存储在内存存储器中
	CvSeq* findSquares4( IplImage* img, CvMemStorage* storage );
	void clearbg2(IplImage* src, double x,double y,double r1,double r2);	//清空背景
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
