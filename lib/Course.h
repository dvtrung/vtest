
class CCourse
{
public:
	CCourse(void);
	~CCourse(void);

	CString m_strCourseTitle;
	CString m_strAuthor;
	CString m_strSubject;
	CString m_strDesc;

	CStringArray m_Tree1Arr;
	CArray<int,int> m_Tree2ArrType;
	CStringArray m_Tree2ArrStr;
	CArray<int,int> m_Tree2ArrIndex;

	void LoadFromFile(CString strPath);
};
