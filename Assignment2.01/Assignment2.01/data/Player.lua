
Player = 
{
	name = "Hero",
	initial_position = { -200.0, 0.0, 0.0 },
	
	SpriteInfo = { 
			SpritePath = "data\\blade1.dds"
	},

	PhysicsInfo = 
	{
		mass = 10.0,
		coefficientOfDrag = 0.001
	},
	velocity = { 100.0, 0.0, 0.0 },
	Center = { 0.0, 30.0, 0.0 },
	BoxExtents = { 35.0, 30.0, 0.0 },
	Roation = 90,
	Controller = "Player2Controller",
	Serializable = 1,
	Trigger = 2
}
