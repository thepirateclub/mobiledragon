/** \file
 *	Bluetooth network connection interface. <br>
 *
 *	Copyright 2005-2006 Herocraft Hitech Co. Ltd.<br>
 *	Version 1.0 beta.
 */

#ifndef __MD_IBTCONNECTION_H__
#define __MD_IBTCONNECTION_H__

namespace mdragon
{

/// Bluetooth endpoint connection interface.
/**
 *	Manages data exchange between two hosts. It allows to send and receive
 *	data packets 126 bytes long.
 */
class IBtConnection
{
public:

	/// Checks if connected to remote host.
	/**
	 *	@return True if connected, False otherwise.
	 */
	virtual Bool IsConnected () = 0;

	/// Checks if disconnected from remote host.
	/**
	 *	@return True if connected, False otherwise.
	 */
	virtual Bool IsDisconnected() = 0;

	/// Call before writing data to connection send buffer.
	/**
	 *	@return True if connection is ready to accept new portion of data.
	 */
	virtual Bool StartWrite() = 0;

	/// Writes data to connection buffer.
	/**
	 *	@param src - pointer to data buffer.
	 *	@param size - data size to write.
	 */
	virtual void Write(const void *src, Word size) = 0;

	/// Sends buffered data to remote host.
	virtual void EndWrite() = 0;

	/// Call before reading data from connection receive buffer.
	/**
	 *	@return True if data packet has been received.
	 */
	virtual Bool StartRead() = 0;

	/// Reads data from connection receive buffer.
	/**
	 *	@param dst - destination buffer.
	 *	@param size - data size to read.
	 */
	virtual void Read(void *dst, Word size) = 0;

	/// Clears connection receive buffer and allows to receive next data packet.
	virtual void EndRead() = 0;
};

} //namespace mdragon

#endif //__MD_IBTCONNECTION_H__
