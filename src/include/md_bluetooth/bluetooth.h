/** \file
 *	Bluetooth support basic types. <br>
 *
 *	Copyright 2005-2006 Herocraft Hitech Co. Ltd.<br>
 *	Version 1.0 beta.
 */

#ifndef __MD_BLUETOOTH_H__
#define __MD_BLUETOOTH_H__

namespace mdragon
{

class BtNetwork;

/// Bluetooth packet size.
#define Bt_Packet_Size 126

/// Size of Bluetooth service UUID.
#define Bt_UUID_Size 16

/// Represents application unique service id.
struct BtUUID
{ 
	/// 16 byte uuid.
	Byte data [Bt_UUID_Size];
};


#define Bt_Address_Size 6
#define Bt_Host_Name_Max_Size 32

/// Represents Bluetooth host address.
struct BtHost
{
public:
	/// Device name.
	Char name [Bt_Host_Name_Max_Size + 1];

	/// Bluetooth address.
	Byte address [Bt_Address_Size];

	/// RFCOMM protocol channel.
	Byte channel;
};


} //namespace mdragon

#endif // __MD_BLUETOOTH_H__
