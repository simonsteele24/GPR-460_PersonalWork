extends Area2D


# Declare member variables here. Examples:
# var a = 2
# var b = "text"

export (NodePath) var newBall = ""
var speed = 60

# Called when the node enters the scene tree for the first time.
func _ready():
	pass # Replace with function body.


# Called every frame. 'delta' is the elapsed time since the previous frame.
func _process(delta):
	var targetLocation = get_node(newBall).position.y
	
	if (targetLocation - position.y > 0):
		position.y += speed * delta
	else:
		position.y -= speed * delta
