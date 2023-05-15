let camera = {
	x: 0,
	y: 0,
	x: 0
}

let mouse = {
	x: 0,
	y: 0
}

let mouseDown = false;

window.addEventListener("mousemove", e => {
	if (mouseDown) {
		camera.x += e.movementX;
		camera.y += e.movementY;
	}
	console.log(camera.x + " " + camera.y);
});

window.addEventListener("mousedown", e => {
	mouseDown = true;
})

window.addEventListener("mouseup", e => {
	mouseDown = false;
})