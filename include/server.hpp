#include <Arduino.h>
const char index_html[] PROGMEM = R"rawliteral(
<!DOCTYPE HTML><html>
<head lang="es">
  <meta charset="UTF-8" />
  <title>Ctral Coatza HGO</title>
  <meta name="viewport" content="width=device-width, initial-scale=1">
  <link rel="icon" href="data:,">
  <style>
    html {font-family: Arial; display: inline-block; text-align: center;}
    p {  font-size: 1.2rem;}
    body {  margin: 0;}
    .topnav { overflow: hidden; background-color: #2f4468; color: white; font-size: 1.7rem; }
    .content { padding: 20px; }
    .card { background-color: white; box-shadow: 2px 2px 12px 1px rgba(140,140,140,.5); }
    .cards { max-width: 600px; margin: 0 auto; display: grid; grid-gap: 2rem; grid-template-columns: repeat(auto-fit, minmax(250px, 1fr)); }
    .reading { font-size: 2.8rem; }
    .packet { color: #bebebe; }
    .card.temperature { color: #fd7e14; }
    .card.humidity { color: #1b78e2; }
    .tmax { color: #fd1414; }
    .tmin { color: #1378eb; }
  </style>
</head>
<body>
  <div class="topnav">
    <h3>CENTRAL HGO (Petrolera)</h3>
  </div>
  <div class="content">
    <div class="cards">
      <div class="card humidity" >
        <span class="tmin">Min. </span><span class="tmin" id="tmin1"></span><span class="tmin">° C</span> - <span class="tmax">Max. </span><span class="tmax" id="tmax1"></span><span class="tmax">° C</span>
        <h4 ><i class="fas fa-thermometer-half"></i> CTI 4° piso - TEMPERATURA</h4><p><span class="reading">
          <span id="t1"></span> &deg;C</span>
        </p>
        <h4><i class="fas fa-tint"></i> HUMEDAD</h4><p><span class="reading">
          <span id="h1"></span> &percnt;</span></p><p class="packet">RSSI dBm: <span id="rh1"></span></p><code>Ultima lectura hace: </code><span id="cont1" ></span><code> Segundos</code>
      </div>
      <div class="card humidity" >
        <span class="tmin">Min. </span><span class="tmin" id="tmin2"></span><span class="tmin">° C</span> - <span class="tmax">Max. </span><span class="tmax" id="tmax2"></span><span class="tmax">° C</span>
        <h4 ><i class="fas fa-thermometer-half"></i> PMCT 4° piso - TEMPERATURA</h4><p><span class="reading">
          <span id="t2"></span> &deg;C</span>
        </p>
        <h4><i class="fas fa-tint"></i> HUMEDAD</h4><p><span class="reading">
          <span id="h2"></span> &percnt;</span></p><p class="packet">RSSI señal dBm: <span id="rh2"></span></p><code>Ultima lectura hace: </code><span id="cont2"></span><code> Segundos</code>
      </div>
      <div class="card humidity" >
        <span class="tmin">Min. </span><span class="tmin" id="tmin3"></span><span class="tmin">° C</span> - <span class="tmax">Max. </span><span class="tmax" id="tmax3"></span><span class="tmax">° C</span>
        <h4><i class="fas fa-thermometer-half"></i> PTTI2 2° piso - TEMPERATURA</h4><p><span class="reading">
          <span id="t3"></span> &deg;C</span>
        </p>
        <h4><i class="fas fa-tint"></i> HUMEDAD</h4><p><span class="reading">
          <span id="h3"></span> &percnt;</span></p><p class="packet">RSSI señal dBm: <span id="rh3"></span></p><code>Ultima lectura hace: </code><span id="cont3"></span><code> Segundos</code>
      </div>
      <div class="card humidity" >
        <span class="tmin">Min. </span><span class="tmin" id="tmin4"></span><span class="tmin">° C</span> - <span class="tmax">Max. </span><span class="tmax" id="tmax4"></span><span class="tmax">° C</span>
        <h4><i class="fas fa-thermometer-half"></i> PTTI 1er piso - TEMPERATURA</h4><p><span class="reading">
          <span id="t4"></span> &deg;C</span>
        </p>
        <h4><i class="fas fa-tint"></i> HUMEDAD</h4><p><span class="reading">
          <span id="h4"></span> &percnt;</span></p><p class="packet">RSSI señal dBm: <span id="rh4"></span></p><code>Ultima lectura hace: </code><span id="cont4"></span><code> Segundos</code>
      </div>
    </div>
  </div>
<script>
  var tmp1,tmp2,tmp3,tmp4;
if (!!window.EventSource) {
 var source = new EventSource('/events');
 
 source.addEventListener('open', function(e) {
  console.log("Events Connected");
 }, false);
 source.addEventListener('error', function(e) {
  if (e.target.readyState != EventSource.OPEN) {
    console.log("Events Disconnected");
  }
 }, false);
 
 source.addEventListener('message', function(e) {
  console.log("message", e.data);
 }, false);
 
 source.addEventListener('new_readings', function(e) {
  //console.log("new_readings", e.data);
  var obj = JSON.parse(e.data);
  
  console.log("Nuevas_Lecturas: ",obj.nameNodo);
  console.log("Metodo: ",obj.modoSend);
  document.getElementById("t"+obj.id).innerHTML = obj.temperature.toFixed(1); //un digito
  document.getElementById("h"+obj.id).innerHTML = obj.humidity.toFixed(1); //un digito
  //document.getElementById("rt"+obj.id).innerHTML = obj.readingId;
  document.getElementById("rh"+obj.id).innerHTML = obj.readingId.toFixed(1);
  document.getElementById("tmin"+obj.id).innerHTML = obj.min.toFixed(1);
  document.getElementById("tmax"+obj.id).innerHTML = obj.max.toFixed(1);
  document.getElementById("cont"+obj.id).innerHTML = obj.tmp;
  
 }, false);
}  
setInterval(function aumentar(){ // se crean la funcion y se agrega al evento onclick en en la etiqueta button con id aumentar
  //se obtiene el valor del input, y se incrementa en 1 el valor que tenga.
    tmp1=document.getElementById("cont1").innerHTML; 
    tmp1++;
    tmp2=document.getElementById("cont2").innerHTML;
    tmp2++;
    tmp3=document.getElementById("cont3").innerHTML;
    tmp3++;
    tmp4=document.getElementById("cont4").innerHTML;
    tmp4++;
    document.getElementById("cont1").innerHTML = tmp1;
    document.getElementById("cont2").innerHTML = tmp2;
    document.getElementById("cont3").innerHTML = tmp3;
    document.getElementById("cont4").innerHTML = tmp4;
  },1000);
  
</script>
</body>
</html>)rawliteral";
