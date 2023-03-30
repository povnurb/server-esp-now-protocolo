/** capturar el url del navegar */
const pathname = window.location.pathname;
/** WebSocket */
const connection = new WebSocket('ws://' + location.hostname + '/ws', ['arduino']);
//var connection = new WebSocket('ws://192.168.1.71/ws', ['arduino']); //cambiar
/** conexión abierta */
connection.onopen = function() {
    console.log('Conexión al WebSocket abierta');
};
/** conexion error */
connection.onerror = function(error){
    console.log('Error en el WebSocket', error);
};
/** Manejo de mensajes entrantes por ws */
connection.onmessage = function(e){
    /**procesar mensajes */
    processData(e.data);
};
/** conexión cerrada */
//----------------------mi variable--------------------------------------
//-----------------------------------------------------------------------
connection.onclose = function() {
    document.getElementById('cat').innerHTML = "#"; //btn-info
    document.getElementById('cpa').innerHTML = "#";
    document.getElementById('cfc').innerHTML = "#";
    document.getElementById('csm').innerHTML = "#";
    document.getElementById('cfrc').innerHTML = "#"; 
    document.getElementById('cgeo').innerHTML = "#";
    document.getElementById('cgeb').innerHTML = "#";
    document.getElementById('cfr').innerHTML = "#";
    document.getElementById('cat').classList.add("btn-info");
    document.getElementById('cpa').classList.add("btn-info");
    document.getElementById('cfc').classList.add("btn-info");
    document.getElementById('csm').classList.add("btn-info");
    document.getElementById('cfrc').classList.add("btn-info");
    document.getElementById('cgeo').classList.add("btn-info");
    document.getElementById('cgeb').classList.add("btn-info");
    document.getElementById('cfr').classList.add("btn-info");
    console.log('Conexión al WebSocket cerrada');
};
/** -----------------------Nuevas funciones por lalo-----------------------------*/
function mostrarAlarmas(lugar){
    document.getElementById(lugar).style.visibility="hidden";
     document.getElementById(lugar).innerHTML = "F. Presente: "+ json.tiempo;
}

/**----------------------------------------------------------------------------- */
function processData(data) {
    let json = JSON.parse(data);
    //console.log(json);
    //Mensajes de retorno en un SweetAlert si retorna un status válido
    if (json.type == "info") {
        //console.log(json);
        Swal.fire({
            position: 'top-end',
            icon: json.icon,
            title: json.texto,
            showConfirmButton: false,
            timer: 2500
        });
    }
    if (pathname == "/") { 
        //console.log(json); //mensajes en consola del navegador
        
        if (json.type == "data") {
            document.getElementById('wifi_status').innerHTML = json.wifi_status; // Estado del WIFI
            document.getElementById('mqtt_status').innerHTML = json.mqtt_status; // Estado del MQTT
            document.getElementById('mqtt_server').innerHTML = json.mqtt_server; // Broker MQTT
            
            // progressbar
            document.getElementById('wifi_Signal').style.width = json.wifi_percent + "%";
            document.getElementById('wifi_label').innerHTML = json.wifi_percent + "%";
            document.getElementById('spiffs_Signal').style.width = json.spiffs_used + "%";
            document.getElementById('spiffs_label').innerHTML = json.spiffs_used + "%";
            document.getElementById('ram_Signal').style.width = json.ram_available + "%";
            document.getElementById('ram_label').innerHTML = json.ram_available + "%";
            document.getElementById('temp_cpu').innerHTML = json.temp_cpu + " °C"; // Muestra Temperatura del CPU
            document.getElementById('active').innerHTML = json.active; // Tiempo Activo del Dispositivo

            // Capturar los estados de los relays en tiempo real
            let RELAY1_Status = document.getElementById('RELAY1_Status'); //indicador
            let RELAY2_Status = document.getElementById('RELAY2_Status');
            let divRELAY1 = document.getElementById('RELAY1').parentNode; //actuador
            let divRELAY2 = document.getElementById('RELAY2').parentNode;

            //let tiempo = json.tiempo;

            //console.log(json.tiempo);
            if (json.relay1_status) {
                divRELAY1.classList.remove('switch-off');
                divRELAY1.classList.add('switch-on');
                RELAY1_Status.innerText = 'Activo';
                RELAY1_Status.classList.remove('label-info');
                RELAY1_Status.classList.add('label-primary');
            } else {
                divRELAY1.classList.remove('switch-on');
                divRELAY1.classList.add('switch-off');
                RELAY1_Status.innerText = 'Apagado';
                RELAY1_Status.classList.remove('label-primary');
                RELAY1_Status.classList.add('label-info');
            }
            if (json.relay2_status) {
                divRELAY2.classList.remove('switch-off');
                divRELAY2.classList.add('switch-on');
                RELAY2_Status.innerText = 'Activo';
                RELAY2_Status.classList.remove('label-info');
                RELAY2_Status.classList.add('label-primary');
            } else {
                divRELAY2.classList.remove('switch-on');
                divRELAY2.classList.add('switch-off');
                RELAY2_Status.innerText = 'Apagado';
                RELAY2_Status.classList.remove('label-primary');
                RELAY2_Status.classList.add('label-info');
            }
            //-------------------------------------------------------------------------------------------------
            // Agregados recientemente por LALO
            //-------------------------------------------------------------------------------------------------
            document.getElementById('cat').innerHTML = json.C_A_TEMP; //cuenta la cantidad de alarmas
            document.getElementById('cpa').innerHTML = json.C_PUERTA;
            document.getElementById('cfc').innerHTML = json.C_F_COMPRE;
            document.getElementById('csm').innerHTML = json.C_SENSOR_MOV;
            document.getElementById('cfrc').innerHTML = json.C_F_RED; 
            document.getElementById('cgeo').innerHTML = json.C_G_E_OPER;
            document.getElementById('cgeb').innerHTML = json.C_G_E_BLO;
            document.getElementById('cfr').innerHTML = json.C_F_REC;
            document.getElementById('tempC').innerHTML = json.tempC + " °C";
            //document.getElementById('humedad').innerHTML = json.humedad + " %"; // se quita si no jala
            if(json.A_TEMP){ //si hay una alarma
                document.getElementById('A_TEMP').classList.remove('btn-success');
                document.getElementById('A_TEMP').classList.add('btn-danger');
                document.getElementById('cat_off').style.visibility='hidden';
                if(json.C_A_TEMP!=0){
                document.getElementById('cat_on').innerHTML = json.TON_A_TEMP;
                }
            }else{
                document.getElementById('A_TEMP').classList.remove('btn-danger');
                document.getElementById('A_TEMP').classList.add('btn-success');
                if(json.C_A_TEMP!=0){
                document.getElementById('cat_on').innerHTML = json.TON_A_TEMP;
                document.getElementById('cat_off').style.visibility='visible';
                document.getElementById('cat_off').innerHTML = json.TOFF_A_TEMP;
            }
        }
            
            if(json.PUERTA){ //si hay una alarma
                document.getElementById('PUERTA').classList.remove('btn-success');
                document.getElementById('PUERTA').classList.add('btn-danger');
                document.getElementById('cpa_off').style.visibility='hidden';
                if(json.C_PUERTA!=0){
                document.getElementById('cpa_on').innerHTML = json.TON_PUERTA;
                }
            }else{
                document.getElementById('PUERTA').classList.remove('btn-danger');
                document.getElementById('PUERTA').classList.add('btn-success');
                if(json.C_PUERTA!=0){
                document.getElementById('cpa_on').innerHTML = json.TON_PUERTA;
                document.getElementById('cpa_off').style.visibility='visible';
                document.getElementById('cpa_off').innerHTML = json.TOFF_PUERTA;
                }
            }
            if(json.F_COMPRE){ //si hay una alarma
                document.getElementById('F_COMPRE').classList.remove('btn-success');
                document.getElementById('F_COMPRE').classList.add('btn-danger');
                document.getElementById('cfc_off').style.visibility='hidden';
                if(json.C_F_COMPRE!=0){
                document.getElementById('cfc_on').innerHTML = json.TON_F_COMPRE;
                }        
            }else{
                document.getElementById('F_COMPRE').classList.remove('btn-danger');
                document.getElementById('F_COMPRE').classList.add('btn-success');
                if(json.C_F_COMPRE!=0){
                document.getElementById('cfc_on').innerHTML = json.TON_F_COMPRE;
                document.getElementById('cfc_off').style.visibility='visible';
                document.getElementById('cfc_off').innerHTML = json.TOFF_F_COMPRE;
                }
            }
            
            if(json.SENSOR_MOV){ //si hay una alarma
                document.getElementById('SENSOR_MOV').classList.remove('btn-success');
                document.getElementById('SENSOR_MOV').classList.add('btn-danger');
                document.getElementById('csm_off').style.visibility='hidden';
                if(json.C_SENSOR_MOV!=0){
                document.getElementById('csm_on').innerHTML = json.TON_SENSOR_MOV;
                }
            }else{
                document.getElementById('SENSOR_MOV').classList.remove('btn-danger');
                document.getElementById('SENSOR_MOV').classList.add('btn-success');
                if(json.C_SENSOR_MOV!=0){
                document.getElementById('csm_on').innerHTML = json.TON_SENSOR_MOV;
                document.getElementById('csm_off').style.visibility='visible';
                document.getElementById('csm_off').innerHTML = json.TOFF_SENSOR_MOV;
                } 
            }
            if(json.F_RED){ //si hay una alarma
                document.getElementById('F_RED').classList.remove('btn-success');
                document.getElementById('F_RED').classList.add('btn-danger');
                document.getElementById('cfrc_off').style.visibility='hidden';
                if(json.C_F_RED!=0){
                document.getElementById('cfrc_on').innerHTML = json.TON_F_RED;
                }
            }else{
                document.getElementById('F_RED').classList.remove('btn-danger');
                document.getElementById('F_RED').classList.add('btn-success');
                if(json.C_F_RED!=0){
                document.getElementById('cfrc_on').innerHTML = json.TON_F_RED;
                document.getElementById('cfrc_off').style.visibility='visible';
                document.getElementById('cfrc_off').innerHTML = json.TOFF_F_RED;
                }
            }
            if(json.G_E_OPER){ //si hay una alarma
                document.getElementById('G_E_OPER').classList.remove('btn-success');
                document.getElementById('G_E_OPER').classList.add('btn-danger');
                document.getElementById('cgeo_off').style.visibility='hidden';
                if(json.C_G_E_OPER!=0){
                document.getElementById('cgeo_on').innerHTML = json.TON_G_E_OPER;
                }
            }else{
                document.getElementById('G_E_OPER').classList.remove('btn-danger');
                document.getElementById('G_E_OPER').classList.add('btn-success');
                if(json.C_G_E_OPER!=0){
                document.getElementById('cgeo_on').innerHTML = json.TON_G_E_OPER;
                document.getElementById('cgeo_off').style.visibility='visible';
                document.getElementById('cgeo_off').innerHTML = json.TOFF_G_E_OPER; 
                }
            }
            if(json.G_E_BLO){ //si hay una alarma
                document.getElementById('G_E_BLO').classList.remove('btn-success');
                document.getElementById('G_E_BLO').classList.add('btn-danger');
                document.getElementById('cgeb_off').style.visibility='hidden';
                if(json.C_G_E_BLO!=0){
                document.getElementById('cgeb_on').innerHTML = json.TON_G_E_BLO;
                }
            }else{
                document.getElementById('G_E_BLO').classList.remove('btn-danger');
                document.getElementById('G_E_BLO').classList.add('btn-success');
                if(json.C_G_E_BLO!=0){
                document.getElementById('cgeb_on').innerHTML = json.TON_G_E_BLO;
                document.getElementById('cgeb_off').style.visibility='visible';
                document.getElementById('cgeb_off').innerHTML = json.TOFF_G_E_BLO;
                }
            }
            if(json.F_REC){ //si hay una alarma
                document.getElementById('F_REC').classList.remove('btn-success');
                document.getElementById('F_REC').classList.add('btn-danger');
                document.getElementById('cfr_off').style.visibility='hidden';
                if(json.C_F_REC!=0){
                document.getElementById('cfr_on').innerHTML = json.TON_F_REC;
                }
            }else{
                document.getElementById('F_REC').classList.remove('btn-danger');
                document.getElementById('F_REC').classList.add('btn-success');
                if(json.C_F_REC!=0){
                document.getElementById('cfr_on').innerHTML = json.TON_F_REC;
                document.getElementById('cfr_off').style.visibility='visible';
                document.getElementById('cfr_off').innerHTML = json.TOFF_F_REC;
                //window.location.pathname;
                }
            }
        }
    }
    // time
    if (json.type == "time"){
        document.getElementById("sys_time").innerHTML = json.msg;
    }
}
/*----------------------------funcion onload del body mqtt.html------------------------- */
/** habilita o deshabilita los input a la hora de la carga del html  */
function mqtt() {
    let x = document.getElementById("mqtten");
    if (x.value=="1") {
        formDisableFalse("mqtt");
    } else {
        formDisableTrue("mqtt");
    }
}
/** Habilitar input WIFI/AP segun estado */
function wifi() {
    let ip = document.getElementById("wifi_staticIPen");
    let ap = document.getElementById("ap_AP_en");
    if (ip.value == "1") {
        formDisableFalse("ip");
    } else {
        formDisableTrue("ip");
    }
    if (ap.value == "1") {
        formDisableFalse("ap");
    } else {
        formDisableTrue("ap");
    }
}
/*-------------------------------------Habilitar MQTT--------------------------------- */
function mqttenable() {
    if (document.getElementById("mqtt_enable").checked){
        document.getElementById("mqtten").value = 1;
        formDisableFalse("mqtt");
    } else {
        document.getElementById("mqtten").value = 0;
        formDisableTrue("mqtt");
    }
}
/** ----------------- Habilitar IP Estática----------------------- */
function staticIPen() {
    if (document.getElementById("wifi_staticIP").checked) {
        document.getElementById('wifi_staticIPen').value = 1;
        formDisableFalse("ip");
    } else {
        document.getElementById('wifi_staticIPen').value = 0;
        formDisableTrue("ip");
    }
}
/** ----------------- Habilitar AP----------------------- */
function apenable() {
    if (document.getElementById("ap_accessPoint").checked) {
        document.getElementById('ap_AP_en').value = 1;
        formDisableFalse("ap");
    } else {
        document.getElementById('ap_AP_en').value = 0;
        formDisableTrue("ap");
    }
}
/** ----------------- Habilitar Visibilidad (0) No (1)----------------------- */
function visibilityen() {
    if (document.getElementById("ap_hiddenap").checked) {
        document.getElementById('ap_visibility').value = 0;
    } else {
        document.getElementById('ap_visibility').value = 1;
    }
}
/* Quitar el disabled de los inputs */
function formDisableFalse(clase) {
    let formElement = document.getElementsByClassName(clase);
    for (let i = 0; i < formElement.length; i++){
        formElement[i].disabled = false;
    }
}
/* Habilitar el disabled de los inputs */
function formDisableTrue(clase) {
    let formElement = document.getElementsByClassName(clase);
    for (let i = 0; i < formElement.length; i++){
        formElement[i].disabled = true;
    }
}
/* Limpiar Formulario */
function clearAdmin() {
    document.getElementById("formulario").reset();
}
/** Funcion para enviar el estado de los relay por ws (websocket) */
let relay = (e) => {
    pass = prompt("Requiere contraseña");
    
    let miCheckbox = document.getElementById(e.id);
    let msg = document.getElementById(e.id + "_Status");
    if (miCheckbox.checked) {
        while(pass != "lalo"){
            alert("contraseña incorrecta");
            pass = prompt("Requiere contraseña");
        }
        msg.innerText = "Activo";
        msg.classList.remove("label-info");
        msg.classList.add("label-primary");
        OnOffRelay(e.id, true);
        
    } else {
        msg.innerText = "Apagado";
        msg.classList.remove("label-primary");
        msg.classList.add("label-info");
        OnOffRelay(e.id, false);
    }

}
/** Funcion que envia el Json del estado de los relays */
let OnOffRelay = (relay, command) => {
    connection.send(`{"protocol": "WS", "output": "${relay}", "value": ${command} }`);
}
/**----------------Funcion para restaurar el dispositivo------------------- */
function restaurar() {
    Swal.fire({
        title: 'Restaurar',
        text: ' Toda configuración que haya guardado se perdera si restablece a los valores de fábrica, ¿Desea continuar?',
        icon: 'warning',
        showCancelButton: true,
        confirmButtonColor: '#3085d6',
        cancelButtonColor: '#d33',
        confirmButtonText: 'Si, restablecer',
        cancelButtonText: 'Cancelar',
        reverseButtons: true
    }).then((result) => {
        if (result.isConfirmed) {
            RestoreRestart("restore");
        } else if (
            result.dismiss === Swal.DismissReason.cancel
        ) {
            history.back();
        }
    })
}
/** Función para Reiniciar el Dispositivo */
function reiniciar() {
    Swal.fire({
        title: 'Reiniciar!',
        text: ' ¿Está seguro de reiniciar el Dispositivo?',
        icon: 'warning',
        showCancelButton: true,
        confirmButtonColor: '#3085d6',
        cancelButtonColor: '#d33',
        confirmButtonText: 'Si, reiniciar',
        cancelButtonText: 'Cancelar',
        reverseButtons: true
    }).then((result) => {
        if (result.isConfirmed) {
            RestoreRestart("restart");
        } else if (
            result.dismiss === Swal.DismissReason.cancel
        ) {
            history.back();
        }
    })
}
/** Conteo de reinicio 10s */
let t = 10;
/** Ocultar Vizualizador de Progress Bar */
function visu() {
    let x = document.getElementById("visu");
    x.style.display = "none";
}
/* reinicio & restaurar */
function RestoreRestart(type) {
    console.log(type);
    t--;
    document.getElementById('visu').style.display = 'block';
    document.getElementById("time").innerHTML = " " + t;
    document.getElementById('progress').style.width = 100-(t * 10   ) + '%'; //la barra
    //document.getElementById("pregressvalue").innerHTML = " " + t * 10 + '%'; //valor dentro de la barra
    if (type == "restart") {
        if (t == 0) {
            document.getElementById('visu').style.display = 'none';
            document.getElementById('btn').disabled = false;
            window.location = "/";
            t = 10;
        } else if (t == 9) {
            connection.send("restart");
            document.getElementById('btn').disabled = true;
            window.setTimeout("RestoreRestart('restart')", 1000);
        } else {
            document.getElementById('btn').disabled = true;
            window.setTimeout("RestoreRestart('restart')", 1000);
        }
    } else {
        if (t == 0) {
            document.getElementById('visu').style.display = 'none';
            document.getElementById('btn').disabled = false;
            window.location = "/";
            t = 10;
        } else if (t == 9) { 
            connection.send("restore");
            document.getElementById('btn').disabled = true;
            window.setTimeout("RestoreRestart('restore')", 1000);
        } else {
            document.getElementById('btn').disabled = true;
            window.setTimeout("RestoreRestart('restore')", 1000);
        }
    }
}

// Sección 8 video 99
//validacion de formulario
const formulario = document.getElementById('form'); 
const inputs = document.querySelectorAll('#form input'); //todos los input del formulario se capturan en esta variable
//objeto de las expresiones regulares
const expresiones = {
    TextNumber: /^[a-zA-Z0-9]{4,30}$/, // Letras a-z A-Z minúsculas - mayúsculas, números caracteres de 4 mínimo a 30 dígitos máximo 
    TextUnderscore: /^[a-zA-Z\_]{4,30}$/, // Letras minúsculas - mayusculas, guión bajo de 4 mínimo a 30 digitos máximo.
    TextNumberPassw: /^[a-zA-Z0-9\_\-\*]{4,30}$/, // Letras minúsculas - mayúsculas, números, guiones y asterisco caracteres de 4 mínimo a 30 dígitos máximo. 
    Dominio: /^([a-zA-Z]{2,6}|[a-zA-Z0-9-]{2,30}\.[a-zA-Z]{2,3})$/, // Ejemplo: ( tudominio.com ) sin los http:// o https://
    ServerPort: /^(6553[0-5]|655[0-2][0-9]|65[0-4][0-9]{2}|6[0-4][0-9]{3}|[0-5]?([0-9]){0,3}[0-9])$/, // Puertos desde 0 a 65535.
    TextNumberWIFI: /^[a-zA-Z0-9 \_\-\.\'\#]{4,30}$/, // Letras minúsculas - mayúsculas, números, guiones, comilla simple, numeral, espacio y punto caracteres de 4 mínimo a 30 dígitos máximo.
    //TextNumberWIFI: /^.{1,30}$/,
    IPv4: /^((25[0-5]|2[0-4]\d|[01]?\d\d?)\.){3}(25[0-5]|2[0-4]\d|[01]?\d\d?)$/, // IPv4 255.255.255.255
    TextNumberAP: /^[a-zA-Z0-9 \_\-\.\'\#]{4,31}$/, // Letras minúsculas - mayúsculas, números, guiones, comilla simple, numeral y punto caracteres de 4 mínimo a 31 dígitos máximo.
    TextNumberPasswAP: /^[a-zA-Z0-9\_\-\*]{4,63}$/, // Letras minúsculas - mayúsculas, números, guiones y asterisco caracteres de 4 mínimo a 63 dígitos máximo. 
    www_username: /^[a-z]{4,15}$/, // Letras minúsculas caracteres de 4-15 digitos maximo.
    www_password: /^[a-zA-Z0-9]{4,15}$/, // Letras minúsculas - mayusculas, numeros, caracteres de 4-15 digitos maximo.
    id: /^[a-z0-9]{4,30}$/, // Letras minúsculas y numeros caracteres de 4-30 digitos maximo.
    }
    // Objeto de los campos a validar por formulario
const campos = {
    mqtt_id: true,
    mqtt_user: true,
    mqtt_passw: true,
    mqtt_server: true,
    mqtt_port: true,
    mqtt_time: true,
    // Wifi 
    wifi_ssid: true,
    wifi_passw: true,
    wifi_ip_static: true,
    wifi_subnet: true,
    wifi_gateway: true,
    wifi_primaryDNS: true,
    wifi_secondaryDNS: true,
    ap_nameap: true,
    ap_passwordap: true,
    ap_canalap: true,
    ap_connetap: true,
    // admin
    www_username: true,
    www_password: true,
    new_www_username: true,
    new_www_password: true,
    // device
    id: true
}
// dejar de teclear y la perdida del foco del input
inputs.forEach((input) => {
    input.addEventListener('keyup', validarFormulario);
    input.addEventListener('blur', validarFormulario);
});
//funcion para validar el Formulario.
function validarFormulario(e) {
    //console.log(e.target.dataset.expresion);
    switch (e.target.name) {
        case "mqtt_id":
            validarCampo(expresiones[e.target.dataset.expresion], e.target, e.target.name);
            break;
        case "mqtt_user":
            validarCampo(expresiones[e.target.dataset.expresion], e.target, e.target.name);
            break;
            case "mqtt_passw":
                validarCampo(expresiones[e.target.dataset.expresion], e.target, e.target.name);
                break;
            case "mqtt_server":
                validarCampo(expresiones[e.target.dataset.expresion], e.target, e.target.name);
                break;
            case "mqtt_port":
                validarCampo(expresiones[e.target.dataset.expresion], e.target, e.target.name);
                break;
            case "mqtt_time":
                validarRango(e.target, e.target.name, 1, 60);
                break;
                // Sección WIFI
            case "wifi_ssid":
                validarCampo(expresiones[e.target.dataset.expresion], e.target, e.target.name);
                break;
            case "wifi_passw":
                validarCampo(expresiones[e.target.dataset.expresion], e.target, e.target.name);
                break;
            case "wifi_ip_static":
                validarCampo(expresiones[e.target.dataset.expresion], e.target, e.target.name);
                break;
            case "wifi_subnet":
                validarCampo(expresiones[e.target.dataset.expresion], e.target, e.target.name);
                break;
            case "wifi_gateway":
                validarCampo(expresiones[e.target.dataset.expresion], e.target, e.target.name);
                break;
            case "wifi_primaryDNS":
                validarCampo(expresiones[e.target.dataset.expresion], e.target, e.target.name);
                break;
            case "wifi_secondaryDNS":
                validarCampo(expresiones[e.target.dataset.expresion], e.target, e.target.name);
                break;
                //AP
            case "ap_nameap":
                validarCampo(expresiones[e.target.dataset.expresion], e.target, e.target.name);
                break;
            case "ap_passwordap":
                validarCampo(expresiones[e.target.dataset.expresion], e.target, e.target.name);
                break;
            case "ap_canalap":
                validarRango(e.target, e.target.name, 1, 13);
                break;
            case "ap_connetap":
                validarRango(e.target, e.target.name, 0, 8);
                break;
                /* ADMIN FORM */
            case "www_username":
                validarCampo(expresiones[e.target.dataset.expresion], e.target, e.target.name);
                break;
            case "www_password":
                validarCampo(expresiones[e.target.dataset.expresion], e.target, e.target.name);
                break;
            case "new_www_username":
                validarCampo(expresiones[e.target.dataset.expresion], e.target, e.target.name);
                break;
            case "new_www_password":
                validarCampo(expresiones[e.target.dataset.expresion], e.target, e.target.name);
                validarPassword();
                break;
            case "c_new_www_password":
                validarPassword();
                break;
            case "id":
                validarCampo(expresiones[e.target.dataset.expresion], e.target, e.target.name);
                break;
    }
}
// Validar Campo
const validarCampo = (expresion, input, campo) => {
    //console.log(campo);
    if (expresion.test(input.value) && input.value != '') {
        document.querySelector(`#form_${campo}`).classList.remove('has-error');
        document.querySelector(`#form_${campo}`).classList.add('has-success');
        document.querySelector(`#form_${campo} .formulario_input-error`).classList.remove('formulario_input-error-activo');
        campos[campo] = true;
    } else {
        document.querySelector(`#form_${campo}`).classList.remove('has-success');
        document.querySelector(`#form_${campo}`).classList.add('has-error');
        document.querySelector(`#form_${campo} .formulario_input-error`).classList.add('formulario_input-error-activo');
        campos[campo] = false;
    }
}
// Validar un Rango de numeros min <-> max
const validarRango = (input, campo, min, max) => {
    if (input.value >= min && input.value <= max) {
        document.querySelector(`#form_${campo}`).classList.add('has-success');
        document.querySelector(`#form_${campo}`).classList.remove('has-error');
        document.querySelector(`#form_${campo} .formulario_input-error`).classList.remove('formulario_input-error-activo');
        campos[campo] = true;
    } else {
        document.querySelector(`#form_${campo}`).classList.add('has-error');
        document.querySelector(`#form_${campo}`).classList.remove('has-success');
        document.querySelector(`#form_${campo} .formulario_input-error`).classList.add('formulario_input-error-activo');
        campos[campo] = false;
    }
}
// Validar new password y confirm new password iguales 
const validarPassword = () => {
    const inputNewPassword = document.getElementById('new_www_password');
    const inputNewPasswordConfirm = document.getElementById('c_new_www_password');
    if (inputNewPassword.value == inputNewPasswordConfirm.value) {
        document.querySelector(`#form_c_new_www_password`).classList.add('has-success');
        document.querySelector(`#form_c_new_www_password`).classList.remove('has-error');
        document.querySelector(`#form_c_new_www_password .formulario_input-error`).classList.remove('formulario_input-error-activo');
        campos['new_www_password'] = true;
    } else {
        document.querySelector(`#form_c_new_www_password`).classList.add('has-error');
        document.querySelector(`#form_c_new_www_password`).classList.remove('has-success');
        document.querySelector(`#form_c_new_www_password .formulario_input-error`).classList.add('formulario_input-error-activo');
        campos['new_www_password'] = false;
    }
}
// Interceptar el Evento Submit Solo en los Formularios (wifi-mqtt-device-admin)
if (pathname == "/esp-wifi" || pathname == "/esp-mqtt" || pathname == "/esp-device" || pathname == "/esp-admin" || pathname == "/esp-time") {
    document.addEventListener("DOMContentLoaded", function(event) {
        document.getElementById('form').addEventListener('submit', manejadorValidacion)
    });
}

function manejadorValidacion(e) {
    e.preventDefault();
    let page = document.getElementById('page').innerHTML;
    if (page == "Configuración del Broker MQTT") {
        //console.log(page);
        if (campos.mqtt_id && campos.mqtt_user && campos.mqtt_passw && campos.mqtt_server && campos.mqtt_port && campos.mqtt_time) {
            document.getElementById('formulario_mensaje').classList.remove('formulario_mensaje-activo');
            SweetAlert('¡Guardar!', page, 'question', this);
        } else {
            document.getElementById('formulario_mensaje').classList.add('formulario_mensaje-activo');
            mensajeFormError();
        }
    } else if (page == "Configuración de la Red Inalámbrica") {
        if (campos.wifi_ssid && campos.wifi_passw && campos.wifi_ip_static && campos.wifi_subnet && campos.wifi_gateway && campos.wifi_primaryDNS && campos.wifi_secondaryDNS && campos.ap_nameap && campos.ap_passwordap && campos.ap_canalap && campos.ap_connetap) {
            document.getElementById('formulario_mensaje').classList.remove('formulario_mensaje-activo');
            SweetAlert('¡Guardar!', page, 'question', this);
        } else {
            document.getElementById('formulario_mensaje').classList.add('formulario_mensaje-activo');
            mensajeFormError();
        }
    } else if (page == "Usuario y Contraseña") { //validado en la pagina admin.html
        if (campos.www_username && campos.www_password && campos.new_www_username && campos.new_www_password) {
            document.getElementById('formulario_mensaje').classList.remove('formulario_mensaje-activo');
            SweetAlert('¡Guardar!', page, 'question', this);
        } else {
            document.getElementById('formulario_mensaje').classList.add('formulario_mensaje-activo');
            mensajeFormError();
        }
    } else if (page == "Información del dispositivo") { //validado en la pagina device.html
        if (campos.id) {
            document.getElementById('formulario_mensaje').classList.remove('formulario_mensaje-activo');
            SweetAlert('¡Guardar!', page, 'question', this);
        } else {
            document.getElementById('formulario_mensaje').classList.add('formulario_mensaje-activo');
            mensajeFormError();
        }
    } else if (page == "Configuración Fecha y Hora") {
        SweetAlert('¿Guardar?', page, 'question', this);
    }
}
// Mansaje para confirmar el Guardado con el Evento Submit
function SweetAlert(title, text, icon, e) {
    Swal.fire({
        title: title,
        text: text,
        icon: icon,
        showCancelButton: true,
        confirmButtonColor: '#3085d6',
        cancelButtonColor: '#d33',
        confirmButtonText: 'Si, guardar',
        cancelButtonText: 'Cancelar',
        reverseButtons: true
    }).then((result) => {
        if (result.isConfirmed) {
            e.submit();
        } else if (
            result.dismiss === Swal.DismissReason.cancel
        ) {
            history.back();
        }
    })
}
// Mansaje de Error al Validar Input
let mensajeFormError = () => {
    Swal.fire({
        position: 'top-end',
        icon: 'error',
        title: '¡No se ha llenado correctamente el formulario!',
        showConfirmButton: false,
        timer: 2000
    });
};
// Escaneo de redes
let escanear = () => {
    const url = 'http://' + location.hostname + '/scan';
    fetch(url)
        .then(respuesta => respuesta.json())//la data ya se convirtio en Json
        .then(data => {
            if (pathname == "/esp-wifi") { //indica si estoy en la pagina wifi
                // capturamos el id de redes
                let redes = document.getElementById('redes');
                // capturamos el id de serial
                let serial = document.getElementById('serial');
                //limpiamos redes
                redes.innerHTML = "";
                //limpiamos serial
                serial.innerHTML = "";
                // mostrar json por consola
                //console.log(data); //para debug
                // Mensaje de retorno Respuesta del Scan de redes WIFI
                if (data.code == 1) {
                    // Count > 0
                    //capturamos el id del Body para dibujar la tabla
                    let mitabla = document.getElementById('mi_tabla');
                    //limpiamos tabla
                    mitabla.innerHTML = "";
                    // Agregamos cantidad de redes
                    redes.innerHTML = data.meta.count;
                    // Agregamos el serial del dispositivo
                    serial.innerHTML = "<i class='icon-barcode'></i> " + data.meta.serial;
                    // Recorremos toda la lonjitud del data key DATA
                    for (let valor of data.data) {
                        if (parseInt(valor.rssi) >= -67) {
                            mitabla.innerHTML += `  <tr class="success">
                                                            <td align="center">${valor.n}</td>
                                                            <td>${valor.ssid}</td>
                                                            <td align="center">${valor.rssi}</td>
                                                            <td>${valor.bssid}/<br>${valor.secure}</td>
                                                            <td align="center">${valor.channel}</td>                  
                                                            <td><button class="btn btn-primary" onclick="addWiFiInput();"><i class="icon-magnet"></i> Add</button></td>
                                                        </tr>
                                                    `;
                        } else if (parseInt(valor.rssi) <= -67 && parseInt(valor.rssi) > -80) {
                            mitabla.innerHTML += `<tr class="info">
                                                            <td align="center">${valor.n}</td>
                                                            <td>${valor.ssid}</td>
                                                            <td align="center">${valor.rssi}</td>
                                                            <td>${valor.bssid}/<br>${valor.secure}</td>
                                                            <td align="center">${valor.channel}</td>
                                                            <td><button class="btn btn-primary" onclick="addWiFiInput();"><i class="icon-magnet"></i> Add</button></td>
                                                        </tr>
                                                    `;
                        } else if (parseInt(valor.rssi) <= -80 && parseInt(valor.rssi) > -90) {
                            mitabla.innerHTML += `<tr class="warning">
                                                            <td align="center">${valor.n}</td>
                                                            <td>${valor.ssid}</td>
                                                            <td align="center">${valor.rssi}</td>
                                                            <td>${valor.bssid}/<br>${valor.secure}</td>
                                                            <td align="center">${valor.channel}</td>
                                                            <td><button class="btn btn-primary" onclick="addWiFiInput();"><i class="icon-magnet"></i> Add</button></td>
                                                        </tr>
                                                        `;
                        } else {
                            mitabla.innerHTML += `<tr class="danger">
                                                            <td align="center">${valor.n}</td>
                                                            <td>${valor.ssid}</td>
                                                            <td align="center">${valor.rssi}</td>
                                                            <td>${valor.bssid}/<br>${valor.secure}</td>
                                                            <td align="center">${valor.channel}</td>
                                                            <td><button class="btn btn-primary" onclick="addWiFiInput();"><i class="icon-magnet"></i> Add</button></td>
                                                        </tr>
                                                    `;
                        }
                    };
                } else {
                    // Count = 0
                    // Agregamos cantidad de redes
                    redes.innerHTML = data.meta.count;
                    // Agregamos el serial del dispositivo
                    serial.innerHTML = "<i class='icon-barcode'></i> " + data.meta.serial;
                }
            };
        });
}
// Agregar el Nombre de la Red al Input segun Click en el Botón en la fila correspondiente
let addWiFiInput = () => {
    const table = document.getElementById("tableId");
    const rows = table.getElementsByTagName("tr");
    for (let i = 0; i < rows.length; i++) {
        let currentRow = table.rows[i];
        let createClickHandler =
            function(row) {
                return function() {
                    let cell = row.getElementsByTagName("td")[1];
                    let ssid = cell.innerHTML;
                    //alert(ssid);
                    let network = document.getElementById("wifi_ssid");
                    network.value = ssid;
                    $('#myModal').modal('hide');
                };
            };
        currentRow.onclick = createClickHandler(currentRow);
    }
}
// tiempo
const auto_man = (e)=>{
    if (e.value == 0) {
        document.getElementById(e.dataset.div_off).classList.remove('time-activo');
        document.getElementById(e.dataset.div_on).classList.remove('time');
        document.getElementById(e.dataset.div_off).classList.add('time');
        document.getElementById(e.dataset.div_on).classList.add('time-activo');
    }else {
        document.getElementById(e.dataset.div_off).classList.remove('time-activo');
        document.getElementById(e.dataset.div_on).classList.remove('time');
        document.getElementById(e.dataset.div_off).classList.add('time');
        document.getElementById(e.dataset.div_on).classList.add('time-activo');
    }
}
const loadTime =()=>{
    const time_h = document.getElementById('time_h');
    const time_m = document.getElementById('time_m');
    //const time_s = document.getElementById('time_s');
    const time_z_horaria = document.getElementById("time_z_horaria");

    time_h.innerHTML = ''
    time_m.innerHTML = ''
    //time_s.innerHTML = ''

    for (let index = 0; index < 24; index++){
        time_h.innerHTML += `<option value="${index}">${ index > 9? index: '0' +index} </option>` //backstep `` asi se llaman se sacan alt gr } y es para que se vean dos cifras de numero
    }
    for (let index = 0; index < 60; index++){
        time_m.innerHTML += `<option value="${index}">${ index > 9? index: '0' +index} </option>` //backstep `` asi se llaman se sacan alt gr } y es para que se vean dos cifras de numero
        //time_s.innerHTML += `<option value="${index}">${ index > 9? index: '0' +index} </option>` //backstep `` asi se llaman se sacan alt gr } y es para que se vean dos cifras de numero
    }
    time_h.value = document.getElementById('time_hr').value
    time_m.value = document.getElementById('time_mn').value
    //time_s.value = document.getElementById('time_sc').value
    time_z_horaria.value = document.getElementById("time_zhoraria").value

    if (document.getElementById("time_ajuste").value == '0') {
        document.getElementById('auto').classList.remove('time-activo');
        document.getElementById('auto').classList.add('time');
        document.getElementById('manual').classList.remove('time');
        document.getElementById('manual').classList.add('time-activo');
    } else {
        document.getElementById('auto').classList.remove('time');
        document.getElementById('auto').classList.add('time-activo');
        document.getElementById('manual').classList.remove('time-activo');
        document.getElementById('manual').classList.add('time');
    }
    
}