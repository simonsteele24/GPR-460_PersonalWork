extends Area2D

# Declare member variables here. Examples:
# var a = 2
# var b = "text"
var velocity = Vector2(300,300)
var screen_size

export (NodePath) var Paddle = ""
export (NodePath) var EnemyPaddle = ""

# Called when the node enters the scene tree for the first time.
func _ready():
	screen_size = get_viewport_rect().size
	pass # Replace with function body.


# Called every frame. 'delta' is the elapsed time since the previous frame.
func _process(delta):
	position += velocity * delta
	if (position.x < 0 or position.x > screen_size.x):
		position = Vector2(screen_size.x / 2, screen_size.y / 2)
		velocity.x = 300
	if (position.y < 0 or position.y > screen_size.y):
		velocity.y = -velocity.y 
	pass
	
	


func _on_Ball_area_entered(area):
	velocity = -velocity
	if (area.overlaps_area(get_node(Paddle))):
		var location = position.y - get_node(Paddle).position.y
		
		if (abs(location) > 100):
			if (location > 0):
				velocity.y = 20
				pass
			else:
				velocity.y = -20
				pass
		else:
			velocity.y = 0
	if (area.overlaps_area(get_node(EnemyPaddle))):
		pass
	pass # Replace with function body.
