extends Entity


# Declare member variables here. Examples:
# var a = 2
# var b = "text"

export (NodePath) var newBall = ""
var speed = 60

# Called when the node enters the scene tree for the first time.
func _ready():
	setShape("Rectangle")
	setPosition(Vector2(1000,284))
	setScale(Vector2(0.1,1))
	path("bestboi.jpg")
	pass # Replace with function body.


# Called every frame. 'delta' is the elapsed time since the previous frame.
func _process(delta):
	
	# interpolate to ball's y position
	var targetLocation = get_node(newBall).getPosition().y
	
	if (targetLocation - getPosition().y > 0):
		setPosition(Vector2(getPosition().x,getPosition().y + (speed * delta)))
	else:
		setPosition(Vector2(getPosition().x,getPosition().y - (speed * delta)))
	pass
