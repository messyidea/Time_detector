
// Time_detectorDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "Time_detector.h"
#include "Time_detectorDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

	// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CTime_detectorDlg 对话框




CTime_detectorDlg::CTime_detectorDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CTime_detectorDlg::IDD, pParent)
	, Miao(_T(""))
	, Fen(_T(""))
	, Shi(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CTime_detectorDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	//DDX_Text(pDX, IDC_EDIT3, Miao);
	//DDX_Text(pDX, IDC_EDIT1, Fen);
	//DDX_Text(pDX, IDC_EDIT2, Shi);
}

BEGIN_MESSAGE_MAP(CTime_detectorDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDCANCEL, &CTime_detectorDlg::OnBnClickedCancel)
	ON_BN_CLICKED(IDOK, &CTime_detectorDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDC_BUTTON1, &CTime_detectorDlg::OnBnClickedButton1)
	ON_WM_LBUTTONDOWN()
	ON_BN_CLICKED(IDOK2, &CTime_detectorDlg::OnBnClickedOk2)
END_MESSAGE_MAP()


// CTime_detectorDlg 消息处理程序

BOOL CTime_detectorDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	GetDlgItem(IDC_EDITS)->SetWindowTextW(_T("--"));
	GetDlgItem(IDC_EDITF)->SetWindowTextW(_T("--"));
	GetDlgItem(IDC_EDITM)->SetWindowTextW(_T("--"));
	have_src = false;
	flag1 = false;
	flag2 = false;

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CTime_detectorDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CTime_detectorDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CTime_detectorDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CTime_detectorDlg::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialogEx::OnCancel();
}


void CTime_detectorDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	//CDialogEx::OnOK();
	CFileDialog opendialog(TRUE);
	CString temp;
	if (opendialog.DoModal() == IDOK)
	{
		temp = opendialog.GetPathName();
	}

	// TODO: 在此添加控件通知处理程序代码
	IplImage *image=NULL; //原始图像
	if(&image) cvReleaseImage(&image);
	const size_t strsize=(temp.GetLength()+1)*2; // 宽字符的长度;
	char * pstr= new char[strsize]; //分配空间;
	size_t sz=0;
	wcstombs_s(&sz,pstr,strsize,temp,_TRUNCATE);
	image = cvLoadImage(pstr,CV_LOAD_IMAGE_UNCHANGED); //显示图片
	if(image == NULL) return ;
	src = image;
	orgin = cvCloneImage(src);
	//-------------------同时生成gray图
	gray_src =  cvCreateImage(cvGetSize(src), IPL_DEPTH_8U, 1);
	cvCvtColor(src, gray_src, CV_BGR2GRAY); 
	gray_orgin = cvCreateImage(cvGetSize(src), IPL_DEPTH_8U, 1);
	gray_orgin = cvCloneImage(gray_src);
	GetDlgItem(IDC_EDITS)->SetWindowTextW(_T("--"));
	GetDlgItem(IDC_EDITF)->SetWindowTextW(_T("--"));
	GetDlgItem(IDC_EDITM)->SetWindowTextW(_T("--"));
	GetDlgItem(IDC_EDITSS)->SetWindowTextW(_T(""));
	have_src = true;
	DrawPicToHDC(image, IDC_STATIC);

}

void CTime_detectorDlg::DrawPicToHDC(IplImage *img, UINT ID) {
	CDC *pDC = GetDlgItem(ID)->GetDC();
	HDC hDC= pDC->GetSafeHdc();
	CRect rect;
	GetDlgItem(ID)->GetClientRect(&rect);
	CvvImage cimg;
	cimg.CopyOf( img ); // 复制图片
	cimg.DrawToHDC( hDC, &rect ); // 将图片绘制到显示控件的指定区域内
	ReleaseDC( pDC );
}

void CTime_detectorDlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	if(!have_src) {
		MessageBox(_T("当前未载入图片！"));
		return ;
	}
	float* p;
	double cx,cy,cr = -1;
	CvPoint center;
	if(flag2) {
		flag2 = false;
		flag1 = false;
		cx = cenx;
		cy = ceny;
		cr = -1;
		center.x = cenx;
		center.y = ceny;
		cvCircle( src, cvPoint(cvRound(cenx),cvRound(ceny)), cvRound(3), CV_RGB(255,0,0), 3, 8, 0 );
		gray_src = cvCloneImage(gray_orgin);
		//DrawPicToHDC(gray_orgin, IDC_STATIC);
		//return ;
		goto TOSOLVE;
	}
	// -------------------------------------------------------------检测圆。
	CvMemStorage *pcvMStorage = cvCreateMemStorage();  
	double fMinCircleGap = gray_src->height / 10;  
	CvSeq *circles = cvHoughCircles(gray_src, pcvMStorage, CV_HOUGH_GRADIENT, 1, fMinCircleGap);  
	for( int i = 0; i < circles->total; i++ )
	{
		float* p = (float*)cvGetSeqElem( circles, i );
	}

	if(circles->total != 0) {
		//-----------------------------------------------------找到了圆，除圆部分清空
		p = (float*)cvGetSeqElem( circles, 0 );
		cx = p[0],cy = p[1];
		cr = p[2];
		center;
		center.x = p[0];
		center.y = p[1];
		clearbg(gray_src,cy,cx,cr);
		//return ;
	} else {
		//-----------------------------------------------------------------检测矩形
		IplImage *linshi = cvCloneImage(src);
		CvMemStorage *pcvhe = cvCreateMemStorage(); 
		//drawSquares( linshi, findSquares4( linshi, pcvhe ) );
		CvSeq* squares =  findSquares4( linshi, pcvhe );
		if(squares->total == 0) {
			GetDlgItem(IDC_EDITSS)->SetWindowTextW(_T("未检测到闹钟"));
			return ;
		}
		CvSeqReader reader;
		cvStartReadSeq( squares, &reader, 0 );
		CvPoint pt[4];
		int count = 4;

		// read 4 vertices
		CV_READ_SEQ_ELEM( pt[0], reader );
		CV_READ_SEQ_ELEM( pt[1], reader );
		CV_READ_SEQ_ELEM( pt[2], reader );
		CV_READ_SEQ_ELEM( pt[3], reader );
		cx = (pt[0].x + pt[1].x + pt[2].x + pt[3].x)/4.0;
		cy = (pt[0].y + pt[1].y + pt[2].y + pt[3].y)/4.0;
		center.x = cx,center.y = cy;
		cr = fabs(cx - pt[0].x);
		clearbg2(gray_src,cy,cx,fabs(cy - pt[0].y),fabs(cx - pt[0].x));
	}

	//-----------------------------------------------------------------细化图像
TOSOLVE:
	t_bin = cvCreateImage(cvGetSize(src), IPL_DEPTH_8U, 1);
	cvThreshold(gray_src, t_bin, 200, 1, CV_THRESH_BINARY); 
	t_thin =  cvCreateImage(cvGetSize(src), IPL_DEPTH_8U, 1);
	for(int i=0; i<t_bin->height;  i++)  
	{  
		for(int j=0; j<t_bin->width; j++)  
		{  
			if(CV_IMAGE_ELEM(t_bin,uchar,i,j)==1)  
			{  
				CV_IMAGE_ELEM(t_bin,uchar,i,j) = 0;  
			}  
			else  
			{  
				CV_IMAGE_ELEM(t_bin,uchar,i,j) = 1;  
			}  
		}  
	}
	cvThin(t_bin,t_thin,1);
	CvSize size = cvGetSize(t_thin);  
	for(int i=0; i<size.height;  i++)  
	{  
		for(int j=0; j<size.width; j++)  
		{  
			if(CV_IMAGE_ELEM(t_thin,uchar,i,j)==1)  
			{  
				CV_IMAGE_ELEM(t_thin,uchar,i,j) = 255;  
			}  
			else  
			{  
				CV_IMAGE_ELEM(t_thin,uchar,i,j) = 0;  
			}  
		}  
	} 
	//cvShowImage( "circles4", t_thin );
	t_canny = cvCloneImage(t_thin);
	//-----------------------------------------------------------------找直线
	CvMemStorage *pcvMStorage2 = cvCreateMemStorage();  
	double fRho = 1;  
	double fTheta = CV_PI / 180;  
	int nMaxLineNumber = 50;   //最多检测条直线  
	double fMinLineLen ;   //最小线段长度
	if(cr == -1) {
		fMinLineLen = 50;
	} else {
		fMinLineLen = cr / 3;
	}
	double fMinLineGap = 10;   //最小线段间隔  
	CvSeq *lines = cvHoughLines2(t_canny, pcvMStorage2, CV_HOUGH_PROBABILISTIC, fRho, fTheta, nMaxLineNumber, fMinLineLen, fMinLineGap); 
	if(lines->total == 0) {
		GetDlgItem(IDC_EDITSS)->SetWindowTextW(_T("未检测到指针"));
		return ;
	}
	for(int i = 0; i < lines->total; i++ )
	{
		CvPoint* line = (CvPoint*)cvGetSeqElem(lines,i);
		if(Distance(center,line[0],line[1]) > 20) continue;
		cvLine( src, line[0], line[1], CV_RGB(255,0,0), 2, 8 );
	}

	//-------------------------------------------------显示在原界面
	DrawPicToHDC(src, IDC_STATIC);

	//--------------------------------------------------抛弃错误直线，并取直线离圆心远的点
	vector <CvPoint> ans;
	for(int i = 0;i < lines->total; ++i) {
		CvPoint* line = (CvPoint*)cvGetSeqElem(lines,i);
		//-----------------------------------------------------------------抛弃错误直线
		if(Distance(center,line[0],line[1]) > 20) continue;
		if(dis(line[0].x,line[0].y,cx,cy) < dis(line[1].x,line[1].y,cx,cy)) 
			ans.push_back(line[1]);
		else ans.push_back(line[0]);
	}
	if(ans.size() == 0) {
		GetDlgItem(IDC_EDITSS)->SetWindowTextW(_T("未检测到指针"));
		return ;
	}
	//---------------------------------------------------------把点根据圆心转换为角度存在an中
	vector <double> an;
	for(int i=0;i<ans.size();++i) {
		CvPoint tp = ans[i];
		tp.x = (tp.x - cx);
		tp.y = (tp.y - cy);
		CvPoint tp2;
		tp2.x = 0;
		tp2.y = -100;
		double ang = Angle(tp,tp2);
		if(ans[i].x < cx) {
			ang = 2*PI - ang;
		}
		ang = ang / PI * 180;
		an.push_back(ang);
	}
	//--------------------------------------临近的角度并为同一角度，并记录个数,按个数从大到小排序
	std::sort(an.begin(),an.end(),cmp);
	vector <pair<double,int> > pp;
	pp.push_back(make_pair(an[0],1));
	for(int i = 1;i < an.size();++i) {
		bool flag = true;
		for(int j = 0;j < pp.size();++j) {
			if(fabs(an[i] - pp[j].first) < 5) {
				pp[j].second ++; 
				flag = false;
				break;
			}
		}
		if(flag) pp.push_back(make_pair(an[i],1));
	}
	std::sort(pp.begin(),pp.end(),cmp2);
	//---------------------------------------------d
	int shi,fen,miao;
	if(pp.size() >= 3) {
		shi = pp[0].first / 360 * 12;
		fen = pp[1].first / 360 * 60;
		if(pp[0].first - shi * 30 <= 5 && fen >= 55) {
			fen = 0;
		} else if(pp[0].first - shi * 30 >= 25 && fen <= 5) {
			shi ++;
		}else if(fen == 60 ) {
			shi ++;
			fen = 0;
		}
		miao = pp[2].first / 360 * 60;
	} else if(pp.size() >= 2){
		shi = pp[0].first / 360 * 12;
		fen = pp[0].first / 360 * 60;
		if(pp[0].first - shi * 30 <= 5 && fen >= 55) {
			fen = 0;
		} else if(pp[0].first - shi * 30 >= 25 && fen <= 5) {
			shi ++;
		}else if(fen == 60 ) {
			shi ++;
			fen = 0;
		}
		miao = pp[1].first / 360 * 60;
	} else {
		shi = pp[0].first / 360 * 12;
		fen = pp[0].first / 360 * 60;
		if(pp[0].first - shi * 30 <= 5 && fen >= 55) {
			fen = 0;
		} else if(pp[0].first - shi * 30 >= 25 && fen <= 5) {
			shi ++;
		}else if(fen == 60 ) {
			shi ++;
			fen = 0;
		}
		miao = pp[0].first / 360 * 60;
	}
	//cout<<shi<<"    "<<fen<<"    "<<miao<<endl;
	//-----------------------------------------------------------------------显示时分秒
	int wcsLen;
	wchar_t* wszString;
	sprintf(mShi,"%d",shi);
	//预转换，得到所需空间的大小
	wcsLen = ::MultiByteToWideChar(CP_ACP, NULL, mShi, strlen(mShi), NULL, 0);
	//分配空间要给'\0'留个空间，MultiByteToWideChar不会给'\0'空间
	wszString = new wchar_t[wcsLen + 1];
	//转换
	::MultiByteToWideChar(CP_ACP, NULL, mShi, strlen(mShi), wszString, wcsLen);
	//最后加上'\0'
	wszString[wcsLen] = '\0';
	GetDlgItem(IDC_EDITS)->SetWindowTextW(wszString);

	sprintf(mFen,"%d",fen);
	//预转换，得到所需空间的大小
	wcsLen = ::MultiByteToWideChar(CP_ACP, NULL, mFen, strlen(mFen), NULL, 0);
	//分配空间要给'\0'留个空间，MultiByteToWideChar不会给'\0'空间
	wszString = new wchar_t[wcsLen + 1];
	//转换
	::MultiByteToWideChar(CP_ACP, NULL, mFen, strlen(mFen), wszString, wcsLen);
	//最后加上'\0'
	wszString[wcsLen] = '\0';
	GetDlgItem(IDC_EDITF)->SetWindowTextW(wszString);

	sprintf(mMiao,"%d",miao);
	//预转换，得到所需空间的大小
	wcsLen = ::MultiByteToWideChar(CP_ACP, NULL, mMiao, strlen(mMiao), NULL, 0);
	//分配空间要给'\0'留个空间，MultiByteToWideChar不会给'\0'空间
	wszString = new wchar_t[wcsLen + 1];
	//转换
	::MultiByteToWideChar(CP_ACP, NULL, mMiao, strlen(mMiao), wszString, wcsLen);
	//最后加上'\0'
	wszString[wcsLen] = '\0';
	GetDlgItem(IDC_EDITM)->SetWindowTextW(wszString);

	GetDlgItem(IDC_EDITSS)->SetWindowTextW(_T("SUCCESS"));

}

void CTime_detectorDlg::cvThin( IplImage* src, IplImage* dst, int iterations) {
	//此时的src是一个二值化的图片  
	CvSize size = cvGetSize(src);  
	cvCopy(src, dst);  

	int n = 0,i = 0,j = 0;  
	for(n=0; n<iterations; n++)//开始进行迭代  
	{  
		IplImage* t_image = cvCloneImage(dst);  
		for(i=0; i<size.height;  i++)  
		{  
			for(j=0; j<size.width; j++)  
			{  
				if(CV_IMAGE_ELEM(t_image,byte,i,j) == 1)  
				{  
					int ap=0;  
					int p2 = (i==0)?0:CV_IMAGE_ELEM(t_image,byte, i-1, j);  
					int p3 = (i==0 || j==size.width-1)?0:CV_IMAGE_ELEM(t_image,byte, i-1, j+1);  
					if (p2==0 && p3==1)  
					{  
						ap++;  
					}  

					int p4 = (j==size.width-1)?0:CV_IMAGE_ELEM(t_image,byte,i,j+1);  
					if(p3==0 && p4==1)  
					{  
						ap++;  
					}  

					int p5 = (i==size.height-1 || j==size.width-1)?0:CV_IMAGE_ELEM(t_image,byte,i+1,j+1);  
					if(p4==0 && p5==1)  
					{  
						ap++;  
					}  

					int p6 = (i==size.height-1)?0:CV_IMAGE_ELEM(t_image,byte,i+1,j);  
					if(p5==0 && p6==1)  
					{  
						ap++;  
					}  

					int p7 = (i==size.height-1 || j==0)?0:CV_IMAGE_ELEM(t_image,byte,i+1,j-1);  
					if(p6==0 && p7==1)  
					{  
						ap++;  
					}  

					int p8 = (j==0)?0:CV_IMAGE_ELEM(t_image,byte,i,j-1);  
					if(p7==0 && p8==1)  
					{  
						ap++;  
					}  

					int p9 = (i==0 || j==0)?0:CV_IMAGE_ELEM(t_image,byte,i-1,j-1);  
					if(p8==0 && p9==1)  
					{  
						ap++;  
					}  
					if(p9==0 && p2==1)  
					{  
						ap++;  
					}  

					if((p2+p3+p4+p5+p6+p7+p8+p9)>1 && (p2+p3+p4+p5+p6+p7+p8+p9)<7)  
					{  
						if(ap==1)  
						{  
							if(!(p2 && p4 && p6))  
							{  
								if(!(p4 && p6 && p8))   
								{  
									CV_IMAGE_ELEM(dst,byte,i,j)=0;//设置目标图像中像素值为0的点  
								}  
							}  
						}  
					}  

				}  
			}  
		}  

		cvReleaseImage(&t_image);  

		t_image = cvCloneImage(dst);  
		for(i=0; i<size.height;  i++)  
		{  
			for(int j=0; j<size.width; j++)  
			{  
				if(CV_IMAGE_ELEM(t_image,byte,i,j) == 1)  
				{  
					int ap=0;  
					int p2 = (i==0)?0:CV_IMAGE_ELEM(t_image,byte, i-1, j);  
					int p3 = (i==0 || j==size.width-1)?0:CV_IMAGE_ELEM(t_image,byte, i-1, j+1);  
					if (p2==0 && p3==1)  
					{  
						ap++;  
					}  
					int p4 = (j==size.width-1)?0:CV_IMAGE_ELEM(t_image,byte,i,j+1);  
					if(p3==0 && p4==1)  
					{  
						ap++;  
					}  
					int p5 = (i==size.height-1 || j==size.width-1)?0:CV_IMAGE_ELEM(t_image,byte,i+1,j+1);  
					if(p4==0 && p5==1)  
					{  
						ap++;  
					}  
					int p6 = (i==size.height-1)?0:CV_IMAGE_ELEM(t_image,byte,i+1,j);  
					if(p5==0 && p6==1)  
					{  
						ap++;  
					}  
					int p7 = (i==size.height-1 || j==0)?0:CV_IMAGE_ELEM(t_image,byte,i+1,j-1);  
					if(p6==0 && p7==1)  
					{  
						ap++;  
					}  
					int p8 = (j==0)?0:CV_IMAGE_ELEM(t_image,byte,i,j-1);  
					if(p7==0 && p8==1)  
					{  
						ap++;  
					}  
					int p9 = (i==0 || j==0)?0:CV_IMAGE_ELEM(t_image,byte,i-1,j-1);  
					if(p8==0 && p9==1)  
					{  
						ap++;  
					}  
					if(p9==0 && p2==1)  
					{  
						ap++;  
					}  
					if((p2+p3+p4+p5+p6+p7+p8+p9)>1 && (p2+p3+p4+p5+p6+p7+p8+p9)<7)  
					{  
						if(ap==1)  
						{  
							if(p2*p4*p8==0)  
							{  
								if(p2*p6*p8==0)  
								{  
									CV_IMAGE_ELEM(dst, byte,i,j)=0;  
								}  
							}  
						}  
					}                      
				}  

			}  

		}              
		cvReleaseImage(&t_image);  
	}  

}

void CTime_detectorDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	//MessageBox(_T("hehe"));
	if(!flag1) return ;
	flag1 = false;
	CRect rect;
	GetDlgItem(IDC_STATIC)->GetClientRect(&rect);
	flag2 = false;
	if(point.x > rect.left && point.x < rect.right && point.y > rect.top && point.y < rect.bottom) {
		//do something
		cenx = (point.x - 22)*1.0/(rect.right - rect.left) * src->width;
		ceny = (point.y - 15)*1.0 / (rect.bottom - rect.top) * src->height;
		flag2 = true;
	}

	CDialogEx::OnLButtonDown(nFlags, point);
}


void CTime_detectorDlg::OnBnClickedOk2()
{
	// TODO: 在此添加控件通知处理程序代码
	if(!have_src) return ;
	if(flag1 == false) flag1 = true;
	else flag1 = false;
}

CvSeq*  CTime_detectorDlg::findSquares4( IplImage* img, CvMemStorage* storage )
{
	CvSeq* contours;
	int i, c, l, N = 11;
	CvSize sz = cvSize( img->width & -2, img->height & -2 );
	IplImage* timg = cvCloneImage( img ); // make a copy of input image
	IplImage* gray = cvCreateImage( sz, 8, 1 ); 
	IplImage* pyr = cvCreateImage( cvSize(sz.width/2, sz.height/2), 8, 3 );
	IplImage* tgray;
	CvSeq* result;
	double s, t;
	// create empty sequence that will contain points -
	// 4 points per square (the square's vertices)
	CvSeq* squares = cvCreateSeq( 0, sizeof(CvSeq), sizeof(CvPoint), storage );

	// select the maximum ROI in the image
	// with the width and height divisible by 2
	cvSetImageROI( timg, cvRect( 0, 0, sz.width, sz.height ));

	// down-scale and upscale the image to filter out the noise
	cvPyrDown( timg, pyr, 7 );
	cvPyrUp( pyr, timg, 7 );
	tgray = cvCreateImage( sz, 8, 1 );

	// find squares in every color plane of the image
	for( c = 0; c < 3; c++ )
	{
		// extract the c-th color plane
		cvSetImageCOI( timg, c+1 );
		cvCopy( timg, tgray, 0 );

		// try several threshold levels
		for( l = 0; l < N; l++ )
		{
			// hack: use Canny instead of zero threshold level.
			// Canny helps to catch squares with gradient shading   
			if( l == 0 )
			{
				// apply Canny. Take the upper threshold from slider
				// and set the lower to 0 (which forces edges merging) 
				cvCanny( tgray, gray, 0, 50, 5 );
				// dilate canny output to remove potential
				// holes between edge segments 
				cvDilate( gray, gray, 0, 1 );
			}
			else
			{
				// apply threshold if l!=0:
				//     tgray(x,y) = gray(x,y) < (l+1)*255/N ? 255 : 0
				cvThreshold( tgray, gray, (l+1)*255/N, 255, CV_THRESH_BINARY );
			}

			// find contours and store them all as a list
			cvFindContours( gray, storage, &contours, sizeof(CvContour),
				CV_RETR_LIST, CV_CHAIN_APPROX_SIMPLE, cvPoint(0,0) );

			// test each contour
			while( contours )
			{
				// approximate contour with accuracy proportional
				// to the contour perimeter
				result = cvApproxPoly( contours, sizeof(CvContour), storage,
					CV_POLY_APPROX_DP, cvContourPerimeter(contours)*0.02, 0 );
				// square contours should have 4 vertices after approximation
				// relatively large area (to filter out noisy contours)
				// and be convex.
				// Note: absolute value of an area is used because
				// area may be positive or negative - in accordance with the
				// contour orientation
				if( result->total == 4 &&
					fabs(cvContourArea(result,CV_WHOLE_SEQ)) > 1000 &&
					cvCheckContourConvexity(result) )
				{
					s = 0;

					for( i = 0; i < 5; i++ )
					{
						// find minimum angle between joint
						// edges (maximum of cosine)
						if( i >= 2 )
						{
							t = fabs(angle(
								(CvPoint*)cvGetSeqElem( result, i ),
								(CvPoint*)cvGetSeqElem( result, i-2 ),
								(CvPoint*)cvGetSeqElem( result, i-1 )));
							s = s > t ? s : t;
						}
					}

					// if cosines of all angles are small
					// (all angles are ~90 degree) then write quandrange
					// vertices to resultant sequence 
					if( s < 0.01 )
						for( i = 0; i < 4; i++ )
							cvSeqPush( squares,
							(CvPoint*)cvGetSeqElem( result, i ));
				}

				// take the next contour
				contours = contours->h_next;
			}
		}
	}

	// release all the temporary images
	cvReleaseImage( &gray );
	cvReleaseImage( &pyr );
	cvReleaseImage( &tgray );
	cvReleaseImage( &timg );

	return squares;
}

void CTime_detectorDlg::clearbg2(IplImage* src, double x,double y,double r1,double r2) {
	CvSize size = cvGetSize(src); 
	int i,j;
	CvScalar s;
	for(i=0; i<src->height;  i++)  
	{  
		for(j=0; j<src->width; j++)
		{  
			if(abs(i - x) > r1 || abs(j - y) > r2) {
				s = cvGet2D(src,i,j); // get the (i,j) pixel value
				s.val[0]=255;
				s.val[1]=255;
				s.val[2]=255; 
				cvSet2D(src,i,j,s);//set the (i,j) pixel value
			}
		}  
	} 
	return ;
}

void CTime_detectorDlg::clearbg(IplImage* src, double x,double y,double r) {
	CvSize size = cvGetSize(src); 
	int i,j;
	CvScalar s;
	for(i=0; i<src->height;  i++)  
	{  
		for(j=0; j<src->width; j++)
		{  
			if(dis(i,j,x,y) > r*r) {
				s = cvGet2D(src,i,j); // get the (i,j) pixel value
				s.val[0]=255;
				s.val[1]=255;
				s.val[2]=255; 
				cvSet2D(src,i,j,s);//set the (i,j) pixel value
			}
		}  
	} 
	return ;
}