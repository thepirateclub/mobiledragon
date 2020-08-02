/** \file
 *	Bluetooth network main class. <br>
 *
 *	Copyright 2005-2006 Herocraft Hitech Co. Ltd.<br>
 *	Version 1.0 beta.
 */

#ifndef __MD_BT_NETWORK_H__
#define __MD_BT_NETWORK_H__

namespace mdragon
{

class BtNetworkImp;

/// Main Bluetooth networking support class.
/**
 *	Manages Bluetooth SDP discovery, advertisement and connection 
 *	establishement. You don't have to create instances of BtNetwork by
 *	yourself, use btnet member of System object instead.
 */
class BtNetwork
{
public:

	void Update();


	/// Initializes bluetooth.
	/**
	 *	Must be called before any other use of BtNetwork class.
	 *	@param app_uuid - pointer to BtUUID object, unique application service identifier.
	 *	@return True on success, False on failure.
	 */
	Bool Init( const BtUUID *app_uuid );

	/// Switches bluetooth into slave mode.
	/**
	 *	Slave registers application in bluetooth SDP and begins listening
	 *	for inbound connections.
	 *	@return True on success, False on failure.
	 */
	Bool StartSlave();


	/// Switches bluetooth into master mode.
	/**
	 *	Master can perform device discovery and establish connections 
	 *	to slave devices.
	 *	@return True on success, False on failure.
	 */
	Bool StartMaster();


	/// Starts slave devices discovery sequence.
	/**
	 * @return True if discovery is pending, False on failure.
	 */
	Bool StartDiscoverSlaves();

	/// Enumerates hosts, found during slave discovery.
	/**
	 * @param hosts pointer to vector of BtHost objects to fill with addresses of found hosts.
	 * @return False if host discovery is pending, True on completion.
	 */
	Bool GetDiscoveredSlaves( vector<BtHost> *hosts );

	/// Retrives inbound connection.
	/**
	 *	Available only in slave mode. Returns pointer to new connection object if
	 *	there was an inbound connection from master accepted or NULL if there 
	 *	is no an inbound connection accepted or there is already one active connection.
	 *	Note, that slave can have only one active connection, so before another connection can 
	 *	be accepted, active connection must be explicitly closed with CloseConnection.
	 *	@return pointer to newly created BtConnection oject or NULL.
	 */
	IBtConnection *GetInboundConnection();

	/// Starts connection establishement.
	/**
	 *	Tries to establish connection to remote device. 
	 *	Returns pointer to created IBtConnection object. This connection
	 *	object will be in connecting state.
	 *	@param remote_host - address of host to connect.
	 *	@return pointer to IBtConnection object or NULL on failure.
	 */
	IBtConnection *ConnectSlave( const BtHost &remote_host );

	/// Disconnects and closes specified connection.
	/**
	 *	Pointer to connection is no longer valid and should not be used any more.
	 *	@param connection - pointer to connection to close.
	 */
	void CloseConnection( IBtConnection *connection );

	/// Starts bluetooth system shutdown.
	/**
	 *	This process can take some time. Call IsShutdownComplete()
	 *	to ensure that bluetooth system shutdown is complete.
	 */
	void StartShutdown();

	/// Verifies if bluetooth system shutdown is finished.
	/**
	 *	@return True if system shutdown is finished, False otherwise.
	 */
	Bool IsShutdownComplete();

private:

	friend class System;

	BtNetwork();

	~BtNetwork();

	BtNetworkImp *bt_network_imp;
};

} //namespace mdragon

#endif //__MD_BT_NETWORK_H__
