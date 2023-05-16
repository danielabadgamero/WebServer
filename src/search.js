let form = document.getElementById("searchForm");

form.onsubmit = (e) => {
    e.preventDefault();
    let http = new XMLHttpRequest();
    http.open("POST", "search.html", false);
    http.send("s=" + form.lastChild.nodeValue);
    console.log(http.responseText);
    let obj = JSON.parse(http.responseText);
    console.log(obj);
};