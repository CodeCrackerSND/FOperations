// FOperationsDlg.cpp : implementation file
//

#include "stdafx.h"
#include "FOperations.h"
#include "FOperationsDlg.h"

#define mod %
#define or |
#define xor ^
#define and &
#define not ~

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CFOperationsDlg dialog




CFOperationsDlg::CFOperationsDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CFOperationsDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CFOperationsDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT4, C_Text);
}

BEGIN_MESSAGE_MAP(CFOperationsDlg, CDialog)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_BUTTON1, &CFOperationsDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CFOperationsDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CFOperationsDlg::OnBnClickedButton3)
END_MESSAGE_MAP()


// CFOperationsDlg message handlers

BOOL CFOperationsDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here

	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CFOperationsDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CFOperationsDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CFOperationsDlg::OnBnClickedButton1()
{
	// TODO: Add your control notification handler code here
char A_ValC[22];
GetDlgItem(IDC_EDIT2)->GetWindowText(A_ValC, 22);
if (A_ValC[0]==0)
{
GetDlgItem(IDC_STATIC4)->SetWindowText("Please enter A value!!!");
return;
}

char B_ValC[22];
GetDlgItem(IDC_EDIT3)->GetWindowText(B_ValC, 22);
if (B_ValC[0]==0)
{
GetDlgItem(IDC_STATIC4)->SetWindowText("Please enter B value!!!");
return;
}

char C_ValC[22];
GetDlgItem(IDC_EDIT4)->GetWindowText(C_ValC, 22);
if (C_ValC[0]==0)
{
GetDlgItem(IDC_STATIC4)->SetWindowText("Please enter C value!!!");
return;
}

char * pEnd;
long A = strtol(A_ValC,&pEnd,10);
long B = strtol(B_ValC,&pEnd,10);
long C = strtol(C_ValC,&pEnd,10);

long FResult = A xor (B or (not C));;
char buf[4*2+1] = {0}; // one extra byte for null
sprintf(buf,"%ld", FResult);

GetDlgItem(IDC_EDIT1)->SetWindowText(buf);

}

CString local_r;
void NumbtoBinaryStrRec(unsigned int n)
{
    local_r=(n%2==0 ?"0":"1")+local_r;
    if (n / 2 != 0) {
        NumbtoBinaryStrRec(n / 2);
    }

}

CString NumbtoBinaryStr(unsigned int n)
{
	local_r = "";
	NumbtoBinaryStrRec(n);
    return local_r;
}



void CFOperationsDlg::OnBnClickedButton2()
{
	// TODO: Add your control notification handler code here
char A_ValC[22];
GetDlgItem(IDC_EDIT2)->GetWindowText(A_ValC, 22);
if (A_ValC[0]==0)
{
GetDlgItem(IDC_STATIC4)->SetWindowText("Please enter A value!!!");
return;
}

char B_ValC[22];
GetDlgItem(IDC_EDIT3)->GetWindowText(B_ValC, 22);
if (B_ValC[0]==0)
{
GetDlgItem(IDC_STATIC4)->SetWindowText("Please enter B value!!!");
return;
}

char F_ValC[22];
GetDlgItem(IDC_EDIT1)->GetWindowText(F_ValC, 22);
if (F_ValC[0]==0)
{
GetDlgItem(IDC_STATIC4)->SetWindowText("Please enter F value!!!");
return;
}

char * pEnd;
long A = strtol(A_ValC,&pEnd,10);
long B = strtol(B_ValC,&pEnd,10);
long F = strtol(F_ValC,&pEnd,10);

long Formula2 = F xor A;  // Formula2 = (B or (Not C))
CString result = NumbtoBinaryStr(Formula2);
CString B_bits = NumbtoBinaryStr(B);
// (B or (Not C)) = 0 only if B = 0 and C = 1 else is 1

while (result.GetLength()<32)
result = '0'+result;  // append some zeros

while (B_bits.GetLength()<32)
B_bits = '0'+B_bits; // append some zeros

CString C_computed = "";

for (int i=result.GetLength()-1;i>=0;i--)
{

TCHAR result_bit = '0';
if (i<result.GetLength())
result_bit = result.GetAt(i);

TCHAR B_bit = '0';
if (i<B_bits.GetLength())
B_bit = B_bits.GetAt(i);

TCHAR C_bit = '0';

// 0 or 0 = 0
// 1 or 0 = 1
// 0 or 1 = 1
// 1 or 1 = 1

// B or Not C
// 0 or (Not 0) = 1
// 1 or (Not 0) = 1
// 0 or (Not 1) = 0
// 1 or (Not 1) = 1

if (result_bit=='0'&&B_bit=='0')
C_bit = '1';
else if (result_bit=='0'&&B_bit=='1')
C_computed = "ERROR";  // this is impossible
else if (result_bit=='1'&&B_bit=='1')
C_bit = 'x';  // any of 0 or 1
else if (result_bit=='1'&&B_bit=='0')
C_bit = '0';

C_computed = C_bit+C_computed;

}

GetDlgItem(IDC_EDIT4)->SetWindowText(C_computed);


}

CString ReplaceBinaryX(CString binary)
{


	for (int i=0;i<binary.GetLength();i++)
	{

	if (tolower(binary.GetAt(i))=='x')
	{
	int rand_num = (rand()&01)+'0';  // only 0 or 1
	binary.SetAt(i,rand_num);
	}

	}

	return binary;

}

unsigned int GetIntFromBinaryStr(char *buffer)
{
   unsigned int result1 = 0;
   int startIndex = 0;
   bool negativeNumber = false;

   if (buffer[0] == '-')
   {
   negativeNumber = true;
   startIndex = 1;
   }


   for (int i = startIndex; i < (int)strlen(buffer); i++)
   {

      if (buffer[i] >= '0' && buffer[i] <= '1')
      {
         unsigned int digit = buffer[i] - '0';
         result1 = result1 * 2 + digit;
      }
      else
      return 0;
	}
 

   if (negativeNumber == true)
      result1 *= -1;

   return result1;
}



void CFOperationsDlg::OnBnClickedButton3()
{
	// TODO: Add your control notification handler code here

CString binary_mask;
C_Text.GetWindowText(binary_mask);

if (binary_mask.GetLength()==0)
return;

CString real_binary_gen = ReplaceBinaryX(binary_mask);
unsigned int numb1 = GetIntFromBinaryStr(real_binary_gen.GetBuffer(0));
char* converted1 = new char[4*3+1];
converted1[0] = 00;
wsprintf(converted1,"%d", numb1);  // convert int number to decimal string

C_Text.SetWindowText(converted1);


}
