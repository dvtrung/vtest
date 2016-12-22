// DlgViewTestStruct.cpp : implementation file
//

#include "stdafx.h"
#include "VTestLib.h"
#include "DlgViewTestStruct.h"
#include "afxdialogex.h"


// CDlgViewTestStruct dialog

IMPLEMENT_DYNAMIC(CDlgViewTestStruct, CDialog)

CDlgViewTestStruct::CDlgViewTestStruct(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgViewTestStruct::IDD, pParent)
{

}

CDlgViewTestStruct::~CDlgViewTestStruct()
{
	delete m_Font;
}

void CDlgViewTestStruct::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TREE, m_Tree);
}


BEGIN_MESSAGE_MAP(CDlgViewTestStruct, CDialog)
	ON_BN_CLICKED(IDC_BTN_CHANGEQUEST, &CDlgViewTestStruct::OnBnClickedBtnChangequest)
	ON_BN_CLICKED(IDC_BTN_VIEW_INFO, &CDlgViewTestStruct::OnBnClickedBtnViewInfo)
	ON_BN_CLICKED(IDOK, &CDlgViewTestStruct::OnBnClickedOk)
	ON_BN_CLICKED(ID_EXPORT, &CDlgViewTestStruct::OnBnClickedExport)
END_MESSAGE_MAP()


// CDlgViewTestStruct message handlers


BOOL CDlgViewTestStruct::OnInitDialog()
{
	CDialog::OnInitDialog();

	m_Font=new Gdiplus::Font(L"Times New Roman",10);

	CRect rectQView;
	GetDlgItem(IDC_STATIC_QUESTVIEW_LOC)->GetWindowRect(&rectQView);
	ScreenToClient(&rectQView);
	m_QuestView.Create(L"QuestView",L"",WS_CHILD | WS_VISIBLE | WS_VSCROLL, rectQView,this,2);
	m_QuestView.m_Items.m_Width=rectQView.Width();
	//m_QuestView.m_Items.m_tInfo;
	
	m_QuestView.m_Items.m_Font=m_Font;
	m_QuestView.m_Items.m_bDispose=false;
	m_QuestView.m_bAllowSelect=true;

	srand((unsigned)time(NULL));

	for (int i=0;i<m_struct->m_arr.GetSize();i++)
	{
		CArray<int,int> idArr;
		m_TagArray->Filter(*m_struct->m_arr[i],idArr);

		for (int j=0;j<idArr.GetSize();j++)
		{
			for (int k=0;k<m_QuestView.m_Items.GetSize();k++) {
				if (m_QuestArray->GetAt(idArr[j])==m_QuestView.m_Items[k]) { idArr.RemoveAt(j); j--; break; }
			}
		}

		if (idArr.GetSize()!=0)
		{
			CItemBase* it=m_QuestArray->GetAt(idArr[rand()%idArr.GetSize()]);

			if (it->m_Type==ItemQuestABCD) {
				((CQuestItemABCD*)it)->m_Mode=QuestMode::ShowAnswer;
				((CQuestItemABCD*)it)->m_bShowHint=false;

				m_QuestView.m_Items.m_Array.Add(it);
				m_QuestView.m_Items.RedrawItem(it);
			}
		}
		else (AfxMessageBox(L"Không có chọn lựa hợp lệ cho câu "+IntToString(i+1)));
	}

	m_QuestView.m_Items.ResetIndex();
	m_QuestView.RefreshScrollBar();

	m_Tree.InitStateImageList();

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}


void CDlgViewTestStruct::OnBnClickedBtnChangequest()
{
	int i=m_QuestView.m_Items.m_hlItem;
	if (i==-1) return;
	CArray<int,int> idArr;
	m_TagArray->Filter(*m_struct->m_arr[i],idArr);

	for (int j=0;j<idArr.GetSize();j++)
	{
		for (int k=0;k<m_QuestView.m_Items.GetSize();k++) {
			if (m_QuestArray->GetAt(idArr[j])==m_QuestView.m_Items[k]) { idArr.RemoveAt(j); j--; break; }
		}
	}

	if (idArr.GetSize()!=0)
	{
		srand((unsigned)time(NULL));
		CItemBase* it=m_QuestArray->GetAt(idArr[rand()%idArr.GetSize()]);

		if (it->m_Type=ItemQuestABCD) {
			((CQuestItemABCD*)it)->m_Mode=QuestMode::ShowAnswer;
			((CQuestItemABCD*)it)->m_bShowHint=false;
		}

		m_QuestView.m_Items.m_Array[i]=it;
		m_QuestView.m_Items.RedrawItem(it);
		m_QuestView.m_Items.ResetIndex();
		m_QuestView.RefreshScrollBar();
	}
}


void CDlgViewTestStruct::OnBnClickedBtnViewInfo()
{
	CString str;
// 	for (int i=0;i<m_TagArray->m_TagName.GetSize();i++)
// 	{
// 		CString s=m_struct->m_arr[m_QuestView.m_Items.m_hlItem]->GetAt(i);
// 		if (s=="") s=L"Tất cả";
// 		if (i!=0) str+=L"\n";
// 		str+=L"• "+m_TagArray->m_TagName[i] + L" : ";
// 		str+=s;
// 	}
	if (m_QuestView.m_Items.m_hlItem==-1) return;
	int id=-1;
	for (int i=0;i<m_QuestArray->GetSize();i++) if (m_QuestArray->GetAt(i)==m_QuestView.m_Items[m_QuestView.m_Items.m_hlItem]) { id=i; break; }

	for (int i=0;i<m_TagArray->m_TagName.GetSize();i++)
	{
		CString s=m_TagArray->m_Array[id]->m_arrTagItem[i];
		if (i!=0) str+=L"\n";
		str+=L"• "+m_TagArray->m_TagName[i] + L" : ";
		str+=s;
	}

	AfxMessageBox(str,MB_ICONINFORMATION);
}


void CDlgViewTestStruct::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	CDialog::OnOK();
}


void CDlgViewTestStruct::OnBnClickedExport()
{
	CItemArray itArr; itArr.m_bDispose=false;
	CTestInfo tInfo;
	itArr.m_tInfo=&tInfo;
	for (int i=0;i<m_QuestView.m_Items.GetSize();i++) itArr.m_Array.Add(m_QuestView.m_Items[i]);

	{
		CFileDialog dlgFile(FALSE, NULL , NULL, 
			OFN_OVERWRITEPROMPT | OFN_DONTADDTORECENT,
			L"Test Files (*.vtest)|*.vtest||", AfxGetMainWnd(), 0, FALSE);
		if (dlgFile.DoModal()==IDOK)
		{
			CString strPath=dlgFile.GetPathName();
			if (strPath.Right(6)!=L".vtest") strPath+=L".vtest";
			tInfo.m_nTime=0;
			tInfo.m_strAuthor=L"VTestLib";

			CFile f; 
			f.Open(strPath,CFile::modeWrite | CFile::modeCreate);
			CArchive ar(&f,CArchive::store);
			tInfo.Serialize(ar);
			itArr.Serialize(ar);
			ar.Close();
			f.Close();

			if (!ShellExecute(NULL, NULL, L"VTest.exe", strPath, NULL, SW_SHOW))
				AfxMessageBox(L"Có lỗi khi mở tập tin");
		}
	}
}
