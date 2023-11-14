/* ZXJ10.H
   Copyright(c) 1993-1997. (ZTE)Shenzhen Zhongxing New Telecom Equip. Co. Ltd.
   Research Institute of Nanjing Zhongxing New Telecom.
   All rights reserved. */

#ifndef __ZXEVENT_H
#define __ZXEVENT_H

/*---------------------For R04 Event: B<--->R04----------------------*/
#define PPSYS                 1
#define PPSYSEND              33
#define RestartEvent          (WORD16)(PPSYS+0x0000)   /*EXE PP From 0xF000:0*/
#define MpR04DataEvent        (WORD16)(PPSYS+0x0001)
#define ResetAplication       (WORD16)(PPSYS+0x0002)   /*EXE PP From 0xC000:0*/
#define BWConnectPath         (WORD16)(PPSYS+0x0003)
#define TnetDelayEvent        (WORD16)(PPSYS+0x0004)
#define BWConnectionAck       (WORD16)(PPSYS+0x0005)
#define TnetReqToneHWEvent    (WORD16)(PPSYS+0x0006)

// main or backup define
#define MAINBACK              10
#define MAINBACKEND           29
#define PrepReqTypeEvent      (WORD16)(MAINBACK+0)
#define ReqTypeEvent          (WORD16)(MAINBACK+1)
#define ReqTypeAck1Event      (WORD16)(MAINBACK+2)
#define ReqTypeAck2Event      (WORD16)(MAINBACK+3)
#define ReqSunitEvent         (WORD16)(MAINBACK+4)
#define ReqSunitAckEvent      (WORD16)(MAINBACK+5)
#define SubStateEvent         (WORD16)(MAINBACK+6)
#define LineStateEvent        (WORD16)(MAINBACK+7)
#define SubStopRingEvent      (WORD16)(MAINBACK+8)
#define SubConnPathEvent      (WORD16)(MAINBACK+9)
#define SubDiscPathEvent      (WORD16)(MAINBACK+10)
#define PortOpEvent           (WORD16)(MAINBACK+11)
#define SendBusyToneEvent     (WORD16)(MAINBACK+12)
#define StopBusyToneEvent     (WORD16)(MAINBACK+13)
#define PrepReqConnectEvent   (WORD16)(MAINBACK+14)
#define ReqConnectEvent       (WORD16)(MAINBACK+15)
#define ReqConnectAckEvent    (WORD16)(MAINBACK+16)
#define SubStartRingEvent     (WORD16)(MAINBACK+17)
/*-------------------------R06 event define--------------------------*/
#define PPR06                 34
#define PPR06End              39
#define ReloadEventFromMP     (WORD16)(PPR06+0x0000)
#define ReloadEventFromPP     (WORD16)(PPR06+0x0001)
/*
#define LoadAlarmEvent        (WORD16)(PPR06+0x0000)
#define RequireLoadEvent      (WORD16)(PPR06+0x0001)
#define RequireLoadAckEvent   (WORD16)(PPR06+0x0002)
#define LoadDataEvent         (WORD16)(PPR06+0x0003)
#define LoadDataAckEvent      (WORD16)(PPR06+0x0004)
#define LoadOKEvent           (WORD16)(PPR06+0x0005)
*/
/*---------------------for R12 event  B<--->R12----------------------*/
#define R12PP                 40
#define R12PPEND              70
#define TestUnitTnetHwEvent   (WORD16)(R12PP+0x0001)
#define DtmfRequestEvent      (WORD16)(R12PP+0x0004)
#define MfcRequestEvent       (WORD16)(R12PP+0x0005)
#define TestTnetMT8985Event   (WORD16)(R12PP+0x0007)
#define TestMPComEvent        (WORD16)(R12PP+0x0008)
#define SP16SelfCallEvent     (WORD16)(R12PP+0x0009)
#define SP16TnetCallEvent     (WORD16)(R12PP+0x000a)
#define TestDtMt8986Event     (WORD16)(R12PP+0x000b)
#define TestSigMT8986Event    (WORD16)(R12PP+0x000d)
#define TEST_C50_EVENT        (WORD16)(R12PP+0x000e)
#define TestTnetMt90820Event  (WORD16)(R12PP+0x0010)
#define MutilModuleHwEvent    (WORD16)(R12PP+0x0011)
#define TestSp24HwEvent       (WORD16)(R12PP+0x0012)
#define SP24SelfCallEvent     (WORD16)(R12PP+0x0013)
#define SP24TnetCallEvent     (WORD16)(R12PP+0x0014)
#define MutilModuleHw2Event   (WORD16)(R12PP+0x0015)
#define MainBackTestEVENT     (WORD16)(R12PP+0x0016)
#define SP24TESTSUNITEVENT    (WORD16)(R12PP+0x0017)

/*--------------------PP Alarm Event to Zhong Wenxing----------------*/
#define PPAlarm               71
#define PPAlarmEnd            89
#define WorstSlipEvent        (WORD16)(PPAlarm+0x0000)
#define NormalSlipEvent       (WORD16)(PPAlarm+0x0001)

/*--------------------------for test 112-----------------------------*/
#define PP112                 90
#define PP112End              95
#define TslcStartTestEvent    (WORD16)(PP112+0x0000)
#define TslcEndTestEvent      (WORD16)(PP112+0x0001)
#define MttTestEvent          (WORD16)(PP112+0x0002)
#define TslcRingEvent         (WORD16)(PP112+0x0003)
#define TslcStopRingEvent     (WORD16)(PP112+0x0004)
#define TslcConver            (WORD16)(PP112+0x0005)

/*----------------------------PPMML event------------------------------*/
#define PPMML                 96
#define PPMMLEnd              127
#define DisplayRamEvent       (WORD16)(PPMML+0x0000)   /*r03 define*/
//#define DispRamAckEvent       (WORD16)(PPMML+0x0001)
#define UpDateRamEvent        (WORD16)(PPMML+0x0002)
#define BlockSLNEvent         (WORD16)(PPMML+0x0003)
#define UnBlockSLNEvent       (WORD16)(PPMML+0x0004)
#define BlockPCMEvent         (WORD16)(PPMML+0x0005)
#define UnBlockPCMEvent       (WORD16)(PPMML+0x0006)
#define BlockBODEvent         (WORD16)(PPMML+0x0007)
#define UnBlockBODEvent       (WORD16)(PPMML+0x0008)
#define ReqBackMsgEvent       (WORD16)(PPMML+0x0009)    /*For Test PP_MP Com*/
#define BackMsgAckEvent       (WORD16)(PPMML+0x000A)

#define BusyToneTSEvent       (WORD16)(PPMML+0x000B)

#define OAMReportPPEvent      (WORD16)(PPMML+0x000C)
#define PPReportOAMEvent      (WORD16)(PPMML+0x000D)
#define S_OAMSendDSPEVENT     (WORD16)(PPMML+0x000C)//used for loading flash tone
#define S_OAMSendBackEVENT    (WORD16)(PPMML+0x000D)

//simucall
#define Simulator             111
#define ReportSimulateInfor   (WORD16)(Simulator+0x0001)
#define GetSimulateInfor      (WORD16)(Simulator+0x0002)
#define ReportPPTroubleInfor  (WORD16)(Simulator+0x0003)

#define PPResponsed           (WORD16)(Simulator+0x0005)
#define StartSimulating       (WORD16)(Simulator+0x0006)
#define StopSimulating        (WORD16)(Simulator+0x0007)
#define RegisterSimulating    (WORD16)(Simulator+0x0008)
#define InstallSimulator      (WORD16)(Simulator+0x0009)
#define UnloadSimulator       (WORD16)(Simulator+0x000a)
#define SimulatorOK           (WORD16)(Simulator+0x000b)
/*----------------------------PPSER event------------------------------*/
#define PPSER                 128
#define PPSEREND              209
#define HookOffEvent          (WORD16)(PPSER+0x0001)
#define HookOffAckEvent       (WORD16)(PPSER+0x0002)
#define InitiateEvent         (WORD16)(PPSER+0x0003)
#define ConLCPathEvent        (WORD16)(PPSER+0x0004)
#define DisLCPathEvent        (WORD16)(PPSER+0x0005)
#define StopDTEvent           (WORD16)(PPSER+0x0006) /* id = 1 DTMF , id = 0 DP*/
#define SendDniEvent          (WORD16)(PPSER+0x0007)
#define AskDeCompleteEvent    (WORD16)(PPSER+0x0008)
#define DeCompleteEvent       (WORD16)(PPSER+0x0009)
#define DeInitiateEvent       (WORD16)(PPSER+0x000a)
#define CalledIdleEvent       (WORD16)(PPSER+0x000b)
#define CalledBusyEvent       (WORD16)(PPSER+0x000c)
#define RingingEvent          (WORD16)(PPSER+0x000d)
#define StopRingEvent         (WORD16)(PPSER+0x000e)
#define FlashEvent            (WORD16)(PPSER+0x0010)
#define DisConnectEvent       (WORD16)(PPSER+0x0011)
#define HookOnEvent           (WORD16)(PPSER+0x0012)
#define BackRingEvent         (WORD16)(PPSER+0x0013)
#define BackCallEvent         (WORD16)(PPSER+0x0014)
#define ReDiscEvent           (WORD16)(PPSER+0x0015)
#define ReRingEvent           (WORD16)(PPSER+0x0016)
#define CompelDiscEvent       (WORD16)(PPSER+0x0017)
#define RelGuardEvent         (WORD16)(PPSER+0x0018)
#define ReleaseSLNEvent       (WORD16)(PPSER+0x0019)
#define SendBTEvent           (WORD16)(PPSER+0x001a)
#define StopBTEvent           (WORD16)(PPSER+0x001b)
#define SendHowlEvent         (WORD16)(PPSER+0x001c)
#define StopHowlEvent         (WORD16)(PPSER+0x001d)
#define TpSlnBusy             (WORD16)(PPSER+0x001e)
#define TpSlnIdle             (WORD16)(PPSER+0x001f)
#define HookOffFwEvent        (WORD16)(PPSER+0x0020)
#define HookOffBwEvent        (WORD16)(PPSER+0x0021)
#define HookOnFwEvent         (WORD16)(PPSER+0x0022)
#define HookOnBwEvent         (WORD16)(PPSER+0x0023)
#define SetPpOprEvent         (WORD16)(PPSER+0x0024)
#define SetPpNormalEvent      (WORD16)(PPSER+0x0025)
#define ReqSTEvent            (WORD16)(PPSER+0x0026)
#define FirstDnEvent          (WORD16)(PPSER+0x0027)
#define SendDnsEvent          (WORD16)(PPSER+0x0028)

#define LCCircleEvent         (WORD16)(PPSER+0x0029)
#define TnetDiscPathEvent     (WORD16)(PPSER+0x002a)
#define TnetConnPathEvent     (WORD16)(PPSER+0x002b)
#define PlayToneEvent         (WORD16)(PPSER+0x002c)
#define StopToneEvent         (WORD16)(PPSER+0x002d)
#define CONNECT_CONF          (WORD16)(PPSER+0x002e)
#define DISCONNECT_CONF       (WORD16)(PPSER+0x002f)
#define TnetConnRingBackEvent (WORD16)(PPSER+0x0030)
#define TnetDiscRingBackEvent (WORD16)(PPSER+0x0031)
#define PermanentCont         (WORD16)(PPSER+0x0032)
#define DisPermanentCont      (WORD16)(PPSER+0x0033)
#define No7TestRstEvent       (WORD16)(PPSER+0x0034)
#define Send16KCEvent         (WORD16)(PPSER+0X0038)
#define CIDEndEvent           (WORD16)(PPSER+0X003A)
#define DSPCidShowReqEvent     (WORD16)(PPSER+0x003C)
#define ConvCidEvent          (WORD16)(PPSER+0X003c)//useless
#define ShowDSPCidEvent        (WORD16)(PPSER+0x003d)
#define StopDSPCidEvent        (WORD16)(PPSER+0x003e)

/*define INAP_PPMessage*/
#define ConnectSpeech         (WORD16)(PPSER+0x0035)
//#define ConnectSpeechS        (WORD16)(PPSER+0x0036)
//#define ConnectSpeechV1       (WORD16)(PPSER+0x0037)
//#define ConnectSpeechV2       (WORD16)(PPSER+0x0038)
#define StopSpeechEvent       (WORD16)(PPSER+0x0036)
#define SpeechOverEvent       (WORD16)(PPSER+0x0037)

/*define V5_PPMphMessage*/

#define TerminalRejEvent        (WORD16)(PPSER+0x39)      /* v5 ring reject */
#define V5_MphAI              (WORD16)(PPSER+0x003f)    /* 第一层链路处于工作状态     */
#define V5_MphDI              (WORD16)(PPSER+0x0040)    /* 第一层链路处于非工作状态   */
#define V5_MphID              (WORD16)(PPSER+0x0041)    /*发送链路ID标识             */
#define V5_MphIDR             (WORD16)(PPSER+0x0042)    /* 发送链路ID标识信息        */
#define V5_MphIDI             (WORD16)(PPSER+0x0043)    /* 链路ID标识指示            */
#define V5_MphNOR             (WORD16)(PPSER+0x0044)    /* 删除链路ID标识             */
#define V5_MphEIaF            (WORD16)(PPSER+0x0045)    /*来自第一层的差错指示        */
#define V5_MphEIg             (WORD16)(PPSER+0x0046)    /* 链路ID标识故障             */

/*use for ccs no.7*/
#define InLoopChnEvent        (WORD16)(PPSER+0x0048)
#define InUnLoopChnEvent      (WORD16)(PPSER+0x0049)
#define OutLoopChnEvent       (WORD16)(PPSER+0x004a)
#define OutUnLoopChnEvent     (WORD16)(PPSER+0x004b)

#define No7TestingEvent       (WORD16)(PPSER+0x004c)
#define No7StopTestEvent      (WORD16)(PPSER+0X004D)

#define ConnectBChanEvent       (WORD16)(PPSER+0x4e)
#define DisconnectBChanEvent    (WORD16)(PPSER+0x4f)

#define ClearAllConf      		232

/*----------------------------PPInner event------------------------------*/
#define PPInner               210
#define PPInnerEnd            255
//r02 define
#define TIMEOUT_MESS          (WORD16)(PPInner+0x0000)
#define SEND_MESS             (WORD16)(PPInner+0x0001)
#define RECEIVE_MESS          (WORD16)(PPInner+0x0002)
#define LINECREATE_MESS       (WORD16)(PPInner+0x0003)
#define RECEIVE_ACK_MESS      (WORD16)(PPInner+0x0004)

//unit inner define
#define UPDATE_UNIT_MESS       (WORD16)(PPInner+0x0005)
#define SUNIT_TYPE_CHANGE_MESS (WORD16)(PPInner+0x0006)
#define BOARD_CHANGE_MESS      (WORD16)(PPInner+0x0007)
#define TEST_UNIT_MESS         (WORD16)(PPInner+0x0008)
#define PULL_BOARD_MESS        (WORD16)(PPInner+0x0009)
#define TEST_SUNIT_MESS        (WORD16)(PPInner+0x000a)

//use by rui
#define AlarmTs0Event         (WORD16)(PPInner+0x000b)
#define MFCOfCodeEvent        (WORD16)(PPInner+0x000c)
#define TerminalEvent         (WORD16)(PPInner+0x000d)
#define EndOfToneEvent        (WORD16)(PPInner+0x000d)

/*  B01_SLC EVENT       */
#define PullBoardEvent        (WORD16)(PPInner+0x000e)
#define InsertBoardEvent      (WORD16)(PPInner+0x000f)
#define SunitMainUseEvent     (WORD16)(PPInner+0x0010)

/* Unit Event*/
#define UnitMainUseEvent      (WORD16)(PPInner+0x0011)
#define UnitBackupUseEvent    (WORD16)(PPInner+0x0012)
#define UnitToMainUseEvent    (WORD16)(PPInner+0x0013)
#define UnitToBackupUseEvent  (WORD16)(PPInner+0x0014)
#define SPIChangeEvent        (WORD16)(PPInner+0x0015)
#define SunitIniEvent         (WORD16)(PPInner+0x0016)

// r12 internal event
#define R12TestNextEvent      (WORD16)(PPInner+0x0017)
#define R12MttRstEvent        (WORD16)(PPInner+0x0018)
#define R12InitiateEvent      (WORD16)(PPInner+0x0019)

// Mtt board
#define MttStartHowEvent      (WORD16)(PPInner+0x001a)
//CID
#define ShowCIDEvent          (WORD16)(PPInner+0x001b)
#define StopCIDEvent          (WORD16)(PPInner+0x001c)

// r12 internal event
#define MainToBackEVENT       (WORD16)(PPInner+0x001d)
#define BackToMainEVENT       (WORD16)(PPInner+0x001e)

// r04 internal event
#define RequireSunitEVENT     (WORD16)(PPInner+0x001f)

// SRF internal event
#define  C50EndPlayEvent      (WORD16)(PPInner+0x0020)
#define  SRFIntervalOut       (WORD16)(PPInner+0x0021)
#define  SRFDurationOut       (WORD16)(PPInner+0x0022)


/*------------------------R01 event define --------------------------*/
#define R01                   0xf000
#define R01End                0xff00
#define Timer1Event           (WORD16)(R01 + 0xe0)
#define Timer2Event           (WORD16)(R01 + 0xe1)
#define Timer3Event           (WORD16)(R01 + 0xe2)
#define Timer4Event           (WORD16)(R01 + 0xe3)
#define Timer5Event           (WORD16)(R01 + 0xe4)
#define Timer6Event           (WORD16)(R01 + 0xe5)
#define Timer7Event           (WORD16)(R01 + 0xe6)
#define Timer8Event           (WORD16)(R01 + 0xe7)
#define PPPowerOnEvent        (WORD16)0x0000
#define PPMasterOnEvent       (WORD16)(R01 +11)
#define PPSlaverOnEvent       (WORD16)(R01 +12)

#define PP_PPInService        (WORD16)(R01 +20)
#define PP_PPOutService       (WORD16)(R01 +21)
/*-------------------------------------------------------------------*/

#endif
