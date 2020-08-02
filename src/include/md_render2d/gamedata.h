/** \file
 *	DragonTool data file. <br>
 *
 *	Copyright 2005-2006 Herocraft Hitech Co. Ltd.<br>
 *	Version 1.0 beta.
 */

#ifndef __MD_GAMEDATA_H__
#define __MD_GAMEDATA_H__

namespace mdragon
{

class TileMap;
class GameDataDummy;

/// CustomData represents custom data storage class.
/**
 *	This class used to store custom data exported from DragonTool.
 */
class CustomData
{
public:

	/// Token id identifier. 
	/**
	 * Set by ExportNode() to equal token name string number in tokens array.
	 */
	Word token;

	/// Data types for variable data.
	/**
	 * It can to have values:
	 * 0 - data is a pointer to string of const Char*. Use data casting (const Char*)data.
	 * 1 - data is a 32 bit integer valuy of type Int.
	 * 2 - data is a fixed point valuy of type Fixed.
	 * 3 - data is a 16 bit short integer valuy of type Short.
	 * 4 - data is a boolean valuy of type Bool.
	 */
	Word data_type;

	/// Custom data value. 
	/**
	 * See data_types for type of value. 
	 */
	Int data;

	/// Pointer to next custom data object. 
	CustomData *next;
};


/// GameData represents DragonTool game data storage class. 
/** 
 *	This class used to import DragoTool game data resource file.
 */
class GameData
{
public:

	/// GameData class constructor.
	GameData();

	/// GameData class destructor.
	/**
	 * Free all memory used to store game data.
	 */
	 ~GameData();

	/// Performs the complete initialization of game data resource file class object. 
	/**
	 * This function must be called before any operations on game data resource file class object.
	 * @param render pointer to Render2D class object.
	 * @param name_ pointer to ASCII name for specified game data resource file to load. Do not add file extension ".dt" to this name.
	 * @return Return True if specified game data resource file load complete successfully else False.
	 */
	Bool Init(Render2D* render_,Char* name_);



////////////////// Possible node types ////////////////////////////////////

	/// Error node type. 
	/**
	 *  Possible reason is trying to work with bad game data resource file.
	 */
	#define GameData_Type_Error -1

	/// Unknown node type.
	/** 
	 *  Possible reason is trying to work with enternal game data nodes or bad game data resource file.
	 */	
	#define GameData_Type_Unknown  0

	/// Dummy node type. 
	#define GameData_Type_Dummy 1

	/// SpriteTransform node type.
	#define GameData_Type_Transform 2

	/// Animation node type.
	#define GameData_Type_Animation 4

	/// Frame node type.
	#define GameData_Type_Frame 5

	/// TileMap node type.
	#define GameData_Type_TileMap 6

///////////////////////////////////////////////////////////////////////////

	/// Returns current active node name.
	/**
	 * @return Returns current active node name.
	 */
	const Char* GetNodeName();

	/// Returns current active node type.
	/**
	 * @return Returns current active node type.
	 */
	Int GetNodeType();

	/// Try to go to next node.
	/**
	 * @return Returns True, if success, else - False.
	 */
	Bool GoToNextNode();

	/// Try to go to previous node.
	/**
	 * @return Returns True, if success, else - False.
	 */
	Bool GoToPreviousNode();

	/// Try to go to top node.
	void GoToTopNode();

	/// Try to go to bottom node.
	void GoToBottomNode();

	/// Try to enter in current node on one level deeper.
	/**
	 *  After successful entrance top first node becomes the current node.
	 *	@return Returns True, if success enter, else - False. 
	 */
	Bool EnterNode();

	/// Try to go up on one level upper.
	/**
	 *  After successful rise parent (the node we last enter) node becomes the current node.
	 *  @return Returns True, if success enter, else - False. 
	 */
	Bool GoToParentNode();

	/// Go to most top root node.
	void GoToRootNode();

	/// Try to go from current to bottom node without deep entering (do search only on current level) and stop on first node with equal specified ASCII name.
	/**
	 * @return Returns True if node success found else False.
	 */
	Bool GoToNextByNameNode(const Char* name_);

	/// Export SpriteTransform class objects from current node.
	/**
	 * @param st_export pointer to vector class object. 
	 *		            This vector class object will be store only pointers 
	 *					on exported SpriteTransform class objects.
	 * @param st_table pointer to SVector class object. 
	 *					All exported SpriteTransform class objects will be 
	 *					created in this unmovable vector.
	 * @param cd_table pointer to SVector class object. 
	 *					All exported CustomData class objects will be 
	 *					created in this unmovable vector.
	 * @param tokens pointer to ASCII names identifications for CustomData 
	 *					class objects tokens. See CustomData token.
	 * @return Return True if export success else False.
	 */	
	Bool ExportNode( vector<SpriteTransform*>* st_export, SVector<SpriteTransform>* st_table, SVector<CustomData>* cd_table, Char** tokens );

	/// Export TileMap class object from current node.
	/**
	 * @param tile_map pointer to store exported TileMap class object.
	 * @return Return True if export success else False.
	 */	
	Bool ExportNode( TileMap* tile_map );

//////////////////////////////////////////////////////////////////////////

private:

	void Parse();

	void ParseSpriteTable();
	void ParseStringTable();

	void ParseMainLoop(Int end_position,Int parent);
	
	Int ParseDummy(Int end_position,Int parent);
	Int ParseTransform(Int end_position,Int parent);
	Int ParseAnimation(Int end_position,Int parent);
	Int ParseFrame(Int end_position,Int parent);
	Int ParseTileMap(Int end_position,Int parent);
	Int ParseSprite(Int end_position,Int parent);

	void ParseCustomProperties(Int end_position,Int parent);

	void CopyCustomData( CustomData* cd, SpriteTransform* st, SVector<CustomData>* cd_table, Char** tokens );

	Sprite2D* FindSpriteMipMap();

	string name;

	Render2D* render;

	Sprite2D* sprites;
	Int sprites_count;

	Char* strings_data;
	Char** strings;
	Int strings_count;

	Resource* gd_res;
	Int gd_size;

	Int dummies;

	SVector<CustomData>* custom_data_table;

	SVector<GameDataDummy>* dummy_table;

	GameDataDummy* dummy_table_loaded;
	Int dummy_table_loaded_size;

#ifdef MD_OS_PALM
Word featureNum_dummy_table_loaded;
Word featureNum_sprites;
Word featureNum_strings_data;
#endif

	SVector<Sprite2D>* sprite_mipmap_table;
	vector<Sprite2D*>* sprite_mipmaps;

	Int sprite_mimmap_index[10];
	Int sprite_mimmap_index_count;

	Int current_node;
	
};

} //namespace mdragon

#endif // __MD_GAMEDATA_H__