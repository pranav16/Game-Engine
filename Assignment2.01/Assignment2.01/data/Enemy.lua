Player = 
{
	name = "Player2",
	initial_position = { 100.0, 0.0, 0.0 },
	
	SpriteInfo = { 
			SpritePath = "data\\blade2.dds"
	},

	PhysicsInfo = 
	{
		mass = 10.0,
		coefficientOfDrag = 0.001
	},
	velocity = { 0.0, 0.0, 0.0 },
	Center = { 0.0, 30.0, 0.0 },
	BoxExtents = { 35.0, 30.0, 0.0 },
	Roation = 90,
	Controller = "PlayerController",
	Serializable = 1,
	Trigger = 2
}
