
#include "../mdconfig.h"

#include "mdragon.h"

using namespace mdragon;

#define GAME_State_Hello 0
#define GAME_State_Error 1
#define GAME_State_Shutdown	2

#define GAME_State_Master_Discover 3
#define GAME_State_Master_Connected 4

#define GAME_State_Slave_Wait 10
#define GAME_State_Slave_Connected 11

/**
 *	Main game class.
 */
class GameProject : public MDGame
{
public:

	///////////////////////////////////////////////////////////////////
	// RemoteConnection structure describes connection to remote host.
	///////////////////////////////////////////////////////////////////
	struct RemoteConnection
	{
		RemoteConnection( IBtConnection * connection )
		{
			data_received = 0;
			data_sent = 0;
			this->connection = connection;
		}

		// test message associated with this connection.
		string text;

		// amount of data received from the remote host.
		size_type data_received;

		// amount of data sent to the remote host.
		size_type data_sent;

		// bluetooth connection pointer.
		IBtConnection * connection;
	};


	// Constructor.
	GameProject(System* system_)
	{
		// remember System object pointer
		system = system_;
	
		// create 2d renderer instance
		system->render2d = new Render2D;

		n_runs = 0;

		// remember bluetooth service uuid for this application.
		BtUUID my_uuid = { 0xca, 0x6b, 0x52, 0xfa, 0xec, 0x3d, 0x4f, 0x8f, 
							0xb6, 0x7d, 0x74, 0xd3, 0x8a, 0x9c, 0x76, 0x0a };
		bt_uuid = my_uuid;

		// set initial application state.
		state = GAME_State_Hello;
	}

	// Destructor
	~GameProject()
	{
		// nothing spectial to do here.
	}

	// Implement MDGame pure virtual.
	Bool Init()
	{
		// Load font.
		font.Create( system->render2d, "tahoma" );

		return True;
	}

	// Implement MDGame pure virtual.
	Bool Update()
	{
		n_runs++;

		// on KEY_A key down start shutdown & exit
		if( system->input.KeyDown( KEY_A ) )
			Shutdown();

		// Initial state is
		// On KEY_UP switch into master mode.
		// On KEY_DOWN switch into slave mode.
		if( GAME_State_Hello == state )
		{
			if( system->input.KeyPressed( KEY_UP ) )
				StartMaster();
			else 
			if( system->input.KeyPressed( KEY_DOWN ) )
				StartSlave();
		}

		// Exit when bluetooth shutdown finished.
		if( ( GAME_State_Shutdown == state ) && 
			system->btnet.IsShutdownComplete() )
		{
			system->Exit();
			return False;
		}

		// Update master mode state.
		UpdateMaster();

		// Update slave mode state.
		UpdateSlave();

		// Update every remote connection state.
		for( size_type i = 0; i < remote_connections.size(); ++i )
			UpdateConnection( remote_connections[i] );

		return True;
	}

	// Implement MDGame pure virtual.
	void Draw()
	{
		Render2D * render = system->render2d;

		// clear screen 
		render->SetViewport( 0, 0, render->GetScreenWidth(), render->GetScreenHeight() );
		render->SetClearColor( Color(0,0,0,0) );
		render->Clear( Render2D_Clear_Color );

		// draw run time
		system->user_string0 = "TIME: ";
		system->user_string0 << n_runs;
		font.Draw( system->user_string0.c_str(), 0, 0 );

		// draw hello message
		if( GAME_State_Hello == state )
		{
			font.Draw( "Bluetooh demo", 0, 20 );
			font.Draw( "press key to choose:", 0, 40 );
			font.Draw( "UP - master", 0, 60 );
			font.Draw( "DOWN - slave", 0, 80 );
			font.Draw( "Soft A - exit", 0, 100 );
		}

		// draw error message
		if( GAME_State_Error == state )
		{
			Int color = font.GetColor();
			font.SetColor( Color( 0xff, 0, 0, 0 ) );
			font.Draw( s_error.c_str(), 0, 20 );
			font.SetColor( color );
		}

		// draw shutdown message
		if( GAME_State_Shutdown == state )
			font.Draw( "shutdown", 0, 20 );

		// draw master' searching message.
		if( GAME_State_Master_Discover == state )
			font.Draw( "searching slaves", 0, 20 );

		// draw slave waiting message.
		if( GAME_State_Slave_Wait == state )
			font.Draw( "waiting for master", 0, 20 );

		// draw every connection state.
		if( ( GAME_State_Master_Connected == state ) ||
			( GAME_State_Slave_Connected == state ) )
		{
			Int y = 20;
			for( size_type i = 0; i < remote_connections.size(); ++i )
			{
				font.Draw( remote_connections[i].text.c_str(), 0, y );
				y += 20;
			}
		}

		// flush draw queue & show it.
		render->Flush();
		render->Show();
	}

	void StartMaster()
	{
		// Init bluetooth
		if( ! system->btnet.Init( &bt_uuid ) )
			Error( "Bluetooth init failed" );
		else
		// Switch to master mode
		if( ! system->btnet.StartMaster() )
			Error( "StartMaster failed" );
		else
		{ // If master initiated succesfully - start to discover slave devices.
			state = GAME_State_Master_Discover;
			if( ! system->btnet.StartDiscoverSlaves() )
				Error( "Discovery failed" );
		}
	}

	void StartSlave()
	{
		// Init bluetooth
		if( ! system->btnet.Init( &bt_uuid ) )
			Error( "Bluetooth init failed" );
		else
		// switch to slave mode
		if( ! system->btnet.StartSlave() )
			Error( "StartSlave failed" );
		else // if slave initiated successfully - wait for inbound connection.
			state = GAME_State_Slave_Wait;
	}

	void UpdateMaster()
	{
		BtNetwork & bt_net = system->btnet;
		if( GAME_State_Master_Discover == state )
		{
			// Check if discovery is finished.
			if( bt_net.GetDiscoveredSlaves( &found_hosts ) )
			{
				// switch to connect state.
				state = GAME_State_Master_Connected;

				// assume that it is error if we cannot find at leas one slave.
				if( found_hosts.size() == 0 )
				{
					Error( "no slaves found" );
					return;
				}

				// start initiating connections to discovered slaves.
				for( size_type i = 0; i < found_hosts.size(); ++i )
				{
					// allow no more than 3 pending connections
					if( remote_connections.size() == 3 )
						break;

					// try to connect
					IBtConnection * new_connection = bt_net.ConnectSlave( found_hosts[i] );
					if( new_connection )
						remote_connections += RemoteConnection( new_connection );
				}

				// assume that it is error if we cannot initiate at least one connection.
				if( remote_connections.size() == 0 )
					Error( "cannot connect" );
			} // if( bt_net.GetDiscoveredSlaves( &found_hosts ) )

		} // if( GAME_State_Master_Discover == state )

	}// void UpdateMaster()

	
	void UpdateSlave()
	{
		BtNetwork & bt_net = system->btnet;
		
		// slave device waiting for connection from master.
		if( GAME_State_Slave_Wait == state )
		{
			// check if there is inbound connection.
			IBtConnection * new_connection = bt_net.GetInboundConnection();
			if( new_connection )
			{
				remote_connections += RemoteConnection( new_connection );
				state = GAME_State_Slave_Connected;
			}
		}
	}

	void UpdateConnection( RemoteConnection & remote_connection )
	{
		remote_connection.text = "connecting";

		IBtConnection * connection = remote_connection.connection;
		if( connection->IsConnected() )
		{
			if( connection->StartWrite() )
			{
				for( Int i = 0; i < Bt_Packet_Size; ++i )
				{
					Byte n = i;
					connection->Write( &n, sizeof(n) );
				}
				connection->EndWrite();

				remote_connection.data_sent += Bt_Packet_Size;
			}

			if( connection->StartRead() )
			{
				Byte n [Bt_Packet_Size];

				connection->Read( &n[0], sizeof( n ) );

				connection->EndRead();

				for( Int i = 0; i < Bt_Packet_Size; ++i )
				{
					if( n[i] != i )
						Error( "data error" );
				}

				remote_connection.data_received += Bt_Packet_Size;
			}

			remote_connection.text = "out: ";
			remote_connection.text << remote_connection.data_sent <<
					" in: " << remote_connection.data_received;
		}

		if( connection->IsDisconnected() )
			remote_connection.text = "disconnected";

	}

	void Shutdown()
	{
		state = GAME_State_Shutdown;
		system->btnet.StartShutdown();
		remote_connections.clear();
	}

	void Error( const string & s_error )
	{
		state = GAME_State_Error;
		this->s_error = s_error;
	}

private:

	System* system;
	Font2D font;

	DWord n_runs;

	Int state;

	vector<BtHost> found_hosts;

	vector<RemoteConnection> remote_connections;

	string s_error;

	BtUUID bt_uuid;
};


/**
 * 	Implement MDGameCreate function.
 */
MDGame* MDGameCreate( System * system )
{
	return new GameProject( system );
}

/**
 *	Implement MDGameSetPreferences function.
 */
void MDGameSetPreferences( MDGamePreferences & p )
{
	p.name = MD_GAME_NAME;
	p.title = MD_GAME_TITLE;
	p.log_level = MD_LOG_LEVEL;
	p.log_name = MD_LOG_NAME;
	p.runs_per_second = MD_AI_RUNS_PER_SECOND;
	p.pack_dir_name = MD_PACKDIR_NAME;
	p.system_pool_size = MD_SYSTEM_POOL_SIZE;
	p.symbian_uid = MD_SYMBIAN_UID;
	p.palm_creator_id = MD_PALM_CREATOR_ID;
}
