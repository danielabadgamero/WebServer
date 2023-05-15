let camera = {
	x: 0,
	y: 0,
	z: 0
}

let mouse = {
	x: 0,
	y: 0
}

let mouseDown = false;
let map = document.getElementById("map");

function updateTiles() {
	map.innerHTML = "";
	for (let startY = 0; startY != Math.trunc(window.outerHeight / 256) + 2; startY++) {
		for (let startX = 0; startX != Math.trunc(window.outerWidth / 256) + 2; startX++) {
			let exists = false;
			let max = Math.trunc(Math.pow(2, camera.z));
			let img = document.createElement("img");
			img.src = `/tiles/${camera.z}/${Math.trunc(startX + camera.x / 256) % max}/${Math.trunc(startY + camera.y / 256) % max}.png`
			map.childNodes.forEach(tile => {
				if (img.src == tile.src) {
					exists = true;
					return;
				}
			});
			if (!exists) {
				img.setAttribute("class", "tile");
				img.draggable = false;
				img.style.left = `${startX * 256 + camera.x}px`;
				img.style.top = `${startY * 256 + camera.y}px`;
				map.appendChild(img);
			}
		}
	}
}

updateTiles();

window.addEventListener("mousemove", e => {
	if (mouseDown) {
		camera.x += e.movementX;
		camera.y += e.movementY;
		updateTiles();
		map.childNodes.forEach(tile => {
			tile.style.left = `${parseInt(tile.style.left) + e.movementX}px`;
			tile.style.top = `${parseInt(tile.style.top) + e.movementY}px`;
		});
	}
});

window.addEventListener("mousedown", e => {
	mouseDown = true;
})

window.addEventListener("mouseup", e => {
	mouseDown = false;
})

window.addEventListener("wheel", e => {
	if (e.deltaY > 0 && camera.z > 0) {
		camera.z--;
		camera.x += e.clientX;
		camera.y += e.clientY;
		camera.x /= 2;
		camera.y /= 2;
	}
	else if (e.deltaY < 0 && camera.z < 19) {
		camera.z++;
		camera.x *= 2;
		camera.y *= 2;
		camera.x -= e.clientX;
		camera.y -= e.clientY;
	}
	updateTiles();
})