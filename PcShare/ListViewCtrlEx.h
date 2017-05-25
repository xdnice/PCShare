/******************************************************************************

$Author$
  
$Modtime$
$Revision$

Description: Interfaces of the classes "CListCtrlEx" and "CListViewEx"
             (list control and list view with sort icons and
              colored sort column)

$Log$

******************************************************************************/

#pragma once

/*** Defines not yet available in MS VC++ 6.0 ********************************/
#ifndef COLOR_HOTLIGHT
#define COLOR_HOTLIGHT 26
#endif

//#define LPUINT UINT*
typedef UINT* LPUINT;

/*** Declaration of "workhorse" class "CListBase" ****************************/
class CListCtrlHelper;

class CListBase
{
  public:
   CListBase();
  ~CListBase();

  void         ColorSortColumn   (BOOL bEnable = TRUE, int nSortColumn = 0);
  virtual void DrawSmallIcon     (CDC* pDC, LVITEM* pItem, LPRECT pRect);
  virtual void DrawStateIcon     (CDC* pDC, LVITEM* pItem, LPRECT pRect);
  virtual void DrawSubItemText   (CDC* pDC, LVITEM* pItem, LVCOLUMN* pColumn,
                                  LPRECT pRect);
  void         EnableColumnHiding(int nColumn, bool bEnableIt = true);
  void         EnableSortIcon    (BOOL bEnable = true, int nSortColumn = 0);

  int GetColumnCount() const
  {
    return static_cast<int>(m_aColumnData.GetSize());
  }

  POSITION GetFirstCheckedItemPosition() const;
  int      GetNextCheckedItem         (POSITION& pos) const;
  int      GetSortColumn() const {return m_nSortColumn;}
  bool     GetState     (LPBYTE* ppState, LPUINT pnStateLen) const;
  bool     KeepLabelLeft(bool bKeepLeft = true);
  bool     RestoreState (LPCTSTR pszSection, LPCTSTR pszEntry);
  bool     SaveState    (LPCTSTR pszSection, LPCTSTR pszEntry) const;
  void     SetSortColumn(int nColumn);
  bool     SetState     (LPBYTE pState, UINT nStateLen);
  void     ShowColumn   (int nColumn, bool bShowIt = true);

	private:
  enum VISUAL_STYLE {Unknown, NotPresent, Present};

  friend class CListCtrlEx;
  friend class CListViewEx;

  struct COLUMN_DATA
  {
     COLUMN_DATA(): m_bHidingAllowed(false),
                    m_bVisible      (true),
                    m_nWidth        (0),
                    m_nOrder        (0),
                    m_pLVColumn     (0) {}
    ~COLUMN_DATA();

    bool      m_bHidingAllowed;
    bool      m_bVisible;
    int       m_nWidth;
    int       m_nOrder;
    LVCOLUMN* m_pLVColumn;
  };

  struct ITEM_DATA
  {
     ITEM_DATA(): m_lParam(0) {}
    ~ITEM_DATA();

    LPARAM                   m_lParam;
    CArray<LVITEM*, LVITEM*> m_apLVItem;
  };

  static int CALLBACK CompareFunc          (LPARAM lParam1, LPARAM lParam2,
                                            LPARAM lParamSort);
  void                CreateSortIcons      ();
  void                DrawItem             (LPDRAWITEMSTRUCT lpDrawItemStruct);
  LVCOLUMN*           DupLVColumn          (LVCOLUMN* pLVColumn) const;
  LVITEM*             DupLVItem            (LVITEM* pLVItem) const;
  int                 GetLabelWidth        (CDC* pDC, LVITEM* pItem,
                                            int nMaxWidth) const;
  LVITEM*             GetLVITEM            (int nItem, int nSubItem = 0) const;
  int                 GetLogicalIndex      (int nPhysicalColumn) const;
  int                 GetLogicalOrder      (int nPhysicalOrder) const;
  int                 GetPhysicalIndex     (int nColumnIndex) const;
  int                 GetPhysicalOrder     (int nColumnOrder) const;
  bool                GetRealSubItemRect   (int iItem, int iSubItem, int nArea,
                                            CRect& ref);
  bool                GetStateIconRect     (int nItem, LPRECT pRect);
  int                 IndexToOrder         (int nIndex);
  void                InvalidateNonItemArea();
  void                JustifyFirstColumn   (int nFormat);
	BOOL                OnColumnclick        (NMHDR* pNMHDR, LRESULT* pResult);
  BOOL                OnCommand            (WPARAM wParam);
	void                OnContextMenu        (CWnd* pWnd);
	void                OnCustomDraw         (NMHDR* pNMHDR, LRESULT* pResult);
  LRESULT             OnDeleteAllItems     ();
  LRESULT             OnDeleteColumn       (WPARAM wParam);
  LRESULT             OnDeleteItem         (WPARAM wParam);
	void                OnDestroy            ();
	BOOL                OnEraseBkgnd         (CDC* pDC);
  LRESULT             OnFindItem           (WPARAM wParam, LPARAM lParam);  
  LRESULT             OnGetColumn          (WPARAM wParam, LPARAM lParam);
  LRESULT             OnGetColumnWidth     (WPARAM wParam);
  LRESULT             OnGetColumnOrderArray(WPARAM wParam, LPARAM lParam);
  BOOL                OnGetdispinfo        (NMHDR* pNMHDR);
  LRESULT             OnGetItem            (LPARAM lParam);
  LRESULT             OnGetItemText        (WPARAM wParam, LPARAM lParam);
  int                 OnHitTest            (LPARAM lParam);
  void                OnHScroll            ();
  LRESULT             OnInsertColumn       (WPARAM wParam, LPARAM lParam);
  LRESULT             OnInsertItem         (LPARAM lParam);
	void                OnKeyDown            (UINT nChar);
	void                OnKeyUp              (UINT nChar);
	void                OnKillFocus          ();
	void                OnLButtonDblClk      (CPoint point);
	void                OnLButtonDown        (CPoint point);
  void                OnLButtonUp          ();
  void                OnMouseMove          (CPoint point) ;
	BOOL                OnNotify             (LPARAM lParam);
  BOOL                OnODCacheHint        (NMHDR* pNMHDR);
  LRESULT             OnSetBkColor         ();
  LRESULT             OnSetColumn          (WPARAM wParam, LPARAM lParam);
  LRESULT             OnSetColumnOrderArray(WPARAM wParam, LPARAM lParam);
  LRESULT             OnSetColumnWidth     (WPARAM wParam, LPARAM lParam);
  LRESULT             OnSetExtendedStyle   (WPARAM wParam, LPARAM lParam);
	void                OnSetFocus           ();
  LRESULT             OnSetImageList       (WPARAM wParam, LPARAM lParam);
  LRESULT             OnSetItem            (LPARAM lParam);
  LRESULT             OnSetItemText        (WPARAM wParam, LPARAM lParam);
  LRESULT             OnSortItems          (WPARAM wParam, LPARAM lParam);
	void                OnSysColorChange     ();
  int                 OrderToIndex         (int nOrder);
  void                PrepareHotUnderlining();
  void                SetHotCursor         (const CPoint& point);
  void                SetSortIcon          ();

  static VISUAL_STYLE                m_visualStyle;
  static const int                   m_nFirstColXOff;
  static const int                   m_nNextColXOff;
  int                                m_nIconXOff; // offset of icon may vary of
                                                  // unknown reason
  CListCtrlHelper*                   m_pListCtrl;
  CArray<COLUMN_DATA*, COLUMN_DATA*> m_aColumnData;
  int                                m_nColumnHidingAllowed;
  BOOL                               m_bSortIconEnabled;
  BOOL                               m_bColorSortColumn;
  CImageList                         m_imglstSortIcons;
  CBitmap                            m_bmpUpArrow;
  CBitmap                            m_bmpDownArrow;
  int                                m_nUpArrow;
  int                                m_nDownArrow;
  DWORD                              m_dwColSortColor;
  int                                m_nSortColumn;
  int                                m_nFormatOfSubItem0;
  bool                               m_bKeepLabelLeft;
  bool                               m_bLocked;
  bool                               m_bControl;
  bool                               m_bIconXOffCalculated;
  DWORD                              m_dwExtendedStyle;
  int                                m_nHotItem;
  COLORREF                           m_dwHotLite;
  HCURSOR                            m_hcursorCustom;
  HCURSOR                            m_hcursorArrow;
  HCURSOR                            m_hcursorHand;
  PFNLVCOMPARE                       m_pfnLVCompare;
  LPARAM                             m_lParamSort;
  int                                m_nFirstCachedItem;
  int                                m_nLastCachedItem;
  bool                               m_bOnGetDispinfo;
};


/*** Declaration of class "CListCtrlEx" **************************************/
class CListCtrlEx: public CListCtrl, public CListBase
{
  DECLARE_DYNCREATE(CListCtrlEx);

  public:
  CListCtrlEx() {m_pListCtrl = reinterpret_cast<CListCtrlHelper*>(this);}

  virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct)
  {
    CListBase::DrawItem(lpDrawItemStruct);
  }

  virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);

  // Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CListViewCtrl)
	protected:
	virtual BOOL OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult);
	//}}AFX_VIRTUAL

	// Generated message map functions
  protected:
	//{{AFX_MSG(CListCtrlEx)
	afx_msg void OnSysColorChange();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnKillFocus(CWnd* pNewWnd);
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnDestroy();
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	//}}AFX_MSG
	afx_msg BOOL    OnColumnclick        (NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void    OnCustomDraw         (NMHDR* pNMHDR, LRESULT* pResult);
  afx_msg LRESULT OnDeleteAllItems     (WPARAM, LPARAM);
  afx_msg LRESULT OnDeleteColumn       (WPARAM wParam, LPARAM);
  afx_msg LRESULT OnDeleteItem         (WPARAM wParam, LPARAM);
  afx_msg LRESULT OnFindItem           (WPARAM wParam, LPARAM lParam);  
  afx_msg LRESULT OnGetColumn          (WPARAM wParam, LPARAM lParam);
  afx_msg LRESULT OnGetColumnOrderArray(WPARAM wParam, LPARAM lParam);
  afx_msg LRESULT OnGetColumnWidth     (WPARAM wParam, LPARAM);
  afx_msg BOOL    OnGetdispinfo        (NMHDR* pNMHDR, LRESULT*);
  afx_msg LRESULT OnGetExtendedStyle   (WPARAM, LPARAM);
  afx_msg LRESULT OnGetItem            (WPARAM, LPARAM lParam);
  afx_msg LRESULT OnGetItemText        (WPARAM wParam, LPARAM lParam);
  afx_msg LRESULT OnHitTest            (WPARAM, LPARAM lParam);
  afx_msg LRESULT OnInsertColumn       (WPARAM wParam, LPARAM lParam);
  afx_msg LRESULT OnInsertItem         (WPARAM, LPARAM lParam);
  afx_msg BOOL    OnODCacheHint        (NMHDR* pNMHDR, LRESULT*);
  afx_msg LRESULT OnSetBkColor         (WPARAM, LPARAM);
  afx_msg LRESULT OnSetColumn          (WPARAM wParam, LPARAM lParam);
  afx_msg LRESULT OnSetColumnOrderArray(WPARAM wParam, LPARAM lParam);
  afx_msg LRESULT OnSetColumnWidth     (WPARAM wParam, LPARAM lParam);
  afx_msg LRESULT OnSetExtendedStyle   (WPARAM wParam, LPARAM lParam);
  afx_msg LRESULT OnSetImageList       (WPARAM wParam, LPARAM);
  afx_msg LRESULT OnSetItem            (WPARAM, LPARAM lParam);
  afx_msg LRESULT OnSetItemText        (WPARAM wParam, LPARAM lParam);
  afx_msg LRESULT OnSortItems          (WPARAM wParam, LPARAM lParam);

	DECLARE_MESSAGE_MAP()
};


/*** Declaration of class "CListViewEx" **************************************/
class CListViewEx: public CListView, public CListBase
{
  DECLARE_DYNCREATE(CListViewEx);

  public:
  CListViewEx()
  {
    m_pListCtrl = reinterpret_cast<CListCtrlHelper*>(&GetListCtrl());
  }

  virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct)
  {
    CListBase::DrawItem(lpDrawItemStruct);
  }

  virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);

  // Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CListViewCtrl)
	protected:
	virtual BOOL OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult);
	//}}AFX_VIRTUAL

	// Generated message map functions
  protected:
	//{{AFX_MSG(CListViewEx)
	afx_msg void OnSysColorChange();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnKillFocus(CWnd* pNewWnd);
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnDestroy();
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	//}}AFX_MSG
	afx_msg BOOL    OnColumnclick        (NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void    OnCustomDraw         (NMHDR* pNMHDR, LRESULT* pResult);
  afx_msg LRESULT OnDeleteAllItems     (WPARAM, LPARAM);
  afx_msg LRESULT OnDeleteColumn       (WPARAM wParam, LPARAM);
  afx_msg LRESULT OnDeleteItem         (WPARAM wParam, LPARAM);
  afx_msg LRESULT OnFindItem           (WPARAM wParam, LPARAM lParam);  
  afx_msg LRESULT OnGetColumn          (WPARAM wParam, LPARAM lParam);
  afx_msg LRESULT OnGetColumnOrderArray(WPARAM wParam, LPARAM lParam);
  afx_msg LRESULT OnGetColumnWidth     (WPARAM wParam, LPARAM);
  afx_msg BOOL    OnGetdispinfo        (NMHDR* pNMHDR, LRESULT*);
  afx_msg LRESULT OnGetExtendedStyle   (WPARAM, LPARAM);
  afx_msg LRESULT OnGetItem            (WPARAM, LPARAM lParam);
  afx_msg LRESULT OnGetItemText        (WPARAM wParam, LPARAM lParam);
  afx_msg LRESULT OnHitTest            (WPARAM, LPARAM lParam);
  afx_msg LRESULT OnInsertColumn       (WPARAM wParam, LPARAM lParam);
  afx_msg LRESULT OnInsertItem         (WPARAM, LPARAM lParam);
  afx_msg BOOL    OnODCacheHint        (NMHDR* pNMHDR, LRESULT*);
  afx_msg LRESULT OnSetBkColor         (WPARAM, LPARAM);
  afx_msg LRESULT OnSetColumn          (WPARAM wParam, LPARAM lParam);
  afx_msg LRESULT OnSetColumnOrderArray(WPARAM wParam, LPARAM lParam);
  afx_msg LRESULT OnSetColumnWidth     (WPARAM wParam, LPARAM lParam);
  afx_msg LRESULT OnSetExtendedStyle   (WPARAM wParam, LPARAM lParam);
  afx_msg LRESULT OnSetImageList       (WPARAM wParam, LPARAM);
  afx_msg LRESULT OnSetItem            (WPARAM, LPARAM lParam);
  afx_msg LRESULT OnSetItemText        (WPARAM wParam, LPARAM lParam);
  afx_msg LRESULT OnSortItems          (WPARAM wParam, LPARAM lParam);

	DECLARE_MESSAGE_MAP()
};
