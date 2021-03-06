// MainDlg.h : interface of the CMainDlg class
//
/////////////////////////////////////////////////////////////////////////////
#pragma once

#include "UDPHelper.h"
#include "DataCenter.h"

#include "Adapter_Lasttalk.h"
#include "Adapter_SearchResult.h"
#include "Adapter_Contact.h"
#include "Adapter_EmotionTileView.h"

class CMainDlg : public SHostWnd
	, public TAutoEventMapReg<CMainDlg>
	, public CAdapter_Lasttalk::IListener
	, public CAdapter_Contact::IListener
{
public:
	CMainDlg();
	~CMainDlg();

	//托盘通知消息处理函数
	//LRESULT OnIconNotify(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL/* bHandled*/);
	//演示如何响应菜单事件

	void OnSize(UINT nType, CSize size);
	void OnCommand(UINT uNotifyCode, int nID, HWND wndCtl);
	int OnCreate(LPCREATESTRUCT lpCreateStruct);
	BOOL OnInitDialog(HWND wndFocus, LPARAM lInitParam);

public://适配器相关回调函数
	void LasttalkItemClick(int nType, const std::string& strID);
	void LasttalkItemRClick(int nType, const std::string& strID);
	void LasttalkItemDelete(int nType, const std::string& strID);

	void ContactItemClick(int nType, const std::string& strID);
	void ContactItemRClick(int nType, const std::string& strID);
	void ContactItemDBClick(int nType, const std::string& strID);

private://内部处理相关函数
	void InitLasttalkList();

protected://控件相关响应函数
	void OnClose();
	void OnMaximize();
	void OnRestore();
	void OnMinimize();

	void OnBnClickMessage();
	void OnBnClickContact();

	void OnBnClickSearchCancel();
	bool OnEditSearchSetFocus(EventArgs* pEvt);
	bool OnEditSearchKillFocus(EventArgs* pEvt);
	bool OnEditSearchChanged(EventArgs *e);

protected://事件中心相关响应函数
	void OnBindPortFailed(EventArgs* e);
	void OnFindDevice(EventArgs* e);
	void OnBroadcastRequest(EventArgs* e);
	void OnSendText(EventArgs* e);
	void OnSendImage(EventArgs* e);
	void OnSendFile(EventArgs* e);
	void OnSendAudio(EventArgs* e);
	void OnSendVideo(EventArgs* e);
protected:
	//soui消息
	EVENT_MAP_BEGIN()
		EVENT_NAME_COMMAND(L"btn_close", OnClose)
		EVENT_NAME_COMMAND(L"btn_min", OnMinimize)
		EVENT_NAME_COMMAND(L"btn_max", OnMaximize)
		EVENT_NAME_COMMAND(L"btn_restore", OnRestore)

		EVENT_NAME_COMMAND(L"btn_message", OnBnClickMessage)
		EVENT_NAME_COMMAND(L"btn_contact", OnBnClickContact)
		
		EVENT_NAME_COMMAND(L"search_cancel", OnBnClickSearchCancel)
		EVENT_NAME_HANDLER(L"search_edit", EventSetFocus::EventID, OnEditSearchSetFocus)
		EVENT_NAME_HANDLER(L"search_edit", EventKillFocus::EventID, OnEditSearchKillFocus)
		EVENT_ID_HANDLER(R.id.search_edit, EventRENotify::EventID, OnEditSearchChanged)

		EVENT_ID_HANDLER(CDataCenter::ObjectId, EventBindPortFailed::EventID, OnBindPortFailed)
		EVENT_ID_HANDLER(CDataCenter::ObjectId, EventFindDevice::EventID, OnFindDevice)
		EVENT_ID_HANDLER(CDataCenter::ObjectId, EventBroadcastRequest::EventID, OnBroadcastRequest)
		EVENT_ID_HANDLER(CDataCenter::ObjectId, EventSendText::EventID, OnSendText)
		EVENT_ID_HANDLER(CDataCenter::ObjectId, EventSendImage::EventID, OnSendImage)
		EVENT_ID_HANDLER(CDataCenter::ObjectId, EventSendFile::EventID, OnSendFile)
		EVENT_ID_HANDLER(CDataCenter::ObjectId, EventSendAudio::EventID, OnSendAudio)
		EVENT_ID_HANDLER(CDataCenter::ObjectId, EventSendVideo::EventID, OnSendVideo)
	EVENT_MAP_END()
		
	//HostWnd真实窗口消息处理
	BEGIN_MSG_MAP_EX(CMainDlg)
		MSG_WM_CREATE(OnCreate)
		MSG_WM_INITDIALOG(OnInitDialog)
		MSG_WM_CLOSE(OnClose)
		MSG_WM_SIZE(OnSize)
	//托盘消息处理
		//MESSAGE_HANDLER(WM_ICONNOTIFY, OnIconNotify)
		MSG_WM_COMMAND(OnCommand)
		CHAIN_MSG_MAP(SHostWnd)
		REFLECT_NOTIFICATIONS_EX()
	END_MSG_MAP()
private:
	BOOL			m_bLayoutInited;	

	CAdapter_Lasttalk*	m_pAdapterLasttalk;
	CAdapter_Contact*	m_pAdapterContact;
};
