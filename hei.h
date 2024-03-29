/*
**
**  HOST ETHERNET INTERFACE (HEI) - HEADER FILE
**
**	Copyright 1996-2001 - Host Automation Products, Inc.
*
*/
#ifndef HEI_H
#define HEI_H

#include "heidefs.h"

/* Force structure alignment on single byte boundary */
#pragma pack(1)

#if !defined(P_ERMA) & !defined(P_ECOM)  & !defined(EBC) & !defined(P_ERMA) & !defined(BOOTER) & !defined(PROFIBUS)
typedef struct
	{
	unsigned IgnoreUserMain : 1;
	unsigned IgnoreVbUserMain : 1;
	unsigned IgnoreDebugMsg : 1;
	unsigned UnusedBits : 29;
	BYTE UnusedBytes[28];
	} StartupSettings;
#endif

typedef struct
	{
	WORD SizeofEthernetStats;
	DWORD MissedFrameCount;
	DWORD TransmitCollisionCount;
	DWORD DiscardedPackets;
	DWORD BadCRCCount;                             
	
	DWORD UnknownTypeCount;
	DWORD SendErrorCount;
	} EthernetStats;     

typedef struct
	{
	BYTE Version;
	BYTE Bytes2Follow;
	
#if defined (ANSI_C)
	BYTE UnusedBytess[16];							/* Support Info */
#else	
	BYTE SUP_FUN_POLLING 				: 1;			/* Polling one base */
	BYTE SUP_FUN_READ_VER_INFO			: 1; 			/* Version Info */
	BYTE SUP_FUN_READ_SUPPORT_INFO		: 1;			/* Support Info */
	BYTE SUP_FUN_READ_DEVICE_INFO		: 1;			/* Device Info  */
	BYTE SUP_FUN_POLLING_ALL			: 1; 			/* Polling all bases (returns ethernet address) */
	BYTE SUP_FUN_WRITE_IO				: 1;			/* Write IO base */
	BYTE SUP_FUN_READ_IO				: 1;			/* Read IO Base */
	BYTE SUP_FUN_READ_BASE_DEF			: 1; 			/* ReadBaseDef */
	
	BYTE SUP_FUN_ENUM_SETUP_DATA		: 1;			/* Enumerate setup data */
	BYTE SUP_FUN_READ_SETUP_DATA   		: 1;			/* Read setup data */
	BYTE SUP_FUN_WRITE_SETUP_DATA		: 1;			/* Write setup data */
	BYTE SUP_FUN_DELETE_SETUP_DATA		: 1; 			/* Delete setup data */
	BYTE SUP_FUN_READ_ETHERNET_STATS	: 1; 			/* Read ethernet statistics */
	BYTE SUP_FUN_PET_LINK				: 1; 			/* Used to keep the link sense timer from firing in the absense of ReadIO or WriteIO messages */
	BYTE SUP_FUN_ADDRESSED_BROADCAST	: 1; 			/* Used to broadcast to a particular ethernet address. */
	BYTE SUP_FUN_READ_MODULE_STATUS		: 1;			/* Read module status short BYTEs */
	
	BYTE SUP_FUN_EXTENDED				: 1;			/* Extended function */
	BYTE SUP_FUN_QUERY_SETUP_DATA		: 1;			/* Query for particular data type/value */
	BYTE SUP_FUN_INIT_BASE_DEF 			: 1;			/* Initialize base def from backplane. */
	BYTE SUP_FUN_DATA_BROADCAST			: 1;			/* Broadcast to a particular data type */
	BYTE SUP_FUN_CCM_REQUEST			: 1;			/* Perform CCM Request */
	BYTE SUP_FUN_KSEQ_REQUEST			: 1;			/* Perform KSEQ Request */
	BYTE SUP_FUN_BACKPLANE_REQUEST		: 1;			/* Perform backplane request */
	BYTE SUP_FUN_WRITE_BASE_DEF			: 1;			/* Write Base Def */
	
	BYTE SUP_FUN_EXTEND_RESPONSE		: 1;			/* Extends the response packet. */
	BYTE SUP_FUN_ACK					: 1;			/* Acknowledge */
	BYTE SUP_FUN_NAK					: 1;			/* NOT Acknowledge */
	BYTE SUP_FUN_RESPONSE			 	: 1;			/* Response */
	BYTE SUP_FUN_SERIAL_PORT			: 1;			/* Execute serial port function (see below) */
	BYTE SUP_FUN_WRITE_MEMORY			: 1;			/* Write a particular memory type */
	BYTE SUP_FUN_READ_MEMORY			: 1;			/* Read a particular memory type */
	BYTE SUP_FUN_ENUM_MEMORY			: 1;			/* Get list of all memory types */

	BYTE SUP_FUN_READ_SHARED_RAM		: 1;			/* Read shared ram */
	BYTE SUP_FUN_WRITE_SHARED_RAM		: 1;			/* Write shared ram */
	BYTE SUP_FUN_ACCESS_MEMORY			: 1;			/* Access (read/write) multiple memory types */
	BYTE SUP_FUN_COMM_RESPONSE			: 1;			/* Response to PLC generated COMM request */
	BYTE SUP_FUN_COMM_REQ_ACK			: 1;			/* Function from PLC generated COMM request */
	BYTE SUP_FUN_WRITE_IO_NO_READ 	: 1;			/* Write IO base with returned read */
	BYTE SUP_FUN_COMM_NO_REQ_ACK		: 1;		/* Function from PLC generated COMM request */
	BYTE SUP_FUN_RUN_PROGRAM			: 1;			/* Function to execute a program */

	BYTE SUP_FUN_REMOTE_API				: 1; 	/* Function to execute a function on remote device */
	BYTE SUP_FUN_NOTIFY					: 1; 	/* Indicates a notification */
	BYTE SUP_FUN_COMPLETION				: 1; 	/* Indicates completion of some activity */
	BYTE SUP_FUN_SET_OS_LOAD			: 1; 	/* Set Load OS Parm. */
	BYTE SUP_FUN_REBOOT					: 1; 	/* Reboot OS			*/
	BYTE SUP_FUN_EXTEND_RESPONSE_FIX	: 1;	/* Fixed version that extends the response packet. */
	BYTE SUP_NEW_STYLE_IO				: 1;	/* This device supports new style I/O requests */
	BYTE SUP_HOT_SWAP						: 1;	/* True if this device supports hot swap */

	BYTE SUP_TCP_IP						: 1;  /* TRUE if this device supports TCP/IP */
	BYTE SUP_HTTP							: 1;  /* TRUE if this device supports HTTP */
	BYTE Reserved							: 6;	
	
	BYTE UnusedBytes[9];							/* Unused */
#endif	
	} SupportDef;


/* Defines for Flags in WPLCSystemInformation structure */
#define WPLC_FLAG_BATT_LOW	0x01

/* Masks for LED indicator */
#define WPLC_LED_POWER	0x01
#define WPLC_LED_RUN		0x02


typedef struct
	{
	DWORD Flags;			/* Bit 0: Battery Low indicator.		*/
								/* Bit 1-31: Unused						*/
	DWORD RAMSize;			/* Total size of RAM in WinPLC	*/
	DWORD FlashSize;		/* Total size of Flash memory in WinPLC	*/
	DWORD BattRAMSize;	/*	Total size of Battery-backed ram in WinPLC	*/
	DWORD DipSwitches;	/* Status of dip switches	*/
								/* Note: Dip Switches #6 & #7 are reserved for system use.	*/
	DWORD LEDs;				/* LED status indicator (see WPLC_LED_XXXX defines)	*/

	DWORD OSSize;			/* Size of the WinPLC OS Image	*/

	DWORD FFSTotal;		/* Total size of the WinPLC flashed based file system	*/
	DWORD FFSFree;			/* Free size of the WinPLC flashed based file system	*/

	DWORD RAMPercentFree;	/* Percent of RAM that is free.	*/
	DWORD RAMPhysicalFree;	/* Physical RAM that is free.		*/

	DWORD VendorID;			/* Vendor ID from the WinPLC */

	DWORD CPUClockFrequency;
	BYTE  ENetAddress[6];	

	BYTE Unused[198];
	} WPLCSystemInformation;
	


/* ERM Defs */
#define BIT_INPUT		0
#define BIT_OUTPUT	1
#define WORD_INPUT	2
#define WORD_OUTPUT	3

/* sERMDevice (128 bytes each) */
typedef struct
	{
	BYTE AddressMode;		/* Defines format of address field (see AM_XXX below)				*/
	BYTE Protocol;			/* HEIP_HOST, HEIP_IPX, or HEIP_IP, 0 == Unused 					*/

	struct
		{
		union
			{
			/* Use this for AM_ETHER addressing (Protocol: HEIP_IPX or HEIP_HOST) */
			BYTE EtherAddr[6];		/* Ethernet network address */

			/* Use this for AM_NODENUM addressing (Protocol: HEIP_IPX or HEIP_HOST or HEIP_IP) */
			DWORD Nodenum;

			/* Use this for AM_IPADDR addressing (Protocol: HEIP_IPX or HEIP_HOST or HEIP_IP) */
			BYTE IPAddr[4];
#if defined (ANSI_C)
			} AM;
#else
			};
#endif

		BYTE Netnum[4];	/* Used for HEIP_IPX protocol; HEIP_IP   */
		WORD Port;			/* Used for HEIP_IPX and HEIP_IP protocols */
		union
			{
			BYTE FrameType;	/* Used for HEIP_IPX protocol (See FT_XXXX) */
			BYTE GatewayAddress[4]; /* Gateway to use for this device (0's for no gateway) */
#if defined (ANSI_C)
			} AM2;
#else
			};
#endif
		/* BYTE Reserved[3];*/
		} Address;

	WORD Timeout;						/* Timeout time for this device											*/
	WORD Retrys;						/* Number of time to retry a request before reporting error.   */
	BYTE ModuleIDs[32];				/* Module ID's for each slot in the device							*/
	WORD Flags;							/* See ERM_FLAG_??? defines												*/
	WORD DataOffsets[4];				/* Data offsets for each type (BIT_INPUT, BIT_OUTPUT,				*/
											/* WORD_INPUT, WORD_OUTPUT) if with a PLC								*/
	WORD DataSizes[4];				/* Data sizes (in bytes) for each type if with a PLC				*/
	WORD WatchDog;						/* Watchdog timeout value to use for this device					*/
	WORD PetFrequency;				/* Freq to pet the device to keep WatchDog from firing			*/
											/* Specified in milliseconds.  If zero no pets will be done		*/
	WORD FailuresBeforeStandby;	/* Number of consecutive failures to put device in					*/
											/* standby mode.																*/
	BYTE Reserved[50];				/* Reserved (set to zero)													*/
	} sERMDevice;

/* Address mode 0 is undefined */
#define AM_NODENUM 1
#define AM_NAME    2		/* Not supported in ERM module. */
#define AM_IPADDR  3
#define AM_ETHER   4

/* Interface defines */
#define IF_UNDEFINED		0	/* ERM I/F not defined / detected									*/
#define IF_PLC				1	/* ERM will use a PLC style interface								*/
#define IF_WINPLC			2	/* ERM will use a WinPLC style interface							*/

#define ERM_FLAG_IGNORE_WARNINGS	 1		/* If set, warnings from this device are ignored	*/
#define ERM_FLAG_AUTO_HOT_SWAP	 2		/* If set, terminator hot swap is automatic			*/

/* Frame type defines */
#define FT_802_2       1
#define FT_802_3       2
#define FT_ETHER_II    3


typedef struct sERMConfig
	{
	BYTE Version;						/* Version of sERMConfig 0=Unconfigured; 1= Current Version	*/
	BYTE Interface;					/* See IF_XXX above.														*/
	WORD PLCAddresses[4];			/* Address for each type. (BIT_INPUT, BIT_OUTPUT,				*/
											/* WORD_INPUT, WORD_OUTPUT) if with a PLC							*/
	WORD PLCDataSizes[4];			/* Size (in bytes) for each type if with a PLC.					*/
	DWORD StandbyCycleTime;			/* Time to wait when a module is not responding before      */
											/* trying to access the module again								*/
											/* If zero, the module will not be accessed again				*/
	DWORD NotSupportedCycleTime;	/* Time to wait when a module is not supported before       */
											/* trying to access the module again								*/
											/* If zero, the module will not be accessed again				*/
	WORD AssumePLCScanTime;			/* PLC Scan time to assume for timeout purposes if zero,       */
											/* default is used															*/
	BYTE Unused[228];
	} sERMConfig;

#define MAX_ERM_DEVICES		16


typedef struct sERMDeviceInfo
	{
	BYTE State;
	BYTE Supported						: 1;
	BYTE GotAddressInfo				: 1;
	BYTE ARPReplyPending				: 1;
	BYTE GotBaseDef					: 1;
	BYTE GotSupportInfo				: 1;
	BYTE GotWatchDogSetupAck		: 1;
	BYTE GotWatchDogSetupComplete : 1;
	WORD TotalRetrys;
	WORD LastError;
	} sERMDeviceInfo;


typedef struct sERMInfo
	{
	BYTE Version;						/* Version of sERMInfo 1 = current version				*/
	BYTE AutoDetectedInterface;	/* Interface which was auto detected by Hx-ERM module */
	BYTE PLCType;						/* PLC Type that Hx-ERM module is in rack with			*/
	BYTE BytesInUsedByERM;			/* Number of Input bytes that Hx-ERM uses					*/
											/* Currently 32 Bits (4 Bytes) of Error Info				*/
	BYTE BytesOutUsedByERM;			/* Number of Output bytes that Hx-ERM uses				*/
											/* Currently 16 Bits (2 Bytes) of disable bits			*/
	sERMDeviceInfo DeviceInfo[MAX_ERM_DEVICES];	
	WORD Error;							/* Error value from ERM											*/
	WORD Status;						/* Bit per device error status								*/
	BYTE RunMode	: 1;				/* 1 if in Run Mode; 0 if not									*/
	BYTE ERMState;						

	WORD	MinScan;						/* Minimum scan time in ms										*/
	WORD	MaxScan;						/* Miximum scan time in ms										*/
	DWORD TotalScans;					/* Total Number of scans										*/
	DWORD TotalTime;					/* Total Time for TotalScans									*/
	DWORD ReadRetrys;					/* Number of PLC Read Retrys									*/
	DWORD WriteRetrys;				/* Number of PLC Write Retrys									*/
	DWORD DeviceRetrys;				/* Number of Device Retrys										*/
	DWORD DeviceTime;					/* Total Time spent on device comm							*/
	BYTE Base;							/* Base number that Hx-ERM module is in					*/
	BYTE Slot;							/* Slot number that Hx-ERM module is in					*/
	BYTE EthernetAddress[6];		/* Ethernet address of controlling WinPLC (0 for PLC)	*/

	BYTE Unused[113];
	} sERMInfo;

typedef struct sDevCommand
	{
	BYTE Version;						/* Version of sDevCommand	1 = current version				*/
	BYTE Command;						/* Command to give to Device	(see DEV_CMD_XXX values)	*/
	BYTE Data[254];					/* Command specific data											*/
	} sDevCommand;

#define DEV_CMD_REINIT			1		/* Used to tell Device to do a reinitialization				*/
#define DEV_CMD_RESET_STATS	2		/* Used to tell Device to clear error / stat info			*/
#define DEV_CMD_RESET_ERROR	3		/* Used to clear LastError value for one or more devices */
												/*   Data[0]: bits 0-7 correspond to devies num 0-7		*/
												/*   Data[1]: bits 0-7 correspond to devies num 8-15		*/


/* Hx-ERM Errors.					*/
#define ERM_CONFIG_ERROR_BITS_IN_TOO_FEW					1	/* Config error: Bits In configured not enough				*/
#define ERM_CONFIG_ERROR_BITS_OUT_TOO_FEW					2	/* Config error: Bits Out configured not enough				*/
#define ERM_CONFIG_ERROR_BITS_IN_OVERLAPS_SYS_DATA		3	/* Configured Bit Inputs overlap system input bits			*/
#define ERM_CONFIG_ERROR_BITS_OUT_OVERLAPS_SYS_DATA	4	/* Configured Bit Outputs overlap system output bits		*/
#define ERM_MULTIPLE_DEVICES_WITH_SAME_NODE_NUM			5	/* More than one device found with same node number		*/
#define ERM_MULTIPLE_DEVICES_WITH_SAME_IP_ADDRESS		6	/* More than one device foudn with same IP address			*/
#define ERM_MODULE_NOT_RESPONDING							7	/* Device is not responding to a function request			*/
#define ERM_MODULE_NOT_SUPPORTED								8	/* Device not supported; may be firmware or cfg error		*/
#define ERM_MODULE_TIMEOUT										9	/* Device timed out on a function request (after retrys) */
#define ERM_MODULE_NO_GATEWAY_ADDRESS						13	/* Gateway address needed, but not specified					*/
#define ERM_NO_SUBNET_MASK										14	/* Subnet mask needed, but not specified						*/
#define ERM_MODULE_MISMATCHED_MODULE_IDS					15	/* Configured module Id's don't match modules in device	*/
#define ERM_MODULE_INCORRECT_BITS_IN						16	/* Number of bit inputs specified is less than actual		*/
#define ERM_MODULE_INCORRECT_BITS_OUT						17	/* Number of bit outputs specified is less than actual	*/
#define ERM_MODULE_INCORRECT_WORDS_IN						18	/* Number of word inputs specified is less than actual	*/
#define ERM_MODULE_INCORRECT_WORDS_OUT						19	/* Number of word outputs specified is less than actual	*/
#define ERM_MODULE_BASE_DEF_ERROR							20	/* Invalid base def for this device								*/
#define ERM_CONFIG_MISSING										21	/* Hx-ERM hasn't been configured									*/
#define ERM_MODULE_BASE_DEF_BUFFER_OVERFLOW				22	/* Overflow of entire BaseDefBuffer								*/
#define ERM_MODULE_BASE_DEF_OVERFLOW						23	/* Overflow of previous Device BaseDef							*/
#define ERM_MODULE_WRITE_PACKET_BUFFER_OVERFLOW			24	/* Overflow of entire WritePacketBuffer						*/
#define ERM_MODULE_WRITE_PACKET_OVERFLOW					25	/* Overflow of previous WritePacketBuffer						*/
#define ERM_CONFIG_IO_BUFFER_OVERFLOW						26	/* Overflow of entire IO buffer									*/
#define ERM_CONFIG_ERROR_WORDS_IN_TOO_FEW					27	/* Config error: Words In configured not enough				*/
#define ERM_CONFIG_ERROR_WORDS_OUT_TOO_FEW				28	/* Config error: Words Out configured not enough			*/

/* ERM Backplane errors */
#define ERM_BPERROR_OBJ_NOT_FOUND     						221 /* Internal backplane error										*/
#define ERM_BPERROR_UNK_PLC_FAMILY							223 /* PLC Family unknown												*/
#define ERM_BPERROR_INVALID_STATUS							224 /* Invalid backplane status value								*/
#define ERM_BPERROR_CCM_CODEERROR							225 /* Code Error returned from PLC									*/
#define ERM_BPERROR_CCM_ERROR									226 /* General Error returned from PLC								*/
#define ERM_BPERROR_TIMEOUT									227 /* Timeout on PLC backplane request								*/
#define ERM_BPERROR_NO_MORE_OBJECTS							228 /* Backplane queue full												*/
#define ERM_BPERROR_INVALID_REQUEST							231 /* Internal request error											*/

/* Serial port defines */
#define SERIAL_1_STOP_BIT	0
#define SERIAL_2_STOP_BITS  1

#define SERIAL_7_DATA_BITS	0
#define SERIAL_8_DATA_BITS	1

#define SERIAL_NO_PARITY	0
#define SERIAL_ODD_PARITY	2
#define SERIAL_EVEN_PARITY	3

#define SERIAL_SLAVE		0
#define SERIAL_MASTER		1
#define SERIAL_PROXY		1

#define SERIAL_NO_RTS		0
#define SERIAL_USE_RTS		1
	
typedef struct
	{
	DWORD BaudRate;				/* Baud rate to use i.e. 9600 */
										/* If Baud rate == 0 then serial port is disabled */
	
#if defined (ANSI_C)
	BYTE 	ConfigData;			
#else
	BYTE	StopBits 	: 1;    /* 0 == 1 Stop bit;  1 == 2 Stop bits */
	BYTE 	DataBits	: 1;    /* 0 == 7 Data bits;  1 == 8 Data bits */
	BYTE	Parity		: 2;    /* 0 == 1 == None; 2 == Odd;  3 == Even */
	BYTE	Mode		: 1;    /* 0 == Slave;  1 == Master/Proxy */
	BYTE	UseRTS		: 1;	/* 0 == Don't use RTS line;  1 == Use RTS line */
	BYTE	Reserved	: 2;    /* Reserved locations */
#endif	
	BYTE	PreTransmitDelay;	/* If UseRTS == 1 delay this many ms (times 2) before starting transmit */
	BYTE	PostTransmitDelay;  /* If UseRTS == 1 delay this many ms (times 2) after ending transmit */

	BYTE 	Unused;		/* Unused byte (set to zero) */
	} SerialSetup;

/* Flags for IPSetup */
#define IPF_USE_BRAM_SETUP	0x00000001
#define IPF_USE_ZERO_BCAST	0x00000002
#define IPF_ENABLE_DHCP		0x00000004
#define IPF_USE_DNS			0x00000008
#define IPF_USE_WINS			0x00000010

typedef struct
	{
	DWORD		Flags;				/* Flags see IPF_XXX above	*/
	BYTE		Gateway[16];		/* Gateway address			*/
	BYTE		IPAddress[16];		/* IP Address					*/
	BYTE		Subnet[16];			/* Subnet address				*/
	BYTE		DNSAddr[16];		/* Primary DNS (used if IPF_USE_DNS flag is set)	*/
	BYTE		WINSAddr[16];		/* Primary WINS (used if IPF_USE_WINS flag is set)	*/
	BYTE		Unused[172];		/* Unused (clear to zero)									*/
	} IPSetup;



typedef struct
	{
	WORD Mode;					/* Mode for ErrorLightSetup see ELS_XXXX below			*/
	WORD InitVal;				/* Initial value used for ELS_SET and ELS_CYCLE			*/
	WORD OnTime;				/* OnTime used for ELS_CYCLE									*/
	WORD OffTime;				/* OffTime used for ELS_CYCLE									*/
	WORD Num;					/* Number of times to loop for ELS_CYCLE					*/
	WORD Val1;					/* Unused value													*/
	WORD Val2;					/* Unused value													*/
	WORD Val3;					/* Unused value													*/
	} ErrorLightSetup;


#define ELS_OFF		0		/* Turns the error light off									*/
#define ELS_SET		1		/* Sets the error light to the value of InitVal			*/
#define ELS_CYCLE		2		/* Cycles error light.  Begins with value of InitVal  */
									/* When light is turned on, it stays on for OnTime		*/
									/* When light is turned off, it stays off for OffTime */
									/* Cycles lights Num times										*/ 

typedef struct
	{
	BYTE	MajorVersion;
	BYTE	MinorVersion;
	WORD	BuildVersion;
	} VersionDef;
	
typedef struct
	{
	BYTE SizeofVersionInfo;
	VersionDef BootVersion;
	VersionDef OSVersion;
	BYTE	NumOSExtensions;
	VersionDef OSExt[10];
	}	VersionInfoDef;
	
/* Module type defines */
#define MT_EBC			0			/* Ethernet base controller			*/
#define MT_ECOM		1			/* Ethernet communications module	*/
#define MT_WPLC		2			/* WinPLC									*/
#define MT_DRIVE		3			/* Drive card								*/
#define MT_ERMA		4			/* Ethernet remote master				*/
#define MT_CTRIO		5			/* Counter I/O card						*/
#define MT_AVG_DISP	6			/* AVG Display Adapter card			*/
#define MT_PBC			7			/* Profibus controller					*/
#define MT_PBCC		8			/* Profibus IO coprocessor				*/
#define MT_UNK			0xFF

/* Module Family defines for MT_EBC, MT_ECOM, MT_WPLC, MT_ERMA */
#define MF_005				0
#define MF_205				2
#define MF_305				3
#define MF_405				4
#define MF_TERM			10

/* Module Family defines for MT_DRIVE */
#define MF_100_SERIES	1		/* Hitachi L100 and SJ100 drives */
#define MF_J300			2		/* Hitachi J300 drive */
#define MF_300_SERIES	3		/* Hitachi SJ300 drive */
#define MF_GS				4		/* GS Series drives  GS-EDRV*/

/* Module Family defines for MT_AVG_DISP */
#define MF_EZ_TOUCH		1		/* AVG EZ-Touch Ethernet adapter */

typedef struct
	{
	BYTE PLCFamily;		/* See MF_XXX defines above */
	BYTE Unused1;
	BYTE ModuleType;		/* See MT_XXX defines above */
	BYTE StatusCode;				
	BYTE EthernetAddress[6];	/* Hardware ethernet address */
	WORD RamSize;  				/* In K-Byte increments */
	WORD FlashSize; 			/* In K-Byte increments */
	BYTE DIPSettings;			/* Settings of the 8 dip switches. */
	BYTE MediaType;				/* 0 == 10-Base T */
								/* 1 == 10-Base F */
	DWORD EPFCount;				/* Early power fail count (405 EBC)*/

#if defined (ANSI_C)
	BYTE 	Status;			
#else
	BYTE RunRelay	: 1;		/* 405 EBC Run Relay Status */
	BYTE BattLow	: 1;			/* 405 EBC Battery Low indicator */
	BYTE UnusedBits	: 6;		/* Unused status bits */
#endif

	WORD BattRamSize;			/* Size in K-Bytes of battery-backed ram */
	BYTE ExtraDIPS;			/* Extra Dip switches on Terminator EBC's */
	BYTE ModelNumber;			
	BYTE EtherSpeed;			/* 0=10MBit; 1=100MBit */
	BYTE PLDRev[2];

	BYTE Unused[14];
	} DeviceDef;

typedef struct
	{
	DWORD Timeout;		/* Timeout 0 == Don't use link monitor */
	BYTE Mode;			/* Mode: */
							/* 		0 == Clear outputs */
							/*			1 == Set outputs to given I/O data pattern */
	BYTE Data[251];	/* Pattern:  Used with set outputs,  same format */
							/* 			 as data for HEIWriteIO call. */
	} LinkMonitor;

typedef struct
	{ 
	BYTE Algorithm;  	/* Algorithm to use for encryption */
							/*		0 == No encryption */
							/*		1 == Private key encryption */
							/* */
	BYTE Unused[3];		/* Reserved for later */
	BYTE Key[60];		/* Encryption key (null terminated) */
	}  Encryption;
	

typedef struct
	{
	WORD Type;			/* Type of memory */
	DWORD Size;			/* Size of memory */
	DWORD UnitSize;	/* 0 = DWORD, 1 = BYTE, 2 = WORD, 4 = DWORD */
	DWORD Unused[3];	/* Unused */
	} MemoryTypeDef;
	
typedef struct
	{
	WORD SizeofSettings		;				/* sizeof(HEISettings) */
	
	/* Action items. */			
	DWORD Flags;        						/* Flags used to control things. */
													/* Bit:   	Function:																				*/
													/*		0-31 		Unused																				*/
	
	/* RXWX Config items. */
	WORD RXWXACKTimeout 			;			/* Timeout for receiving ACK / NAK */
	WORD RXWXResponseTimeout 	;			/* Timeout for receiving response. */
	WORD RXWXMaxRetrys			;			/* Number of times to retry a transaction. */
	
	/* RXWX Stat Items. */
	WORD RXWXMaxACKTime			;			/* STAT: Max number of ms we have waited for an ack. */
	WORD RXWXMaxRSPTime			;			/* STAT: Max number of ms we have waited for a response. */
	DWORD RXWXACKRetrys			;      	/* STAT: Number of retrys for an ack. */
	DWORD RXWXRSPRetrys			;			/* STAT: Number of retrys for a response. */
	DWORD RXWXCompleted			;			/* STAT: Number of successfully completed transactions */
	DWORD RXWXTimeouts			;			/* STAT: Number of timeouts on transactions (after retrys) */
	DWORD RXWXOverruns			;			/* STAT: Number of times the PLC requested a transaction while */
													/* one was being processed. */
	DWORD RXWXErrors				;			/* STAT: Number of times an invalid code was found or a transaction */
													/* was NAKed. */
													
	/* Other stuff */													
	BYTE Version;								/* Version of this structure.  Currently 0 */
	
	/* K-Sequence Retrys */
	WORD KSeqMaxRetrys;						/* Max number of times to retry a K-Sequence request 	*/
	WORD KSeqRetrys;							/* STAT: Number of K-Sequence retrys.								*/
	WORD KSeqTimeouts;						/* STAT: Number of K-Sequence timeouts. */
	
	BYTE Unused[81];							/* Reserved for future use.  (Configure protocol, etc. */
	} HEISettings;

	
typedef struct
	{
	BYTE RunRelayMode;		/* Relay Mode */
									/* See Relay modes below. */
	DWORD SerialTimeout;		/* Used for RRM_DRIVE_COMM_BAD */
	DWORD EthernetTimeout;	/* Used for RRM_DRIVE_COMM_BAD */

	BYTE Unused[55];
	} ModuleSetup;


typedef struct
	{
	/*
	** GS Series drive setup timeouts.
	** In order for a value to be used, set the most significant bit.
	*/
	WORD ReceiveCharTimeout[4];
	WORD CommandResponseTimeout[4];
	WORD WriteCacheClearTime;			/* 250 ms default */
	WORD TimeoutsBeforeAutoBaud;		/*  50 ms default */
	WORD RTSPreTransmitDelay;			/*   4 ms default */
	WORD RTSPostTransmitDelay;			/*   4 ms default */
	WORD AutoBaudDelay;					/*  10 ms default */
	WORD ProcessSlaveIdle;				/*  10 ms default */
	WORD RetryDelay;						/*  20 ms default */
	WORD Unused[49];
	} DriveSetup;


/* Relay Modes */
#define RRM_LINK_GOOD		0	/* Run relay on when link is good (default) */
#define RRM_LINK_NOT_GOOD	1	/* Run relay on when link is not good */
#define RRM_POWERUP_ON		2	/* EBC turns run relay mode on on powerup			*/
#define RRM_MANUAL_ON		3	/* Run relay mode is controlled by control software */
#define RRM_DRIVE_COMM_BAD	4	/* Relay on if serial or ethernet comm lost (for Drive controller card) */


#define ACCESS_READ		0
#define ACCESS_WRITE	1

typedef struct sMemRefDetail
	{
	BYTE Direction;	/* ACCESS_READ == Read, ACCESS_WRITE == Write */
	WORD Type;			/* Memory type */ 
	DWORD Offset;		/* Memory Offset */
	WORD NumBytes;		/* Number of bytes */
	} MemRefDetail;

typedef struct
	{
	MemRefDetail Detail;
	BYTE *pBuffer;		/* Data buffer */
	} MemRef;

/* RescanFlags */
#define RESCAN_LEAVE_IMAGE_RAM	0		/* Don't clear the image RAM */
#define RESCAN_CLEAR_IMAGE_RAM	1		/* Clear the image RAM */

/* Protocol Defines */
#define HEIP_HOST   		1
#define HEIP_IPX	  		2
#define HEIP_IP			3
#define HEIP_SERIAL		4


#if !defined(FIRMWARE)

#if defined(HEIDEFS)
typedef int		BOOL;
typedef unsigned char	BYTE;
typedef unsigned short	WORD;
typedef unsigned long	DWORD;
#define FALSE 0
#define TRUE 1
#endif /* #if defined(HEIDEFS) */

#define HEIAPIVERSION 3
#define HEIAPIVERSIONSTRING "3"

#define HEIT_HOST			1
#define HEIT_IPX			2	
#define HEIT_WINSOCK		4
#define HEIT_OTHER_TRANSPORT 8
#define HEIT_UNIX			16
#define HEIT_SERIAL		32

/* Encryption Algorithms */
#define HEIEN_NONE			0	
#define HEIEN_A1			1  

#define PACKET_HEADER_SIZE 9

#if defined(HEIDOS)
#define __declspec(dllexport)
#endif	/* #if defined(HEIDOS) */

#if defined(HEI16)
#define __declspec(dllexport)
#endif	/* #if defined(HEI16) */

#if defined(HEIUNIX)
#define __declspec(dllexport)
#endif	/* #if defined(HEIT_UNIX) */


/* Default values for HEIOpenDevice */
#define DefDevTimeout 100
#define DefDevRetrys  3
#define DefDevUseAddressedBroadcast FALSE


typedef struct 
	{
	union
		{
		/* Use this for HEIP_HOST protocol addressing. */
		struct 
			{
			short Family;			/* AF_UNSPEC == 0 */
			char Nodenum[6];		/* Ethernet network address */
			unsigned short LANNum;	/* Lana number */
			} AddressHost;

		/* Use this for HEIP_IPX protocol addressing. */
		struct 
			{
			short Family;			/* AF_IPX == 6 */
			char Netnum[4];			/* Network number */
			char Nodenum[6];		/* Ethernet network address */
			unsigned short Socket;	/* Socket number == 0x7070 */
			} AddressIPX;

		/* Use this for HEIP_IP protocol addressing. */
		struct 
			{
			short Family;			/* AF_INET == 2 */
			unsigned short Port;	/* Port number == 0x7070 */
			union					/* Internet address */
				{
				struct { unsigned char b1,b2,b3,b4; } bAddr;/* Byte addressing */
				struct { unsigned short w1,w2; } wAddr;		/* Word addressing */
				unsigned long lAddr;						/* DWord addressing */
				} AddressingType;
			char  Zero[8];			/* Initialize to zeros */
			} AddressIP;

		/* This is the generic address buffer. */
		BYTE Raw[20];
#ifdef ANSI_C	/*  ANSI C cannot have anonymous structures */
		} Address;
#else
		};
#endif
	} ENetAddress;


#if defined(__cplusplus)
extern "C"
	{
#endif	/* #if defined(__cplusplus) */

	/* INITIALIZATION / SHUTDOWN */
	__declspec(dllexport) int HEIOpen(WORD HEIAPIVersion);
	__declspec(dllexport) int HEIClose();
	
	/* Protocol Stuff */
	typedef struct 
		{
		WORD Transport;		/* HEIT_HOST */
							/* HEIT_IPX */
							/* HEIT_NETBIOS */
							/* HEIT_WINSOCK */

		WORD Protocol;		/* HEIP_HOST*/
							/* HEIP_IPX */
							/* HEIP_IP */
							/* HEIP_NETBIOS */
		/* Encryption stuff. */
		Encryption Encrypt;	/* Set this up before calling HEIOpenTransport  */
							/* .Algorithm == HEIEN_NONE OR HEIEN_A1 */
							/* .Key == Encryption key */
									
		/* DWORD NetworkAddress; */
		ENetAddress *pSourceAddress;	/* Used for multiple ethernet cards.  This address is the address of the card to use. */

		/*int (*pSendPacket)(HEIDevice *pDevice, BYTE *pPacket, WORD PacketSize);*/
		/*int (*pReceivePacket)(HEIDevice *pDevice, BYTE *pResponse, int *pResponseSize);*/
#if HEIAPIVERSION==3
		BYTE Reserved[48];		/* Reserved bytes, set to zero */
#endif
		} HEITransport;
	
	__declspec(dllexport) int HEIOpenTransport(HEITransport *pTransport, WORD Version,  ENetAddress *pSourceAddress);
	/* __declspec(dllexport) int HEIOpenTransport(HEITransport *pTransport, WORD Version, DWORD NetworkAddress );*/
	/* __declspec(dllexport) int HEIOpenTransport(HEITransport *pTransport, WORD Version, DWORD NetworkAddress = 0); */
	__declspec(dllexport) int HEICloseTransport(HEITransport *pTransport);
	
	
	/* DEVICE Stuff */
	typedef struct 
		{
		union
			{
			/* Use this for HEIP_HOST protocol addressing. */
			struct 
				{
				short Family;			/* AF_UNSPEC == 0 */
				char Nodenum[6];		/* Ethernet network address */
				unsigned short LANNum;	/* Lana number */
				} AddressHost;

			/* Use this for HEIP_IPX protocol addressing. */
			struct 
				{
				short Family;			/* AF_IPX == 6 */
				char Netnum[4];			/* Network number */
				char Nodenum[6];		/* Ethernet network address */
				unsigned short Socket;	/* Socket number == 0x7070 */
				} AddressIPX;

			/* Use this for HEIP_IP protocol addressing. */
			struct 
				{
				short Family;			/* AF_INET == 2 */
				unsigned short Port;	/* Port number == 0x7070 */
				union					/* Internet address */
					{
					struct { unsigned char b1,b2,b3,b4; } bAddr;/* Byte addressing */
					struct { unsigned short w1,w2; } wAddr;		/* Word addressing */
					unsigned long lAddr;						/* DWord addressing */
					} AddressingType;
				char  Zero[8];			/* Initialize to zeros */
				} AddressIP;

			struct
				{
				BYTE CommPort;
				BYTE ByteSize;
				BYTE Parity;  
				BYTE StopBits;
				DWORD Baud;
				void *hLocal;
				} AddressSerial;

			/* This is the generic address buffer. */
			BYTE Raw[20];
			} Address;

		WORD wParam;				/* Application can use this. */
		DWORD dwParam;				/* Application can use this. */

		WORD Timeout;				/* Timeout value in ms (can be changed without closing the device). */
		WORD Retrys;				/* Number of times to retry (can be changed without closing the device). */

		BYTE ENetAddress[6];		/* The ethernet address is placed here in the HEIQueryDevices call. */

		WORD RetryCount;			/* Number of retrys which have occured. */
		WORD BadCRCCount;		 	/* Number of packets received with bad CRC */
		WORD LatePacketCount; 		/* Number of packets received, but after a timeout */

		BOOL ParallelPackets;		/* Setting this to TRUE (after HEIOpenDevice) will enable an application */
									/* to send multiple HEIReadIO, HEIWriteIO, HEICCMRequest or  HEIKSEQRequest requests  */
									/* (to different) modules before waiting for any responses.   */
									/* The application will then need to implement its own retry / timeout mechanism  */
									/* while waiting for the responses. */
									/* The application uses HEIGetResponse to see if a response for a module has arrived. */
									/* NOTE: The application should not send multiple requests to a single module */
									/*       without waiting for the response in between. */

		/* Internal - Do not touch!! */
		BOOL UseAddressedBroadcast;	/* Need to close the device and reopen it to change this! */
		BOOL UseBroadcast;				
		DWORD _dwParam;	
		WORD DataOffset;
		HEITransport *_pTransport;	/* Need to close the device and reopen it to change this! */
		int SizeOfData;
		BYTE *pData;
		void *pBuffer;
		unsigned short LastAppVal;
#if HEIAPIVERSION==3
		BYTE UseProxy;
		BYTE ProxyBase;
		BYTE ProxySlot;
		BYTE ProxyDevNum;

		BYTE Reserved[44];		/* Reserved bytes, set to zero */
#endif
		} HEIDevice;
	
	__declspec(dllexport) int HEIQueryDevices(HEITransport *pTransport, HEIDevice *pDevices, WORD *pNumDevices, WORD HEIAPIVersion);
	
	__declspec(dllexport) int HEIOpenDevice(HEITransport *pTransport, HEIDevice *pDevice, WORD HEIAPIVersion, WORD Timeout, WORD Retrys, BOOL UseAddressedBroadcast);
	/*	__declspec(dllexport) int HEIOpenDevice(HEITransport *pTransport, HEIDevice *pDevice, WORD HEIAPIVersion, WORD Timeout=DefDevTimeout, WORD Retrys=DefDevRetrys, BOOL UseAddressedBroadcast=DefDevUseAddressedBroadcast); */
	__declspec(dllexport) int HEICloseDevice(HEIDevice *pDevice);
	
	__declspec(dllexport) int HEIQueryDeviceData(HEITransport *pTransport, HEIDevice *pDevices, WORD *pNumDevices, WORD HEIAPIVersion, WORD DataType, BYTE *pData, WORD SizeofData);
	
	/* SUPPORT INFORMATION */
	__declspec(dllexport) int HEIReadSupportInfo(HEIDevice *pDevice, BYTE *pSupportInfo, WORD SizeOfSupportInfo);
	
	
	/* VERSION INFORMATION */
	__declspec(dllexport) int HEIReadVersionInfo(HEIDevice *pDevice, BYTE *pVerInfo, WORD SizeVerInfo);
	
	
	/* BASE DEFINITION */
	__declspec(dllexport) int HEIReadBaseDef(HEIDevice *pDevice, BYTE *pBaseDefInfo, WORD *pSizeOfBaseDefInfo);
	__declspec(dllexport) int HEIWriteBaseDef(HEIDevice *pDevice, BYTE *pInputBaseDef, WORD SizeOfInputBaseDef, BYTE *pOutputBaseDef, WORD *pSizeOfOutputBaseDef);
	__declspec(dllexport) int HEIInitBaseDef(HEIDevice *pDevice, BYTE *pBaseDefInfo, WORD *pSizeOfBaseDefInfo);
	__declspec(dllexport) int HEIRescanBase(HEIDevice *pDevice, DWORD RescanFlags, BYTE *pBaseDefInfo, WORD *pSizeOfBaseDefInfo);

	
	
	/* DEVICE DEFINITION */
	__declspec(dllexport) int HEIReadDeviceDef(HEIDevice *pDevice, BYTE *pModuleDefInfo, WORD SizeOfModuleDefInfo);

	/* IO ACCESS */
	__declspec(dllexport) int HEIReadIO(HEIDevice *pDevice, BYTE *pData, WORD *DataSize);
	__declspec(dllexport) int HEIWriteIO(HEIDevice *pDevice, BYTE *pData, WORD SizeofData, BYTE *pReturnData, WORD *pSizeofReturnData);
	__declspec(dllexport) int HEIWriteIONoRead(HEIDevice *pDevice, BYTE *pData, WORD SizeofData);

	__declspec(dllexport) int HEIReadIOEx(HEIDevice *apDevice[], BYTE *apData[], WORD aSizeofData[], int aErrorCode[], int DeviceCount);
	__declspec(dllexport) int HEIWriteIOEx(HEIDevice *apDevice[], BYTE *apData[], WORD aSizeofData[], BYTE *apReturnData[], WORD aSizeofReturnData[], int aErrorCode[], int DeviceCount);

	/* CONFIG */
	__declspec(dllexport) int HEIReadConfigData(HEIDevice *pDevice, BYTE *pData, WORD *DataSize);
	__declspec(dllexport) int HEIWriteConfigData(HEIDevice *pDevice, BYTE *pData, WORD SizeofData, BYTE *pReturnData, WORD *pSizeofReturnData);
	// NOTE: You can also Use HEIWriteIO to write config data using type DF_CONFIG


	/* SETUP */
	__declspec(dllexport) int HEIReadSetupData(HEIDevice *pDevice, WORD SetupType, BYTE *pData, WORD *pSizeofData);
	__declspec(dllexport) int HEIWriteSetupData(HEIDevice *pDevice, WORD SetupType, BYTE *pData, WORD SizeofData);
	__declspec(dllexport) int HEIDeleteSetupData(HEIDevice *pDevice, WORD SetupType);
	__declspec(dllexport) int HEIEnumSetupData(HEIDevice *pDevice, WORD *pData, WORD *pSizeofDataInWords);

	/* WATCHDOG */
	__declspec(dllexport) int HEIPetDevice(HEIDevice *pDevice);

	/* STATISTICS */
	__declspec(dllexport) int HEIReadEthernetStats(HEIDevice *pDevice, BYTE *pData, WORD *DataSize, BOOL Clear);
	/* __declspec(dllexport) int HEIReadEthernetStats(HEIDevice *pDevice, BYTE *pData, WORD *DataSize, BOOL Clear=FALSE); */

	/* MODULES STATUS */
	__declspec(dllexport) int HEIReadModuleStatus(HEIDevice *pDevice, BYTE *pData, WORD *DataSize, BOOL Reset);
	/* __declspec(dllexport) int HEIReadModuleStatus(HEIDevice *pDevice, BYTE *pData, WORD *DataSize, BOOL Reset=FALSE); */

	/* Multiple Packet Stuff. */
	__declspec(dllexport) int HEIGetResponse(HEIDevice *pDevice, BYTE *pResponse, int *pResponseSize, BOOL CheckAppVal);
	/* __declspec(dllexport) int HEIGetResponse(HEIDevice *pDevice, BYTE *pResponse, int *pResponseSize, BOOL CheckAppVal=TRUE); */

   /* ECOM STUFF */
	__declspec(dllexport) int HEICCMRequest(HEIDevice *pDevice, BOOL bWrite, BYTE DataType, WORD Address, WORD DataLen, BYTE *pData);
	__declspec(dllexport) int HEIKSEQRequest(HEIDevice *pDevice, WORD DataLenIn, BYTE *pData, WORD *pDataLen);

	/* SERIAL PORT STUFF */
	__declspec(dllexport) int HEIWriteComm(HEIDevice *pDevice, WORD Num2Write, BYTE *pData);
	__declspec(dllexport) int HEIReadComm(HEIDevice *pDevice, WORD *pNum2Read, BYTE *pData);
	__declspec(dllexport) int HEIGetRXAvailable(HEIDevice *pDevice, WORD *pAvailable);
	__declspec(dllexport) int HEIFlushRXQueue(HEIDevice *pDevice);
	__declspec(dllexport) int HEIGetTXLeft(HEIDevice *pDevice, WORD *pLeft);
	__declspec(dllexport) int HEISetupSerialPort(HEIDevice *pDevice, SerialSetup *pSetup, BOOL WriteToFlash);
	__declspec(dllexport) int HEIReadSerialPortSetup(HEIDevice *pDevice, SerialSetup *pSetup);
	
	/* SERIAL PORT STUFF (EX) */
	__declspec(dllexport) int HEIWriteCommEx(HEIDevice *pDevice,BYTE Port ,WORD Num2Write, BYTE *pData);
	__declspec(dllexport) int HEIReadCommEx(HEIDevice *pDevice, BYTE Port, WORD *pNum2Read, BYTE *pData);
	__declspec(dllexport) int HEIGetRXAvailableEx(HEIDevice *pDevice, BYTE Port, WORD *pAvailable);
	__declspec(dllexport) int HEIFlushRXQueueEx(HEIDevice *pDevice, BYTE Port);
	__declspec(dllexport) int HEIFlushTXQueueEx(HEIDevice *pDevice, BYTE Port);
	__declspec(dllexport) int HEIGetTXLeftEx(HEIDevice *pDevice, BYTE Port, WORD *pLeft);
	__declspec(dllexport) int HEISetupSerialPortEx(HEIDevice *pDevice, BYTE Port, SerialSetup *pSetup, BOOL WriteToFlash);
	__declspec(dllexport) int HEIReadSerialPortSetupEx(HEIDevice *pDevice, BYTE Port, SerialSetup *pSetup);
	__declspec(dllexport) int HEIAccessComm(HEIDevice *pDevice, WORD SendDataSize, BYTE *pSendData, WORD *pReturnDataSize, BYTE *pReturnData);


	/* MEMORY STUFF (see below for types) */
	__declspec(dllexport) int HEIReadMemory(HEIDevice *pDevice, WORD Type, DWORD Offset, WORD NumBytes, BYTE *pBuffer);
	__declspec(dllexport) int HEIWriteMemory(HEIDevice *pDevice, WORD Type, DWORD Offset, WORD NumBytes, BYTE *pBuffer);
	__declspec(dllexport) int HEIENumMemory(HEIDevice *pDevice, WORD *pNumWords, MemoryTypeDef *pBuffer);
	__declspec(dllexport) int HEIAccessMemory(HEIDevice *pDevice, MemRef MemRefs[], WORD NumRefs);


	/* SHARED RAM STUFF (for Intelligent modules) */
	__declspec(dllexport) int HEIReadSharedRAM(HEIDevice *pDevice, WORD Base, WORD Slot, WORD Address, WORD Bytes2Read, BYTE *pBuffer);
	__declspec(dllexport) int HEIWriteSharedRAM(HEIDevice *pDevice, WORD Base, WORD Slot, WORD Address, WORD Bytes2Write, BYTE *pBuffer);


	/* WinPLC specific functions */
#ifndef WINPLC
	__declspec(dllexport) int WPLCSetOSLoad(HEIDevice *pDevice, int Val);
	__declspec(dllexport) int WPLCReboot(HEIDevice *pDevice);
	__declspec(dllexport) int WPLCRunProgram(HEIDevice *pDevice, BYTE *pProgram);

	__declspec(dllexport) int HEIWriteERMData(HEIDevice *pDevice, WORD Base, WORD Slot, BYTE DataType, BYTE *pData, WORD NumBytes, WORD Offset);
	__declspec(dllexport) int HEIReadERMData(HEIDevice *pDevice, WORD Base, WORD Slot, BYTE DataType, BYTE *pData, WORD NumBytes, WORD Offset);
	__declspec(dllexport) int HEIDoERMCommand(HEIDevice *pDevice, WORD Base, WORD Slot, WORD Command);
	__declspec(dllexport) int HEIDoERMCommandEx(HEIDevice *pDevice, WORD Base, WORD Slot, WORD Command, BYTE *pExtra, WORD ExtraLen);

	__declspec(dllexport) int WPLCWriteERMData(HEIDevice *pDevice, WORD Base, WORD Slot, BYTE DataType, BYTE *pData, WORD NumBytes, WORD Offset);
	__declspec(dllexport) int WPLCReadERMData(HEIDevice *pDevice, WORD Base, WORD Slot, BYTE DataType, BYTE *pData, WORD NumBytes, WORD Offset);
	__declspec(dllexport) int WPLCDoERMCommand(HEIDevice *pDevice, WORD Base, WORD Slot, WORD Command);
	__declspec(dllexport) int WPLCDoERMCommandEx(HEIDevice *pDevice, WORD Base, WORD Slot, WORD Command, BYTE *pExtra, WORD ExtraLen);
#endif
	/* 
	** Query timeout function 
	*/
	/* Sets new query timeout value and returns the old query timeout value */
	__declspec(dllexport) DWORD HEISetQueryTimeout(DWORD NewTimeout);
	/* Gets current query timeout value */
	__declspec(dllexport) DWORD HEIGetQueryTimeout();

	/*
	** Async Handler for handling extra packets.
	*/
	__declspec(dllexport) int HEISetAsyncHandler(void (*pFun)(HEIDevice *pDevice, BYTE *pResponse, int ResponseLen));
	__declspec(dllexport) int HEIGetAsyncHandler(void (**pFun)(HEIDevice *pDevice, BYTE *pResponse, int ResponseLen));

/*
** EZ-Ethernet defs
*/
typedef signed   char    SBIT8;
#define MAX_PGM_DATA_LEN  255   // Max packet sent by AVG.
#define MAX_ERR_MSG_SZ     40   // Forty bytes of error message space.
#define MAC_LEN             6   // Six bytes for MAC address
#define SPARE_BYTES         4   // Four spare bytes for future use.
#ifndef NO_ERROR
#define NO_ERROR				 0L
#endif

typedef struct
{
    unsigned char Name[20];
    unsigned char Node_ID[2];
    HEIDevice    *pDevice;
} NODELIST;


/*
** Layout of the control buffer.
*/
typedef struct CntlBuffer
{
    BYTE   TaskCode;               /*  Taskcode byte (future use)*/
	BYTE   PanelLock;              /*  1 - Panel has lock, 0 - not locked*/
	BYTE   AdapterLock;            /*  1 - Adapter has lock, 0 - not locked*/
	BYTE   InStatus;               /*  Incoming status*/
	BYTE   OutStatus;              /*  Outgoing status*/
	SBIT8  Seq;                    /*  Sequence number assigned by panel*/
	BYTE   ErrorOffset;            /*  Offset into error array*/
    BYTE   ItemCnt[2];             /*  Two bytes since read tags can be > 256.*/
	BYTE   ErrMsg[MAX_ERR_MSG_SZ]; /*  40 character string.*/
    BYTE   EcomOffset;             /*  Used for panel to panel communications.*/
    BYTE   Mac[MAC_LEN];           /*  Stores mac address of responding device.*/
	BYTE   Spare[SPARE_BYTES];     /*  Future use*/
} CNTL_BUF;

/*
** Layout of the program shared ram frame
*/
typedef struct PgmBuffer
{
    CNTL_BUF   CntlBuf;
	BYTE       PgmData[MAX_PGM_DATA_LEN];
	
} PGM_BUF;


	/*
	**	EZ-Ethernet functions
	*/
	__declspec(dllexport) int HEIWriteEZethernetPgmSpace(HEIDevice *pDevice, BYTE *pData, WORD SizeofData);
	__declspec(dllexport) BOOL EZSendPacket(HEIDevice *pDevice, PGM_BUF *pBuffer, BYTE *Error_message, unsigned short int Len);
	__declspec(dllexport) NODELIST *EZGetNodeList(unsigned short int *TotalEZ);

	__declspec(dllexport) int SetCRCMode(int Mode);
	__declspec(dllexport) int SendPacketTwoResponses(HEIDevice *pDevice, BYTE *pPacket, WORD PacketSize, BYTE *pResponse, int *pResponseSize, 
									BOOL WaitForResponse, BOOL ReturnWarnings, WORD Bytes2Verify, BYTE *pVerifyData, 
									WORD ExtraTime, BOOL ProcessTimeout, BOOL CheckAppVal);

#if defined(__cplusplus)
	}
#endif	/* #if defined(__cplusplus) */

#endif	/* #if !defined(FIRMWARE) */

/* Errors */
#define HEIE_NULL								0	/* No Error */
#define HEIE_FIRST_ERROR					0x8000	/* Number for First Error */
#define HEIE_LAST_ERROR						0xFFFF	/* Number for Last Error */

#define HEIE_NOT_IMPLEMENTED				0x8000	/* Function not implemented */
#define HEIE_VER_MISMATCH					0x8001	/* Version passed to function not correct for library */
#define HEIE_UNSUPPORTED_TRANSPORT			0x8002	/* Supplied transport not supported */
#define HEIE_INVALID_DEVICE					0x8003	/* Supplied device is not valid */
#define HEIE_BUFFER_TOO_SMALL				0x8004	/* Supplied buffer is too small */
#define HEIE_ZERO_BYTES_RECEIVED			0x8005	/* Zero bytes were returned in the packet */
#define HEIE_TIMEOUT						0x8006	/* Timeout error */
#define HEIE_UNSUPPORTED_PROTOCOL			0x8007	/* Supplied protocol not supported */
#define HEIE_IP_ADDR_NOT_INITIALIZED		0x8008	/* The devices IP address has not be set. NOTE: Need to use */
													/* addressed broadcast to talk to the module (with IP) to setup */
													/* the IP address. */
#define HEIE_NULL_TRANSPORT	 				0x8009	/* No transport specified. */
#define HEIE_IPX_NOT_INSTALLED				0x800A	/* IPX Transport not installed. */
#define HEIE_IPX_OPEN_SOCKET			 	0x800B	/* Error opening IPX Socket. */
#define HEIE_NO_PACKET_DRIVER				0x800C	/* No packet driver found. */
#define HEIE_CRC_MISMATCH					0x800D	/* CRC did not match. */
#define HEIE_ALLOCATION_ERROR				0x800E	/* Memory allocation error failed. */
#define HEIE_NO_IPX_CACHE					0x800F	/* No cache has been allocated for IPX */
#define HEIE_INVALID_REQUEST				0x8010	/* Invalid request */
#define HEIE_NO_RESPONSE					0x8011	/* No response was available./ requested */
#define HEIE_INVALID_RESPONSE				0x8012	/* Invalid format response was received. */
#define HEIE_DATA_TOO_LARGE					0x8013	/* Given data is too large */
#define HEIE_LOAD_PROC_ERROR				0x8014  /* Error loading procedures */
#define HEIE_NOT_LOADED						0x8015	/* Attempted command before successfull OpenTransport */
#define HEIE_ALIGNMENT_ERROR				0x8016	/* Data not aligned on proper boundary */
#define HEIE_FILE_NOT_OPEN					0x8017    /* File not open */

#define HEIE_LOAD_ERROR						0x8100	/* Mask for WinSock load Error see below (from HEIOpenTransport) */
#define HEIE_LAST_LOAD_ERROR				0x811F	/* Last in the range of WinSock load Errors */

#define HEIE_IO_ERROR						0x9000	/* Mask for IO Error condition (from HEIReadModuleStatus, HEIReadIO, or HEIWriteIO) */
#define HEIE_IO_WARNING						0xA000	/* Mask for IO Warning condition (from HEIReadModuleStatus, HEIReadIO, or HEIWriteIO) */
#define HEIE_IO_INFO							0xC000	/* Mask for IO Info condition (from HEIReadModuleStatus, HEIReadIO, or HEIWriteIO) */

#define HEIE_ICMP_PKT_FOUND				65
#define HEIE_ARP_PKT_FOUND				   66
#define HEIE_TYPE_NOT_HANDLED			   67
#define HEIE_LINK_SENSE_TRIGGERED		68
#define HEIE_UNK_IP_PACKET					100
#define HEIE_UNK_ETHERTYPE					101
#define HEIE_UNK_PACKET_TYPE 				102
#define HEIE_UNK_802X_PACKET_TYPE		103
#define HEIE_UNK_LLC_TYPE					104
#define HEIE_CRC_DOES_NOT_MATCH			105
#define HEIE_CRC_NO_DATA					106
#define HEIE_ENET_ADDR_REPROGRAMMED		107
#define HEIE_NULL_DATA_POINTER			108
#define HEIE_SIZE_ERROR						109
#define HEIE_NOT_FOUND						110
#define HEIE_INVALID_TYPE					111
#define HEIE_RAM_ALREADY_LOCKED			112
#define HEIE_INVALID_REQUEST_INT 		113
#define HEIE_TIMEOUT_ERROR					114
#define HEIE_FLASH_PROGRAM_ERROR			115
#define HEIE_INVALID_OS						116
#define HEIE_INVALID_LOCATION				117
#define HEIE_INVALID_SLOT_NUMBER			118
#define HEIE_INVALID_DATA					119
#define HEIE_MODULE_BUSY					120
#define HEIE_CHANNEL_FAILURE				121
#define HEIE_UNUSED_CHANNELS_EXIST		122
#define HEIE_INVALID_UDP_PORT				123
#define HEIE_SHUTDOWN_OS					124
#define HEIE_NOT_MY_IP_ADDRESS			125
#define HEIE_PROTECTION_ERROR				126
#define HEIE_UNK_TYPE_ERROR				127
#define HEIE_BACKPLANE_INIT_ERROR		128
#define HEIE_UNK_RESPONSE					129
#define HEIE_UNK_RXWX_FORMAT				130
#define HEIE_UNK_ACK							131
#define HEIE_UNK_NAK							132
#define HEIE_RANGE_ERROR					133
#define HEIE_LENGTH_WARNING				134
#define HEIE_INVALID_BASE_NUMBER			135
#define HEIE_INVALID_MODULE_TYPE			136
#define HEIE_INVALID_OFFSET				137
#define HEIE_INVALID_BOOT_VER_FOR_OS	138
#define HEIE_BROKEN_TRANSMITTER			139
#define HEIE_INVALID_ADDRESS				140
#define HEIE_TIMING							141
#define HEIE_CHANNEL_FAILURE_MULTI		142
#define HEIE_SERIAL_SETUP_ERROR			143
#define HEIE_NOT_INITIALIZED				144
#define HEIE_INVALID_MODE					145
#define HEIE_COMM_FAILURE					146
#define HEIE_OPERATION_ABORTED			147
#define HEIE_INVALID_RX_CHAR				148
#define HEIE_REQUEST_NAKED					149
#define HEIE_INVALID_OPERATION			150
#define HEIE_VAL_ALREADY_USED				151
/* define HEIE_MODULE_ERROR					152 */
#define HEIE_MODULE_NOT_RESPONDING		153
#define HEIE_BASE_CHANGED					154	/* I/O Base has changed */
#define HEIE_MODULE_FAILURE				155
#define HEIE_PARITY_ERROR					156
#define HEIE_FRAMING_ERROR					157
#define HEIE_OVER_RUN_ERROR				158
#define HEIE_BUFFER_OVERFLOW				159
#define HEIE_ABORT							160
#define HEIE_BUSY								161
#define HEIE_DRIVE_TRIP						162  /* Drive has tripped */
#define HEIE_COMMAND_PENDING				163


#define HEIE_CHANNELS_UNUSED_0			200
#define HEIE_CHANNELS_UNUSED_1			201
#define HEIE_CHANNELS_UNUSED_2			202
#define HEIE_CHANNELS_UNUSED_3			203
#define HEIE_CHANNELS_UNUSED_4			204
#define HEIE_CHANNELS_UNUSED_5			205
#define HEIE_CHANNELS_UNUSED_6			206
#define HEIE_CHANNELS_UNUSED_7			207
#define HEIE_CHANNELS_UNUSED_8			208
#define HEIE_CHANNELS_UNUSED_9			209
#define HEIE_CHANNELS_UNUSED_10			210
#define HEIE_CHANNELS_UNUSED_11			211
#define HEIE_CHANNELS_UNUSED_12			212
#define HEIE_CHANNELS_UNUSED_13			213
#define HEIE_CHANNELS_UNUSED_14			214
#define HEIE_CHANNELS_UNUSED_15			215
#define HEIE_CHANNELS_UNUSED_16			216


/* 	Winsock Load Errors
If OpenTransport for WinSock fails, it will return one of the following errors:
0x8014	Error getting addresses from WinSock.DLL
0x8100	System was out of memory, executable file was corrupt, or relocations were invalid. 
0x8101	Unused
0x8102	File was not found. 
0x8103	Path was not found. 
0x8104	Unused
0x8105	Attempt was made to dynamically link to a task, or there was a sharing or network-protection error. 
0x8106	Library required separate data segments for each task. 
0x8107  Unused
0x8108	There was insufficient memory to start the application. 
0x8109  Unused
0x810A	Windows version was incorrect. 
0x810B	Executable file was invalid. Either it was not a Windows application or there was an error in the .EXE image. 
0x810C	Application was designed for a different operating system. 
0x810D	Application was designed for MS-DOS 4.0. 
0x810E	Type of executable file was unknown. 
0x810F	Attempt was made to load a real-mode application (developed for an earlier version of Windows). 
0x8110	Attempt was made to load a second instance of an executable file containing multiple data segments that were not marked read-only. 
0x8111	Unused
0x8112	Unused
0x8113	Attempt was made to load a compressed executable file. The file must be decompressed before it can be loaded. 
0x8114	Dynamic-link library (DLL) file was invalid. One of the DLLs required to run this application was corrupt. 
0x8115	Application requires Microsoft Windows 32-bit extensions. 
0x8116-0x811F	Unused
*/
													

/* Warnings */
#define HEIW_FIRST_WARNING					0x2000	/* Number for First Error */
#define HEIW_LAST_WARNING					0x2FFF	/* Number for Last Error */
#define HEIW_RETRY							0x2000	/* One or more retrys have occurred. */


/* These are masks for values returned from HEIReadIO and/or HEIWriteIO and indicate that some  */
/* error/warning/info condition exists for some module in the base (it could be an I/O  */
/* module or it could be the ethernet module.  The function HEIReadModuleStatus can then be used  */
/* to retrieve the actual conditions.  Note that more than one of the conditions can exist at any time. */
#define MASK_DEVICE_ERROR			0x1000
#define MASK_DEVICE_WARNING  		0x2000
#define MASK_DEVICE_INFO     		0x4000


/* Data Types */
#define DT_IP_ADDRESS				0x0010	/* 4 Byte IP address */
#define DT_NODE_NUMBER				0x0020	/* 4 Byte Node Number */
#define DT_SUBNET_MASK				0x0030	/* 4 Byte Subnet Mask */
#define DT_GATEWAY_ADDRESS			0x0040	/* 4 Byte Gateway Address */
#define DT_ERASE_COUNT				0x0050   /* 4 Byte used internally */

#define DT_SERIAL_SETUP				0x0011	/* 8 Byte Serial Setup (see SerialSetup)*/
#define DT_SET_PARM					0x8011	/* 8 Byte Parm Setup (see PARM_XXXX defines) */

#define DT_SETUP_ERROR_LIGHT		0x8012	/* 16 Byte Error Light Setup (see ErrorLightSetup) */

#define DT_STARTUP_SETTINGS		0x0013	/* 32 Byte Startup settings data (see StartupSettings above) */
#define DT_TIME_OF_DAY				0x8013	/* SYSTEMTIME structure */
#define DT_TYPE_STRING				0x0033	/* 32 Byte ASCII String for netedit type identification */

#define DT_ENCRYPT_KEY_FLASH		0x0014	/* 64 Byte key data from FALSH See Encryption structure */
#define DT_ENCRYPT_KEY_RAM			0x8014	/* 64 Byte key data from RAM - This is the working copy! */
														/* See Encryption structure */
#define DT_MODULE_SETUP				0x0024	/* 64 Byte data from FLASH. See ModuleSetup structure */

#define DT_RXWX_SETTINGS			0x0015	/* 128 Bytes settings see HEISettings */
#define DT_SETTINGS					0x0015	/* 128 Bytes settings see HEISettings */
#define DT_DRIVE_SETUP				0x0025	/* 128 Byte DriveSetup structure	*/

#define DT_NODE_NAME					0x0016	/* 256 Byte Node Name */
#define DT_DESCRIPTION				0x0026	/* 256 Byte Node Description */
#define DT_LINK_MONITOR				0x8006	/* 256 Byte Link monitor setup (Ram Based) */
														/* See LinkMonitor structure below */
#define DT_IP_SETUP					0x0036	/* 256 Byte IP Setup structure (see IPSetup) */
#define DT_WPLC_SYS_INFO			0x0046	/* 256 Byte WinPLC system info (see WPLCSystemInformation) */
#define DT_ERM_CONFIG				0x0056	/* 256 Byte ERM Config info (see sERMConfig) */
#define DT_ERM_INFO					0x8016	/* 256 Byte ERM Info (see sERMInfo) */
#define DT_DEV_COMMAND				0x8026	/* 32 Byte ERM Command	(see sDevCommand)	*/

#define DT_BASE_DEF					0x0017	/* 512 Byte Base Def (405 HEIWriteBaseDef) */
#define DT_RXWX_NODE_ADDR_1		0x0027	/* 512 Byte node address data for addr 00-31 */
#define DT_RXWX_NODE_ADDR_2		0x0037	/* 512 Byte node address data for addr 32-63 */
#define DT_RXWX_NODE_ADDR_3		0x0047	/* 512 Byte node address data for addr 64-95 */

#define DT_R_W_IO_DEF				0x0057	/* 512 Byte read/write IO def (for Drive card) (base 0) (see MemoryItemBase) */

#define DT_ERM_DEV_00_03			0x0067	/* 512 Byte ERM device data (Devices numbers 00 - 03) (See sERMDevice) */
#define DT_ERM_DEV_04_07			0x0077	/* 512 Byte ERM device data (Devices numbers 04 - 07) (See sERMDevice) */
#define DT_ERM_DEV_08_11			0x0087	/* 512 Byte ERM device data (Devices numbers 08 - 11) (See sERMDevice) */
#define DT_ERM_DEV_12_15			0x0097	/* 512 Byte ERM device data (Devices numbers 12 - 15) (See sERMDevice) */

#define DT_RESET						0x8010	/* 4 Byte (32-Bit) reset flag.  (RESET_XXX values below) */
#define DT_BOOT_OS					0x0023	/* 32 Byte OS Boot data */

#define DT_MODULE_INIT_BASE		0x8057	/* 512 Byte Module Initialization data: (from I/O Base) */



/* Common functions. */
#define FUN_POLLING  				0x00 	/* Polling one module */
#define FUN_READ_VER_INFO			0x01 	/* Read Version Info from module */
#define FUN_READ_SUPPORT_INFO		0x02 	/* Read Support Info from module */
											/* 0x03 UNUSED                								 */
#define FUN_READ_DEVICE_INFO		0x04 	/* Read Device Info from module */
#define FUN_POLLING_ALL				0x05 	/* Polling all bases on the network (returns ethernet address) */
											/* Used as a broadcast function to locate devices on the network. */
#define FUN_WRITE_IO				0x06 	/* Write IO data to the base */
#define FUN_READ_IO					0x07 	/* Read IO data from Base */
#define FUN_READ_BASE_DEF			0x08 	/* Read Base Definition */
#define FUN_QUERY_SETUP_DATA		0x09	/* Query the network for a particular type of data with a particular value */
#define FUN_ENUM_SETUP_DATA			0x0A	/* Enumerate the types of data stored in a module */
#define FUN_READ_SETUP_DATA			0x0B	/* Read a particular type of data from a module */
#define FUN_WRITE_SETUP_DATA		0x0C	/* Write a particular type of data to a module */
#define FUN_DELETE_SETUP_DATA		0x0D	/* Delete a particular type of data from a module */
#define FUN_READ_ETHERNET_STATS		0x0E	/* Read ethernet statistics from the module. */
#define FUN_WRITE_BASE_DEF			0x0F	/* Write Base Definition (305/405 EBC) */
											/* 0x10 UNUSED                								 */
											/* 0x11 UNUSED                								 */
											/* 0x12 UNUSED                								 */
											/* 0x13 UNUSED                								 */
#define FUN_PET_LINK				0x14 	/* Used to keep the link sense timer from firing in the absense of ReadIO or WriteIO messages */
#define FUN_ADDRESSED_BROADCAST		0x15	/* Used to broadcast to a particular ethernet address. Used to setup IP address in a new module. */
#define FUN_DATA_BROADCAST			0x16	/* Used to broadcast to a particular data type. */
#define FUN_READ_MODULE_STATUS		0x17	/* Read the status bytes from each of the slots of the module. */
#define FUN_INIT_BASE_DEF			0x18	/* Initialize the base def by re-reading from the backplane */
#define FUN_CCM_REQUEST				0x19	/* Perform a CCM Request with an ECom Module */
#define FUN_KSEQ_REQUEST			0x1A	/* Perform a K-Seq Request with an ECom Module */
#define FUN_BACKPLANE_REQUEST		0x1B	/* Perform a backplane request on an ECom Module */
#define FUN_EXTEND_RESPONSE			0x1C 	/* Extends the response packet. */

#define FUN_ACK						0x20	/* Acknowledge */
#define FUN_NAK						0x21	/* Not acknowledge */
#define FUN_RESPONSE				0x22	/* Response */

#define FUN_SERIAL_PORT				0x23	/* Execute serial port function (see below) */
#define FUN_WRITE_MEMORY			0x24	/* Write a particular memory type */
#define FUN_READ_MEMORY				0x25	/* Read a particular memory type */
#define FUN_ENUM_MEMORY				0x26	/* Get list of all memory types */
#define FUN_ACCESS_MEMORY			0x27	/* Access (Read/Write) multiple memory types */

#define FUN_READ_SHARED_RAM			0x28	/* Read shared ram */
#define FUN_WRITE_SHARED_RAM		0x29	/* Write shared ram */
#define FUN_WRITE_IO_NO_READ		0x30	/* Write IO without returned read */

#define FUN_COMM_RESPONSE			0x31	/* Response to PLC generated COMM request */
#define FUN_COMM_REQ_ACK			0x32	/* Function from PLC generated COMM request */
#define FUN_COMM_NO_REQ_ACK		0x33	/* Function from PLC generated COMM request */
#define FUN_RUN_PROGRAM				0x34	/* Function to execute a program */
#define FUN_REMOTE_API				0x35	/* Function to execute a function on remote device */

#define FUN_NOTIFY					0x36	/* Indicates a notification */
#define FUN_COMPLETION				0x37	/* Indicates completion of some activity */
#define FUN_PROXY						0x38	/* Indicates a proxy function request */
#define FUN_QUERY_RESPONSE			0x55	/* This is a response to a query function */

#define FUN_USER_CONFIG_PANEL    0x60    /* User specific data for AVG Panel	*/

#define FUN_WRITE_CONFIG_DATA		0x61 	/* Write Config data to the base */
#define FUN_READ_CONFIG_DATA		0x62 	/* Read Config data from Base */

#define FUN_UNSUPPORTED				0x99	/* This function will never be supported by any device (internal use only) */

#define FUN_SET_OS_LOAD				0xF9	/* Set Load OS Parm. */
#define FUN_REBOOT					0xFA	/* Reboot OS			*/


/* Serial port functions */
#define SPF_WRITE_COMM				0x01		/* Writes one or more characters to the serial port */
#define SPF_READ_COMM				0x02		/* Reads zero or more characters from the serial port */
#define SPF_RX_AVAILABLE			0x03		/* Returns number of characters available in the input queue */
#define SPF_RX_FLUSH					0x04		/* Flushs the serial port input queue */
#define SPF_SETUP						0x05		/* Setup serial port (see SerialSetup above) */
#define SPF_TX_LEFT					0x06		/* Returns number of characters left in the output queue */
#define SPF_READ_SETUP				0x07		/* Read Setup serial port (see SerialSetup above) */
#define SPF_ACCESS_COMM				0x08		/* Used to read / write multiple ports */
#define SPF_TX_FLUSH					0x09		/* Flushs the serial port output queue */

/* Serial port commands for HEIAccessComm */
#define SPC_WRITE_PORT				0x01
#define SPC_READ_PORT				0x02
#define SPC_RX_FLUSH					0x04
#define SPC_TX_FLUSH					0x09
#define SPC_ERROR						0x80
#define SPC_READ_RESPONSE			0x82
#define SPC_DONE						0xFF

/* Reset values */
#define RESET_DRIVE_RELAY			0x01	/* Reset relay on ethernet drive card */

/* Parm values */
#define PARM_RETURN_SYS_ERRORS	0x01  


/*
	Memory Types.
	Description of memory types.
	A memory type is a 16 bit value that is divided up as follows:
			FEDCBA9876543210
			PKAAFFFFTTTTUNNN
			||| |   |   ||
			||| |   |   ||-- Number: Index number from 0 to 7
			||| |   |   |
			||| |   |   |-- Undefined (set to zero)
			||| |   |
			||| |   |-- Type: 0000 = General Purpose
			||| |             0001 = Program
			||| |             0010 = System
			||| |             0011 = Timer
			||| |             0100 = Counter
			||| |             0101 = Setup
			||| |             0110 = Input
			||| |             0111 = Output
			||| |             1000 = Undefined 
			||| |             1001 = Undefined 
			||| |             1010 = Undefined 
			||| |             1011 = Undefined 
			||| |             1100 = Undefined 
			||| |             1101 = Undefined 
			||| |             1110 = Undefined 
			||| |             1111 = Undefined 
			||| |
			||| |-- Format: 0000 = Bit
			|||             0001 = Byte
			|||             0010 = Word
			|||             0011 = DWord
			|||             0100 = Float
			|||             0101 = Undefined
			|||             0110 = Undefined
			|||             0111 = Undefined
			|||             1000 = Undefined
			|||             1001 = Undefined 
			|||             1010 = Undefined
			|||             1011 = Undefined
			|||             1100 = Undefined
			|||             1101 = Undefined
			|||             1110 = Undefined
			|||             1111 = Undefined
			|||
			|||-- Access:  00 = Read / write
			||             01 = Read Only
			||             10 = Write Only
			||             11 = Undefined
			||
			||-- Kind of memory: 0 = Ram;  1 = Flash
			|
			|-- Protection:  1 = Protected;  0 = Not Protected
			
			
		Example:  
			V-Memory in Koyo boxes (205/405) is General Purpose, WORD format, Read / Write, RAM.
			this would make the type be: 0000 0010 0000 0000 = 0200h = 512
			
			CR Memory in Koyo boxes is General Purpose, Bit format, Read / Write, RAM,
			this would make the type be: 0000 0000 0000 0000 = 0000h = 0
			
			Scratch Pad Memory in Koyo boxes is System, Byte Format, Read / Write, RAM.
			this would make the type be: 0000 0001 0010 0000 = 0120h = 288
			
			SP's in Koyo boxes is System, Bit Format, Read Only, RAM
			this would make the type be: 0001 0000 0010 0000 = 1020h = 4128
*/

#define MT_KOYO_V		0x0200		/* V-Memory */
#define MT_KOYO_C		0x0000		/* C-Memory */
#define MT_KOYO_Z		0x0120		/* Scratch Pad Memory */	
#define MT_KOYO_SP	0x1020		/* SP-Memory */

#define MT_DRIVE_FIRST 0x300		/* First memory type for Hitachi Drives */
#define MT_HITACHI_D	0x300			/* Hitachi Drive Memory: Monitoring functions */
#define MT_HITACHI_F	0x301			/* Hitachi Drive Memory: Basic Profile functions */
#define MT_HITACHI_A	0x302			/* Hitachi Drive Memory: Standard functions */
#define MT_HITACHI_B	0x303			/* Hitachi Drive Memory: Fine tuning functions */
#define MT_HITACHI_C	0x304			/* Hitachi Drive Memory: Intelligent terminal functions */
#define MT_HITACHI_H	0x305			/* Hitachi Drive Memory: Sensorless vector functions */
#define MT_HITACHI_O	0x306			/* Hitachi Drive Memory: Other functions */
#define MT_HITACHI_OP 0x307		/* Hitachi Drive Memory: Option Board */
#define MT_HITACHI_R 0x308			/* Hitachi Drive Memory: Reference codes */

/* The following offsets can only be used with HEIReadMemory (not HEIAccessMemory) */
#define MT_INFO_OFFSET			0x100		/* Add MT_INFO_OFFSET to above MT_HITACHI_? types to get MemoryTypeInfo for the given ID */
#define MT_VALID_IDS_OFFSET	0x200		/* Add MT_VALID_IDS_OFFSET to above MT_HITACHI_? types to get the valid Ids for the given memory type */
#define MT_MEMORY_TYPE_STRING 0x300		/* Add MT_MEMORY_TYPE_STRING to above MT_HITACHI_? types to get the string name for the memory type (use 128 byte length) */
#define MT_DRIVE_STRING			0x400		/* Add MT_DRIVE_STRING to any of the MT_HITACHI_? types to get the string name for the current drive (use 32 byte length) */
#define MT_VERSION_STRING		0x500		/* Add MT_DRIVE_STRING to any of the MT_HITACHI_? types to get the version string current drive (use 32 byte length) */

typedef struct 
	{
	DWORD MinVal;			/* Minimum value for this type */
	DWORD MaxVal;			/* Maximum value for this type */
	BYTE	Magnitude;		/* Magnitude of type.  See MAG_XXXX values */
	BYTE	RunModeEdit;	/* If TRUE, this field can be edited in run mode */
	BYTE	ReadOnly;		/* If TRUE, this field is read-only */
	BYTE	FieldType;		/* Type of memory.  see FIELD_XXXX values */
	BYTE	NumBits;			/* If FieldType == FIELD_BIT, this tells the number of bits */
	BYTE	StartBit;		/* If FieldType == FIELD_BIT, this tells the starting bit number */
	BYTE  Size;				/* Internal size in bytes */
	WORD  Addr;				/* Internal address */
	BYTE	Unused[13];		/* Unused */
	WORD	NameLength;		/* Length of pName (including null terminator) */
	char Name[224];		/* Name string for the given memory type */
	} MemoryTypeInfo;


typedef struct
	{
	WORD Type;
	WORD Id;
	} MemoryItem;

typedef struct
	{
	MemoryItem Items[16];
	} MemoryItemSlot;

typedef struct
	{
	MemoryItemSlot Slot[8];
	} MemoryItemBase;

#define FIELD_NORMAL		0
#define FIELD_CODE		1
#define FIELD_BIT			2

#define MAG_00001			0
#define MAG_00010			1
#define MAG_00100			2
#define MAG_01000			3


/* Hitachi Drive type defines */
#define L100	1
#define SJ100	2	
#define J300	3
#define SJ300	4

/* GS Drive type defines */
#define GS1		1
#define GS2		2
#define GS3		3
#define GS4		4

/* Defines for Data formats */
#define DF_BIT_IN			0x03
#define DF_BIT_OUT		0x04
#define DF_BYTE_IN		0x10
#define DF_BYTE_OUT		0x11
#define DF_WORD_IN		0x05
#define DF_WORD_OUT		0x06
#define DF_DWORD_IN		0x08
#define DF_DWORD_OUT		0x09
#define DF_DOUBLE_IN		0x12
#define DF_DOUBLE_OUT	0x13
#define DF_FLOAT_IN		0x14
#define DF_FLOAT_OUT		0x15
#define DF_CONFIG			0x16


/* Data type defines for HX-ERM */
#define DATA_SIZE_INFO		0		/* Used to read the size info for					*/
#define DATA_INPUT			1		/* Used to read/write all input data				*/
#define DATA_OUTPUT			2		/* Used to read/write all output data				*/
#define DATA_DESCRIPTION	3		/* Used to read description/layout of I/O data	*/
#define DATA_COMMAND			4		/* Used to read/write to command buffer			*/
#define DATA_ERMINFO			5		/* Used to read sERMInfo structure					*/

/* Commands for the HX-ERM module */
#define COMMAND_PROCESS_IO						1
#define COMMAND_ABORT							2
#define COMMAND_PROCESS_COMMAND_BUFFER		3



/* Restore structure alignment boundary */
#pragma pack()


#endif
