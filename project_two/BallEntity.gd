extends Entity


# Declare member variables here. Examples:
var velocity = Vector2(300,300)
var screen_size


# Called when the node enters the scene tree for the first time.
func _ready():
	screen_size = get_viewport_rect().size
	setShape("Circle")
	path("Circle.png")
	setScale(Vector2(0.02,0.02))
	setPosition(Vector2(518,267))
	pass # Replace with function body.


# Called every frame. 'delta' is the elapsed time since the previous frame.
func _process(delta):
	
	# Move based on velocity
	setPosition(getPosition() + (velocity * delta))
	
	#Move ball to center of screen if out
	if (getPosition().x < 0 or getPosition().x > screen_size.x):
		setPosition(Vector2(screen_size.x / 2, screen_size.y / 2))
		velocity.x = 300
	
	# Bounce ball if on horizontal edges
	if (getPosition().y < 0 or getPosition().y > screen_size.y):
		velocity.y = -velocity.y 
	
	if checkForOverlap():
		velocity.x *= -1
	
	update()
	pass
