let camera = {
	x: 0,
	y: 0,
	z: 3
}

let mouse = {
	x: 0,
	y: 0
}

let mouseDown = false;
let map = document.getElementById("map");

function mod(n, m) {
	return ((n % m) + m) % m;
}

let tiles = [[[]]];

function updateTiles() {
	map.innerHTML = "";
	let max = Math.trunc(Math.pow(2, camera.z));
	for (let startY = -1; startY != Math.trunc(window.outerHeight / 256) + 3; startY++) {
		for (let startX = -1; startX != Math.trunc(window.outerWidth / 256) + 3; startX++) {
			let exists = false;
			let img = document.createElement("img");
			img.src = `/tiles/${camera.z}/${mod(Math.trunc(startX - camera.x / 256), max)}/${mod(Math.trunc(startY - camera.y / 256), max)}.png`
			map.childNodes.forEach(tile => {
				if (img.src == tile.src) {
					exists = true;
					return;
				}
			});
			if (!exists) {
				img.setAttribute("class", "tile");
				img.draggable = false;
				img.style.left = `${startX * 256 + (camera.x % 256) + 128}px`;
				img.style.top = `${startY * 256 + (camera.y % 256) + 256}px`;
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