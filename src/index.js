let logged_in = localStorage.getItem("logged");

let registerButton = document.createElement('button');
let loginButton = document.createElement('button');

function login(form) {

}

function register(form) {

}

function close(form) {
	document.body.removeChild(form);
	registerButton.disabled = false;
	loginButton.disabled = false;
}

function showLogin() {
	let form = document.createElement('form');
	form.className = "form";

	form.appendChild(document.createElement('span'));
	form.lastChild.className = "formTitle";
	form.lastChild.innerHTML = "Iniciar sesi&oacute;n";

	form.appendChild(document.createElement('input'));
	form.lastChild.setAttribute("name", "usr");
	form.lastChild.setAttribute("placeholder", "Nombre de usuario");
	form.lastChild.className = "logForm";

	form.appendChild(document.createElement('input'));
	form.lastChild.setAttribute("name", "pass");
	form.lastChild.setAttribute("placeholder", "Contrase\u00f1a");
	form.lastChild.setAttribute("type", "password");
	form.lastChild.className = "logForm";

	let closeButton = document.createElement('button');
	closeButton.innerHTML = "x";
	closeButton.className = "close";
	form.appendChild(closeButton);
	closeButton.onclick = (e) => {
		e.preventDefault();
		close(form);
	};

	let submit = document.createElement('button');
	submit.className = "submit";
	form.appendChild(submit);
	submit.addEventListener('click', (e) => {
		e.preventDefault();
		login(form);
	});

	document.body.appendChild(form);
}

function showRegister() {
	let form = document.createElement('form');
	form.className = "form";

	form.appendChild(document.createElement('span'));
	form.lastChild.className = "formTitle";
	form.lastChild.innerHTML = "Registrarse";

	form.appendChild(document.createElement('input'));
	form.lastChild.setAttribute("name", "usr");
	form.lastChild.setAttribute("placeholder", "Nombre de usuario");
	form.lastChild.className = "logForm";

	form.appendChild(document.createElement('input'));
	form.lastChild.setAttribute("name", "pass");
	form.lastChild.setAttribute("placeholder", "Contrase\u00f1a");
	form.lastChild.setAttribute("type", "password");
	form.lastChild.className = "logForm";

	form.appendChild(document.createElement('input'));
	form.lastChild.setAttribute("name", "rep_pass");
	form.lastChild.setAttribute("placeholder", "Repetir contrase\u00f1a");
	form.lastChild.setAttribute("type", "password");
	form.lastChild.className = "logForm";

	let closeButton = document.createElement('button');
	closeButton.innerHTML = "x";
	closeButton.className = "close";
	form.appendChild(closeButton);
	closeButton.onclick = (e) => {
		e.preventDefault();
		close(form);
	};

	let submit = document.createElement('button');
	submit.className = "submit";
	form.appendChild(submit);
	submit.addEventListener('click', (e) => {
		e.preventDefault();
		register(form);
	});

	document.body.appendChild(form);
}

if (!logged_in) {
	registerButton.setAttribute("id", "regButton");
	loginButton.setAttribute("id", "logButton");
	registerButton.innerHTML = "Registrar";
	loginButton.innerHTML = "Iniciar sesi&oacute;n";
	document.body.append(registerButton);
	document.body.append(loginButton);

	registerButton.addEventListener("click", (e) => {
		showRegister();
		registerButton.disabled = true;
		loginButton.disabled = true;
	});
	loginButton.addEventListener("click", (e) => {
		showLogin();
		e.target.setAttribute("disabled", "true");
		registerButton.disabled = true;
		loginButton.disabled = true;
	});
}