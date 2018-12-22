
// PL0_compilerDlg.cpp: 实现文件
//

#include "stdafx.h"
#include "PL0_compiler.h"
#include "PL0_compilerDlg.h"
#include "afxdialogex.h"
#include "PL0.h"
#include "interpret.h"
#include <string>
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CPL0compilerDlg 对话框



CPL0compilerDlg::CPL0compilerDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_PL0_COMPILER_DIALOG, pParent)
	, m_fileName(_T(""))
	, m_inputCode(_T(""))
	, m_input(_T(""))
	, m_output(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CPL0compilerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_MFCEDITBROWSE1, m_fileName);
	DDX_Text(pDX, IDC_EDIT1, m_inputCode);
	DDX_Text(pDX, IDC_EDIT2, m_input);
	DDX_Control(pDX, IDC_LIST1, m_listCtrl);
	DDX_Text(pDX, IDC_EDIT3, m_output);
}

BEGIN_MESSAGE_MAP(CPL0compilerDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CPL0compilerDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDC_BUTTON2, &CPL0compilerDlg::OnBnClickedButton2)
END_MESSAGE_MAP()


// CPL0compilerDlg 消息处理程序

BOOL CPL0compilerDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
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

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	canInterpret = -1;
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CPL0compilerDlg::OnSysCommand(UINT nID, LPARAM lParam)
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
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CPL0compilerDlg::OnPaint()
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
HCURSOR CPL0compilerDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

LPCWSTR stringToLPCWSTR(std::string orig)
{
	size_t origsize = orig.length() + 1;
	const size_t newsize = 100;
	size_t convertedChars = 0;
	wchar_t *wcstring = (wchar_t *)malloc(sizeof(wchar_t)*(orig.length() - 1));
	mbstowcs_s(&convertedChars, wcstring, origsize, orig.c_str(), _TRUNCATE);

	return wcstring;
}

void CPL0compilerDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	m_input = "";
	m_output = "";
	//在左边显示代码
	CFile inputCodeFile;
	inputCodeFile.Open(m_fileName, CFile::modeRead, NULL);
	DWORD len = inputCodeFile.GetLength();
	char Buf[10000];
	Buf[len] = 0;
	inputCodeFile.Read(Buf, len);
	m_inputCode = Buf;
	

	vector<vector<string>> str = compiler(Buf, len);
	m_listCtrl.DeleteAllItems();
	DWORD dwStyle = m_listCtrl.GetExtendedStyle();
	dwStyle |= LVS_EX_FULLROWSELECT;
	dwStyle |= LVS_EX_GRIDLINES;
	m_listCtrl.SetExtendedStyle(dwStyle);
	if (str[0][0] == "ok")
	{
		canInterpret = 1;
		for(int i = 0; i <= 3; i++)
			m_listCtrl.DeleteColumn(0);
		m_listCtrl.InsertColumn(0, _T(" "), LVCFMT_LEFT, 45);
		m_listCtrl.InsertColumn(1, _T("PCode"), LVCFMT_LEFT, 100);
		m_listCtrl.InsertColumn(2, _T("l"), LVCFMT_LEFT, 100);
		m_listCtrl.InsertColumn(3, _T("a"), LVCFMT_LEFT, 100);
	}
	else
	{
		canInterpret = 0;
		for (int i = 0; i <= 3; i++)
			m_listCtrl.DeleteColumn(0);
		m_listCtrl.InsertColumn(0, _T(" "), LVCFMT_LEFT, 45);
		m_listCtrl.InsertColumn(1, _T("行数"), LVCFMT_LEFT, 50);
		m_listCtrl.InsertColumn(2, _T("列数"), LVCFMT_LEFT, 50);
		m_listCtrl.InsertColumn(3, _T("错误信息"), LVCFMT_LEFT, 200);
	}
	for (int i = 1; i < str.size(); i++)
	{
		string tmp = to_string(i);
		LPCTSTR sss = stringToLPCWSTR(tmp);
		int row = m_listCtrl.InsertItem(i + 1, sss);
		for (int j = 0; j < 3; j++)
			m_listCtrl.SetItemText(row, j + 1, stringToLPCWSTR(str[i][j]));
	}
	UpdateData(FALSE);
}


void CPL0compilerDlg::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	if (canInterpret == 0)
	{
		if (MessageBox(_T("please debug and interpret again"), _T("error!"), MB_YESNO | MB_ICONWARNING) == IDNO)
		return;
	}
	else if (canInterpret == -1)
	{
		if (MessageBox(_T("please choose your PL0 code file"), _T("error!"), MB_YESNO | MB_ICONWARNING) == IDNO)
			return;
	}
	else
	{
		//获取编辑框内容
		UpdateData(TRUE);
		CString strEditStr;//编辑框的内容
		CString strTemp;//用于分割的临时字符串
		int inputValue[100];
		memset(inputValue, -573249, sizeof(inputValue));
		strEditStr = m_input;//strEditStr为编辑框内的多行内容
		//将编辑框的内容根据换行符分割开
		CStringArray editArr;
		int nPos = strEditStr.Find(_T('\n'));
		strTemp = _T("");
		while (0 <= nPos)
		{
			strTemp = strEditStr.Left(nPos);
			if (!strTemp.IsEmpty())
				editArr.Add(strTemp);
			strEditStr = strEditStr.Right(strEditStr.GetLength() - nPos - 1);
			nPos = strEditStr.Find(_T('\n'));
		}
		if (!strEditStr.IsEmpty())
		{
			editArr.Add(strEditStr);
		}//多行字符串分割完毕
		//此时editArr里面保存的就是每一行的内容，可以用editArr.GetAt(i)进行访问
		int i;
		for (i = 0; i < editArr.GetCount(); i++)
			inputValue[i] = _ttoi(editArr.GetAt(i));
		string res = interpret(inputValue, i);
		m_output = res.c_str();

		UpdateData(FALSE);
	}
}
