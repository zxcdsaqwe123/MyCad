﻿
// MyCadView.h: CMyCadView 类的接口
//

#pragma once
#define MAXEDITNUM 1000;

class CMyCadView : public CView
{
protected: // 仅从序列化创建
	CMyCadView() noexcept;
	DECLARE_DYNCREATE(CMyCadView)

// 特性
public:
	CMyCadDoc* GetDocument() const;

// 操作
public:

// 重写
public:
	virtual void OnDraw(CDC* pDC);  // 重写以绘制该视图
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 实现
public:
	virtual ~CMyCadView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	afx_msg void OnFilePrintPreview();
//	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()


public:
	struct Points	//保存像素点链表
	{
		int x, y;	//像素点位置
		COLORREF color;	//像素点颜色
		Points * next;
	};

	typedef struct StepPoints		//每一步绘制的点数据
	{
		int step;		//第step步
		Points  point;	//当前操作步骤链表头节点
	}*pStepPoints;

	enum Type {
		LINE,
		RECT,
		CIRCLE
	};


	typedef struct EditStep
	{
		Type type;	//绘制类型
		CPoint centerPoint;	//图形中心点
		Points point;	//关键点链表
	}pEditStep;

	int currentStep = 0;	//当前已经操作了的操作步骤
	int currentEditStep = 0;		//当前正在修改的图形所在步骤

	StepPoints stepPoints[1000];//存储每一步绘制的像素点，保存1000条操作记录
	EditStep editSteps[1000];//记录每一步的绘制类型，及其关键点
	CPoint beginPoint, endPoint;	//开始绘制点和结束绘制点
	bool beginTransform = false;	//记录当前是否进行移动


	void DrawPoints(CDC *pDC);	//绘制点
	void CMyCadView::SetLine(CPoint p1, CPoint p2, COLORREF color,int s);	//设置线条,s为设置的步骤
	void SetTreeDialog(int num, CString str);	//设置树状图
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnExportImage();

	virtual BOOL PreTranslateMessage(MSG* pMsg);
	
};

#ifndef _DEBUG  // MyCadView.cpp 中的调试版本
inline CMyCadDoc* CMyCadView::GetDocument() const
   { return reinterpret_cast<CMyCadDoc*>(m_pDocument); }
#endif

