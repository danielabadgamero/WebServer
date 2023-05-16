let form = document.getElementById("searchForm");
let frame = document.getElementById("cards");
let coords;

function deg2rad(deg) {
	return deg * (Math.PI / 180)
}

// https://stackoverflow.com/questions/18883601/function-to-calculate-distance-between-two-coordinates
function getDistance(lat1, lon1, lat2, lon2) {
	let R = 6371; // Radius of the earth in km
	let dLat = deg2rad(lat2 - lat1);  // deg2rad below
	let dLon = deg2rad(lon2 - lon1);
	let a =
		Math.sin(dLat / 2) * Math.sin(dLat / 2) +
		Math.cos(deg2rad(lat1)) * Math.cos(deg2rad(lat2)) *
		Math.sin(dLon / 2) * Math.sin(dLon / 2);
	let c = 2 * Math.atan2(Math.sqrt(a), Math.sqrt(1 - a));
	let d = R * c; // Distance in km
	return d;
}

function addActivity() {

}

form.onsubmit = (e) => {
	frame.innerHTML = "";
	navigator.geolocation.getCurrentPosition((pos) => { coords = pos.coords }, () => { coords = { lat: 39.482087872995955, lon: -0.36355921220606224 } });
	e.preventDefault();
	let http = new XMLHttpRequest();
	http.open("POST", "search.html", false);
	http.send("s=" + form.children[0].value);
	let obj = JSON.parse(http.responseText);

	obj.forEach((act) => {
		let card = document.createElement('div');
		let title = document.createElement('span');
		let people = document.createElement('span');
		let distance = document.createElement('span');
		let time = document.createElement('span');
		let button = document.createElement('button');
		title.className = "title";
		people.className = "content";
		distance.className = "content";
		time.className = "content";
		button.className = "joinButton";
		button.innerHTML = "Unirse";
		button.onclick = addActivity;
		title.innerHTML = act.name.toUpperCase();
		people.innerHTML = act.people[0] + " y " + (act.people.length - 1) + " m&aacute;s";
		distance.innerHTML = "A " + Math.round(getDistance(coords.lat, coords.lon, act.pos.lat, act.pos.lon) * 10) / 10 + "km";
		time.innerHTML = act.time.h + ":" + act.time.m;
		card.className = "card";
		card.append(title);
		card.append(people);
		card.append(distance);
		card.append(time);
		frame.append(card);
	})
};