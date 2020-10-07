extends Entity


export var speed = 400  # How fast the player will move (pixels/sec).
var screen_size  # Size of the game window.


# Called when the node enters the scene tree for the first time.
func _ready():
	screen_size = get_viewport_rect().size
	setShape("Rectangle")
	setPosition(Vector2(16,284))
	setScale(Vector2(0.1,1))
	path("bestboi.jpg")
	pass # Replace with function body.


# Called every frame. 'delta' is the elapsed time since the previous frame.
func _process(delta):
	var velocity = Vector2()  # The player's movement vector.
	if Input.is_action_pressed("ui_down"):
		velocity.y += 1
	if Input.is_action_pressed("ui_up"):
		velocity.y -= 1
	if velocity.length() > 0:
		velocity = velocity.normalized() * speed
	setPosition(getPosition() + (velocity * delta))
	setPosition(Vector2(getPosition().x,clamp(getPosition().y, 0, screen_size.y)))
	update()
	pass
