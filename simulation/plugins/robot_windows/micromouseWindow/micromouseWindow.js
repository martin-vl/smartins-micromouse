window.onload = function() {
  window.robotWindow = webots.window("micromouseWindow");
  window.robotWindow.receive = function(value, robot) {
     values = value.split(" ");
     document.getElementById("sensL").innerHTML   = values[0];
     document.getElementById("sensLF").innerHTML  = values[1];
     document.getElementById("sensF").innerHTML   = values[2];
     document.getElementById("sensRF").innerHTML  = values[3];
     document.getElementById("sensR").innerHTML   = values[4];
     document.getElementById("motL").innerHTML    = values[5];
     document.getElementById("motR").innerHTML    = values[6];
    
  }
}