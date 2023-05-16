let form = document.getElementById("searchForm");
let frame = document.getElementById("cards");
let coords;


// https://stackoverflow.com/questions/18883601/function-to-calculate-distance-between-two-coordinates
function getDistanceFromLatLonInKm(lat1, lon1, lat2, lon2) {
	var R = 6371; // Radius of the earth in km
	var dLat = deg2rad(lat2 - lat1);  // deg2rad below
	var dLon = deg2rad(lon2 - lon1);
	var a =
		Math.sin(dLat / 2) * Math.sin(dLat / 2) +
		Math.cos(deg2rad(lat1)) * Math.cos(deg2rad(lat2)) *
		Math.sin(dLon / 2) * Math.sin(dLon / 2)
		;
	var c = 2 * Math.atan2(Math.sqrt(a), Math.sqrt(1 - a));
	var d = R * c; // Distance in km
	return d;
}

function deg2rad(deg) {
	return deg * (Math.PI / 180)
}

form.onsubmit = (e) => {
	frame.innerHTML = "";
	navigator.geolocation.getCurrentPosition((pos) => { coords = pos.coords });
	e.preventDefault();
	let http = new XMLHttpRequest();
	http.open("POST", "search.html", false);
	http.send("s=" + form.children[0].value);
	let obj = JSON.parse(http.responseText);

	obj.forEach((act) => {
		let card = document.createElement('div');
		let title = document.createElement('span');
		title.className = "title";
		card.className = "card";
		title.innerHTML = act.name.toUpperCase();
		card.append(title);
		frame.append(card);
	})
};