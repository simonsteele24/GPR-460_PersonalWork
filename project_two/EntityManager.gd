extends EntityManager


# Declare member variables here. Examples:
# var a = 2
# var b = "text"


# Called when the node enters the scene tree for the first time.
func _ready():
	var entity = Entity.new()
	entity.setID(generateID())
	setPosition(entity.getID(),Vector2(10,10))
	print(getPosition(entity.getID()))
	pass # Replace with function body.


# Called every frame. 'delta' is the elapsed time since the previous frame.
#func _process(delta):
#	pass
