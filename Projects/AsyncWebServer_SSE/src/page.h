const char index_html[] = R"=====(
    <!DOCTYPE html>
    <html lang="en">
        <head>
            <meta charset="UTF-8">
            <meta name="viewport" content="width=device-width, initial-scale=1.0">
            <title>Document</title>
            <style>
                @import url('https://fonts.googleapis.com/css?family=Poppins:200,300,400,500,600,700,800,900&display=swap');
                *{
                    margin: 0;
                    padding: 0;
                    box-sizing: border-box;
                    font-family: 'Poppins', sans-serif;
                }
                body{
                    display: flex;
                    justify-content: center;
                    align-items: center;
                    min-height: 100vh;
                    background: #161616;
                }
                .container{
                    position: relative;
                    display: flex;
                    gap: 30px;            
                }
                .container .box{
                    position: relative;
                    padding: 40px;
                    width: 240px;
                    background: #222;
                    display: flex;
                    justify-content: center;
                    align-items: center;
                    flex-direction: column;
                    border-radius: 10%;
                }
                .container .box .circle{
                    position: relative;
                    width: 150px;
                    height: 150px;
                    background: conic-gradient(from 0deg, var(--clr) 0%, var(--clr) 0% var(--i), #333 var(--i), #333 100%);
                    border-radius: 50%;
                    display: flex;
                    justify-content: center;
                    align-items: center;
                }
                .container .box .circle::before{
                    content: '';
                    position: absolute;
                    inset: 10px;
                    background: #25252b;
                    border-radius: 50%;
                }
                .container .box h2{
                    position: relative;
                    text-align: center;
                    font-size: 2.5em;
                    color: #fff;
                    font-weight: 600;
                }
                .container .box h2 small{
                    font-size: 0.5em;
                    font-weight: 300;
                }
                .container .box h3{
                    color: #fff;
                    text-transform: uppercase;
                    margin-top: 20px;
                    font-weight: 500;
                    letter-spacing: 0.1em;
                }
            </style>
        </head>
        <body>
        
            <div class="container">
            
                <div class="box" id="range1" style="--i:0%;--clr:#fd0a54">
                    <div class="circle">
                        <h2>0<small>%</small></h2>
                    </div>
                    <h3>temperature</h3>
                </div>
                
                <div class="box" id="range2" style="--i:0%;--clr:#ffbc11">
                    <div class="circle">
                        <h2>0<small>%</small></h2>
                    </div>
                    <h3>humidity</h3>
                </div>
                
                <div class="box" id="range3" style="--i:0%;--clr:#0de5a8">
                    <div class="circle">
                        <h2>0<small>%</small></h2>
                    </div>
                    <h3>pressure</h3>
                </div>
                
            </div>
            
            <!-- <script>
                if (!!window.EventSource) {
                    const source = new EventSource('/events');
                    const range1 = document.getElementById('range1');
                    const range2 = document.getElementById('range2');
                    const range3 = document.getElementById('range3');
                    
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
                    
                    source.addEventListener('temperature', function(e) {
                        console.log("temperature", e.data);
                     
                        range1.childNodes[1].childNodes[1].innerHTML = `${e.data}<small>%</small>`; 
                        range1.style.cssText = `--i: ${e.data}%; --clr: #fd0100;`
                        
                    }, false);
                    
                    source.addEventListener('humidity', function(e) {
                        console.log("humidity", e.data);
                        
                        range2.childNodes[1].childNodes[1].innerHTML = `${e.data}<small>%</small>`;
                        range2.style.cssText = `--i: ${e.data}%; --clr:#ffbc11;`
                        
                    }, false);
                    
                    source.addEventListener('pressure', function(e) {
                        console.log("pressure", e.data);
                        
                        range3.childNodes[1].childNodes[1].innerHTML = `${e.data}<small>%</small>`;
                        range3.style.cssText = `--i: ${e.data}%; --clr:#0de5a8;`
                        
                    }, false);
                }
                    
            </script> -->
        </body>
         
    </html>
)=====";