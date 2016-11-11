/*Copyright 2015 Huawei Technologies Co., Ltd. All rights reserved.
eSDK is licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at
		http://www.apache.org/licenses/LICENSE-2.0
Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.*/

// common.h

// espaceframework event/////////////////////////
#define RETCODE_SUCCESS 0
#define RETCODE_ERROR -1
#define RETCODE_REFUSE -2
// P2P
#define EE_P2P_CHOOSE       100
#define EE_P2P_STOP         101
#define EE_P2P_START_RESULT 102
#define EE_P2P_STOP_RESULT  103
#define EE_P2P_PROGRESS     104
#define EE_P2P_VOLUMN       105
#define EE_P2P_RING         106
#define EE_P2P_ONHODE       107
#define EE_P2P_REQUEST_MUTEMIC 108

//增加对IM消息发送通知处理
#define EE_CHAT_SINGLE_ERROR 111
#define EE_CHAT_GROUP_ERROR  112
#define EE_CHAT_TEMPGROUP_ERROR 113
#define EE_CHAT_MULTIMEDIA_NOTIFY 114
#define EE_CHAT_SINGLE_ACK 115
#define EE_CHAT_TEMP_ACK   116
#define EE_CHAT_GROUP_ACK  117
#define EE_CHAT_TEMPGROUP_ACK 118
#define EE_CHAT_MULTIMEETINGS 119
#define EE_CHAT_SINGLE 120
#define EE_CHAT_TEMP   121
#define EE_CHAT_GROUP  122
#define EE_CHAT_TEMPGROUP 123
#define EE_CHAT_NOTIFY 124
#define EE_CHAT_STATUS 125
#define EE_CHAT_NOAUTH 126
#define EE_CHAT_NOTIFY2 127
#define EE_CHAT_AUDIOSTATUS_NOFITY 145

// 讨论组相关
//#define EE_CHAT_DISCUSSIONGROUP  145
//#define EE_CHAT_DISCUSSIONGROUP_ACK  146
//#define EE_CHAT_DISCUSSIONGROUP_ERROR  147
#define EE_DISCUSSION_NOTIFY 148

#define EE_APPDATA 130
#define EE_CHANGE_USERSTATUS 131 
#define EE_P2PDATA 132

#define EE_P2P_CHANNEL_TIMEOUT      128
#define EE_P2P_CHANNEL_PROGRESS     129
#define EE_P2P_CHANNEL_CHOOSE 133
#define EE_P2P_CHANNEL_STOP   134
#define EE_P2P_CHANNEL_START_RESULT 135
#define EE_P2P_CHANNEL_STOP_RESULT  136
#define EE_P2P_CHANNEL_STARTED      137
#define EE_P2P_CHANNEL_STOPED       138
#define EE_P2P_CHANNEL_ONDATA       139
#define EE_P2P_CHANNEL_ONNOTIFY     144

#define EE_SMS_RECEIVE 140
#define EE_SMS_SENDSUCCESS 141
#define EE_SMS_RECEIPT 142
#define EE_SMS_SENDFAIL 143
#define EE_SMS_RECEIPTFAIL 144

//#define EE_MENU_FRIENDLIST_GROUP 150
//#define EE_MENU_FRIENDLIST_USER 151
//#define EE_MENU_FRIENDLIST_DEFAULT 152



#define EE_MENU_CONTACTLIST_FRIEND 150
#define EE_MENU_CONTACTLIST_GROUP 151
#define EE_MENU_CONTACTLIST_CONTACT 152
#define EE_MENU_CONTACTLIST_DEFAULT 153

#define EE_CONTACTLIST_DBCLICK_FRIEND 154
#define EE_CONTACTLIST_DBCLICK_CONTACT 155
#define EE_MENU_IMGROUP_GROUP 158
#define EE_MENU_IMGROUP_USER 159
#define EE_MENU_IMGROUP_DEFAULT 160
#define EE_MENU_IMGROUP_USER_DBCLICK 161
#define EE_MENU_IMGROUP_GROUP_DBCLICK 162

#define EE_MENU_DEPTLIST_DEPT 163
#define EE_MENU_DEPTLIST_USER 164
#define EE_DEPTLIST_DBCLICK 165

#define EE_MENU_MULTISELECTED 166
#define EE_GET_CLIENTTYPE 167
/*******************///wkf39030   IPPhone状态
#define EE_IPPHONE_STATUS 168
#define EE_CONTACTLIST_STARTCALL_CONTACT 156
/*******************///wkf39030   IPPhone状态

#define EE_SIP_MSG_REGISTER_OK            0       // 0 注册成功
#define EE_SIP_MSG_REGISTER_FORBIDDEN     1       // 1 禁止注册(403)
#define EE_SIP_MSG_REGISTER_FAILURE       2       // 2 注册失败
#define EE_SIP_MSG_UNREGISTERED           3       // 3 已经注销

#define EE_SIP_MSG_CALL_START             4       // 3 开始呼出
#define EE_SIP_MSG_CALL_RING              5       // 4 对方振铃
#define EE_SIP_MSG_CALL_RING_NO_SDP       6       // 4 对方振铃,没有SDP
#define EE_SIP_MSG_CALL_ANSWER            7               // 5 对方摘机,非视频
#define EE_SIP_MSG_CALL_REJECT            8              // 6 对方拒绝
#define EE_SIP_MSG_CALL_NO_ANWSER         9           // 7 对方无应答
#define EE_SIP_MSG_CALL_BUSY              10             // 8 对方忙
#define EE_SIP_MSG_CALL_BYE               11           // 9 挂机或呼叫终止
#define EE_SIP_MSG_INCOMING_CALL          12            // 10新来电
#define EE_SIP_MSG_CALL_TREM              13            // 10呼叫被终止
#define EE_SIP_MSG_INCOMING_VIDEOCALL     14            // 10新视频呼叫

#define EE_SIP_MSG_CTD_ANSWER             15               // 11成功
#define EE_SIP_MSG_CTD_NO_ANSWER          16            // 12无应答
#define EE_SIP_MSG_CTD_BUSY               17                 // 13忙
#define EE_SIP_MSG_CTD_REJECT             18               // 14拒绝

#define EE_SIP_MSG_FORWARD_OK             19               // 15呼叫前转成功
#define EE_SIP_MSG_FORWARDING             20               // 16呼叫转移中
#define EE_SIP_MSG_FORWARD_FAILURE        21          // 17呼叫前转失败

#define EE_SIP_MSG_CONF_START             22               // 18会议开始
#define EE_SIP_MSG_CONF_END               23                 // 19会议结束 
#define EE_SIP_MSG_CONF_FAIL              24                // 20创建会议失败
#define EE_SIP_MSG_CONF_COMPERE_COME      25        // 21主持人进会，回调函数的caller是主持人
#define EE_SIP_MSG_CONF_COMPERE_LEAVE     26       // 22主持人离开，回调函数的caller是主持人
#define EE_SIP_MSG_CONF_COME              27                // 23与会者加入会议，回调函数的caller是与会者
#define EE_SIP_MSG_CONF_LEAVE             28               // 24与会者离开会议，回调函数的caller是与会者
#define EE_SIP_MSG_CONF_TALKING_ENABLED   29     // 25与会者得到话语权，回调函数的caller是与会者
#define EE_SIP_MSG_CONF_TALKING_DISABLED  30    // 26与会者失去话语权，回调函数的caller是与会者   
#define EE_SIP_MSG_CONF_ADD_FAIL          31            // 27邀请与会者失败
#define EE_SIP_MSG_CONF_DEL_FAIL          32              // 28踢出与会者失败
#define EE_SIP_MSG_CONF_SPK_FAIL          33            // 29允许发言/禁止发言失败
#define EE_SIP_MSG_CONF_ADD_INCOMING_FAIL 34   // 30将来电加入会议失败
#define EE_SIP_MSG_CONF_INVITE            35   // 30将来电加入会议失败
#define EE_SIP_MSG_CONF_ADD_SUCCESS       36   // 30将来电加入会议失败
#define EE_SIP_MSG_CONF_ADD_FAILED        37   // 30将来电加入会议失败

#define EE_SIP_MSG_ERR_PORT_USED          42      // 35 SIP端口被其他应用占用，此种情况，应用应该退出运行。
#define EE_SIP_MSG_KICKOUT                43    // 36 已经注销

#define EE_SIP_GETFORWARDNO               178    // 获取前转号码
#define EE_SIP_SETFORWARDNO               179    // 设置前转号码

//it热线
#define EE_HOTLINE_HELPACK              180    // 热线响应（分别对客服与求助者响应）
#define EE_HOTLINE_ENDHOTLINE           181   // 结束热线服务（包括取消请求排队）
#define EE_HOTLINE_HELPQUEUESTATUS      182    //排队状态

#define EE_P2P_ERR_TARGET_OFFLINE      (-104)
#define EE_P2P_ERR_TIMEOUT             (-100)
#define EE_P2P_ERR_SELF_BUSY           (-110)
#define EE_P2P_ERR_NOT_P2P_REPLY       (-111)
#define EE_P2P_ERR_PEER_REJECT         (-112)
#define EE_P2P_ERR_PEER_BUSY           (-113)
#define EE_P2P_ERR_UNKNOWN_REPLY       (-114)
#define EE_P2P_ERR_NOT_TALKING_WITH    (-115)
#define EE_P2P_ERR_NO_REQUEST_FROM     (-116)
#define EE_P2P_ERR_NO_FILE_TO_SEND     (-117)
#define EE_P2P_ERR_STARTTALK_ERROR     (-118)
#define EE_P2P_ERR_ACCEPTTALK_ERROR    (-119)
#define EE_P2P_ERR_SENDFILE_ERROR      (-120)
#define EE_P2P_ERR_ACCEPTFILE_ERROR    (-121)
#define EE_P2P_ERR_OPEN_FILE_ERROR     (-122)
#define EE_P2P_ERR_NOT_INCOMING        (-123)
#define EE_P2P_ERR_CANCELLED           (-124)
#define EE_P2P_ERR_FILE_BUSY           (-125)
#define EE_P2P_ERR_SERECTLEVEL         (-126)
#define EE_P2P_ERR_FILE_STOPPED        (-127)
#define EE_P2P_ERR_FILE_IS_EMPTY       (-128)
#define EE_P2P_ERR_START_APP_ERROR     (-129)
#define EE_P2P_ERR_ACCEPT_APP_ERROR    (-130)
#define EE_P2P_ERR_FUTURE_RESULT       (-131)
#define EE_P2P_ERR_COMMMODE_MISMATCH   (-132)
#define EE_P2P_ERR_AUDIO_NO_AUTH	   (-133)
#define EE_P2P_ERR_VIDEO_NO_AUTH	   (-134)
#define EE_P2P_ERR_PEER_IGNORE		   (-135)
//////////////////////////////////////////////////////////////////////////
// function : TrayIcon notify event
// vParam1 : it contains the identifier of the windows "taskbar" icon in which the event occurred. 
// vParam2 : it holds the mouse or keyboard message associated with the event. 
// vParam3 : it specify the current tray icon id that return by IECSMainWindow::AddTrayIcon.
#define EE_TRAYICON_NOTIFY 250

#define EE_LOADALLPLUGIN 251

#define EE_LOADALLDATA 252 //客户端加载所有信息
//////////////////////////////////////////////////////////////////////////
// function : click tip event of message tip dialog.
// vParam1 : it contains the current message tip id value.
#define EE_MSGTIPDLG_CLICK_TIP 260

//显示电话历史记录
#define EE_HISTORY_SHOW_TEL 261
//显示短信历史记录
#define EE_HISTORY_SHOW_SMS 262
//显示彩信历史记录
#define EE_HISTORY_SHOW_MMS 263

#define ECS_SET_MISS_NUMBER_INIT 700

//////////////////////////////////////////////////////////////////////////
//Notify CFrame Event Define
#define EE_EVENT_BEGIN (500)
//////////////////////////////////////////////////////////////////////////
//eventID - ECS_PLUGIN_CREATE_EVENT
//pSender - specified the event send from which plugIn.
//ulParam1 - NULL.
//ulParam2 - NULL.
#define EE_PLUGIN_CREATE_EVENT ( EE_EVENT_BEGIN + 0 )
//////////////////////////////////////////////////////////////////////////
//eventID - ECS_PLUGIN_CREATE_EVENT
//pSender - specified the event send from which plugIn.
//ulParam1 - NULL.
//ulParam2 - NULL.
#define EE_PLUGIN_DESTROY_EVENT ( EE_EVENT_BEGIN + 1 )
//////////////////////////////////////////////////////////////////////////
//eventID - ECS_FRAME_CHANG_EVENT.
//pSender - NULL, reserved.
//ulParam1 - new Frame state.
//ulParam2 - old Frame state.
#define EE_FRAME_CHANG_EVENT ( EE_EVENT_BEGIN + 2 )
//////////////////////////////////////////////////////////////////////////


#define EE_PLUGIN_MINIMIZE_EVENT ( EE_EVENT_BEGIN + 3 )

//通知插件框架准备关闭
#define EE_CLOSE_EVENT ( EE_EVENT_BEGIN + 4 )

//插件不允许框架关闭
#define EE_PLUGIN_DONOT_CLOSE_EVENT ( EE_EVENT_BEGIN + 5 )

//同步某IM群组信息事件
#define EE_FINISH_SYNCGROUPINFO_EVENT ( EE_EVENT_BEGIN + 6 )

//同步某IM群成员事件
#define EE_FINISH_SYNCGROUPMEMBERS_EVENT ( EE_EVENT_BEGIN + 7 )

//删除群组事件
#define EE_FINISH_REMOVEIMGROUP_EVENT ( EE_EVENT_BEGIN + 8 )

//客户端同步完成后通知消息
#define EE_FINISH_SYNC_EVENT ( EE_EVENT_BEGIN + 9 )


//刷新IM头像
#define EE_REFLESH_IMAGE (EE_EVENT_BEGIN + 10)


/*f00152768 add 通知IM窗口点击了拨号盘 2010-12-3*/
#define EE_CLICK_NUMENTER_EVENT (EE_EVENT_BEGIN + 11)
/*end*/
/*f00152768 add 通知IM窗口点击了拨号盘 2010-12-3*/
#define EE_KEYBOARD_DISPALY_EVENT (EE_EVENT_BEGIN + 12)
/*end*/

/*BEGIN : Added by mKF42992 at 2011-6-13 10:02:43*/
/** 通知IM关闭"im.db"文件 */
#define EE_CLOSE_IM_DB (EE_EVENT_BEGIN + 13)

/** 通知IM关闭"meeting.db"文件 */
#define EE_CLOSE_MEETING_DB (EE_EVENT_BEGIN + 14)

/** 通知SMS关闭"sms.db"文件 */
#define EE_CLOSE_SMS_DB (EE_EVENT_BEGIN + 15)
/*END : Added by mKF42992 at 2011-6-13 10:02:43*/

#define EE_CLOSE_IM_DB_ARCHIVE (EE_EVENT_BEGIN + 16)

#define EE_CLOSE_MEETING_DB_ARCHIVE (EE_EVENT_BEGIN + 17)

#define EE_CLOSE_SMS_DB_ARCHIVE (EE_EVENT_BEGIN + 18)

#define EE_CLOUD_MEDIA_MODE_CHANGE (EE_EVENT_BEGIN + 19)

/** 处理关闭现有通话消息 */
#define EE_CLOSE_CALLING (EE_EVENT_BEGIN + 20)

#define EE_IMAINWINDOW_USERSTATUS ( EE_EVENT_BEGIN +  21 )
/*******************///wkf39030   IPPhone状态
#define EE_IMAINWINDOW_IPPHONESTATUS ( EE_EVENT_BEGIN +  22 )

#define EE_IMAINWINDOW_TRAYICON_NOTIFY ( EE_EVENT_BEGIN +  23 )

#define EE_PLUGIN_RESTORE_EVENT ( EE_EVENT_BEGIN + 41 )

#define EE_MSG_TRANSMIT_NOTIFY ( EE_EVENT_BEGIN + 42 )

#define EE_CLOSE_GROUPWIN_WHEN_EXIT (EE_EVENT_BEGIN + 50)

#define EE_DELETE_GROUP_MEMBER_IN_SHOWING_WINDOW (EE_EVENT_BEGIN + 51)

#define EE_FINISH_SYNC_EVENT_USERINFO (EE_EVENT_BEGIN + 52)
/** 处理固定群组成员加入消息 *///wkf39030 问题单DTS2011082306482 
#define EE_ADD_GROUP_MEMBER_IN_SHOWING_WINDOW (EE_EVENT_BEGIN + 53)
//设置IPPHONE联动信息
#define EE_IPPHONE_SET_USESTATUS ( EE_EVENT_BEGIN + 54 )

/** \brief 获取Webcc的信息 */
#define EE_GET_WEBCC_INFO (EE_EVENT_BEGIN + 55)

#define ECS_CLIPBORAD_FORMAT_STRING _T("{C4446E2A-0FA0-4ff7-A033-00E24EC4E85F}")
//

//刷新用户资料信息
#define EE_REFLESH_USERINFO (EE_EVENT_BEGIN + 24)

//通知插件框架准备关闭
#define EE_KICKOUT_EVENT ( EE_EVENT_BEGIN + 25 )

//------------------内部使用------------------------------------------

//msg - ECS_MSG_TRANSMIT_NOTIFY
//wParam - specified the notify event id 
//lParam - specified the "ulParam1" parameter in DoNotify function.
//////////////////////////////////////////////////////////////////////////
//eventID - ECS_PLUGIN_RESTORE_EVENT
//pSender - specified the event send from which plugIn.
//ulParam1 - NULL.
//ulParam2 - NULL.


////eventID - ECS_SIPMSG_INCOMING_ANSWER_EVENT
//pSender - NULL, reserved.
//ulParam1 - specified the point of caller name.
//ulParam2 - specified the call id.
//////////////////////////////////////////////////////////////////////////
//eventID - ECS_IM_WANT_TO_SHOW_UI_EVENT
//pSender - NULL.
//ulParam1 - NULL.
//ulParam2 - NULL.
//////////////////////////////////////////////////////////////////////////
//eventID - ECS_IMAINWINDOW_TRAYICON_NOTIFY
//pSender - NULL
//ulParam1 - NULL
//ulParam2 - NULL
//remark : CMainWindow will receive the event, when trayicon receive msg.

/*******************///wkf39030   IPPhone状态
//eventID - ECS_MSGTIPDLG_CLICK_TIP
//pSender - NULL
//ulParam1 - specified the current MsgTipID
//ulParam2 - NULL
//remark : 
//#define EE_MSGTIPDLG_CLICK_TIP ( EE_EVENT_BEGIN +  30 )
//////////////////////////////////////////////////////////////////////////
//eventID - ECS_TEL_WANT_TO_CREATE_NOTIFYBAR
//
//


#define IMDB_MSG_ADDCHATRECORD				1
#define IMDB_MSG_ADDTEMPCHATCONTACT			2
#define IMDB_MSG_ADDGROUPCHATRECORD			3
#define IMDB_MSG_ADDORUPDATECHATGROUP		4
#define IMDB_MSG_ADDHOTLINECHATCONTACT		5
#define IMDB_MSG_ADDSIPRECORD				6
#define MEETINGDB_MSG_ADDCONFRECORD			7
#define MEETINGDB_MSG_ADDATTENDERRECORD		8
