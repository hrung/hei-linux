 /*
**	HEI.C - Platform dependent code for communicating with Host Automation Products
**			line of ethernet modules using the WinSock transport.
** 
**	Copyright (C) - 1996-1997 Host Automation Products, Inc.
**      Portions Copyright Northwestern University, DND-CAT
*/
#include <sys/time.h>
#include <netinet/in.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <memory.h>
#include "heidefs.h"
#include "hei.h"	

#define SOCKET_ERROR -1
#define INVALID_SOCKET -1

typedef int SOCKET;

/*
**	Notes for porting code to another platform:
**
**	This file contains the transport/system dependant code for use with the
**	Host Ethernet Interface (HEI).  There are nine functions which must be
**	implemented by this code:
**
**		1) int HEIIOpen();
**		2) int HEIIClose();
**		3) int HEIIOpenTransport(HEITransport *pTransport);
**		4) int HEIICloseTransport(HEITransport *pTransport);
**		5) int HEIIOpenDevice(HEITransport *pTransport, HEIDevice *pDevice);
**		6) int HEIICloseDevice(HEIDevice *pDevice);
**		7) int HEIIReceivePacket(HEIDevice *pDevice, BYTE *pResponse, int *pResponseSize);
**		8) int HEIISendPacket(HEIDevice *pDevice, BYTE *pPacket, WORD PacketSize);
**		9) DWORD HEIIGetCounter();
**
**	Make changes in this file, do not change HEI.C or any structures in HEI.H!  
**	If you find that you must change something in HEI.C, contact the person
**	you got this source from.
**
**	Feel free to remove any of the WinSock specific code from this module.
**	
**	To compile the code for ANSI C, ANSI_C must be defined!
**
**	See all sections containing "TODO_FOR_OTHER_SYSTEM" for further details.
**
*/


/* We will want to store the starting time in seconds that the Module
   was called.  This is so that we can give back a millisecond timer
   function that doesn't have roundoff problems */ 


/* This is the port number to use when talking to a module. */
#define PORT_ID 0x7070

unsigned long hei_starttime = 0;
/* This function should return a millisecond resolution tick counter. */

DWORD HEIIGetCounter()
	{
  /* We will use the gettimeofday function to provide the millisecond
     tick counter.  We will return the timer tick relative to the
     first time the routine is called    */
         struct timeval date;
         struct timezone tz;
	 unsigned long now;
         gettimeofday(&date,&tz);
	 /* The first time this timer is called, initialize the starttime
	 ** variable */  
         if (hei_starttime==0) {hei_starttime = date.tv_sec;};
         now = ((date.tv_sec-hei_starttime)*1000)+(date.tv_usec/1000);
         return now;
	}

/* 
** This function is called from within HEIOpen. It gives the opportunity
** to do initialization type stuff.  NOTE: This function may be called more
** than once!
**
** RETURNS:  0 on success
**           non-zero on error.
*/
int HEIIOpen()
	{
	/* 
	** TODO_FOR_OTHER_SYSTEM 
	** Do system level init stuff here.  
	** Be aware that this may be called more than once.
	*/
        /* Nothing needs to be done for Unices since they are real
           operating systems */ 
	return HEIE_NULL;
	}
	
/* 
** This function is called from within HEIClose. It gives the opportunity
** to do shutdown type stuff.  NOTE: This function may be called more
** than once!
**
** RETURNS:  0 on success
**           non-zero on error.
*/
int HEIIClose()	
	{
	/* 
	** TODO_FOR_OTHER_SYSTEM 
	** Do system level shut down stuff here.  
	** Be aware that this may be called more than once.
	*/
        /* Nothing needs to be done for Unices since they are real
           operating systems */ 
	return HEIE_NULL;	
	}	
	
/*
** This function is called from within HEIOpenTransport.  It is used to prepare
** the given Transport to be used in subsequent HEIOpenDevice calls.
**
** RETURNS:  0 on success
**           non-zero on error.
*/
int HEIIOpenTransport(HEITransport *pTransport)
	{	
  /* Once again, nothing needs to be done */
	return HEIE_NULL;
        }
   
   
/*
** This function is called from within HEICloseTransport.  It indicates
** that the given Transport is no longer in use.
**
** RETURNS:  0 on success
**           non-zero on error.
*/
int HEIICloseTransport(HEITransport *pTransport)
	{
  /* Once again, nothing needs to be done */		
	return HEIE_NULL;	
	}

/**
** This function is called from within HEIOpenDevice.  It is used to prepare
** the given Device to be used with the given Transprot.
**
** RETURNS:  0 on success
**           non-zero on error.
*/
int HEIIOpenDevice(HEITransport *pTransport, HEIDevice *pDevice)
	{
	switch (pTransport->Transport)	
		{
		case HEIT_UNIX: 	/* Open Device type HEIT_UNIX */
			{
			/* WinSock Transport. */
			SOCKET sock;
			struct sockaddr *pRemAddr, *pMyAddr;
			int SizeRemAddr, SizeMyAddr;

			if (pTransport->Protocol == HEIP_IP)
				{
				static struct sockaddr_in RemAddr, MyAddr;

				/*
				** If Protocol is IP and we are not using broadcast, and 
				** Address.Raw[19] == 1 then the IP address in the module
				** is undefined.
				*/
				if (!pDevice->UseBroadcast && (pDevice->Address.Raw[19] == 1))
					return HEIE_IP_ADDR_NOT_INITIALIZED;
					
				/* Initialize remote address */
				if (!pDevice->UseBroadcast)
					memcpy(&RemAddr, pDevice->Address.Raw, sizeof(RemAddr));

				/* Initialize MyAddr to all zeros so that the OS can tell me who I am! */
				MyAddr.sin_family = AF_INET;
				MyAddr.sin_port = 0;
				MyAddr.sin_addr.s_addr = 0;

				/* get socket handle */
				sock = socket(AF_INET,     /* IP family */
							  SOCK_DGRAM,    /* Datagram */
							  IPPROTO_UDP);      

				pRemAddr = (struct sockaddr *) &RemAddr;
				pMyAddr = (struct sockaddr *) &MyAddr;
				SizeRemAddr = sizeof(RemAddr);
				SizeMyAddr = sizeof(MyAddr);
				}
			else 
				return HEIE_UNSUPPORTED_PROTOCOL;


			if(sock == INVALID_SOCKET) 
				return errno;

			if (bind (sock,	pMyAddr, SizeMyAddr) == SOCKET_ERROR)
				{
				close(sock);
				return errno;
				} 

			if (pDevice->UseBroadcast)
				{
				int rSetSockOpt;
				int AllowBroadcast = TRUE;
				rSetSockOpt = setsockopt(sock, SOL_SOCKET, SO_BROADCAST, (const char *) &AllowBroadcast, sizeof(AllowBroadcast));
				
				if (rSetSockOpt == SOCKET_ERROR)
					{
					close(sock);
					return errno;
					}
				}
			else /* If not a broadcast */
				{
				if (connect (sock,pRemAddr, SizeRemAddr) == SOCKET_ERROR)
					{
					close(sock);
					return errno;
					} 
				}

			/* Setup for non-blocking mode */

			if (fcntl (sock, F_SETFL, O_NONBLOCK) == SOCKET_ERROR)
				{
				close(sock);
				return errno;
				}

			pDevice->_dwParam = (DWORD) sock;
			break;
			}
			
		case HEIT_OTHER_TRANSPORT:
			{
			/* 
			** TODO_FOR_OTHER_SYSTEM 
			** Prepare to communicate with the given device.
			** The address to talk to is stored in pDevice->Address (see HEI.H for format)
			** Be aware that pDevice->UseBroadcast indicates that we
			** will be broadcasting to the module.
			** For IP, pDevice->Address.Raw[19] == 1 (after a query)
			** if the given module's IP address is not initialized.  In
			** this case, the only way to talk to it (using IP) is by 
			** using addressed broadcast.
			** You can use pDevice->_dwParam to store whatever (such as
			** a socked number).
			** Don't return HEIE_UNSUPPORTED_TRANSPORT
			*/
			return HEIE_UNSUPPORTED_TRANSPORT;
			}
		
		default:
			return HEIE_UNSUPPORTED_TRANSPORT;
		}
		
	return HEIE_NULL;
	}

/*
** This function is called from within HEICloseDevice.  It indicates
** that the given Device is no longer in use.
**
** RETURNS:  0 on success
**           non-zero on error.
*/
int HEIICloseDevice(HEIDevice *pDevice)
	{
	switch (pDevice->_pTransport->Transport)	
		{
		case HEIT_UNIX:		/* Close Device type HEIT_UNIX */
			{
			/* WinSock Transport. */
			if (pDevice->_pTransport->Protocol == HEIP_IP)
				{
				SOCKET sock = (SOCKET) pDevice->_dwParam;
			   
				if (close(sock) == SOCKET_ERROR)
					return errno;
				}
			else
				return HEIE_UNSUPPORTED_PROTOCOL;

			break;
			}
			
		case HEIT_OTHER_TRANSPORT:
			{
			/* 
			** TODO_FOR_OTHER_SYSTEM
			** Do device type shutdown stuff.
			** Don't return HEIE_UNSUPPORTED_TRANSPORT
			*/
			return HEIE_UNSUPPORTED_TRANSPORT;
			}
		
		default:
			return HEIE_UNSUPPORTED_TRANSPORT;
		}
   	
	return HEIE_NULL;	
	}
	
	
/*
**	This is the code for receiving a packet from the ethernet driver for the given
**  device.  The response should be stored in the given response buffer - pResponse.
**  On entry, pResponseSize contains the size of the response buffer (pResponse).
**  On exit, pResponseSize MUST contain the number of bytes copied to the response buffer.
**
** RETURNS:  0 on success
**           non-zero on error.
*/
int HEIIReceivePacket(HEIDevice *pDevice, BYTE *pResponse, int *pResponseSize)
	{
	int Retval = HEIE_NULL;
	
	switch (pDevice->_pTransport->Transport)	
		{
		case HEIT_UNIX:		/* GetResponse from HEIT_UNIX */
			{
			int NumBytes;
			SOCKET sock = (SOCKET) pDevice->_dwParam;
			
			if (pDevice->UseBroadcast)
				{
				struct sockaddr FromAddr;
				int FromLen = sizeof(FromAddr);
		
				NumBytes = recvfrom(sock, (char *) pResponse, *pResponseSize, 0, &FromAddr, (socklen_t*)(&FromLen));
				
				if (pDevice->pData)
					{
					/* Need to copy FROM address. */
					int Num2Copy = FromLen;
			
					if (pDevice->SizeOfData < Num2Copy)
						{
						Retval = HEIE_BUFFER_TOO_SMALL;
						Num2Copy = pDevice->SizeOfData;
						}
			
					memcpy(pDevice->pData, &FromAddr, Num2Copy);					
					}
				}
			else
				{
				NumBytes = recv(sock, (char *) pResponse, *pResponseSize, 0);
				}
			
			if (NumBytes == SOCKET_ERROR)
				{
				/* Check to see if the error is WSAWOULDBLOCK. */
				int Error = errno;
		
				if (Error != EWOULDBLOCK)
					{
					*pResponseSize = 0;
					Retval = Error;
					}
				else
					{
					Retval = HEIE_NO_RESPONSE;
					}
				}
			else
				{
				(*pResponseSize) = NumBytes;
				}
			
			break;
			}

		case HEIT_OTHER_TRANSPORT:
			{
			/* 
			** TODO_FOR_OTHER_SYSTEM 
			** Receive a packet for the given device into the buffer pResponse.
			** *pResponseSize indicated the length of the pResponse buffer.
			** If pDevice->UseBroadcast && pDevice->pData, 
			** then we need to copy the FROM address into pDevice->pData.
			** pDevice->SizeOfData tells how long the buffer pDevice->pData is.
			** Store the number of bytes received in (*pResponseSize).
			** Don't return HEIE_UNSUPPORTED_TRANSPORT
			*/
			return HEIE_UNSUPPORTED_TRANSPORT;
			}
		
		default:
			return HEIE_UNSUPPORTED_TRANSPORT;
		}
		
	return Retval;
	}             
	
/*
** This is the code for sending the given packet for the given device.
** pPacket is the pointer to the actual packet data, and PacketSize is the
** number of bytes in the packet to be sent.
**
** RETURNS:  0 on success
**           non-zero on error.
*/
int HEIISendPacket(HEIDevice *pDevice, BYTE *pPacket, WORD PacketSize)
	{
	switch (pDevice->_pTransport->Transport)	
		{
		case HEIT_UNIX:			/* Send packet of type HEIT_UNIX */
			{
			/* Unix Transport. */
			SOCKET sock = (SOCKET) pDevice->_dwParam;

			if (pDevice->UseBroadcast)
				{
				/* Initialize remote address */
				struct sockaddr *pRemAddr = (struct sockaddr *) NULL;
				int SizeRemAddr = 0;

				if (pDevice->_pTransport->Protocol == HEIP_IP)
					{
					static struct sockaddr_in RemAddr;
		
					RemAddr.sin_family = AF_INET;
					RemAddr.sin_port = PORT_ID;
					RemAddr.sin_addr.s_addr = INADDR_BROADCAST;
		
					pRemAddr = (struct sockaddr *) &RemAddr;
					SizeRemAddr = sizeof(RemAddr);
					}

				if (sendto(sock, (char *) pPacket, PacketSize, 0, pRemAddr, SizeRemAddr) == SOCKET_ERROR)
					return  errno;
				}
			else
				{
				if (send(sock, (char *) pPacket, PacketSize, 0) == SOCKET_ERROR)
					return  errno;
				}
			
			return HEIE_NULL;
			}

		case HEIT_OTHER_TRANSPORT:
			{
			/* 
			** TODO_FOR_OTHER_SYSTEM 
			** Send a packet to the given device.
			** If pDevice->UseBroadcast, then we need to broadcast the packet.
			** Don't return HEIE_UNSUPPORTED_TRANSPORT
			*/
			return HEIE_UNSUPPORTED_TRANSPORT;
			}
		
		default:
			return HEIE_UNSUPPORTED_TRANSPORT;
		}
	}	
