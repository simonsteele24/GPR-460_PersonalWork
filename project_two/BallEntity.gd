extends Entity


# Declare member variables here. Examples:
var velocity = Vector2(300,300)
var screen_size


# Called when the node enters the scene tree for the first time.
func _ready():
	screen_size = get_viewport_rect().size
	path("Circle.png")
	setScale(Vector2(0.02,0.02))
	setPosition(Vector2(518,267))
	pass # Replace with function body.


# Called every frame. 'delta' is the elapsed time since the previous frame.
func _process(delta):
	setPosition(getPosition() + (velocity * delta))
	if (getPosition().x < 0 or getPosition().x > screen_size.x):
		setPosition(Vector2(screen_size.x / 2, screen_size.y / 2))
		velocity.x = 300
	if (getPosition().y < 0 or getPosition().y > screen_size.y):
		velocity.y = -velocity.y 
	
	if checkForOverlap():
		var location = position.y - get_node(Paddle).getPosition().y
		
		if (abs(location) > 100):
			if (location > 0):
				velocity.y = 20
				pass
			else:
				velocity.y = -20
				pass
		else:
			velocity.y = 0
	
	update()
	pass
