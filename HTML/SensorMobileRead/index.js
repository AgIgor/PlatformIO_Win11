
rotation.oninput = (e)=> box.style.transform = `rotate(${rotation.value}deg`; 


if ("AmbientLightSensor" in window) {
  const sensor = new AmbientLightSensor();
  sensor.addEventListener("reading", (event) => {
    light.innerText = "Current light level:" + sensor.illuminance;
  });
  sensor.addEventListener("error", (event) => {
    light.innerText =  event.error.name + event.error.message;
  });
  sensor.start();
}


const acl = new Accelerometer({ frequency: 2 });
acl.addEventListener("reading", () => {
  s1.innerText = `X-axis ${acl.x}`;
  s2.innerText = `Y-axis ${acl.y}`;
  s3.innerText = `Z-axis ${acl.z}`;
});

acl.start();
