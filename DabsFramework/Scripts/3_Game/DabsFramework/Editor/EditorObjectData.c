// temp until i can find a better way to find "First" in a map that doesnt blow the software up
static int EditorObjectID;
class EditorObjectData: SerializableBase
{	
	[NonSerialized()]
	int m_Id;
	int GetID() { return m_Id; }
	
	string Type;
	string DisplayName;
	vector Position;
	vector Orientation;
	float Scale = 1;
	
	// Re-enable this once we get versioned serializing working :)
	//bool EditorOnly = false;
	
	[NonSerialized()]
	string Model;
	
	[NonSerialized()]
	vector BottomCenter;

	int Flags;
	
	[NonSerialized()]
	ModStructure Mod;
	
	[NonSerialized()]
	string Icon;
	
	[NonSerialized()]
	Object WorldObject;
	
	void EditorObjectData() 
	{
		EditorObjectID++;
		m_Id = EditorObjectID;
		
		//Mod = LoadModData(Type, Path); todo idk
		//Icon = EditorPlaceableItem.GetIcon(Mod);
	}
	
	static EditorObjectData Create(string type, vector transform[4], EditorObjectFlags flags = EditorObjectFlags.ALL)
	{	
		return Create(type, transform[3], Math3D.MatrixToAngles(transform), 1, flags);
	}
	
	static EditorObjectData Create(string type, vector position, vector orientation, float scale, EditorObjectFlags flags)
	{				
		if (GetGame().GetModelName(type) == "UNKNOWN_P3D_FILE") {
			//EditorLog.Warning(string.Format("EditorObjectData::Create %1 is not a valid Object Type!", type));
			//return null;
		}
		
		EditorObjectData data = new EditorObjectData();
		data.Type = type; 
		data.Model = GetGame().GetModelName(data.Type);
		data.Position = position; 
		data.Orientation = orientation;
		data.Scale = scale;
		data.Flags = flags;
		data.DisplayName = data.Type;
		//data.Mod = GetModFromObject(data.Type); todo refactor.

		//EditorLog.Debug(string.Format("EditorObjectData::Create ID: %1", data.m_Id));
				
		return data;
	}
	
	static EditorObjectData Create(notnull Object target, EditorObjectFlags flags = EditorObjectFlags.ALL)
	{
		// We do this because all 'baked' objects are ID'd to 3. cant store a bunch of 3's can we?
		// todo... actually we might be able to :)
		if (target.GetID() == 3) { 
			return null;
		}
		
		EditorObjectData data = new EditorObjectData();
		data.Type = target.GetType();
		data.Model = GetGame().GetModelName(data.Type);
		data.WorldObject = target;
		data.Position = data.WorldObject.GetPosition(); 
		data.Orientation = data.WorldObject.GetOrientation(); 
		data.Scale = data.WorldObject.GetScale();
		data.Flags = flags;
		data.DisplayName = data.Type;
		
		//EditorLog.Debug(string.Format("EditorObjectData::Create ID: %1", data.m_Id));
		
		return data;
	}
	
	override void Write(Serializer serializer, int version)
	{
		serializer.Write(Type);
		serializer.Write(DisplayName);
		serializer.Write(Position);
		serializer.Write(Orientation);
		serializer.Write(Scale);
		serializer.Write(Flags);
	}
	
	override bool Read(Serializer serializer, int version)
	{
		serializer.Read(Type);
		serializer.Read(DisplayName);
		serializer.Read(Position);
		serializer.Read(Orientation);
		serializer.Read(Scale);
		serializer.Read(Flags);
		
		return true;
	}
}
