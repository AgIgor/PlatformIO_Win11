const char root[] PROGMEM = R"=====(
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Pwm 0</title>
</head>
<body>
    <h1>Controle de PWM</h1>
    <form action='/move' method='get'>
      <input id="pi_input" type="range" min="0" max="255" step="1" />
      <p>PWM: <output id="value"></output></p>
    </form>
</body>
<script>

    const value = document.querySelector("#value");
    const input = document.querySelector("#pi_input");
    const title = document.querySelector("title");

    async function read(){
        try{
            const read = await fetch("/read")
                                  .then(response => response.text())
                                    //.then(result => console.log(result))
                                  .then(result =>{
                                        input.value = result;
                                        value.textContent = result;
                                        title.textContent = `Pwm ${value.textContent}`;
                                    })
                                  .catch(error => console.log('error', error));  
        }
        catch(error){
            console.error('Error:', error);
        }
    }
    
    read()
    
    input.addEventListener("input", (event) => {
        value.textContent = event.target.value;
        title.textContent = `Pwm ${value.textContent}`;
        sendPos();
    });
        
    const sendPos = async()=>{
        try{
            const response = await fetch(`/move?angle=${value.textContent}`);
            if (!response.ok) {
                throw new Error(`HTTP error! Status: ${response.status}`);
            }
            // const data = await response;
            // console.log(data); // Do something with the data
        }
        catch (error) {
            console.error('Error:', error);
        }
    }

    setInterval(async() => {
       await read();
    }, 2000);
  
</script>
</html>
)=====";
