const char webpage[] PROGMEM = R"=====(
<!DOCTYPE html>
<html>  
<head>
  <title>ESP Web Server</title>
  <meta name="viewport" content="width=device-width, initial-scale=1">
  <link rel="icon" href="data:,">
  <link rel="stylesheet" type="text/css" href="style.css">
  <link rel="stylesheet" href="all.css" integrity="sha384-fnmOCqbTlWIlj8LyTjo7mOUStjsKC4pOpQbqyi7RrhN7udi9RwhKkMHpvLbHG9Sr" crossorigin="anonymous">
  <script src="three.min.js"></script>
</head>
<meta name="viewport" content="width=device-width, initial-scale=1">
<style type="text/css">
body {
  font-family: Arial, Helvetica, sans-serif;
}
#flip-box1{
  background-color: blue;
  width: 150px;
  height: 150px;
  border-radius: 15px;
  perspective: 1000px;
}
#flip-box2 {
  background-color: red;
  width: 150px;
  height: 150px;
  border-radius: 15px;
  perspective: 1000px;
}
#flip-box3 {
  background-color: green;
  width: 150px;
  height: 150px;
  border-radius: 15px;
  perspective: 1000px;
}
#led {
  background-color: gray;
  width: 40px;
  height: 40px;
  border-radius: 100px;
  perspective: 1000px;
}
.grid {
  display: grid;
  grid-template-columns: repeat(auto-fit, minmax(200px, 1fr));
  grid-gap: 10px;
}
html {
  font-family: Arial;
  display: inline-block;
  text-align: center;
}
p {
  font-size: 1.2rem;
}
body {
  margin: 0;
}
.topnav {
  overflow: hidden;
  background-color: #003366;
  color: #FFD43B;
  font-size: 1rem;
}
.content {
  padding: 20px;
}
.card {
  background-color: white;
  box-shadow: 2px 2px 12px 1px rgba(140,140,140,.5);
}
.card-title {
  color:#003366;
  font-weight: bold;
}
.cards {
  max-width: 800px;
  margin: 0 auto;
  display: grid; grid-gap: 2rem;
  grid-template-columns: repeat(auto-fit, minmax(200px, 1fr));
}
.reading {
  font-size: 1.2rem;
}
.cube-content{
  width: 100%;
  background-color: white;
  height: 300px; margin: auto;
  padding-top:2%;
}
#reset{
  border: none;
  color: #FEFCFB;
  background-color: #003366;
  padding: 10px;
  text-align: center;
  display: inline-block;
  font-size: 14px; width: 150px;
  border-radius: 4px;
}
#resetX, #resetY, #resetZ{
  border: none;
  color: #FEFCFB;
  background-color: #003366;
  padding-top: 10px;
  padding-bottom: 10px;
  text-align: center;
  display: inline-block;
  font-size: 14px;
  width: 20px;
  border-radius: 4px;
}
 dl {
      margin: 30px 0;
    }
    .test-cubelet-container {
      margin: 200px auto 0;
      overflow: visible;
      position: relative;
      width: 0;
    }
    .test-cubelet-container img {
      left: -22px;
      position: absolute;
      top: -22px;
    }
* {
  box-sizing: border-box;
}

#column {
  float: left;
  width: 33.33%;
  padding: 5px;
}

/* Clearfix (clear floats) */
#row::after {
  content: "";
  clear: both;
  display: table;
}

/* Responsive layout - makes the three columns stack on top of each other instead of next to each other */
@media screen and (max-width: 500px) {
  .column {
    width: 100%;
  }
}
</style>
<body style="background-color: white ">
<div class="topnav">
    <h1 style=" text-align:center;"><i class="far fa-compass"></i> Badminton Hand Movement Analysis Page<i class="far fa-compass"></i></h1>
  </div>
  <center>
  <div class="content">
    <div class="cards">
      <div class="card">
        <p class="card-title">GYROSCOPE</p>
        <p><span class="reading">X: <span id="adc_val_1"></span></span></p>
        <p><span class="reading">Y: <span id="adc_val_2"></span></span></p>
        <p><span class="reading">Z: <span id="adc_val_3"></span></span></p>
        <div id="led" style="float:center;"></div><p id="adc_val_4">Shooting is </p>
        <br>
      </div>
      
    </div>
    </div>
    </center>
  <center>
  <div class="grid">
  <div id="flip-box1" style="margin-inline: 10px; margin:0 auto;"><p style="font-size: 30px;">^_^</p></div>
  <div id="flip-box2" style="margin-inline: 10px; margin:0 auto;"><p style="font-size: 30px;">^_^</p></div>
  <div id="flip-box3" style="margin-inline: 10px; margin:0 auto;"><p style="font-size: 30px;">^_^</p></div>
  </div>
  </center>
<script>

setInterval(function() {getData1();}, 10); 
setInterval(function() {getData2();}, 10); 
setInterval(function() {getData3();}, 10); 
setInterval(function() {getData4();}, 10); 
setInterval(function() {getData5();}, 10); 


function getData1() {
  var xhttp = new XMLHttpRequest();
  var x;
  xhttp.onreadystatechange = function() {
    if (this.readyState == 4 && this.status == 200) {
      x1 = this.responseText;
      document.getElementById("adc_val_1").innerHTML = x1;
      document.getElementById("flip-box1").style.transform = "rotateZ("+(x1*-1)+"deg)"; 
    }
  };
  xhttp.open("GET", "adcread1", true);
  xhttp.send();
}

function getData2() {
  var xhttp = new XMLHttpRequest();
  xhttp.onreadystatechange = function() {
    if (this.readyState == 4 && this.status == 200) {
      x2 = this.responseText;
      document.getElementById("adc_val_2").innerHTML = x2;
      document.getElementById("flip-box2").style.transform = "rotateX("+x2+"deg)"; 
    }
  };
  xhttp.open("GET", "adcread2", true);
  xhttp.send();
}

function getData3() {
  var xhttp = new XMLHttpRequest();
  xhttp.onreadystatechange = function() {
    if (this.readyState == 4 && this.status == 200) {
      x3 = this.responseText;
      document.getElementById("adc_val_3").innerHTML = x3;
      document.getElementById("flip-box3").style.transform = "rotateY("+(x3*-1)+"deg)"; 
    }
  };
  xhttp.open("GET", "adcread3", true);
  xhttp.send();
}

function getData4() {
  var xhttp = new XMLHttpRequest();
  xhttp.onreadystatechange = function() {
    if (this.readyState == 4 && this.status == 200) {
      x4 = this.responseText;
      if(x4 == "1")
      {
        document.getElementById("led").style.backgroundColor = "green"; 
        document.getElementById("adc_val_4").innerHTML = "Shooting is Correct";
        document.getElementById("adc_val_4").style.color = "green";
      }
      else 
      {
        document.getElementById("led").style.backgroundColor = "red"; 
        document.getElementById("adc_val_4").innerHTML = "Shooting is Wrong";
        document.getElementById("adc_val_4").style.color = "red";
      }
      
    }
  };
  xhttp.open("GET", "adcread4", true);
  xhttp.send();
}
</script>
</body>
</html>
)=====";
