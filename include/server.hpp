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
    body {  
      margin: 0;
      background-color: #d7fafc;
    }
    .topnav { 
      overflow: hidden; background-color: #2f4468; 
      color: white; 
      font-size: 1.7rem; 
      background-image:
            -webkit-gradient(linear, left top, left bottom,
            from(rgba(255,255,255,.4)),
            to(rgba(255,255,255,.05)) ),
            -webkit-gradient(linear, left top, left bottom,
            from(transparent),
            to(rgba(0,0,64,.1)) );
    }
    .content { padding: 20px; }
    .card { background-color: white; box-shadow: 2px 2px 12px 1px rgba(126, 125, 125, 0.5); }
    .cards { max-width: 600px; margin: 0 auto; display: grid; grid-gap: 2rem; grid-template-columns: repeat(auto-fit, minmax(250px, 1fr)); }
    .reading { font-size: 2.8rem; }
    .packet { color: #bebebe; }
    .card.temperature { color: #fd7e14; }
    .card.humidity { color: #1b78e2; }
    .tmax { color: #fd1414; }
    .tmin { color: #1378eb; }
    .group-wrapper table {
      background-color: #fff;
      -webkit-border-radius: 10px;
      -moz-border-radius: 10px;
      -khtml-border-radius: 10px;
      border-radius: 10px;
      font-size: 17px;
      line-height: 20px;
      margin: 9px 0 20px;
      border: solid 1px #a9abae;
      padding: 11px 3px 12px 3px;
      margin-left:auto;
      margin-right:auto;
      /*-moz-transform :scale(1); 
      -moz-transform-origin: 0 0;*/
      }
    .red-circle {
      display: block;
      height: 23px;
      width: 23px;
      background-color: rgba(254, 0, 0);
      -moz-border-radius: 12px;
      -webkit-border-radius: 12px;
      -khtml-border-radius: 12px;
      border-radius: 12px;
      margin: auto; 
      background-image: -webkit-gradient(linear, 0% 0%, 0% 90%, from(rgba(184, 46, 0, 0.8)), to(rgba(255, 148, 112, .9)));
      /*@border: 2px solid #ccc;*/
      -webkit-box-shadow: rgba(11, 140, 27, 0.5) 0px 10px 16px;
      -moz-box-shadow: rgba(11, 140, 27, 0.5) 0px 10px 16px; 
      box-shadow: rgba(11, 140, 27, 0.5) 0px 10px 16px; 
      }
    .blue-circle {
      display: block;
      height: 23px;
      width: 23px;
      background-color: #0ad;
      -moz-border-radius: 11px;
      -webkit-border-radius: 11px;
      -khtml-border-radius: 11px;
      border-radius: 11px;
      margin: auto;
      -webkit-box-shadow: rgba(11, 140, 27, 0.5) 0px 10px 16px;
      -moz-box-shadow: rgba(11, 140, 27, 0.5) 0px 10px 16px; /* FF 3.5+ */ 
      box-shadow: rgba(11, 140, 27, 0.5) 0px 10px 16px; /* FF 3.5+ */
      }
    .glare {
      position: relative;
      top: 1;
      left: 5px;
      -webkit-border-radius: 10px;
      -moz-border-radius: 10px;
      -khtml-border-radius: 10px;
      border-radius: 10px;
      height: 1px;
      width: 13px;
      padding: 5px 0; 
      background-color: rgba(200, 200, 200, 0.25);
      background-image: -webkit-gradient(linear, 0% 0%, 0% 95%, from(rgba(255, 255, 255, 0.7)), to(rgba(255, 255, 255, 0)));
      }
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
          <table border="0" align="center">
            <tr id="a11" hidden><td>1.- </td><td id="alr11"></td><td><div class='red-circle'><div class='glare'></div></div></td></tr>
            <tr id="a21" hidden><td>2.- </td><td id="alr21"></td><td><div class='red-circle'><div class='glare'></div></div></td></tr>
            <tr id="a31" hidden><td>3.- </td><td id="alr31"></td><td><div class='red-circle'><div class='glare'></div></div></td></tr>
            <tr id="a41" hidden><td>4.- </td><td id="alr41"></td><td><div class='red-circle'><div class='glare'></div></div></td></tr>
            <tr id="a51" hidden><td>5.- </td><td id="alr51"></td><td><div class='red-circle'><div class='glare'></div></div></td></tr>
            <tr id="a61" hidden><td>6.- </td><td id="alr61"></td><td><div class='red-circle'><div class='glare'></div></div></td></tr>
            <tr id="a71" hidden><td>7.- </td><td id="alr71"></td><td><div class='red-circle'><div class='glare'></div></div></td></tr>
            <tr id="a81" hidden><td>8.- </td><td id="alr81"></td><td><div class='red-circle'><div class='glare'></div></div></td></tr>
          </table>
      </div>
      <div class="card humidity" >
        <span class="tmin">Min. </span><span class="tmin" id="tmin2"></span><span class="tmin">° C</span> - <span class="tmax">Max. </span><span class="tmax" id="tmax2"></span><span class="tmax">° C</span>
        <h4 ><i class="fas fa-thermometer-half"></i> PMCT 4° piso - TEMPERATURA</h4><p><span class="reading">
          <span id="t2"></span> &deg;C</span>
        </p>
        <h4><i class="fas fa-tint"></i> HUMEDAD</h4><p><span class="reading">
          <span id="h2"></span> &percnt;</span></p><p class="packet">RSSI señal dBm: <span id="rh2"></span></p><code>Ultima lectura hace: </code><span id="cont2"></span><code> Segundos</code>
          <table border="0" align="center">
            <tr id="a12" hidden><td>1.- </td><td id="alr12"></td><td><div class='red-circle'><div class='glare'></div></div></td></tr>
            <tr id="a22" hidden><td>2.- </td><td id="alr22"></td><td><div class='red-circle'><div class='glare'></div></div></td></tr>
            <tr id="a32" hidden><td>3.- </td><td id="alr32"></td><td><div class='red-circle'><div class='glare'></div></div></td></tr>
            <tr id="a42" hidden><td>4.- </td><td id="alr42"></td><td><div class='red-circle'><div class='glare'></div></div></td></tr>
            <tr id="a52" hidden><td>5.- </td><td id="alr52"></td><td><div class='red-circle'><div class='glare'></div></div></td></tr>
            <tr id="a62" hidden><td>6.- </td><td id="alr62"></td><td><div class='red-circle'><div class='glare'></div></div></td></tr>
            <tr id="a72" hidden><td>7.- </td><td id="alr72"></td><td><div class='red-circle'><div class='glare'></div></div></td></tr>
            <tr id="a82" hidden><td>8.- </td><td id="alr82"></td><td><div class='red-circle'><div class='glare'></div></div></td></tr>
          </table>
        </div>
      <div class="card humidity" >
        <span class="tmin">Min. </span><span class="tmin" id="tmin3"></span><span class="tmin">° C</span> - <span class="tmax">Max. </span><span class="tmax" id="tmax3"></span><span class="tmax">° C</span>
        <h4><i class="fas fa-thermometer-half"></i> PTTI2 2° piso - TEMPERATURA</h4><p><span class="reading">
          <span id="t3"></span> &deg;C</span>
        </p>
        <h4><i class="fas fa-tint"></i> HUMEDAD</h4><p><span class="reading">
          <span id="h3"></span> &percnt;</span></p><p class="packet">RSSI señal dBm: <span id="rh3"></span></p><code>Ultima lectura hace: </code><span id="cont3"></span><code> Segundos</code>
          <table border="0" align="center">
            <tr id="a13" hidden><td>1.- </td><td id="alr13"></td><td><div class='red-circle'><div class='glare'></div></div></td></tr>
            <tr id="a23" hidden><td>2.- </td><td id="alr23"></td><td><div class='red-circle'><div class='glare'></div></div></td></tr>
            <tr id="a33" hidden><td>3.- </td><td id="alr33"></td><td><div class='red-circle'><div class='glare'></div></div></td></tr>
            <tr id="a43" hidden><td>4.- </td><td id="alr43"></td><td><div class='red-circle'><div class='glare'></div></div></td></tr>
            <tr id="a53" hidden><td>5.- </td><td id="alr53"></td><td><div class='red-circle'><div class='glare'></div></div></td></tr>
            <tr id="a63" hidden><td>6.- </td><td id="alr63"></td><td><div class='red-circle'><div class='glare'></div></div></td></tr>
            <tr id="a73" hidden><td>7.- </td><td id="alr73"></td><td><div class='red-circle'><div class='glare'></div></div></td></tr>
            <tr id="a83" hidden><td>8.- </td><td id="alr83"></td><td><div class='red-circle'><div class='glare'></div></div></td></tr>
          </table>
      </div>
      <div class="card humidity" >
        <span class="tmin">Min. </span><span class="tmin" id="tmin4"></span><span class="tmin">° C</span> - <span class="tmax">Max. </span><span class="tmax" id="tmax4"></span><span class="tmax">° C</span>
        <h4><i class="fas fa-thermometer-half"></i> PTTI 1er piso - TEMPERATURA</h4><p><span class="reading">
          <span id="t4"></span> &deg;C</span>
        </p>
        <h4><i class="fas fa-tint"></i> HUMEDAD</h4><p><span class="reading">
          <span id="h4"></span> &percnt;</span></p><p class="packet">RSSI señal dBm: <span id="rh4"></span></p><code>Ultima lectura hace: </code><span id="cont4"></span><code> Segundos</code>
          <table border="0" align="center">
            <tr id="a14" style="display: none"><td>1.- </td><td id="alr14"></td><td><div class='red-circle'><div class='glare'></div></div></td></tr>
            <tr id="a24" style="display: none"><td>2.- </td><td id="alr24"></td><td><div class='red-circle'><div class='glare'></div></div></td></tr>
            <tr id="a34" style="display: none"><td>3.- </td><td id="alr34"></td><td><div class='red-circle'><div class='glare'></div></div></td></tr>
            <tr id="a44" style="display: none"><td>4.- </td><td id="alr44"></td><td><div class='red-circle'><div class='glare'></div></div></td></tr>
            <tr id="a54" style="display: none"><td>5.- </td><td id="alr54"></td><td><div class='red-circle'><div class='glare'></div></div></td></tr>
            <tr id="a64" style="display: none"><td>6.- </td><td id="alr64"></td><td><div class='red-circle'><div class='glare'></div></div></td></tr>
            <tr id="a74" style="display: none"><td>7.- </td><td id="alr74"></td><td><div class='red-circle'><div class='glare'></div></div></td></tr>
            <tr id="a84" style="display: none"><td>8.- </td><td id="alr84"></td><td><div class='red-circle'><div class='glare'></div></div></td></tr>
          </table>
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
  
  
  //las siguientes lineas son para darle mas funcionalidad a los dispositivos
  // las siguientes linea son para saber el nombre de las alarmas prensentes del dispositivo
  document.getElementById("alr1"+obj.id).innerHTML = obj.alr1;
  document.getElementById("alr2"+obj.id).innerHTML = obj.alr2;
  document.getElementById("alr3"+obj.id).innerHTML = obj.alr3;
  document.getElementById("alr4"+obj.id).innerHTML = obj.alr4;
  document.getElementById("alr5"+obj.id).innerHTML = obj.alr5;
  document.getElementById("alr6"+obj.id).innerHTML = obj.alr6;
  document.getElementById("alr7"+obj.id).innerHTML = obj.alr7;
  document.getElementById("alr8"+obj.id).innerHTML = obj.alr8;

  //aqui falta una funcion que muestre la alarma presente (quite el hidden)
  document.getElementById('a1'+obj.id).style.display = obj.va1?'block': 'none';
  document.getElementById('a2'+obj.id).style.display = obj.va2?'block': 'none';
  document.getElementById('a3'+obj.id).style.display = obj.va3?'block': 'none';
  document.getElementById('a4'+obj.id).style.display = obj.va4?'block': 'none';
  document.getElementById('a5'+obj.id).style.display = obj.va5?'block': 'none';
  document.getElementById('a6'+obj.id).style.display = obj.va6?'block': 'none';
  document.getElementById('a7'+obj.id).style.display = obj.va7?'block': 'none';
  document.getElementById('a8'+obj.id).style.display = obj.va8?'block': 'none';
 
 }, false);
}  

//la siguiente funcion se ejecuta apesar de la informacion exitente la cual aumenta el contador
//y en caso de llegar informacion resetea el contador
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
